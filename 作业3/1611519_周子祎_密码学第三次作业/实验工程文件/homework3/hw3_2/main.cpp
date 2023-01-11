#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "BigInt.h"
#include "PrimerTable.h"
#include "PrimerGen.h"
#include<ctime>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	ofstream outfile("test.txt");

	cout << "***************************************************************************" << endl;
	cout << "*                                  RSA����                                *" << endl;
	cout << "***************************************************************************" << endl;
	cout << "��ʼ����" << endl;

	cout << "***************************************************************************" << endl;
	cout << "���ɴ����� p" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	//��¼�����˶��ٴδ�����
	int time = 0;

	//��ʼ��ʱ
	clock_t start = clock();

	//����������
	BigInt p = GeneratePrime(time);

	//������ʱ
	clock_t finish = clock();

	cout <<"����512��������p�ɹ���"<< endl;
	cout << "���ɴ�����p��ʱ����I/O��ʱ��: " << (double)(finish - start) / CLOCKS_PER_SEC << "s." << endl;
	cout << "���ɴ����������� " << time<< "��" << endl;
	cout << "���ɴ�����pΪ�� "<< endl;

	//16������ʽ��ʾ
	p.display();
	outfile << "������p:" << endl;
	outfile << p;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "���ɴ����� q" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	//��¼�����˶��ٴδ�����
	int time2 = 0;

	//��ʼ��ʱ
	clock_t start2 = clock();

	//����������
	BigInt q = GeneratePrime(time2);

	//������ʱ
	clock_t finish2 = clock();

	cout <<"����512��������q�ɹ���"<< endl;
	cout << "���ɴ�����q��ʱ����I/O��ʱ��: " << (double)(finish2 - start2) / CLOCKS_PER_SEC << "s." << endl;
	cout << "���ɴ����������� " << time2<< "��" << endl;
	cout << "���ɴ�����qΪ�� "<< endl;

	//16������ʽ��ʾ
	p.display();
	outfile << "������q:" << endl;
	outfile << q;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "���㹫��Կn = p * q" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt n = p*q;

	cout << "����ԿnΪ�� "<< endl;
	//16������ʽ��ʾ
	n.display();
	outfile << "����ԿnΪ��" << endl;
	outfile << n;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "���㹫��Կe ������Կd " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt t = (p - 1)*(q - 1);

	//eΪ����Կ
	BigInt e;

	//dΪ����Կ����eģt�ĳ˷���Ԫ
	BigInt d;

	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;

	BigInt temp;

	while (1)
	{
		//������t���ʵ�e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}

		//����չŷ������㷨��ͼ���eģt�ĳ˷���Ԫ
		temp = ExtendedGcd(e, t, d, y);

		//e*dģt���Ϊ1��˵��dȷʵ��eģt�ĳ˷���Ԫ
		temp = (e*d) % t;
		if (temp == 1)
			break;

		//������������e
	}

	
	cout << "����ԿeΪ�� "<< endl;
	//16������ʽ��ʾ
	e.display();
	outfile << "����Կe:" << endl;
	outfile << e;
	cout << endl;

	cout << "����ԿdΪ�� "<< endl;
	//16������ʽ��ʾ
	d.display();
	outfile << "����Կd:" << endl;
	outfile << d;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "����������ķ���m " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt m;
	m.Random();
	cout << "���ķ���mΪ��"<< endl;
	//16������ʽ��ʾ
	m.display();
	outfile << "���ķ���mΪ��" << endl;
	outfile << m;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "������Կe��m����,�õ����ķ���c " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt c = PowerMode(m, e, n);
	cout << "���ķ���cΪ��"<< endl;
	//16������ʽ��ʾ
	c.display();
	outfile << "���ķ���cΪ��" << endl;
	outfile << c;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "�ù���Կd��c���ܣ��õ����ķ���m2 " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt m2 = PowerMode(c, d, n);
	cout << "���ķ���m2Ϊ��"<< endl;
	//16������ʽ��ʾ
	m2.display();
	outfile << "���ķ���m2Ϊ��" << endl;
	outfile << m2;
	cout << endl;

	system("pause");
	return 0;
}
