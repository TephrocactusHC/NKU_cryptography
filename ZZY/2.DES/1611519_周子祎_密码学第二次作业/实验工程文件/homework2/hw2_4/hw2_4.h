#include <iostream>
#include <string>
#include "hw2_4_data.h"
using namespace std;

char * get_Key(string String_Key_Input); //将用户输入String 转换为 char数组Char_Key

char * get_PlainText(string String_PlainText_Input); //将用户输入String 转换为 char数组Char_PlainText

bool is_input_valid(char * str);//检查用户输入16进制数是否合法

void Hex_to_Bin(char * Hex, int * Bin);//十六进制char数组转换为二进制int数组

void Bin_to_Hex(int * Bin, char * Hex);//二进制int数组转换为十六进制char数组

//将用户输入String 转换为 char数组Char_Key
char * get_Key(string String_Key_Input)
{
	//截取前16位十六进制数作为密钥
	string String_Key = String_Key_Input.substr(0,16);

	//不足16位十六进制数则末尾补0至16位十六进制数
	if(String_Key.size()<16)
	{
		int temp_String_Key_size = String_Key.size();
		for(int i=1;i<=16 - temp_String_Key_size;i++)
		{
			String_Key = String_Key + '0';
		}
	}

	char* Char_Key = new char[17];
	String_Key.copy(Char_Key, 16, 0);
	Char_Key[16] = '\0';

	return Char_Key;
}

//将用户输入String 转换为 char数组Char_PlainText
char * get_PlainText(string String_PlainText_Input)
{
	//截取前16位十六进制数作为明文
	string String_PlainText = String_PlainText_Input.substr(0,16);

	//不足16位十六进制数则末尾补0至16位十六进制数
	if(String_PlainText.size()<16)
	{
		int temp_String_PlainText_size = String_PlainText.size();
		for(int i=1;i<=16 - temp_String_PlainText_size;i++)
		{
			String_PlainText = String_PlainText + '0';
		}
	}

	char* Char_PlainText = new char[17];
	String_PlainText.copy(Char_PlainText, 16, 0);
	Char_PlainText[16] = '\0';

	return Char_PlainText;
}

//检查用户输入16进制数是否合法
bool is_input_valid(char * str)
{
	for(int i=0;i<=15;i++)
	{
		if(!( (str[i]>='A'&&str[i]<='F') || (str[i]>='a'&&str[i]<='f') ||(str[i]>='0'&&str[i]<='9') ))
		{
			return 0;
		}
	}
	return 1;
}

//十六进制char数组转换为二进制int数组
void Hex_to_Bin(char * Hex, int * Bin)
{
	int i=0,k=0,j=0;

	for(i=0;i<16;i++)
	{
		int val = 0;
		if(Hex[i] >= '0' && Hex[i] <= '9')
			val = Hex[i]-'0';
		else if (Hex[i] >= 'A' && Hex[i] <= 'F')
			val = Hex[i]-'A'+10;
		else if (Hex[i] >= 'a' && Hex[i] <= 'f')
			val = Hex[i]-'a'+10;

		for(int k=4*i+3;k>=4*i;k--)
		{
			Bin[k] = val % 2;
			val/=2;
		}
	}
}

//二进制int数组转换为十六进制char数组
void Bin_to_Hex(int * Bin, char * Hex)
{
	int i=0,k=0,j=0;

	for(i=0;i<16;i++)
	{
		int val = 0;

		for(int k=4*i;k<=4*i+3;k++)
		{
			val *= 2;
			val += Bin[k];
		}
		
		if( val<10 )
			Hex[i] = val+'0';
		else if (val >=10 && val <=15 )
			Hex[i] = val-10+'A';
	}

	Hex[16]='\0';
}