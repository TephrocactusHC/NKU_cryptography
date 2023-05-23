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

	char letter_record[26] = {'a'};//��¼(*freq_tbl)��Ƶ���ɵ͵��������,ÿ��Ƶ�ζ�Ӧ����ĸ

	for(int i=1;i<=26;i++)
	{
		(*freq_tbl).push_back(0);
		(*letter_tbl).push_back(0);
	}	

	cout<<"�����������ַ�����\n";
	getline(cin, input_str);
	cout << "****************************************************************************"<<endl;
	cout<<"�ַ�������ĸ����Ƶ��ͳ�����£�\n";
	int total_letter_num = 0;

	//���������ַ�������¼��ĸƵ��
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

	//freq_tbl����ĸƵ������(Ĭ����������)
	sort((*freq_tbl).begin(),(*freq_tbl).end());

	for(int f=25;f>=0;f--)//����(*freq_tbl)��(*freq_tbl)��Ƶ��ֵ�ɵ͵���˳��洢��ĸƵ��ֵ
	{
		for(int l=0;l<26;l++)//����(*letter_tbl)��(*letter_tbl)����ĸ˳��洢��ĸƵ��ֵ
		{
			if( (*letter_tbl)[l] == (*freq_tbl)[f] )
			{
				letter_record[f] = 'a'+l;
				(*letter_tbl)[l] = -1;//Ƶ��ֵ��ͬ����ĸƥ���ĸ�Ƶ�ζ����ԣ���ƥ����һ��֮��Ͳ�����ƥ���ˣ�����letter_record���ظ���¼
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