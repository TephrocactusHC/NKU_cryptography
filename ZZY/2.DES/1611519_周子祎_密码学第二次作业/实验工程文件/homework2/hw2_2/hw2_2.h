#include <iostream>
#include <string>
#include "hw2_2_data.h"
using namespace std;

char * get_Key(string String_Key_Input); //将用户输入String 转换为 char数组Char_Key

char * get_CipherText(string String_CipherText_Input); //将用户输入String 转换为 char数组Char_CipherText

bool is_input_valid(char * str);//检查用户输入16进制数是否合法

void Hex_to_Bin(char * Hex, int * Bin);//十六进制char数组转换为二进制int数组

void Bin_to_Hex(int * Bin, char * Hex);//二进制int数组转换为十六进制char数组
