#include <iostream>
#include <string>
#include "hw2_2_data.h"
using namespace std;

char * get_Key(string String_Key_Input); //���û�����String ת��Ϊ char����Char_Key

char * get_CipherText(string String_CipherText_Input); //���û�����String ת��Ϊ char����Char_CipherText

bool is_input_valid(char * str);//����û�����16�������Ƿ�Ϸ�

void Hex_to_Bin(char * Hex, int * Bin);//ʮ������char����ת��Ϊ������int����

void Bin_to_Hex(int * Bin, char * Hex);//������int����ת��Ϊʮ������char����
