#include<iostream>
#include<stdio.h>
#include<fstream>
#include"md5.h"//一些用到的固定数据
using namespace std;

//计算长度
int longtonum(long long t)
{
	int i = 0;
	for (int j = 0; j < 8; j++)
	{
		if ((t >> (j * 8)) & 0x00000000000000ff)
			i=j;
	}
	return i;
}
//左移
int leftShift(unsigned int& dst, int num)
{
	unsigned int temp1 = dst >> (32-num);
	unsigned int temp2 = dst << num;
	dst = temp1 | temp2;
	return 0;
}
//模32加
unsigned int Plus32(unsigned int a,unsigned int b)
{
	unsigned long int temp;
	temp = a + b;
	temp = temp % 0x100000000;
	return (int)temp;
}
//小端存储
unsigned int LittleEnd(unsigned int a)
{
	unsigned int temp1 = (a >> 24) & 0x000000ff;
	unsigned int temp2 = (a >> 8) & 0x0000ff00;
	unsigned int temp3 = (a << 24) & 0xff000000;
	unsigned int temp4 = (a << 8) & 0x00ff0000;
	unsigned re = temp1 | temp2 | temp3 | temp4;
	//printf("%08x", re);
	return re;
}
//转化
int trans(unsigned int t[],unsigned char s[],int l)
{
	for (int i = 0; i < l; i++)
	{
		    t[i] = 0;
			t[i] |= s[i * 4];
			t[i] =t[i]<< 8;
			t[i] |= s[i * 4+1];
			t[i] =t[i]<< 8;
			t[i] |= s[i * 4+2];
			t[i] =t[i]<< 8;
			t[i] |= s[i * 4+3];
			t[i] = LittleEnd(t[i]);
	}
	return 0;
}
//转化
int trans(unsigned int t[], char s[], int l)
{
	for (int i = 0; i < l; i++)
	{
		t[i] = 0;
		t[i] |= s[i * 4];
		t[i] = t[i] << 8;
		t[i] |= s[i * 4 + 1];
		t[i] = t[i] << 8;
		t[i] |= s[i * 4 + 2];
		t[i] = t[i] << 8;
		t[i] |= s[i * 4 + 3];
		t[i] = LittleEnd(t[i]);
	}
	return 0;
}
//F轮
void functionF(unsigned int& a,unsigned int& b,unsigned int& c,unsigned int& d,unsigned int x[])
{
	for (int i = 0; i < 16; i++)
	{
		unsigned int t = F(b, c, d);
		t = Plus32(t,a);
		int selection = i;
		t = Plus32(t,x[selection]);	
		t = Plus32(t , T[i]);
		leftShift(t, FN[i]);
		t = Plus32(t,b);
		a = d;
		d = c;
		c = b;
		b = t;
	}
}
//G轮
void functionG(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int x[])
{
	for (int i = 0; i < 16; i++)
	{
		unsigned int t = G(b, c, d);
		t = Plus32(t,a);
		int selection = (1+5*i)%16;
		t = Plus32(t,x[selection]);
		t = Plus32(t , T[16+i]);
		leftShift(t, GN[i]);
		t = Plus32(t,b);
		a = d;
		d = c;
		c = b;
		b = t;
	}
}
//H轮
void functionH(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int x[])
{
	for (int i = 0; i < 16; i++)
	{
		unsigned int t = H(b, c, d);
		t = Plus32(t,a);
		int selection = (5+3*i) % 16;
		t = Plus32(t,x[selection]);
		t = Plus32(t , T[32+i]);
		leftShift(t, HN[i]);
		t = Plus32(t,b);
		a = d;
		d = c;
		c = b;
		b = t;
	}
}
//I轮
void functionI(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int x[])
{
	for (int i = 0; i < 16; i++)
	{
		unsigned int t = I(b, c, d);
		t = Plus32(t,a);
		int selection = (7*i) % 16;
		t = Plus32(t,x[selection]);
		t = Plus32(t , T[48+i]);
		leftShift(t, IN[i]);
		t = Plus32(t,b);
		a = d;
		d = c;
		c = b;
		b = t;
	}
}

