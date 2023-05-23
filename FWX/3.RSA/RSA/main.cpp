#include<iostream>
#include<time.h>
#include<ctime>
#include<fstream>
#include"bigInt.h"
using namespace std;

// ����һ����������,��֤����Ϊ����,�Ҳ��ܱ�С��5000����������
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
		for (; i < length; i++)
		{
			divisor = prime[i];
			if ((n % divisor) == 0)
				break;
		}
	}
}

// RabinMiller���ĳ�����Ƿ�������
bool RabinMiller(const BigInt& n)
{
	BigInt r, a, y;
	unsigned int s, j;
	r = n - 1;
	s = 0;

	while (!r.IsOdd())
	{
		s++;
		r >> 1;
	}

	//�������һ��С��N-1�ļ����a
	a.RandomSmall();

	//y = a��r����ģn
	y = PowerMode(a, r, n);

	//���J=2��J<S��
	if ((!(y == 1)) && (!(y == (n - 1))))
	{
		j = 1;
		while ((j <= s - 1) && (!(y == (n - 1))))
		{
			y = (y * y) % n;
			if (y == 1)
				return false;
			j++;
		}
		if (!(y == (n - 1)))
			return false;
	}
	return true;
}

//����һ������
BigInt GeneratePrime()
{
	BigInt n;
	int i = 0;
	// ��¼�ܹ������˶��ٴ�����
	int time = 0;

	//���޴�ѭ�������ϲ���������ֱ��i==5ʱ��ͨ������RabinMiller���ԣ��Ż�����whileѭ��
	while (i < 5)
	{
		//��¼�����˶��ٴδ�����
		time++;

		//����һ����������
		cout << endl << endl;
		cout << "�������ɵ�" << time << "����������" << endl;
		SortPrime(n);
		n.display();

		i = 0;
		//��������RABINMILLER����,����ȫ��ͨ���������ϸ�
		for (; i < 5; i++)
		{
			cout << "���ڽ��е�" << i + 1 << "��RabinMiller���ԣ�";
			if (!RabinMiller(n))
			{
				cout << "������������ʧ��" << endl << endl;
				break;
			}
			cout << "������������ͨ��" << endl << endl;
		}
	}
	return n;
}

// շת��������������������Լ��
BigInt Gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return Gcd(n, m % n);
}

// ��չŷ�������˷���Ԫ
BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//���һ��������Ϊ�����޷����г�������
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	d = ExtendedGcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - ((a / b) * y);
	return d;
}

// RSA����
BigInt RSAEn(BigInt& m, BigInt& e, BigInt& n) {
	// ���ܺ�Ľ��
	BigInt c;
	c = PowerMode(m, e, n);
	return c;
}

// RSA����
BigInt RSADe(BigInt& c, BigInt& d, BigInt& n) {
	// ���ܺ�Ľ��
	BigInt m;
	m = PowerMode(c, d, n);
	return m;
}

int main() {
	cout << "==================��һ������p����================\n";
	// ����ʱ������һ�������
	srand((unsigned)time(NULL));

	BigInt randomP = GeneratePrime();
	cout << "==================����p���ɳɹ�===================\np��\n";
	randomP.display();

	cout << "\n\n==================�ڶ�������q����================\n";
	BigInt randomQ = GeneratePrime();
	cout << "==================����q���ɳɹ�===================\nq��\n";
	randomQ.display();

	// �����ɵ�����������prime.txt��
	ofstream outfile("./prime.txt");
	outfile << randomP;
	outfile << '\n';
	outfile << randomQ;
	outfile << '\n';
	// �ر��ļ�
	outfile.close();

	// ����n
	BigInt n;
	n = randomP * randomQ;
	
	// ����գ�n��
	BigInt fn = (randomP - 1) * (randomQ - 1);

	// ��Կe
	BigInt e;
	//dΪ����Կ����eģt�ĳ˷���Ԫ
	BigInt d;
	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;
	// �����־λ���ж��㷨�Ƿ�ɹ�
	BigInt temp;
	// ����������ʵ���
	while (1)
	{
		//������fn���ʵ�e
		e.Random();
		while (!(Gcd(e, fn) == 1))
		{
			e.Random();
		}

		//����չŷ������㷨��ͼ���eģt�ĳ˷���Ԫ
		temp = ExtendedGcd(e, fn, d, y);

		//e*dģt���Ϊ1��˵��dȷʵ��eģt�ĳ˷���Ԫ
		temp = (e * d) % fn;
		if (temp == 1)
			break;

		//������������e
	}
	cout << "\n\n===========================����׼��===========================\n";
	cout << "��������õ���Կ(n,e)Ϊ��\n("; n.display(); cout << " ,\n"; e.display(); cout << ")\n";
	cout << "�õ�˽Կ(n,d)Ϊ��\n("; n.display(); cout << " ,\n"; d.display(); cout << ")\n";
	cout << endl << endl;

	cout << "\n\n===========================�����������===========================\n";
	BigInt m;
	m.Random();
	cout << "���ɵ��������Ϊ��\n";
	m.display();

	// ���ܺ������
	BigInt c;
	c = RSAEn(m, e, n);
	cout << "���ܺ�õ�������Ϊ��\n";
	c.display();

	// �Լ��ܵ����Ľ��ܺ�õ�������
	BigInt newm;
	newm = RSADe(c, d, n);
	cout << "�����Ľ��ܺ�õ�������Ϊ��\n";
	newm.display();

	// д�ļ�����RSA�йص����ݶ�д��
	ofstream rsaResult("./rsaResult.txt");
	// д��n,e,d,m,c,newm
	rsaResult << "n:\n";
	rsaResult << n;
	rsaResult << '\n';
	rsaResult << "e:\n";
	rsaResult << e;
	rsaResult << '\n';
	rsaResult << "d:\n";
	rsaResult << d;
	rsaResult << '\n';
	rsaResult << "m:\n";
	rsaResult << m;
	rsaResult << '\n';
	rsaResult << "c:\n";
	rsaResult << c;
	rsaResult << '\n';
	rsaResult << "newm:\n";
	rsaResult << newm;
	rsaResult << '\n';
	rsaResult.close();
	cout << "RSA��������Ѿ�д��rsaResult.txt��\n";

	return 0;
}