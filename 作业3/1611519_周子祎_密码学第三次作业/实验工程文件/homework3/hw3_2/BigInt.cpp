#pragma once
#include <iostream>
#include <stdlib.h>
#include "BigInt.h"
#include "PrimerTable.h"
using namespace std;

//Ĭ�Ϲ��캯��,��Ա������0
BigInt::BigInt()
{
	for (int i = 0; i<thesize; i++)
		data[i] = 0;
	sign = true;
}


//��int��ʼ������
BigInt::BigInt(const int& input)
{
	for (int i = 0; i<thesize; i++)
		data[i] = 0;
	data[0] = input;
	if (input >= 0)
		sign = true;
	else
		sign = false;
}

//�ô�����������ֵ
BigInt::BigInt(const BigInt& input)
{
	for (int i = 0; i<thesize; i++)
		data[i] = input.data[i];
	sign = input.sign;
}

//�ô�����������ֵ
void BigInt::operator= (const BigInt& input)
{
	for (int i = 0; i<thesize; i++)
		data[i] = input.data[i];
	sign = input.sign;
}

//�Ƚ����������Ĵ�С,a<b,������,���򷵻ؼ�
bool operator< (const BigInt& a, const BigInt& b)
{
	for (int i = thesize - 1; i>0; i--)
	{
		if (a.data[i]<b.data[i])
			return true;
		if (a.data[i]>b.data[i])
			return false;
	}
	return a.data[0]<b.data[0];
}

//�Ƚ����������Ĵ�С,a>b,������,���򷵻ؼ�
bool operator> (const BigInt& a, const BigInt& b)
{
	for (int i = thesize - 1; i >= 0; i--)
	{
		if (a.data[i]>b.data[i])
			return true;
		if (a.data[i]<b.data[i])
			return false;
	}
	return false;
}

