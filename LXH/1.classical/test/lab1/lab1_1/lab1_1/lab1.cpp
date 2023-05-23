#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<fstream>
#include <cstdlib> 
#include "paint.h"
#include "singleTable.h"
using namespace std;

//移位密码
string encry1(string str, int k) {
	int i, c;
	for (i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			str[i] = str[i];
			continue;
		}
		c = str[i] - 'a';
		c = (c + k) % 26;
		str[i] = 'a' + c;
	}
	return str;
}
string decry1(string str, int k) {
	int i, c;
	for (i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			str[i] = str[i];
			continue;
		}
		c = str[i] - 'a';
		c = c - k;
		if (c < 0)
			c += 26;
		str[i] = 'a' + c;
	}
	return str;
}
string trans(string str) {
	int i;
	for (i = 0; i < str.length(); i++) {
		if (str[i] <= 'z'&&str[i] >= 'a')
			str[i] = str[i];
		else if (str[i] <= 'Z'&&str[i] >= 'A')
			str[i] = str[i] - 'A' + 'a';
	}
	return str;

}
//移位密码加密
string firstEncry() {
	init(0);
	int key;
	string inputStr;
	getline(cin, inputStr);
	string plainText = trans(inputStr);
	output1(1, plainText);
	cin >> key;
	string encryStr = encry1(plainText, key);
	output1(2, encryStr);
	return encryStr;
}
//移位密码解密
string firstDecry() {
	init(2);
	int key;
	string inputStr;
	getline(cin, inputStr);
	string cipherText = trans(inputStr);
	output1(3, cipherText);
	cin >> key;
	string decryStr = decry1(cipherText, key);
	output1(4, decryStr);
	return decryStr;
}
//移位密码攻击
void firstAttack() {
	init(1);
	int i;
	string inputStr;
	getline(cin, inputStr);
	string cipherText = trans(inputStr);
	cout << "要进行攻击的密文为" << endl;
	cout << cipherText << endl;

	for (int i = 1; i < 26; i++) {
		string decryString = decry1(cipherText, i);
		cout << "当密钥为" << i << "时，解密出的明文为：" << decryString << endl;
	}
	cout << "从中选择最合适的密钥：" << endl;
	int result;
	cin >> result;
	cout << "您选择的结果为：" << decry1(cipherText, result) << endl;
}
//单表置换密码
//构造置换表
string getkey(string key) {
	string keys;
	int i, j;
	key = trans(key);
	for (i = 0; i < key.length(); i++) {
		bool temp = true;
		if (key[i] >= 'a'&&key[i] <= 'z') {
			for (j = 0; j < keys.length(); j++) {
				if (keys[j] == key[i]) {
					temp = false;
					break;
				}
			}
			if (temp)
				keys += key[i];
		}
	}
	int len = keys.length();

	char t;
	for (i = 0; i < 26; i++) {
		bool tmp = true;
		t = 'a' + i;
		for (j = 0; j < len; j++) {
			if (keys[j] == t) {
				tmp = false;
				break;
			}
		}
		if (tmp)
			keys += t;
	}
	return keys;
}
//排序方式
int cmp1(const void *a, const void *b)//排序 character
{
	return ((p_character*)b)->count - ((p_character*)a)->count;
}
int cmp2(const void *a, const void *b)//单词 按次数从大到小排列
{
	return ((word_count*)b)->count - ((word_count*)a)->count;
}
string encry2(string str, string keys, single_table entable) {

	int i = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a'&&str[i] <= 'z')
		{
			str[i] = entable.table[str[i] - 'a'].c;
		}
		else
			str[i] = str[i];
	}
	return str;
}
string decry2(string str, string keys, single_table entable) {
	int k;
	int i, j;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'a'&&str[i] <= 'z')
		{
			//for (j = 0; entable.table[j].c == str[i]; j++) {}
			for (j = 0; j < 26; j++) {
				if (entable.table[j].c == str[i]) {
					k = j;
					break;
				}
			}
			//str[i] = entable.table[j].m;
			str[i] = entable.table[k].m;
		}
		else
			str[i] = str[i];
	}
	return str;
}
//字母频率攻击
single_table letterAttack(single_table tableAttack, char pletter[]) {
	string results;
	p_character letter[26];
	for (int i = 0; i < 26; i++)
		letter[i] = p_character(i);

	ifstream file;
	file.open("input.txt");
	char s;
	while (!file.eof())
	{
		file >> s;
		if (s >= 'A'&&s <= 'Z')
			letter[s - 'A'].count++;
	}
	qsort(letter, 26, sizeof(p_character), cmp1);
	for (int i = 0; i < 26; i++)//character
	{
		tableAttack.table[pletter[i] - 'a'].m = pletter[i] - 'a' + 'A';
		tableAttack.table[pletter[i] - 'a'].c = letter[i].character;
	}

	cout << endl << " -------------------------字母词数统计表------------------------ " << endl<<endl;
	for (int i = 0; i < 26; i++) {
		cout << letter[i].character << " --- " << letter[i].count ;
		if (i % 4 == 3) {
			cout << endl;
			continue;
		}
		if (letter[i].count < 10)
			cout << "   |  ";
		else
			cout << "  |  ";

	}
	cout << endl;
	cout << endl<<" -------------------------字母近似对照表------------------------ " <<endl<< endl;
	for (int i = 0; i < 26; i++)
	{
		cout << tableAttack.table[i].m << " --- " << tableAttack.table[i].c << "		";
		if (i % 4 ==3)
			cout << endl;
	}
	cout << endl;
	cout <<endl<< " ------------------------字母频率攻击结果----------------------- " << endl<<endl;
	ifstream file2;
	ofstream file3;
	file3.open("output.txt",ios::out);
	file2.open("input.txt");
	while (!file2.eof())
	{
		file2 >> results;
		for (int i = 0; i < results.length(); i++)
			for (int k = 0; k < 26; k++)
			{
				if (results[i] == tableAttack.table[k].c)
				{
					cout << tableAttack.table[k].m;
					file3<< tableAttack.table[k].m;
				}
			}
		cout << " ";
		file3 << " ";
	}
	file3.close();
	return tableAttack;
}
//单词频率攻击
single_table wordAttack(single_table tableAttack, p_word word[]) {
	vector<word_count> it;
	ifstream file;
	file.open("input.txt");
	string s;
	word_count temp;

	//读取文件进行单词计数
	while (!file.eof())
	{
		file >> s;
		if ((s.length() > 0) && (s.length() < 5))
		{
			if (it.size() == 0)
			{
				temp.word = s;
				temp.count = 1;
				it.push_back(temp);
			}
			else
			{
				bool flag = false;
				for (int i = 0; i < it.size(); i++)
				{
					if (it[i].word == s)
					{
						it[i].count++;
						flag = true;
					}
				}
				if (!flag)
				{
					temp.word = s;
					temp.count = 1;
					it.push_back(temp);
				}
			}
		}

	}
	file.close();
	qsort(&it[0], it.size(), sizeof(word_count), cmp2);
	//sortWord(it);
	cout << endl << " -------------------------单词次数统计表------------------------ " << endl << endl;
	for (int i = 0; i < it.size(); i++)
	{
		cout << it[i].word << "\t" << it[i].count << "\t";
		if (i % 4 == 3)
			cout << endl;
	}
	cout << endl;
	int num;
	while ((!isFull(word, 9)))
	{
		num = 0;
		while (num != it.size())
		{
			for (int i = 0; i < 9; i++)
			{
				if ((it[num].word.length() == word[i].word.length()) && (!word[i].use))
				{
					word[i].use = true;
					word[i].connectstr = it[num].word;
					break;
				}
			}
			num++;
		}
	}
	cout << endl << " -------------------------单词近似对照表------------------------ " << endl << endl;
	for (int i = 0; i < 9; i++)
	{
		if (word[i].use)
			cout << word[i].word << "\t" << word[i].connectstr << endl;
		else
			cout << word[i].word << endl;
	}
	for (int i = 0; i < 9; i++)//word
	{
		for (int k = 0; k < word[8 - i].word.length(); k++)
		{
			tableAttack.table[word[8 - i].word[k] - 'A'].m = word[8 - i].word[k];
			tableAttack.table[word[8 - i].word[k] - 'A'].c = word[8 - i].connectstr[k];
			for (int j = 0; j < 26; j++)
			{
				if (tableAttack.table[j].c == word[8 - i].connectstr[k])
					tableAttack.table[j].flag = false;
			}
			tableAttack.table[word[8 - i].word[k] - 'A'].flag = true;
		}
	}

	cout << endl << " ----------------------单词统计频率攻击结果--------------------- " << endl << endl;
	ifstream file3;
	file3.open("input.txt");
	string results;
	while (!file3.eof())
	{
		file3 >> results;
		for (int i = 0; i < results.length(); i++)
		{
			bool judge = false;
			for (int k = 0; k < 26; k++)
			{
				if (results[i] == tableAttack.table[k].c&&tableAttack.table[k].flag)
				{
					cout << tableAttack.table[k].m;
					judge = true;
				}
			}
			if (!judge)
				cout << results[i];
		}
		cout << " ";
	}
	cout << endl;
	return tableAttack;
}

