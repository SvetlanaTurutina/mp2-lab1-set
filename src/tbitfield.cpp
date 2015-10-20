// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <iostream>
#include <assert.h>

TBitField::TBitField(int len) //конструктор
{
	if (len < 0)
		throw   "Incorrect entries";
	if (len == 0)
	{
		BitLen = 0;
		pMem = NULL;
		return;
	}
	MemLen = (len + sizeof(TELEM)*8-1)/(sizeof(TELEM)*8);
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		BitLen = len;
		for (int i = 0; i < MemLen; i++) pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{ 
	return n/(sizeof(TELEM)*8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM)*8)); //n << GetMemIndex(n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	else throw   "Incorrect index";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
    else throw   "Incorrect index";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else throw   "Incorrect index";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL)
			delete pMem;
		pMem = new TELEM[MemLen];
	}
	if (pMem != NULL)
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else 
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i]) 
		{ 
			res = 0; break; 
		}
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen) res = 1;
	else
	for (int i = 0; i < MemLen; i++)
	if (pMem[i] != bf.pMem[i])
	{
		res = 1; break;
	}
	return res;
  //return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и" 
{
	int i, len = BitLen;
	if (bf.BitLen > len) len = bf.BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	/*int len = BitLen;
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++) 
		temp.pMem[i] = ~pMem[i];
	return temp;*/

	TBitField temp(BitLen);
	for (int i = 0; i<BitLen; ++i)
	if (GetBit(i))
		temp.ClrBit(i);
	else
		temp.SetBit(i);
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод исправить!
{//формат данных - последовательность 0 и 1 без пробелов, начальные пробелы игнорируются, при не 0 и 1 - завершение ввода
	//int i, l = 0;
	//char ch;
	//char line[128];
	//char a[3];
	//do
	//{
	//	istr >> line;
	//	l = strlen(line);
	//	if (l != bf.BitLen)
	//		cout << " Incorrect lenght";
	//} while (l == bf.BitLen);
	//	do { istr >> ch; } while (ch != ' '); //поиск
	//do{
	//	a[i] = ch;
	//} while (ch != ' ');
	//	while (1) //
	//	//ввод элементов и включение в множество
	//{ istr >> ch;
	//if (ch == '0') bf.ClrBit(i++);
	//else if (ch == '1') bf.SetBit(i++); else break;
	//}

	int i, l = 0;
	int n = 0;			// номер бита
	char line[128];
	char a[3];
	do
	{
		istr >> line;
		l += strlen(line);
		if (l > bf.BitLen)
			cout << " Incorrect lenght";
		else
		{
			for (i = 0; i<l; i++)
			{
				if (strncmp(&line[i], "1", 1) == 0)
				{
					bf.SetBit(n);
					n++;
				}
				else if (strncmp(&line[i], "0", 1) == 0)
				{
					bf.ClrBit(n);
					n++;
				}
				else
					cout << " Incorrect bit";
			}
		}
	} while (l != bf.BitLen);

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength(); //формат данных - последовательность 0 и 1
	for (int i = 0; i < len; i++)
	if (bf.GetBit(i)) ostr << 1; else ostr << 0;
	return ostr;
}
