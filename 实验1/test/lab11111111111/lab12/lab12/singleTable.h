#include<iostream>
using namespace std;
class single_table_element//��Ԫ��
{
public:
	char m;
	char c;
	bool flag = false;//����Ƶ�ʹ������û�
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
	int count = 0;
	p_character(char ch, double p1)
	{
		character = ch;
		count = p1;
	}
	p_character()
	{}
	p_character(int i)
	{
		character = 'A' + i;
	}
};
class word_count {//���ʼ�����
public:
	string word;
	int count = 0;
	//bool use = false;
};
class char_count {//��ĸ����&����
public:
	char ch;
	int count = 0;
};
p_word* setWordP() {
	p_word word[9];
	word[0].word = "THE";
	word[0].p = 4.65;
	word[1].word = "TO";
	word[1].p = 3.02;
	word[2].word = "OF";
	word[2].p = 2.61;
	word[3].word = "I";
	word[3].p = 2.2;
	word[4].word = "A";
	word[4].p = 1.95;
	word[5].word = "AND";
	word[5].p = 1.82;
	word[6].word = "IS";
	word[6].p = 1.68;
	word[7].word = "THAT";
	word[7].p = 1.62;
	word[8].word = "IN";
	word[8].p = 1.57;
	return word;
}
void swapWordP(vector<word_count> it,int i,int j) {
	word_count temp;
	temp.count = it[j].count;
	temp.word = it[j].word;
	it[j].count = it[i].count;
	it[j].word = it[i].word;
	it[i].count = temp.count;
	it[j].word = temp.word;

}
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