//交换置换表中的两个字母的对应关系
single_table changeFun(single_table attacktable,char a,char b) {
	char temp = attacktable.table[b - 'a'].c;
	char temp2= attacktable.table[a- 'a'].c;
	attacktable.table[b-'a'].c =temp2;
	attacktable.table[a - 'a'].c = temp;
	return attacktable;
}


//单表置换密码加密
string secondEncry()
{
	init(3);
	string key, inputStr;
	single_table entable;
	getline(cin, inputStr);
	string plainText = trans(inputStr);
	output1(1, plainText);
	getline(cin, key);
	string keys = getkey(key);
	int length = keys.length();
	for (int i = 0; i < length; i++)
		entable.table[i].c = keys[i];
	string encryStr = encry2(plainText, keys, entable);
	output1(2, encryStr);
	return encryStr;
}

//单表置换密码解密
string secondDecry()
{
	init(4);
	string key, inputStr;
	single_table detable;
	getline(cin, inputStr);
	string cipherText = trans(inputStr);
	output1(3, cipherText);
	getline(cin, key);
	string keys = getkey(key);
	int length = keys.length();
	for (int i = 0; i < length; i++)
		detable.table[i].c = keys[i];
	string decryStr = decry2(cipherText, keys, detable);
	output1(4, decryStr);
	return decryStr;
}

