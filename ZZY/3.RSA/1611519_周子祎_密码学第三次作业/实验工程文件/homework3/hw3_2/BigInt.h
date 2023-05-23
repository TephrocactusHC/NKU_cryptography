#pragma once
#include <iostream>
using namespace std;

const int thesize = 64;

class BigInt {

	friend BigInt operator+ (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const int&);
	friend BigInt operator* (const BigInt&, const BigInt&);
	friend BigInt operator% (const BigInt&, const BigInt&);
	friend BigInt operator/ (const BigInt&, const BigInt&);
	friend BigInt operator* (const BigInt&, const unsigned int&);
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const int&);
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator== (const BigInt&, const int&);
	friend ostream& operator<< (ostream&, const BigInt&);
	friend BigInt PowerMode(const BigInt&, const BigInt&, const BigInt&);
	friend void SortPrime(BigInt& n);

public:
	BigInt();
	BigInt(const int&);
	BigInt(const BigInt&);

	void operator= (const BigInt&);
	void operator= (const int& a) { Clear(); data[0] = a; }
	void operator>> (const int&);

	inline int GetLength() const;   //���ش����ĳ���
	bool TestSign() { return sign; }  //�жϴ��������� 
	void Clear();  //������0
	void Random(); //�������һ������
	void Randomsmall();  //�������һ����С�Ĵ���
	void display() const;
	void Output(ostream& out) const;
	bool IsOdd() const { return (data[0] & 1); }  //�жϴ�����ż��

private:
	unsigned int data[thesize];
	bool sign;
};

BigInt operator+ (const BigInt&, const BigInt&);
BigInt operator- (const BigInt&, const BigInt&);
BigInt operator- (const BigInt&, const int&);
BigInt operator* (const BigInt&, const BigInt&);
BigInt operator/ (const BigInt&, const BigInt&);
BigInt operator% (const BigInt&, const BigInt&);
BigInt operator* (const BigInt&, const unsigned int&);
BigInt PowerMode(const BigInt&, const BigInt&, const BigInt&);
bool operator< (const BigInt&, const BigInt&);
bool operator> (const BigInt&, const BigInt&);
bool operator<= (const BigInt&, const int&);
bool operator== (const BigInt&, const BigInt&);
bool operator== (const BigInt&, const int&);
ostream& operator<< (ostream&, const BigInt&);
void SortPrime(BigInt& n);