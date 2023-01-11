#include<iostream>
using namespace std;
void keyToBinary(char *key,int*mykey1){
	int i,j,k=0;
	for(i=0;i<32;i++)
	{
		if(key[i]<='9')
		{
			for(j=0;j<4;j++)
			{
				mykey1[k+3-j]=int(key[i])%2;
				//char tmp1=(int)key[i]/2;
				//key[i]=tmp1;
				key[i]/=2;

			}
			k=k+4;
		}
		else
		{
			if(key[i]=='a')
			{
				mykey1[k++]=1;
				mykey1[k++]=0;
				mykey1[k++]=1;
				mykey1[k++]=0;
			}
			if(key[i]=='b')
			{
				mykey1[k++]=1;
				mykey1[k++]=0;
				mykey1[k++]=1;
				mykey1[k++]=1;
			}
			if(key[i]=='c')
			{
				mykey1[k++]=1;
				mykey1[k++]=1;
				mykey1[k++]=0;
				mykey1[k++]=0;
			}
			if(key[i]=='d')
			{
				mykey1[k++]=1;
				mykey1[k++]=1;
				mykey1[k++]=0;
				mykey1[k++]=1;
			}
			if(key[i]=='e')
			{
				mykey1[k++]=1;
				mykey1[k++]=1;
				mykey1[k++]=1;
				mykey1[k++]=0;
			}
			if(key[i]=='f')
			{
				mykey1[k++]=1;
				mykey1[k++]=1;
				mykey1[k++]=1;
				mykey1[k++]=1;
			}

		}
	}

}
//将输入的十六进制转换为二进制
void main(){
	int count=0;
	char str1[]="03319a22f0416ae301a35743bf5d6ba6";
	int mykey1[128];
	keyToBinary(str1,mykey1);
	cout<<"-----------d331-----------"<<endl;
	for(int i=0;i<128;i++)
		cout<<mykey1[i];
	cout<<endl;

	cout<<"-----------d1-----------"<<endl;
	for(int i=0;i<32;i++)
		cout<<mykey1[i];
	cout<<endl;

	char str2[33];
	cin>>str2;
	int mykey2[128];
	keyToBinary(str2,mykey2);

	for(int i=0;i<32;i++)
		cout<<mykey2[i];
	cout<<endl<<endl;



	for(int i=0;i<128;i++)
		if(mykey2[i]!=mykey1[i])
			count++;
	cout<<count<<endl<<endl;


		cout<<"-----------d2-----------"<<endl;
	for(int i=32;i<64;i++)
		cout<<mykey1[i];
	cout<<endl;

		for(int i=32;i<64;i++)
		cout<<mykey2[i];
	cout<<endl<<endl;

			cout<<"-----------d3-----------"<<endl;
	for(int i=64;i<96;i++)
		cout<<mykey1[i];
	cout<<endl;

for(int i=64;i<96;i++)
		cout<<mykey2[i];
	cout<<endl<<endl;

			cout<<"-----------d4-----------"<<endl;
	for(int i=96;i<128;i++)
		cout<<mykey1[i];
	cout<<endl;

	for(int i=96;i<128;i++)
		cout<<mykey2[i];
	cout<<endl<<endl;




	system("pause");

}