//单表置换密码攻击
void secondAttack() {
	single_table attacktable1;
	single_table attacktable2;
	//p_word* word=setWordP();
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
	char mcha[26] = {
		'e','t','o','i','a','n','s','r','h','l','d','u',
		'c','m','p','y','f','g','w','b','v','k','x','j','q','z'
	};
	attacktable1=wordAttack(attacktable1, word);
	attacktable2=letterAttack(attacktable2, mcha);

	char inputChar,judge;
	int n;
	cout << endl;
	cout << "请问您要在字母频率攻击的基础上进行修改吗？(输入y进行修改，输入n退出)" << endl;
	cin >> inputChar;
	ifstream file;

	if (inputChar == 'y'|| inputChar == 'Y') {


		do {
			ofstream file2;
			file2.open("output.txt");
			cout << "请输入要修改的置换表中对应关系的个数" << endl;
			cin >> n;
			char *m = new char[2*n];
			for (int i = 0; i < 2 * n; i+=2) {
				cin >> m[i] >> m[i + 1];
				attacktable2 = changeFun(attacktable2,m[i],m[i+1]);
			}
			cout <<endl<< " -----------------------------置换表---------------------------- " <<endl<< endl;
			for (int i = 0; i < 26; i++) {
				cout << attacktable2.table[i].m << " --- " << attacktable2.table[i].c ;
				if (i % 4 == 3) {
					cout << endl;
					continue;
				}
				cout << "    |    " ;
			}
			string buf;
			cout << endl;
			file.open("input.txt");

			while (!file.eof())
			{
				file >> buf;
				for (int i = 0; i < buf.length(); i++)
					for (int k = 0; k < 26; k++)
					{
						if (buf[i] == attacktable2.table[k].c)
						{
							cout << attacktable2.table[k].m;
							file2 << attacktable2.table[k].m;
							//count_endl++;
						}
					}
				cout << " " ;
				file2 << " ";

			}
			file.close();
			cout << endl<<endl;
			cout << "是否继续进行更改？（输入y继续，输入n退出）" << endl;
			cin >> judge;
			file2.close();
		} while (judge=='y'|| judge == 'Y');
		
		return;
	}
	
	
	if (inputChar == 'n' || inputChar == 'N')
		return;

}

void main() {
	int i;
	show();

	cin>>i;
	while(i!=0){
		cin.ignore();
		if(i==1)
			firstEncry();
		if(i==2)
			firstDecry();
		if(i==3)
			firstAttack();
		if(i==4)
			secondEncry();
		if (i == 5)
			secondDecry();
		if (i == 6)
			secondAttack();
		cout<<"继续进行加密解密还是退出？退出请按0，否则请输入接下来进行的操作："<<endl;
		cin>>i;
	}
	system("pause");

}


