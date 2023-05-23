#include<iostream>
using namespace std;
//显示功能，进行选择
void show(){
	cout<<"  ---------------------古典密码算法及攻击方法--------------------  "<<endl;
	cout<<"  |                                                             | "<<endl;
	cout<<"  |              移位密码： 1.加密   2.解密   3.攻击            | "<<endl;
	cout<<"  |                                                             | "<<endl;
	cout<<"  |          单表置换密码： 4.加密   5.解密   6.攻击            | "<<endl;
	cout<<"  |                                                             | "<<endl;
	cout<<"  --------------------------------------------------------------  "<<endl;
	cout<<"请输入您要进行的操作1-6：（输入0退出）"<<endl;
}
//title
void init(int i){
	if(i==0){
		cout<<endl;
		cout<<"     --------------------------移位密码加密--------------------------    "<<endl;
		cout<<endl;
		cout<<"请输入要进行加密的明文（不分大小写）:"<<endl;
	}
	if(i==1){
		cout<<endl;
		cout<<"     --------------------------移位密码攻击--------------------------    "<<endl;
		cout<<endl;
		cout<<"请输入要进行攻击的密文（不分大小写）:"<<endl;
	}
	if(i==2){
		cout<<endl;
		cout<<"     --------------------------移位密码解密--------------------------    "<<endl;
		cout<<endl;
		cout<<"请输入要进行解密的密文（不分大小写）:"<<endl;
	}
	if(i==3){
		cout<<endl;
		cout<<"     ------------------------单表置换密码加密------------------------    "<<endl;
		cout<<endl;
		cout<<"请输入要进行加密的明文（不分大小写）:"<<endl;
	}
	if (i == 4) {
		cout << endl;
		cout << "     ------------------------单表置换密码解密------------------------    " << endl;
		cout << endl;
		cout << "请输入要进行解密的密文（不分大小写）:" << endl;
	}
	if (i == 5) {
		cout << endl;
		cout << "     ------------------------单表置换密码攻击------------------------    " << endl;
		cout << endl;
		cout << "请输入要进行攻击的密文（不分大小写）:" << endl;
	}

}
//输入提示
void output1(int i,string str){

	if(i==1){
		cout<<"明文为："<<endl;
		cout<<str<<endl;
		cout<<"请输入密钥："<<endl;
	}
	if(i==2){
		cout<<"加密后的密文为"<<endl;
		cout<<str<<endl;
	}
	if(i==3){
		cout<<"要解密的密文为："<<endl;
		cout<<str<<endl;
		cout<<"请输入密钥："<<endl;
	}
	if(i==4){
		cout<<"解密后的明文为"<<endl;
		cout<<str<<endl;
	}

}

