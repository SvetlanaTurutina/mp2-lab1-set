#include "tbitfield.h"  
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	TBitField bit(10);
	cout << bit << " constructor\n";
	int m = bit.GetLength();
	cout << m << " lenght of bit\n";
	bit.SetBit(1);
	bit.SetBit(5);
	bit.SetBit(4);
	cout << bit << " Setting bits 1,4,5 on bit(10)\n";
	bit.ClrBit(5);
	cout << bit << " Clear bit 5 on bit(10)\n";
	TBitField bit3(21);
	bit3.SetBit(2);
	bit3.SetBit(15);
	bit3.SetBit(4);
	cout<<bit3<<" Setting bits 2, 4,15 on bit3(21)\n";
	TBitField bittemp(10);
	bittemp = bit | bit3;
	cout << bittemp << " Operation bit|bit3\n";
	bittemp = bit & bit3;
	cout << bittemp << " Operation bit&bit3\n";
	bittemp = ~bit;
	cout << bittemp << " Operation ~bit\n";
	TBitField bit4(10);
	cin >> bit4;
	cout << "bit4: " <<  bit4 << "\n";
	//int a;
	//cin >> a;
	const int size = 4;
	TBitField bf1(size), bf2(size);
	bf1.SetBit(1);
	bf1.SetBit(3);
	bf2.SetBit(1);
	bf2.SetBit(2);
	//int result = bf1 == bf2;
	//cout << "result = bf1 == bf2: " << result;
	int result = bf1 != bf2;
	cout << "result = bf1 != bf2: " << result;

}