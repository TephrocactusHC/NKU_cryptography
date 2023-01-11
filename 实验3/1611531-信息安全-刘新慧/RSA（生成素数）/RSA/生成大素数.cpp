#include <iostream>
#include <fstream>
#include <string>
#include<stdlib.h>
#include<time.h>
#include "RSA.h"
#include "tchar.h"
using namespace std;

int main()
{
	srand((int)time(0));
	bigNum temp;
	int primeNum[303];
	ifstream infile("shortprime.txt");
	int ix=0;
	while(infile>>primeNum[ix])ix++;
	ofstream outfile("result.txt");
	for(int i=0;i<5;i++)
	{
		while(true)
		{
			temp.random(512);
			temp.output();
			int i1;
			for(i1=0;i1<303;i1++)
			{
				if((temp%primeNum[i1]) == 0)
					break;
			}
			if(i1==303)
				break;
		}	
		bool f;
		f=temp.isPrimeNumber();
		if(f==false){i--; continue;}
		cout<<"Yes£¡£¡£¡"<<endl;
		temp.outfile(outfile);
		outfile<<endl;	
		cout<<i<<endl;
		temp.output();
		cout<<endl;
	}
	outfile.close();
	system("pause");
	return 0;
}

