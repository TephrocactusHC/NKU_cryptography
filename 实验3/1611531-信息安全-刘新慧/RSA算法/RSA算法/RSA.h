#include<iostream>
#include<math.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
const int MAX=1025;  //��ʾ�����ദ������λ�����ɸ�����Ҫ��������,�������ֵ�����ǲ������ȵĶ����ӡ�
//���λ��Ϊ����ж�λ
const int m=0x80000000-1;
int xn=1;
int xn1=xn;
const int aa=16807;
class bigNum{
private:
	bool num[MAX];     //0��ʾ��λ 

public:	
	bool flag;  	     //0��ʾ����1��ʾ��	 
	static bool isFirst;                   //������������ĳ�ʼֵ
	bigNum(){                              //���캯�����ó�ֵΪ0
		int i;
		for(i=0;i<MAX;i++){
			num[i]=0;
		}
		flag=0;
	}
	bigNum(int input);						//���캯������������������ó�ֵ
	bigNum(string input);                  //���캯�������������ʮ�������ַ����ó�ֵ
	void random(int n);					   //�������������nλ��
	bool isPrimeNumber();				   //�ж��ǲ�������
	friend bigNum operator*(bigNum a,bigNum b);        //��������أ��˷�
//	bigNum modMult(bigNum a,bigNum b,bigNum c);			//ģ��
	friend bigNum operator+(bigNum a,bigNum b);        //��������أ��ӷ�
	friend bigNum operator-(bigNum a,bigNum b);        //��������أ�����
	friend bigNum operator/(bigNum a,bigNum b);        //��������أ�����
	friend bigNum operator%(bigNum a,bigNum b);        //��������أ�ȡ����
	friend bool operator>(bigNum a,bigNum b);          //��������أ����ں��ж�
	friend bool operator==(bigNum a,bigNum b);         //��������أ�����ж�
	friend bool operator!=(bigNum a,bigNum b);         //��������أ���Ȳ��ж�
	bigNum exp(bigNum b,bigNum c);//a^b mod c  ָ������
	bigNum inverse(bigNum b);    //a-1 mod b   ����Ԫ����
	void conversation(int a);     //������a��ת��Ϊ���������
	void moveLeft(int i);         //����iλ
	bool operator[](int i);       //��������أ�ȡ��iλ
	void make(int i,bool a);      //�������ĵ�iλ��Ϊa
	void output();                //�����������
	void outfile(ofstream& outfile);
	void fu();                    //����������Ϊ���෴��
	bigNum abs();                 //��������ľ���ֵ
};
void bigNum::fu(){
	this->flag=!(this->flag);
}
bigNum bigNum::abs(){
	bigNum temp=(*this);
	if(temp.flag==0){
		return temp;
	}
	else{
		temp.fu();
		return temp;
	}
}
bool bigNum::operator [](int i){
	return num[i];
}
void bigNum::make(int i,bool a){
	num[i]=a;
}
bool operator==(bigNum a,bigNum b){
	int i;
	bool same=true;
	if(a.flag!=b.flag){
		same=false;
	}
	for(i=0;i<MAX;i++){
		if(a[i]!=b[i]){
			same=false;
			break;
		}
	}
	return same;
}
bool operator!=(bigNum a,bigNum b){
	int i;
	if(a.flag!=b.flag){
		return true;
	}
	for(i=0;i<MAX;i++){
		if(a[i]!=b[i]){
			return true;
		}
	}
	return false;
}
bigNum::bigNum(string input){
	int i,j=0;
	int temp;
	for(i=0;i<MAX;i++){
		num[i]=0;
	}
	for(i=input.length()-1;i>=0;i--){
		if(input[i]>='a'&&input[i]<='f'){
			temp=input[i]-'a'+10;
		}
		else{
			if(input[i]>='A'&&input[i]<='F'){
				temp=input[i]-'A'+10;
			}
			else{
				temp=input[i]-'0';
			}
		}
		if(temp/8){
			num[4*j+3]=1;
		}
		if((temp%8)/4){
			num[4*j+2]=1;
		}
		if((temp%4)/2){
			num[4*j+1]=1;
		}
		if(temp%2){
			num[4*j]=1;
		}
		j++;
	}
	flag=0;
}
bigNum::bigNum(int input)
{
	if(input>=0)flag=0;
	else flag=1;
	int i=0;
	while(input)
	{
		num[i]=input%2;
		input=input/2;
		i++;
	}
	for(;i<MAX;i++)num[i]=0;
}
bigNum operator+(bigNum a,bigNum b){
	bigNum result;
	int i;
	bool temp=0;
	if(a.flag==b.flag){
		for(i=0;i<MAX;i++){
			if(a[i]==0&&b[i]==0&&temp==0){
				result.make(i,0);
				temp=0;
			}
			else{
				if(a[i]==1&&b[i]==0&&temp==0||
					a[i]==0&&b[i]==1&&temp==0||
					a[i]==0&&b[i]==0&&temp==1){
						temp=0;
						result.make(i,1);
				}
				else{
					if(a[i]==1&&b[i]==1&&temp==0||
						a[i]==0&&b[i]==1&&temp==1||
						a[i]==1&&b[i]==0&&temp==1){
							temp=1;
							result.make(i,0);
					}
					else{
						if(a[i]==1&&b[i]==1&&temp==1){
							temp=1;
							result.make(i,1);
						}
					}
				}
			}
		}
		result.flag=a.flag;
	}
	if(a.flag==0&&b.flag==1){
		b.fu();
		return a-b;
	}
	if(a.flag==1&&b.flag==0){
		a.fu();
		return b-a;
	}
	if(temp){
		cout<<"Overflow"<<endl;
	}
	return result;
}
bigNum operator*(bigNum a,bigNum b){
	bigNum result;
	int i;
	bool first=true;
	for(i=0;i<MAX;i++){
		if(b[i]==1){
			result=result+a;
		}		
		a.moveLeft(1);
	}
	if(a.flag==b.flag){
		result.flag=0;
	}
	else{
		result.flag=1;
	}
	return result;
}
bigNum modMult(bigNum a,bigNum b,bigNum c)
{
	bigNum result;
	int i;
	bool first=true;
	for(i=0;i<MAX;i++){
		if(b[i]==1){
			result=result+a;
			while(result>c)
				result=result-c;
		}		
		a.moveLeft(1);
		while(a>c)
			a=a-c;
	}
	if(a.flag==b.flag){
		result.flag=0;
	}
	else{
		result.flag=1;
	}
	return result;
}
bool operator>(bigNum a,bigNum b){
	bool aBiger=0;
	int i;
	if(a.flag==0&&b.flag==1){
		aBiger=true;
		bool allZERO=true;
		for(i=0;i<MAX;i++){
			if(a[i]!=0||b[i]!=0){
				allZERO=false;
			}
		}
		if(allZERO){
			aBiger=false;
		}
	}
	else{
		if(a.flag==1&&b.flag==0){
			aBiger=false;
			bool allZERO=true;
			for(i=0;i<MAX;i++){
				if(a[i]!=0||b[i]!=0){
					allZERO=false;
				}
			}
			if(allZERO){
				aBiger=false;
			}
		}
		else{
			if(a.flag==0&&b.flag==0){
				for(i=MAX-1;i>=0;i--){
					if(a[i]==1&&b[i]==0){
						aBiger=true;
						break;
					}
					if(a[i]==0&&b[i]==1){
						aBiger=false;
						break;
					}
				}
			}
			else{
				for(i=MAX-1;i>=0;i--){
					if(a[i]==1&&b[i]==0){
						aBiger=false;
						break;
					}
					if(a[i]==0&&b[i]==1){
						aBiger=true;
						break;
					}
				}
			}
		}
	}	
	return aBiger;
}
bigNum operator-(bigNum a,bigNum b){
	bigNum result;
	int i;
	bool temp=0;
	if(a.flag==b.flag){
		if(!(b.abs()>a.abs())){
			for(i=0;i<MAX;i++){
				if(a[i]==0&&b[i]==0&&temp==0||
					a[i]==1&&b[i]==0&&temp==1||
					a[i]==1&&b[i]==1&&temp==0){
						result.make(i,0);
						temp=0;
				}
				else{
					if(a[i]==0&&b[i]==0&&temp==1||
						a[i]==0&&b[i]==1&&temp==0||
						a[i]==1&&b[i]==1&&temp==1){
							temp=1;
							result.make(i,1);
					}
					else{
						if(a[i]==0&&b[i]==1&&temp==1){
							temp=1;
							result.make(i,0);
						}
						else{
							if(a[i]==1&&b[i]==0&&temp==0){
								temp=0;
								result.make(i,1);
							}
						}
					}
				}
			}
			result.flag=a.flag;
		}
		else{			
			result=(b-a);
			result.flag=!a.flag;
		}
	}
	if(a.flag==0&&b.flag==1){
		b.fu();
		return a+b;
	}
	if(a.flag==1&&b.flag==0){
		b.fu();
		return a+b;
	}
	if(temp){
		cout<<"Overflow"<<endl;
	}
	return result;
}
bigNum operator/(bigNum a,bigNum b){
	bigNum count("0");
	if(a.flag==b.flag){
		count.flag=0;
	}
	else{
		count.flag=1;
	}
	int i,j;
	bigNum tempA=a,tempB=b,ZERO("0");
	if(ZERO>tempA){
		tempA.fu();
	}
	if(ZERO>tempB){
		tempB.fu();
	}
	for(j=MAX-1;j>=0;j--){
		if(b[j]){
			break;
		}
	}
	bigNum tempBB=tempB;
	for(i=MAX-j-1;i>=0;i--){
		tempBB=tempB;
		tempBB.moveLeft(i);
		if(!(tempBB>tempA)){
			count.make(i,1);
			tempA=tempA-tempBB;
		}
	}
	return count;
}
bigNum operator%(bigNum a,bigNum b){
	bigNum result;
	result=a-(a/b)*b;
	return result;
}
void bigNum::conversation(int a){
	int i;
	if(a>0){
		flag=0;
	}
	else{
		flag=1;
	}
	if(a<0){
		a=-a;
	}
	for(i=0;i<MAX;i++){
		num[i]=0;
	}
	for(i=0;i<MAX;i++){
		if(a%2){
			num[i]=1;
		}
		a=a/2;
		if(a==0){
			break;
		}
	}
}
bigNum bigNum::exp(bigNum b,bigNum c){        
	bigNum d("1");
	int i=MAX-1;
	while(!b[i]){
		i--;
	}
	int j;
	for(j=i;j>=0;j--){
		d=modMult(d,d,c);
		if(b[j]){
			d=modMult(d,(*this),c);
		}
	}
	return d;
}

