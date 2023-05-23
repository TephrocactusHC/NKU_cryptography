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
	string mstring_input;//加密时输入的明文字符串
	string cstring_input;//解密时输入的密文字符串
	int offset;

	cout << "**************************************"<<endl;
	cout << "               加密过程               "<<endl;
	cout << "**************************************"<<endl;
	cout << "请输入明文字符串：\n";
	getline(cin, mstring_input);
	cout << "**************************************"<<endl;
	cout << "请输入秘钥（明文右移位数）：\n";
	cin >> offset;
	cout << "**************************************"<<endl;

	//使用STL中的vector，便于后续操作
	
	//加密过程明文向量指针enc_plaintext
	vector<char> * enc_plaintext = new vector<char> (mstring_input.begin(), mstring_input.end());

	//加密过程密文向量指针enc_ciphertext
	vector<char> * enc_ciphertext;

	//移位加密
	enc_ciphertext=shift_encrypt(enc_plaintext, offset);
	
	//输出加密后的密文
	cout << "加密结果：\n";
	for(int i = 0; i < (*enc_ciphertext).size(); i++) 
	{
		cout<<(*enc_ciphertext)[i];
	}
	cout<<endl;
	cout << "--------------------------------------"<<endl;

	cout << "**************************************"<<endl;
	cout << "               解密过程               "<<endl;
	cout << "**************************************"<<endl;
	cout << "请输入密文字符串：\n";
	//防止之前的cin输入造成影响
	cin.ignore();
	getline(cin, cstring_input);
	cout << "**************************************"<<endl;
	cout << "请输入秘钥（明文右移位数）：\n";
	cin >> offset;
	cout << "**************************************"<<endl;
	//使用STL中的vector，便于后续操作
	
	//解密过程密文向量指针dec_ciphertext
	vector<char> * dec_ciphertext = new vector<char> (cstring_input.begin(), cstring_input.end());

	//解密过程明文向量指针dec_plaintext
	vector<char> * dec_plaintext;

	//移位加密
	dec_plaintext=shift_decrypt(dec_ciphertext, offset);

	//输出解密后的明文
	cout << "解密结果：\n";
	for(int i = 0; i < (*dec_plaintext).size(); i++) 
	{
		cout<<(*dec_plaintext)[i];
	}
	cout<<endl<<endl;

	system("pause");
	return 0;
}