int  main()
{
	unsigned int A = a;
	unsigned int B = b;
	unsigned int C = c;
	unsigned int D = d;
	//备份
	unsigned int tmp1 = a;
	unsigned int tmp2 = b;
	unsigned int tmp3 = c;
	unsigned int tmp4 = d;
	bool f1 = false;
	bool f2 = false;
	ifstream openFile("input.txt");
	openFile.seekg(0, ios::end);
	long long int length = openFile.tellg() * 8;
	openFile.seekg(0, ios::beg);
	int mod1 = length % 512;
	if (mod1 < 448)
		f1 = true;
	if (mod1 >= 448)
		f2 = true;
	int num = length / 512;
	for (int i = 0; i < num; i++)
	{
		char buf1[64];
		openFile.read(buf1, 64);
		unsigned int test[16];
		unsigned char buf[64];
		for (int i = 0; i < 64; i++)
			buf[i] = buf1[i];
		trans(test, buf, 16);
		functionF(A, B, C, D, test);
		functionG(A, B, C, D, test);
		functionH(A, B, C, D, test);
		functionI(A, B, C, D, test);
		A = Plus32(A, tmp1);
		B = Plus32(B, tmp2);
		C = Plus32(C, tmp3);
		D = Plus32(D, tmp4);
		tmp1 = A;
		tmp2 = B;
		tmp3 = C;
		tmp4 = D;
	}
	if (f1)
	{
		unsigned int rest[16] = { 0 };
		char buf1[64] = { 0 };
		openFile.read(buf1, 64);
		unsigned char buf[64] = { 0 };
		for (int l = 0; l < 64; l++)
			buf[l] = buf1[l];
		buf[mod1 / 8] = 0x80;
		for (int nn = 0; nn <= longtonum(length); nn++)
		{
			buf[56+nn]= (length >>(nn*8)) & 0x00000000000000ff;
		}
		for (int n2 = longtonum(length); n2 < 7; n2++)
		{
			buf[56+n2+1] = 0x00;
		}
		trans(rest, buf, 16);
		functionF(A, B, C, D, rest);
		functionG(A, B, C, D, rest);
		functionH(A, B, C, D, rest);
		functionI(A, B, C, D, rest);
		A = Plus32(A, tmp1);
		B = Plus32(B, tmp2);
		C = Plus32(C, tmp3);
		D = Plus32(D, tmp4);
	}
	if (f2)
	{
		unsigned int rest[16] = { 0 };
		char buf1[64] = { 0 };
		openFile.read(buf1, 64);
		unsigned char buf[64] = { 0 };
		for (int l = 0; l < 64; l++)
			buf[l] = buf1[l];
		buf[mod1 / 8] = 0x80;
		for (int i = mod1 / 8 + 1; i < 64; i++)
			buf[i] = 0x00;
		trans(rest, buf, 16);
		functionF(A, B, C, D, rest);
		functionG(A, B, C, D, rest);
		functionH(A, B, C, D, rest);
		functionI(A, B, C, D, rest);
		A = Plus32(A, tmp1);
		B = Plus32(B, tmp2);
		C = Plus32(C, tmp3);
		D = Plus32(D, tmp4);
		tmp1 = A;
		tmp2 = B;
		tmp3 = C;
		tmp4 = D;
		unsigned int rest1[16] = { 0 };
		unsigned char buf2[64];
		for (int i = 0; i < 56; i++)
			buf2[i] = 0x00;
		for (int nn = 0; nn <= longtonum(length); nn++)
		{
			buf2[56 + nn] = (length >> (nn* 8)) & 0x00000000000000ff;
		}
		for (int n2 = longtonum(length); n2 < 7; n2++)
		{
			buf2[56 + n2 + 1] = 0x00;
		}
		trans(rest1, buf2, 16);
		functionF(A, B, C, D, rest1);
		functionG(A, B, C, D, rest1);
		functionH(A, B, C, D, rest1);
		functionI(A, B, C, D, rest1);
		A = Plus32(A, tmp1);
		B = Plus32(B, tmp2);
		C = Plus32(C, tmp3);
		D = Plus32(D, tmp4);
	}
	cout <<endl<< "----------------MD5加密结果----------------" << endl;
	cout<<"A: ";
	printf("0x%08x", LittleEnd(A));
	cout << endl;
	cout<<"B: ";
	printf("0x%08x", LittleEnd(B));
	cout << endl;
	cout<<"C: ";
	printf("0x%08x", LittleEnd(C));
	cout << endl;
	cout<<"D: ";
	printf("0x%08x", LittleEnd(D));
	cout << endl;
	system("pause");
	return 0;
}