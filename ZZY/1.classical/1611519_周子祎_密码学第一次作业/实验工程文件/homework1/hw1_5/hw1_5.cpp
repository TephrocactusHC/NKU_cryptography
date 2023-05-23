#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <algorithm>
using namespace std;

//加密过程：根据置换表rpltbl_vector对明文plaintext进行加密
vector<char>* encrypt(vector<char>* plaintext, vector<char>* rpltbl_vector)
{
	vector<char> * ciphertext= new vector<char>;

	for(int i = 0; i < (*plaintext).size(); i++)
	{
		//小写字母
		if((*plaintext)[i]>= 97 && (*plaintext)[i]<= 122)
		{
			(* ciphertext).push_back(  (*rpltbl_vector) [((*plaintext)[i]-97)]  );
			continue;
		}

		//大写字母
		if((*plaintext)[i]>= 65 && (*plaintext)[i]<= 90)
		{
			(* ciphertext).push_back(   (*rpltbl_vector)[(*plaintext)[i]-65] - 32  );
			continue;
		}

		//非字母内容，默认不加密
		(* ciphertext).push_back((*plaintext)[i]);

	}
	return ciphertext;
}

//解密过程：根据置换表rpltbl_vector对密文ciphertext进行解密
vector<char>* decrypt(vector<char>* ciphertext, vector<char>* rpltbl_vector)
{
	vector<char> * plaintext= new vector<char>;

	vector<char>::iterator result;

	vector<char>::iterator first = (*rpltbl_vector).begin();

	for(int i = 0; i < (*ciphertext).size(); i++)
	{
		//小写字母
		if((*ciphertext)[i]>= 97 && (*ciphertext)[i]<= 122)
		{
			// 在*rpltbl_vector 中 查找值为 (*ciphertext)[i]的那一项的下标
			result = find((*rpltbl_vector).begin(),(*rpltbl_vector).end(),(*ciphertext)[i]);

			//使用distance根据迭代器获得数组下标
			(*plaintext).push_back(  (char) ( 97+ distance(first,result) )  );

			continue;
		}

		//大写字母
		if((*ciphertext)[i]>= 65 && (*ciphertext)[i]<= 90)
		{
			// 在*rpltbl_vector 中 查找值为 (*ciphertext)[i]+32的那一项的下标
			result = find((*rpltbl_vector).begin(),(*rpltbl_vector).end(),((*ciphertext)[i]+32) );

			//使用distance根据迭代器获得数组下标
			(*plaintext).push_back(  (char) ( 65+ distance(first,result) )  );

			continue;
		}

		//非字母内容，默认不解密
		(* plaintext).push_back((*ciphertext)[i]);

	}
	return plaintext;
}




//根据用户输入字符串构造置换表
vector<char>*  mk_replace_tbl(vector<char>* mktbl_vector)
{
	vector<char> * rpltbl_vector= new vector<char>;

	//用于存储哪些字母被输入字符串所包含
	//0代表未被包含
	int flag[26]={0};

	for (int i = 0; i < (*mktbl_vector).size(); i++)
	{
		//大写字母转为小写
		if ((*mktbl_vector)[i] >= 65 && (*mktbl_vector)[i] <= 90) 
		{
			(*mktbl_vector)[i] += 32;
		}

		//(*mktbl_vector)[i]是字母
		if ( (*mktbl_vector)[i] >= 97 && (*mktbl_vector)[i] <= 122 )
		{
			//查找(*mktbl_vector)[i]是否在*rpltbl_vector中
			vector<char>::iterator result = find((*rpltbl_vector).begin(),(*rpltbl_vector).end(),(*mktbl_vector)[i]);
			
			//如果不在*rpltbl_vector中的话
			if(result==(*rpltbl_vector).end())
			{
				//插入到rpltbl_vector向量中
				(* rpltbl_vector).push_back((*mktbl_vector)[i]);

				//更新flag表
				flag[(*mktbl_vector)[i]-97]=1;
			}
		}
	}

	for(int i=0;i<26;i++)
	{
		if(flag[i]==0)
			(* rpltbl_vector).push_back((char)(i+97));
	}
	return rpltbl_vector;
}

int main()
{
	string string_mktbl;//构造置换表时输入的字符串
	string mstring_input;//加密过程用户输入的明文字符串
	string cstring_input;//解密过程用户输入的密文字符串

	cout << "****************************************************************************"<<endl;
	cout << "                                单表置换加密                               "<<endl;
	cout << "****************************************************************************"<<endl;
	cout << "请输入用于构造置换表的字符串：\n";
	getline(cin, string_mktbl);
	cout << "****************************************************************************"<<endl;
	//构造置换表所使用的向量指针crk_ciphertext
	vector<char> * mktbl_vector= new vector<char> (string_mktbl.begin(), string_mktbl.end());

	//存储置换表的向量指针rpltbl_vector
	vector<char> * rpltbl_vector= new vector<char>;

	rpltbl_vector = mk_replace_tbl(mktbl_vector);

	cout << "置换表为：\n";

	for(int i = 0; i < (*rpltbl_vector).size(); i++) 
	{
		cout<<(char)(97+i)<<" ";
	}
	cout<<endl;

	for(int i = 0; i < (*rpltbl_vector).size(); i++) 
	{
		cout<<(*rpltbl_vector)[i]<<" ";
	}
	cout<<endl;
	cout << "****************************************************************************"<<endl;
	cout << "----------------------------------------------------------------------------"<<endl;
	cout << "****************************************************************************"<<endl;
	cout << "                                  解密过程                                  "<<endl;
	cout << "****************************************************************************"<<endl;
	cout << "请输入密文字符串：\n";
	getline(cin,cstring_input);
	cout << "****************************************************************************"<<endl;
	cout << "解密结果为：\n";

	//存储解密过程的密文
	vector<char> * dec_ciphertext= new vector<char> (cstring_input.begin(), cstring_input.end()) ;

	//存储解密过程的明文
	vector<char> * dec_plaintext= new vector<char>;

	//解密
	dec_plaintext = decrypt(dec_ciphertext, rpltbl_vector);

	//输出解密结果
	for(int i = 0; i < (*dec_plaintext).size(); i++) 
	{
		cout<<(*dec_plaintext)[i];
	}
	cout<<endl;
	cout << "****************************************************************************"<<endl;

	system("pause");

	return 0;
}
