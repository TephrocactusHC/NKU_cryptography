#include<iostream>
#include<string>
#include"md5.h"

using namespace std;


int main() 
{
	//�洢ԭʼ��Ϣ
	string OrigiMsg = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	//�洢ԭʼժҪ
	string OrigiSumry;

	//�洢50�θı�����Ϣ
	string NewMsg [50];

	//�洢50�θı���ժҪ
	string NewSumry [50];

	//�洢50�θı���ժҪ���ر仯λ��
	int SumryBitChanged [50];

	cout << "***************************************************************************" << endl;
	cout << "*                      MD5��ϣ�㷨ѩ��ЧӦ���Գ���                        *" << endl;
	cout << "***************************************************************************" << endl;
	cout << "��ʼ����" << endl;
	cout << "***************************************************************************" << endl;
	cout << "ԭʼ��Ϣ��"<< OrigiMsg << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	OrigiSumry = md5(OrigiMsg);
	cout << "ԭʼժҪ��"<< OrigiSumry << endl;
	cout << "***************************************************************************" << endl;
	cout <<endl;

	for(int i = 0;i<50;i++)
	{
		cout << "***************************************************************************" << endl;
		cout << "���е�"<< i+1<<"��ѩ������" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "ԭʼ��Ϣ��"<< OrigiMsg << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		NewMsg[i] = OrigiMsg;
		//�ı�һ���ַ���һ������
		//������õķ����ǣ�OrigiMsg�ĵ�һ���ַ�����Ӧ�Ķ�������ֵ��ĩλΪ1���Ϊ0��ĩλΪ0���Ϊ1
		if(NewMsg[i][i] % 2 ==1)
			NewMsg[i][i]-=1;
		else
			NewMsg[i][i]+=1;

		cout << "����Ϣ"<< i+1<<"��" <<NewMsg[i]<< endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "ԭʼժҪ��"<< OrigiSumry << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		NewSumry[i] = md5(NewMsg[i]);
		cout << "��ժҪ"<< i+1<<"��" <<NewSumry[i]<< endl;
		cout << "---------------------------------------------------------------------------" << endl;

		SumryBitChanged[i] = BitCmp(NewSumry[i],OrigiSumry);

		cout << "ժҪ��������λ����"<< SumryBitChanged[i] << endl;
		cout << "***************************************************************************" << endl;
		cout << endl;
	}
	cout << "***************************************************************************" << endl;
	cout << "ժҪλ���ı������"<<endl;
	int ave=0;
	for(int t = 0;t<50;t++)
	{
		ave += SumryBitChanged [t];
		cout<<SumryBitChanged [t] <<" ";
		if(t == 24)
			cout<<endl;
	}
	cout<<endl;

	ave /= 50;
	cout << "ժҪƽ���ı�λ��Ϊ��"<< ave << "λ"<<endl;

	system("pause");
	return 0;
}