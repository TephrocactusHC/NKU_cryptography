#include<iostream>
using namespace std;
class single_table_element//表元素
{
public:
	char m;
	char c;
	bool flag ;//用于频率攻击的置换
	single_table_element(){
		flag=false;
	}
};
class single_table {//置换表
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
class p_word {//单词频率攻击 保存单词频率&保存单词对
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
class p_character {//字母频率攻击 排序类
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
class word_count {//单词计数表
public:
	string word;
	int count ;
	//bool use = false;
	word_count(){
		count=0;
	}
};
class char_count {//字母计数&排序
public:
	char ch;
	int count ;
	char_count(){
		count=0;
	}
};

bool isFull(p_word w[], int len)//得到单词频率解密明文时的判断函数
{
	bool flag = true;
	for (int i = 0; i < len; i++)
	{
		if (!w[i].use)
			flag = false;
	}
	return flag;
}