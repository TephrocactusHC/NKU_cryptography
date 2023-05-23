#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
using namespace std;

//��λ����
vector<char> * shift_encrypt(vector<char> * plaintext, int offset)
{
	int real_offset = offset % 26;

	//��������ָ��
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
			//����temp���ܶ���Ϊchar����Ϊchar�ͱ�������128ʱ���Զ�ȡ���룬����쳣�ַ�
			int temp = (*plaintext)[i] + real_offset;	
			if (temp >122)
				temp -= 26;
			(* ciphertext).push_back((char)temp);
			continue;
		}

		//����ĸ���ݣ�Ĭ�ϲ�����
		(* ciphertext).push_back((*plaintext)[i]);

	}
	return ciphertext;
}

//��λ����
vector<char> * shift_decrypt(vector<char> * ciphertext, int offset)
{
	int real_offset = offset % 26;

	//��������ָ��
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
		//����ĸ���ݣ�Ĭ�ϲ�����
		(* plaintext).push_back((*ciphertext)[i]);

	}
	return plaintext;
}




int main()
{
	string cstring_crack;//�ƽ�ʱ����������ַ���
	int offset=0;
	
	cout << "**************************************"<<endl;
	cout << "               �ƽ����               "<<endl;
	cout << "**************************************"<<endl;
	cout << "������Ҫ�ƽ�������ַ�����\n";
	getline(cin, cstring_crack);
	cout << "**************************************"<<endl;
	cout << "�����ƽ���̣�\n";

	//�ƽ������������ָ��crk_ciphertext
	vector<char> * crk_ciphertext = new vector<char> (cstring_crack.begin(), cstring_crack.end());

	//�ƽ������������ָ��crk_plaintext
	vector<char> * crk_plaintext = new vector<char>;

	for(;offset<=25;offset++ )
	{
		cout << "�����λλ��Ϊ"<<offset<<"��������Ϊ��";

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