//�ж����������Ƿ����,��ȷ�����,���򷵻ؼ�
bool operator== (const BigInt& a, const BigInt& b)
{
	for (int i = 0; i<thesize; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

//�ж�һ��������һ��intֵ�Ƿ����,��ȷ�����,���򷵻ؼ�
bool operator== (const BigInt& a, const int& b)
{
	for (int i = 1; i<a.GetLength(); i++)
		if (a.data[i] != 0)
			return false;
	return a.data[0] == b;
}

//�������������ĺ�,������ʽ��ӷ�
BigInt operator+ (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64λ����,���ÿ��λ����ӵ���ʱ��
	unsigned __int64 sum;
	//carryΪ��λ��־,subΪ��������������ʱ,���ÿ��λ���������ʱ��
	unsigned int carry = 0, sub;
	//ȡa,b�г��Ƚϳ��ĳ���
	int length = (a.GetLength() >= b.GetLength() ? a.GetLength() : b.GetLength());

	//������������ͬʱ,���мӷ�����
	if (a.sign == b.sign)
	{
		//ÿһλ������ʽ���
		for (int i = 0; i<length; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum�ĸ�λΪ��λ
			carry = (sum >> 32);
		}

		result.sign = a.sign;
		return result;
	}

	//�������Ų�ͬʱ,���м�������
	else
	{
		BigInt tempa, tempb;

		//ȡ��a,b�о���ֵ�ϴ����Ϊ������
		if (a<b)
		{
			tempa = b;
			tempb = a;
		}
		else
		{
			tempa = a;
			tempb = b;
		}

		//ÿһλ������ʽ��
		for (int i = 0; i<length; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				//��λ��
				result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
}

//�������������Ĳ�,������ʽ�����
BigInt operator- (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64λ����,���ÿ��λ����ӵ���ʱ��
	unsigned __int64 sum;
	//carryΪ��λ��־,subΪ��������������ʱ,���ÿ��λ���������ʱ��
	unsigned int carry = 0, sub;

	//������ͬʱ,���м�������
	if (a.sign == b.sign)
	{
		BigInt tempa, tempb;

		//ȡ��a,b�о���ֵ�ϴ����Ϊ������
		if (a<b)
		{
			tempa = b;
			tempb = a;
			tempa.sign = !tempa.sign;
		}
		else
		{
			tempa = a;
			tempb = b;
		}

		//ÿһλ������ʽ��
		for (int i = 0; i<thesize; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				//��λ��
				result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}

	//�������Ų�ͬʱ,���мӷ�����
	else
	{
		//ÿһλ������ʽ���
		for (int i = 0; i<thesize; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum�ĸ�λΪ��λ
			carry = (sum >> 32);
		}
		result.sign = a.sign;
		return result;
	}
}

//������һ��int��
BigInt operator- (const BigInt& a, const int& b)
{
	BigInt temp(b);
	BigInt result = a - temp;
	return result;
}


//��������һ��INT��
BigInt operator* (const BigInt& a, const unsigned int& b)
{
	BigInt result;
	//���B����A��ÿһλ����ʱ��
	unsigned __int64 sum;
	//��Ž�λ
	unsigned int carry = 0;

	for (int i = 0; i<thesize; i++)
	{
		sum = ((unsigned __int64)a.data[i])*b + carry;
		result.data[i] = (unsigned int)sum;
		//��λ��SUM�ĸ�λ��
		carry = (sum >> 32);
	}
	result.sign = a.sign;
	return result;
}

//�������,������ʽ��
BigInt operator* (const BigInt& a, const BigInt& b)
{
	//last�����ʽ��һ�еĻ�,temp��ŵ�ǰ�еĻ�
	BigInt result, last, temp;
	//sum��ŵ�ǰ�д���λ�Ļ�
	unsigned __int64 sum;
	//��Ž�λ
	unsigned int carry;

	//������ʽ��
	for (int i = 0; i<b.GetLength(); i++)
	{
		carry = 0;
		//B��ÿһλ��A���
		for (int j = 0; j<a.GetLength() + 1; j++)
		{
			sum = ((unsigned __int64)a.data[j])*(b.data[i]) + carry;
			if ((i + j)<thesize)
				temp.data[i + j] = (unsigned int)sum;
			carry = (sum >> 32);
		}
		result = (temp + last);
		last = result;
		temp.Clear();
	}

	//�жϻ��ķ���
	if (a.sign == b.sign)
		result.sign = true;
	else
		result.sign = false;

	return result;
}

//������,�������̳���,���ö��ֲ��ҷ��Ż�
BigInt operator/ (const BigInt& a, const BigInt& b)
{
	//mulΪ��ǰ����,low,highΪ���ֲ�������ʱ���õı�־
	unsigned int mul, low, high;
	//subΪ�����뵱ǰ���̵Ļ�,subsequentΪ��������һ���̵Ļ�
	//dividend�����ʱ������
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//���������С�ڳ���,ֱ�ӷ���0
	if (a<b)
	{
		if (a.sign == b.sign)
			quotient.sign = true;
		else
			quotient.sign = false;
		return quotient;
	}

	//�ѱ������������ĳ��ȴӸ�λ��λ
	int i;
	for (i = 0; i<lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		//���������С�ڳ���,������λ
		if (dividend<b)
		{
			for (int j = lengthb; j>0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		//���ֲ��ҷ���������
		while (low<high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b*mul);
			subsequent = (b*(mul + 1));

			if (((sub<dividend) && (subsequent>dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub<dividend) && (subsequent<dividend))
			{
				low = mul;
				continue;
			}
			if ((sub>dividend) && (subsequent>dividend))
			{
				high = mul;
				continue;
			}

		}

		//���̽�����浽����ȥ
		quotient.data[i] = mul;
		//��ʱ��������Ϊ�����������̻��Ĳ�
		dividend = dividend - sub;

		//��ʱ����������λ
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j>0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//�ж��̵ķ���
	if (a.sign == b.sign)
		quotient.sign = true;
	else
		quotient.sign = false;
	return quotient;
}

//������ģ����,�������������
BigInt operator% (const BigInt& a, const BigInt& b)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//���������С�ڳ���,���ر�����Ϊģ
	if (a<b)
	{
		dividend = a;
		//����������Զ�뱻������ͬ
		dividend.sign = a.sign;
		return dividend;
	}

	//���г�������
	int i;
	for (i = 0; i<lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend<b)
		{
			for (int j = lengthb; j>0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		while (low <= high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b*mul);
			subsequent = (b*(mul + 1));

			if (((sub<dividend) && (subsequent>dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub<dividend) && (subsequent<dividend))
			{
				low = mul;
				continue;
			}
			if ((sub>dividend) && (subsequent>dividend))
			{
				high = mul;
				continue;
			}
		}

		quotient.data[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j>0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//��ʱ��������Ϊ����ģ
	dividend.sign = a.sign;
	return dividend;
}

//����һ���������,������LENGTHΪSIZE��1/4,��Ϊ�˷�ֹ����ʱ�����
void BigInt::Random()
{
	for (int i = 0; i<(thesize / 4); i++)
		//����RAND()���ֻ�ܲ���0X7FFF����,Ϊ���ܲ���32λ�������,��Ҫ
		//3��RAND()����
		data[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
}


//����һ����С���������,������LENGTHΪSIZE��1/8
void BigInt::Randomsmall()
{
	for (int i = 0; i<(thesize / 16); i++)
		//����RAND()���ֻ�ܲ���0X7FFF����,Ϊ���ܲ���32λ�������,��Ҫ
		//3��RAND()����
		data[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
}

//��������16������ʾ����Ļ��
void BigInt::display() const
{
	unsigned int temp, result;
	unsigned int and = 0xf0000000;

	int changeline = 0;
	for (int i = GetLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		//������ÿһλ����ת����16�������
		for (int j = 0; j<8; j++)
		{
			result = temp&and;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				cout << result;
			else
			{
				switch (result)
				{
				case 10:
					cout << "A";
					break;
				case 11:
					cout << "B";
					break;
				case 12:
					cout << "C";
					break;
				case 13:
					cout << "D";
					break;
				case 14:
					cout << "E";
					break;
				case 15:
					cout << "F";
					break;
				}
			}
		}
		cout << " ";

		changeline++;
		if(changeline == 8)
		{
			changeline = 0;
			cout<<endl;
		}
	}
	cout << endl;
}

//��������������������
void BigInt::Output(ostream& out) const
{
	unsigned int temp, result;
	unsigned int and = 0xf0000000;

	for (int i = GetLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		//������ÿһλ����ת����16�������
		for (int j = 0; j<8; j++)
		{
			result = temp&and;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				out << result;
			else
			{
				switch (result)
				{
				case 10:
					out << "A";
					break;
				case 11:
					out << "B";
					break;
				case 12:
					out << "C";
					break;
				case 13:
					out << "D";
					break;
				case 14:
					out << "E";
					break;
				case 15:
					out << "F";
					break;
				}
			}
		}
	}
	out << endl;
}

//�������������
ostream& operator<< (ostream& out, const BigInt& x)
{
	x.Output(out);
	return out;
}

//������0
void BigInt::Clear()
{
	for (int i = 0; i<thesize; i++)
		data[i] = 0;
}

//���ش�������
inline int BigInt::GetLength() const
{
	int length = thesize;
	for (int i = thesize - 1; i >= 0; i--)
	{
		//��һλ��Ϊ0��ΪLENGTH
		if (data[i] == 0)
			length--;
		else
			break;
	}
	return length;
}

//������λ������,������Nλ
void BigInt::operator>> (const int& a)
{
	unsigned int bit;
	data[0] = (data[0] >> a);
	for (int i = 1; i < GetLength(); i++)
	{
		//�Ƚ�ÿһλ�ĵ�λ�Ƶ�BIT��
		bit = data[i] & 1;
		//�ٰ�BIT�Ƶ���һλ�ĸ�λ��
		bit = bit << (32 - a);;
		data[i - 1] = data[i - 1] | bit;
		data[i] = (data[i] >> a);
	}
}

//�жϴ�����һ��INT�Ĵ�С
bool operator<= (const BigInt& a, const int& b)
{
	for (int i = 1; i<a.GetLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	if (a.data[0] <= b)
		return true;
	else
		return false;
}


//ģ�����㡪������n��p����ģm
//����Montgomery�㷨��
BigInt PowerMode(const BigInt& n, const BigInt& p, const BigInt& m)
{
	BigInt temp = p;
	BigInt base = n%m;
	BigInt result(1);

	//���ָ��p�Ķ�������ʽ��ÿһλ
	while (!(temp <= 1))
	{
		//�����λΪ1�����ʾ��λ��Ҫ����ģ����
		if (temp.IsOdd())
		{
			result = ( result * base) % m;
		}
		base = (base * base) % m;
		temp >> 1;
	}
	return (base * result) % m;
}


//����һ����������,��֤����Ϊ����,�Ҳ��ܱ�С��5000����������
void SortPrime(BigInt& n)
{
	int i = 0;
	BigInt divisor;
	const int length = sizeof(prime) / sizeof(int);

	while (i != length)
	{
		n.Random();
		while (!n.IsOdd())
			n.Random();

		i = 0;
		for (; i<length; i++)
		{
			divisor = prime[i];
			if ((n%divisor) == 0)
				break;
		}
	}
}
