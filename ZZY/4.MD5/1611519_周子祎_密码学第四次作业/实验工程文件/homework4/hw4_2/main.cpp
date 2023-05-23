#include<iostream>
#include<string>
#include"md5.h"

using namespace std;


int main() 
{
	//存储原始消息
	string OrigiMsg = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	//存储原始摘要
	string OrigiSumry;

	//存储50次改变后的消息
	string NewMsg [50];

	//存储50次改变后的摘要
	string NewSumry [50];

	//存储50次改变后的摘要比特变化位数
	int SumryBitChanged [50];

	cout << "***************************************************************************" << endl;
	cout << "*                      MD5哈希算法雪崩效应测试程序                        *" << endl;
	cout << "***************************************************************************" << endl;
	cout << "开始测试" << endl;
	cout << "***************************************************************************" << endl;
	cout << "原始消息："<< OrigiMsg << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	OrigiSumry = md5(OrigiMsg);
	cout << "原始摘要："<< OrigiSumry << endl;
	cout << "***************************************************************************" << endl;
	cout <<endl;

	for(int i = 0;i<50;i++)
	{
		cout << "***************************************************************************" << endl;
		cout << "进行第"<< i+1<<"次雪崩测试" << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "原始消息："<< OrigiMsg << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		NewMsg[i] = OrigiMsg;
		//改变一个字符的一个比特
		//这里采用的方法是：OrigiMsg的第一个字符，对应的二进制数值，末位为1则变为0；末位为0则变为1
		if(NewMsg[i][i] % 2 ==1)
			NewMsg[i][i]-=1;
		else
			NewMsg[i][i]+=1;

		cout << "新消息"<< i+1<<"：" <<NewMsg[i]<< endl;
		cout << "---------------------------------------------------------------------------" << endl;
		cout << "原始摘要："<< OrigiSumry << endl;
		cout << "---------------------------------------------------------------------------" << endl;
		NewSumry[i] = md5(NewMsg[i]);
		cout << "新摘要"<< i+1<<"：" <<NewSumry[i]<< endl;
		cout << "---------------------------------------------------------------------------" << endl;

		SumryBitChanged[i] = BitCmp(NewSumry[i],OrigiSumry);

		cout << "摘要相差二进制位数："<< SumryBitChanged[i] << endl;
		cout << "***************************************************************************" << endl;
		cout << endl;
	}
	cout << "***************************************************************************" << endl;
	cout << "摘要位数改变情况："<<endl;
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
	cout << "摘要平均改变位数为："<< ave << "位"<<endl;

	system("pause");
	return 0;
}