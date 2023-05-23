#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

//移位加密
vector<char> * shift_encrypt(vector<char> * plaintext, int offset)
{
	int real_offset = offset % 26;

	//密文向量指针
	vector<char>* ciphertext = new vector<char>;

	for (int i = 0; i < (*plaintext).size(); i++)
	{
		if ((*plaintext)[i] >= 65 && (*plaintext)[i] <= 90)
		{
			int temp = (*plaintext)[i] + real_offset;
			if (temp > 90)
				temp -= 26;
			(* ciphertext).push_back((char)temp);
			continue;
		}

		if ((*plaintext)[i] >= 97 && (*plaintext)[i] <= 122)
		{
			//这里temp不能定义为char，因为char型变量超过128时会自动取补码，造成异常字符
			int temp = (*plaintext)[i] + real_offset;	
			if (temp >122)
				temp -= 26;
			(* ciphertext).push_back((char)temp);
			continue;
		}

		//非字母内容，默认不加密
		(* ciphertext).push_back((*plaintext)[i]);

	}
	return ciphertext;
}

//移位解密
vector<char> * shift_decrypt(vector<char> * ciphertext, int offset)
{
	int real_offset = offset % 26;

	//明文向量指针
	vector<char>* plaintext = new vector<char>;

	for (int i = 0; i < (*ciphertext).size(); i++)
	{
		if ((*ciphertext)[i] >= 65 && (*ciphertext)[i] <= 90)
		{
			int temp = (*ciphertext)[i] - real_offset;
			if (temp < 65)
				temp += 26;
			(* plaintext).push_back((char)temp);
			continue;
		}

		if ((*ciphertext)[i] >= 97 && (*ciphertext)[i] <= 122)
		{
			int temp = (*ciphertext)[i] - real_offset;
			if (temp < 97)
				temp += 26;
			(* plaintext).push_back((char)temp);
			continue;
		}
		//非字母内容，默认不解密
		(* plaintext).push_back((*ciphertext)[i]);

	}
	return plaintext;
}




int main()
{
	string cstring_crack;//破解时输入的密文字符串
	int offset=0;
	
	cout << "**************************************"<<endl;
	cout << "               破解过程               "<<endl;
	cout << "**************************************"<<endl;
	cout << "请输入要破解的密文字符串：\n";
	getline(cin, cstring_crack);
	cout << "**************************************"<<endl;
	cout << "暴力破解过程：\n";

	//破解过程密文向量指针crk_ciphertext
	vector<char> * crk_ciphertext = new vector<char> (cstring_crack.begin(), cstring_crack.end());

	//破解过程明文向量指针crk_plaintext
	vector<char> * crk_plaintext = new vector<char>;

	for(;offset<=25;offset++ )
	{
		cout << "如果移位位数为"<<offset<<"，则明文为：";

		crk_plaintext=shift_decrypt(crk_ciphertext, offset);
		
		for(int i = 0; i < (*crk_plaintext).size(); i++) 
		{
			cout<<(*crk_plaintext)[i];
		}
		cout<<endl;
	}

	system("pause");
	return 0;
}