bigNum gcd(bigNum f,bigNum d)        //-------�������������������
{
	bigNum t,ZERO("0");
	if(d==ZERO)
		return f;
	else
	{
		do{
			t=f%d;
			f=d;
			d=t;
		}while(!(t==ZERO));
		return f;
	}
}
bigNum bigNum::inverse(bigNum b)    //------��������Ԫ
{
	bigNum ZERO("0"),ONE("1");
	bigNum x1=ONE,x2=ZERO,x3=b;
	bigNum y1=ZERO,y2=ONE,y3=(*this);
	bigNum t1,t2,t3;
	if(y3==ONE){
		return ONE;
	}	
	bigNum q;
	bigNum g;	
	do{
		q=x3/y3;
		t1=x1-q*y1;
		t2=x2-q*y2;
		t3=x3-q*y3;
		x1=y1;
		x2=y2;
		x3=y3;
		y1=t1;
		y2=t2;
		y3=t3;
	}while(!(y3==ONE));
	g=y2;
	if(!(g>ZERO))
		g=b+g;
	return g;      //------������������Ԫ
}

void bigNum::moveLeft(int i){    //�����
	int k;
	for(k=MAX-1;k>i-1;k--){
		num[k]=num[k-i];
	}
	for(k=0;k<i;k++){
		num[k]=0;
	}
}
void bigNum::output(){
	if(this->flag==1){
		cout<<'-';
	}
	char result[MAX];
	int i;
	for(i=MAX-1;i>=0;i--){
		if((*this)[i]==1){
			break;
		}
	}
	i++;
	int k;
	int length=0;
	switch(i%4){
		case 1:
			length=i+3;
			break;
		case 2:
			length=i+2;
			break;
		case 3:
			length=i+1;
			break;
		case 0:
			length=i;
			break;
	}
	for(k=0;k<length;k=k+4){
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='0';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='1';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='2';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='3';
		}
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='4';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='5';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='6';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='7';
		}
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='8';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='9';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='A';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='B';
		}
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='C';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='D';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='E';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='F';
		}
	}
	if(i==0){
		cout<<'0'<<endl;
	}else{
		for(i=(k/4)-1;i>=0;i--){
			cout<<result[i];
		}
		cout<<endl;
	}
}	
void bigNum::random(int n)
{	
	flag=0;
	bigNum temp;
	for(int i=0;i<n;)
	{
		xn1=(aa*xn)%m;
		xn=xn1;
		temp=xn1;
		int tflag=32;
		while(temp[tflag]==false)tflag--;
		tflag++;
		for(int ii=0;ii<tflag;ii++)
		{
			num[i]=temp[ii];
			i++;
		}
	}
	for(int i=MAX-1;i>=n;i--)//��λ����
	{
		num[i]=false;
	}
//	num[n-1]=true;
	num[0]=true;
}
bool bigNum::isPrimeNumber()
{
	//�������������������
	bigNum temp=(*this);
	bigNum n=(*this);
	n.make(0,0);
	ifstream infile("longprime.txt");
	//longprime.txt���ŵ���С��100000������������ʣ�µĴ��������ѡȡ
	int primeNum;
	const bigNum ONE(1);
	int fb;
	for(fb=511;temp[fb]==false;fb--);
	//���Լ���	
	for(int i=0;i<5;i++)
	{
		int find=(int (rand()) % 1600)*6+i*9600;
		infile.seekg(find,ios::beg);
		infile>>primeNum;
		bigNum pNum(primeNum);
		bigNum d(1);
		for(int ii=fb;ii>-1;ii--)
		{
			bigNum x;
			x=d;
			d=(d*d)%temp;
			bool a1=(d==ONE);
			bool a2=(x!=ONE);
			bool a3=(x!=n);
			if(a1 && a2 && a3){return false;}
			if(n[ii]==true) d=(d * pNum) % temp;
		}
		if(d!=ONE){return false;}
	}
	infile.close();	
	return true;
}
void bigNum::outfile(ofstream &outfile)
{
	char result[MAX];
	int i;
	for(i=MAX-1;i>=0;i--){
		if((*this)[i]==1){
			break;
		}
	}
	i++;
	int k;
	int length=0;
	switch(i%4){
		case 1:
			length=i+3;
			break;
		case 2:
			length=i+2;
			break;
		case 3:
			length=i+1;
			break;
		case 0:
			length=i;
			break;
	}
	for(k=0;k<length;k=k+4){
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='0';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='1';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='2';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==0){
			result[k/4]='3';
		}
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='4';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='5';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='6';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==0){
			result[k/4]='7';
		}
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='8';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='9';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='A';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==0&&(*this)[k+3]==1){
			result[k/4]='B';
		}
		if((*this)[k]==0&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='C';
		}
		if((*this)[k]==1&&(*this)[k+1]==0&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='D';
		}
		if((*this)[k]==0&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='E';
		}
		if((*this)[k]==1&&(*this)[k+1]==1&&(*this)[k+2]==1&&(*this)[k+3]==1){
			result[k/4]='F';
		}
	}
	if(i==0){
		outfile<<'0'<<endl;
	}else{
		for(i=(k/4)-1;i>=0;i--){
			outfile<<result[i];
		}
		outfile<<endl;
	}
}
bool bigNum::isFirst=true;