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
	string mstring_input;//����ʱ����������ַ���
	string cstring_input;//����ʱ����������ַ���
	int offset;

	cout << "**************************************"<<endl;
	cout << "               ���ܹ���               "<<endl;
	cout << "**************************************"<<endl;
	cout << "�����������ַ�����\n";
	getline(cin, mstring_input);
	cout << "**************************************"<<endl;
	cout << "��������Կ����������λ������\n";
	cin >> offset;
	cout << "**************************************"<<endl;

	//ʹ��STL�е�vector�����ں�������
	
	//���ܹ�����������ָ��enc_plaintext
	vector<char> * enc_plaintext = new vector<char> (mstring_input.begin(), mstring_input.end());

	//���ܹ�����������ָ��enc_ciphertext
	vector<char> * enc_ciphertext;

	//��λ����
	enc_ciphertext=shift_encrypt(enc_plaintext, offset);
	
	//������ܺ������
	cout << "���ܽ����\n";
	for(int i = 0; i < (*enc_ciphertext).size(); i++) 
	{
		cout<<(*enc_ciphertext)[i];
	}
	cout<<endl;
	cout << "--------------------------------------"<<endl;

	cout << "**************************************"<<endl;
	cout << "               ���ܹ���               "<<endl;
	cout << "**************************************"<<endl;
	cout << "�����������ַ�����\n";
	//��ֹ֮ǰ��cin�������Ӱ��
	cin.ignore();
	getline(cin, cstring_input);
	cout << "**************************************"<<endl;
	cout << "��������Կ����������λ������\n";
	cin >> offset;
	cout << "**************************************"<<endl;
	//ʹ��STL�е�vector�����ں�������
	
	//���ܹ�����������ָ��dec_ciphertext
	vector<char> * dec_ciphertext = new vector<char> (cstring_input.begin(), cstring_input.end());

	//���ܹ�����������ָ��dec_plaintext
	vector<char> * dec_plaintext;

	//��λ����
	dec_plaintext=shift_decrypt(dec_ciphertext, offset);

	//������ܺ������
	cout << "���ܽ����\n";
	for(int i = 0; i < (*dec_plaintext).size(); i++) 
	{
		cout<<(*dec_plaintext)[i];
	}
	cout<<endl<<endl;

	system("pause");
	return 0;
}

