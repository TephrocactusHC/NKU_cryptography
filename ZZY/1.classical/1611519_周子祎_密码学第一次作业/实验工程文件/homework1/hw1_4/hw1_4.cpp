#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
	string input_str;
	vector<int>* freq_tbl=  new vector<int>;

	vector<int>* letter_tbl=  new vector<int>;

	char letter_record[26] = {'a'};//记录(*freq_tbl)按频次由低到高排序后,每个频次对应的字母

	for(int i=1;i<=26;i++)
	{
		(*freq_tbl).push_back(0);
		(*letter_tbl).push_back(0);
	}	

	cout<<"请输入密文字符串：\n";
	getline(cin, input_str);
	cout << "****************************************************************************"<<endl;
	cout<<"字符串中字母出现频率统计如下：\n";
	int total_letter_num = 0;

	//遍历输入字符串，记录字母频次
	for (int i = 0; i<input_str.length(); i++)
	{
		if ( input_str[i] >= 'A' && input_str[i] <= 'Z' )
		{
			(*freq_tbl)[ input_str[i] - 'A']++;
			(*letter_tbl)[ input_str[i] - 'A']++;
			total_letter_num++;
			continue;
		}

		if ( input_str[i] >= 'a' && input_str[i] <= 'z' )
		{
			(*freq_tbl)[ input_str[i] - 'a']++;
			(*letter_tbl)[ input_str[i] - 'a']++;
			total_letter_num++;
			continue;
		}
	}

	//freq_tbl按字母频次重排(默认升序排列)
	sort((*freq_tbl).begin(),(*freq_tbl).end());

	for(int f=25;f>=0;f--)//遍历(*freq_tbl)，(*freq_tbl)按频率值由低到高顺序存储字母频次值
	{
		for(int l=0;l<26;l++)//遍历(*letter_tbl)，(*letter_tbl)按字母顺序存储字母频次值
		{
			if( (*letter_tbl)[l] == (*freq_tbl)[f] )
			{
				letter_record[f] = 'a'+l;
				(*letter_tbl)[l] = -1;//频率值相同的字母匹配哪个频次都可以，但匹配上一次之后就不能再匹配了，否则letter_record会重复记录
				break;
			}
		}
	}

	for (int k = 25; k >= 0; k--)
	{
		if((*freq_tbl)[k]!=0)
			cout << letter_record[k]<< " ------- " <<double((*freq_tbl)[k])/double(total_letter_num)<< endl;
	}
	system("pause");

	return 0;
}