#include <iostream>
#include <fstream>
#include "RSA.h"
#include"tchar.h"
using namespace std;

int main()
{
	
	bigNum p("8AAC05688FE148E33810A426BF31A8E4D1DE1E59AE1D4C795288747484846DC39FEA04572C67BC60076CB310B9CE6D13BBE369A19FCE320D07504A3B0E71B0EB");
	bigNum q("E0913E18DAD029405377F58DAB4469ABDD5E2D847EF5F67A29BA69F0D4B5FECE19B5F9A0F7C668DC99362D26428CB4E41CE660E411077AEF1532CB8DA0C49CC3");
	bigNum n=p*q;
	cout << "n=  ";
	n.output();
	cout<<"运行中！"<<endl;
	bigNum fi=(p-1)*(q-1);
	bigNum e("10001");
	cout << endl << "e=  ";
	e.output();
	bigNum d;
	cout <<"运行中! "<<endl ;
	d=e.inverse(fi);
	cout << endl << "d=  ";
	d.output();
	cout<<"运行中！"<<endl;
	bigNum m("30");
	cout << endl<<"m=  ";
	m.output();
	bigNum c;
	c=m.exp(e,n);
	cout<<"运行中！"<<endl;
	cout << "密文  ";
	c.output();
	cout<<endl;
	cout<<"运行中！"<<endl;
	cout<<endl<<"解密结果为:";
	bigNum dp,dq;
	dp=d%(p-1);
	dq=d%(q-1);
	bigNum mp,mq;
	mp=c.exp(dp,p);
	mq=c.exp(dq,q);
	bigNum M11,M22;
	M11=q.inverse(p);
	M22=p.inverse(q);
	bigNum mt1,mt2;
	mt1=modMult(q*M11,mp,n);
	mt2=modMult(p*M22,mq,n);
	m=(mt1+mt2)%n;
	m.output();
	system("pause");
}

