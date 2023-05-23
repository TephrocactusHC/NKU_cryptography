#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <algorithm>
using namespace std;

//���ܹ��̣������û���rpltbl_vector������plaintext���м���
vector<char>* encrypt(vector<char>* plaintext, vector<char>* rpltbl_vector)
{
	vector<char> * ciphertext= new vector<char>;

	for(int i = 0; i < (*plaintext).size(); i++)
	{
		//Сд��ĸ
		if((*plaintext)[i]>= 97 && (*plaintext)[i]<= 122)
		{
			(* ciphertext).push_back(  (*rpltbl_vector) [((*plaintext)[i]-97)]  );
			continue;
		}

		//��д��ĸ
		if((*plaintext)[i]>= 65 && (*plaintext)[i]<= 90)
		{
			(* ciphertext).push_back(   (*rpltbl_vector)[(*plaintext)[i]-65] - 32  );
			continue;
		}

		//����ĸ���ݣ�Ĭ�ϲ�����
		(* ciphertext).push_back((*plaintext)[i]);

	}
	return ciphertext;
}

//���ܹ��̣������û���rpltbl_vector������ciphertext���н���
vector<char>* decrypt(vector<char>* ciphertext, vector<char>* rpltbl_vector)
{
	vector<char> * plaintext= new vector<char>;

	vector<char>::iterator result;

	vector<char>::iterator first = (*rpltbl_vector).begin();

	for(int i = 0; i < (*ciphertext).size(); i++)
	{
		//Сд��ĸ
		if((*ciphertext)[i]>= 97 && (*ciphertext)[i]<= 122)
		{
			// ��*rpltbl_vector �� ����ֵΪ (*ciphertext)[i]����һ����±�
			result = find((*rpltbl_vector).begin(),(*rpltbl_vector).end(),(*ciphertext)[i]);

			//ʹ��distance���ݵ�������������±�
			(*plaintext).push_back(  (char) ( 97+ distance(first,result) )  );

			continue;
		}

		//��д��ĸ
		if((*ciphertext)[i]>= 65 && (*ciphertext)[i]<= 90)
		{
			// ��*rpltbl_vector �� ����ֵΪ (*ciphertext)[i]+32����һ����±�
			result = find((*rpltbl_vector).begin(),(*rpltbl_vector).end(),((*ciphertext)[i]+32) );

			//ʹ��distance���ݵ�������������±�
			(*plaintext).push_back(  (char) ( 65+ distance(first,result) )  );

			continue;
		}

		//����ĸ���ݣ�Ĭ�ϲ�����
		(* plaintext).push_back((*ciphertext)[i]);

	}
	return plaintext;
}




//�����û������ַ��������û���
vector<char>*  mk_replace_tbl(vector<char>* mktbl_vector)
{
	vector<char> * rpltbl_vector= new vector<char>;

	//���ڴ洢��Щ��ĸ�������ַ���������
	//0����δ������
	int flag[26]={0};

	for (int i = 0; i < (*mktbl_vector).size(); i++)
	{
		//��д��ĸתΪСд
		if ((*mktbl_vector)[i] >= 65 && (*mktbl_vector)[i] <= 90) 
		{
			(*mktbl_vector)[i] += 32;
		}

		//(*mktbl_vector)[i]����ĸ
		if ( (*mktbl_vector)[i] >= 97 && (*mktbl_vector)[i] <= 122 )
		{
			//����(*mktbl_vector)[i]�Ƿ���*rpltbl_vector��
			vector<char>::iterator result = find((*rpltbl_vector).begin(),(*rpltbl_vector).end(),(*mktbl_vector)[i]);
			
			//�������*rpltbl_vector�еĻ�
			if(result==(*rpltbl_vector).end())
			{
				//���뵽rpltbl_vector������
				(* rpltbl_vector).push_back((*mktbl_vector)[i]);

				//����flag��
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
	string string_mktbl;//�����û���ʱ������ַ���
	string mstring_input;//���ܹ����û�����������ַ���
	string cstring_input;//���ܹ����û�����������ַ���

	cout << "****************************************************************************"<<endl;
	cout << "                                �����û�����                               "<<endl;
	cout << "****************************************************************************"<<endl;
	cout << "���������ڹ����û�����ַ�����\n";
	getline(cin, string_mktbl);
	cout << "****************************************************************************"<<endl;
	//�����û�����ʹ�õ�����ָ��crk_ciphertext
	vector<char> * mktbl_vector= new vector<char> (string_mktbl.begin(), string_mktbl.end());

	//�洢�û��������ָ��rpltbl_vector
	vector<char> * rpltbl_vector= new vector<char>;

	rpltbl_vector = mk_replace_tbl(mktbl_vector);

	cout << "�û���Ϊ��\n";

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
	cout << "                                  ���ܹ���                                  "<<endl;
	cout << "****************************************************************************"<<endl;
	cout << "�����������ַ�����\n";
	getline(cin,cstring_input);
	cout << "****************************************************************************"<<endl;
	cout << "���ܽ��Ϊ��\n";

	//�洢���ܹ��̵�����
	vector<char> * dec_ciphertext= new vector<char> (cstring_input.begin(), cstring_input.end()) ;

	//�洢���ܹ��̵�����
	vector<char> * dec_plaintext= new vector<char>;

	//����
	dec_plaintext = decrypt(dec_ciphertext, rpltbl_vector);

	//������ܽ��
	for(int i = 0; i < (*dec_plaintext).size(); i++) 
	{
		cout<<(*dec_plaintext)[i];
	}
	cout<<endl;
	cout << "****************************************************************************"<<endl;

	system("pause");

	return 0;
}
