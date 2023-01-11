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
	cout << "*                               �������ɲ���                              *" << endl;
	cout << "***************************************************************************" << endl;
	cout << "��ʼ����" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	
	//��¼�����˶��ٴδ�����
	int time = 0;

	//��ʼ��ʱ
	clock_t start = clock();

	//����������
	BigInt p = GeneratePrime(time);

	//������ʱ
	clock_t finish = clock();

	cout <<"����512���������ɹ���"<< endl;
	cout << "����������ʱ����I/O��ʱ��: " << (double)(finish - start) / CLOCKS_PER_SEC << "s." << endl;
	cout << "���ɴ����������� " << time<< "��" << endl;
	cout << "���ɴ�����Ϊ�� "<< endl;

	//16������ʽ��ʾ
	p.display();
	outfile << "������:" << endl;
	outfile << p;
	cout << endl;
	cout << "***************************************************************************" << endl;

	system("pause");
	return 0;
}
