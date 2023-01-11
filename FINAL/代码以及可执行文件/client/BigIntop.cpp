#pragma once
#include <stdlib.h>
#include "BigInt.h"
using namespace std;

// 初始化BigInt
BigInt::BigInt()
{
    for (int i = 0; i < BIsize; i++)
        data[i] = 0;
    sign = true;
}
BigInt::BigInt(const int &input)
{
    for (int i = 0; i < BIsize; i++)
        data[i] = 0;
    data[0] = input;
    if (input >= 0)
        sign = true;
    else
        sign = false;
}
BigInt::BigInt(const BigInt &input)
{
    for (int i = 0; i < BIsize; i++)
        data[i] = input.data[i];
    sign = input.sign;
}

// 赋值
void BigInt::operator=(const BigInt &input)
{
    for (int i = 0; i < BIsize; i++)
        data[i] = input.data[i];
    sign = input.sign;
}

// 比较
bool operator<(const BigInt &a, const BigInt &b)
{
    for (int i = BIsize - 1; i > 0; i--)
    {
        if (a.data[i] < b.data[i])
            return true;
        if (a.data[i] > b.data[i])
            return false;
    }
    return a.data[0] < b.data[0];
}
bool operator>(const BigInt &a, const BigInt &b)
{
    for (int i = BIsize - 1; i >= 0; i--)
    {
        if (a.data[i] > b.data[i])
            return true;
        if (a.data[i] < b.data[i])
            return false;
    }
    return false;
}
bool operator<=(const BigInt &a, const int &b)
{
    for (int i = 1; i < a.GetLenth(); i++)
    {
        if (a.data[i] != 0)
            return false;
    }
    return (a.data[0] <= b);
}

// 相等判断（!=也可用==结果判断
bool operator==(const BigInt &a, const BigInt &b)
{
    for (int i = 0; i < BIsize; i++)
        if (a.data[i] != b.data[i])
            return false;
    return true;
}
bool operator==(const BigInt &a, const int &b)
{
    for (int i = 1; i < a.GetLenth(); i++)
        if (a.data[i] != 0)
            return false;
    return a.data[0] == b;
}

// 重载输出运算符，实现文件写BigInt
void BigInt::Output(ostream &out) const
{
    unsigned int temp, result;
    unsigned int tempAnd = 0xf0000000;

    for (int i = GetLenth() - 1; i >= 0; i--)
    {
        temp = data[i];
        for (int j = 0; j < 8; j++)
        {
            result = temp & tempAnd;
            result = (result >> 28);
            temp = (temp << 4);
            switch (result)
            {
                case 10:out << "A";break;
                case 11:out << "B";break;
                case 12:out << "C";break;
                case 13:out << "D";break;
                case 14:out << "E";break;
                case 15:out << "F";break;
                default:out << result;break;
            }
        }
    }
    out << endl;
}
ostream &operator<<(ostream &out, const BigInt &num)
{
    num.Output(out);
    return out;
}

// 重载输入运算符，实现从文件中读BigInt
istream &operator>>(istream &in, BigInt &num)
{
    num=0;
    char temp;
    in.get(temp);
    while(temp!='\n')
    {
        int val;
        // 16进制转十进制
        switch (temp)
        {
            case '0':val=0;break;
            case '1':val=1;break;
            case '2':val=2;break;
            case '3':val=3;break;
            case '4':val=4;break;
            case '5':val=5;break;
            case '6':val=6;break;
            case '7':val=7;break;
            case '8':val=8;break;
            case '9':val=9;break;
            case 'A':val=10;break;
            case 'B':val=11;break;
            case 'C':val=12;break;
            case 'D':val=13;break;
            case 'E':val=14;break;
            case 'F':val=15;break;
        }
        num = num * 16 + val;	// 累加求值
        in.get(temp);
    }
    return in;
}

// 返回data中不为0的位数
inline int BigInt::GetLenth() const
{
    int lenth = BIsize;
    for (int i = BIsize - 1; i >= 0; i--)
    {
        //第一位不为0即为LENGTH
        if (data[i] == 0)
            lenth--;
        else
            break;
    }
    return lenth;
}

// 重载移位操作符，向右移N位
void BigInt::operator>>(const int &a)
{
    unsigned int bit;
    data[0] = (data[0] >> a);
    for (int i = 1; i < GetLenth(); i++)
    {
        // 先将每一位的低位移到BIT中
        bit = data[i] & 1;
        // 再把BIT移到上一位的高位中
        bit = bit << (32 - a);
        data[i - 1] = data[i - 1] | bit;
        data[i] = (data[i] >> a);
    }
}

