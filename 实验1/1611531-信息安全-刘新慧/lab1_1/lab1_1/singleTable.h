#include<iostream>
using namespace std;
class single_table_element//��Ԫ��
{
public:
	char m;
	char c;
	bool flag ;//����Ƶ�ʹ������û�
	single_table_element(){
		flag=false;
	}
};
class single_table {//�û���
public:
	single_table_element table[26];
	single_table() 
	{
		for (int i = 0; i < 26; i++)
		{
			table[i].m = 'A' + i;
			table[i].c = table[i].m;
		}
	}
	single_table(int i)
	{
		for (int i = 0; i < 26; i++)
			table[i].c = 'a' + i;
	}
};
class p_word {//����Ƶ�ʹ��� ���浥��Ƶ��&���浥�ʶ�
public:
	string word;
	string connectstr;
	double p;
	bool use;
	p_word(string str, double p1)
	{
		word.append(str);
		p = p1;
		use = false;
	}
	p_word()
	{
		use = false;
	}
};
class p_character {//��ĸƵ�ʹ��� ������
public:
	char character;
	//char connectchar;
	int count;
	p_character(char ch, double p1)
	{
		character = ch;
		count = p1;
	}
	p_character()
	{
		count=0;
	}
	p_character(int i)
	{
		character = 'A' + i;
		count=0;
	}
};
class word_count {//���ʼ�����
public:
	string word;
	int count ;
	//bool use = false;
	word_count(){
		count=0;
	}
};
class char_count {//��ĸ����&����
public:
	char ch;
	int count ;
	char_count(){
		count=0;
	}
};

bool isFull(p_word w[], int len)//�õ�����Ƶ�ʽ�������ʱ���жϺ���
{
	bool flag = true;
	for (int i = 0; i < len; i++)
	{
		if (!w[i].use)
			flag = false;
	}
	return flag;
}