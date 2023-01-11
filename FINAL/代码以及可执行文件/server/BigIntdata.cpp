#pragma once
#include<stdlib.h>
#include"BigInt.h"

using namespace std;

// BigInt清零
void BigInt::Clear()
{
    for (int i = 0; i < BIsize; i++)
        data[i] = 0;
}

// 产生一个随机大数，LENTH为SIZE的1/4
void BigInt::Random()
{
    for (int i = 0; i<(BIsize / 4); i++)
        //由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
        //3次RAND()操作
        data[i] = (rand() << 17) + (rand() << 2) + rand() % 4;

}

// 产生一个较小的随机大数,大数的LENGTH为SIZE的1/8
void BigInt::RandomSmall()
{
    for (int i = 0; i < (BIsize / 16); i++)
        data[i] = (rand() << 17) + (rand() << 2) + rand() % 4;	// 通过3次rand()产生32位随机数
}

// BigInt转16进制后输出
void BigInt::display() const
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
                case 10:cout << "A";break;
                case 11:cout << "B";break;
                case 12:cout << "C";break;
                case 13:cout << "D";break;
                case 14:cout << "E";break;
                case 15:cout << "F";break;
                default:cout<<result;break;
            }
        }
        cout << " ";
        if (i == GetLenth() / 2)
            cout << endl;
    }
    cout << endl;
}

// BigInt转16进制存放在string中
string BigInt::ToHex()
{
    unsigned int temp, result;
    unsigned int tempAnd = 0xf0000000;
    string hex="";

    for (int i = GetLenth() - 1; i >= 0; i--)
    {
        temp = data[i];
        for (int j = 0; j < 8; j++)
        {
            result = temp & tempAnd;
            result = (result >> 28);
            temp = (temp << 4);
            char val;
            switch (result)
            {
                case 0:val='0';break;
                case 1:val='1';break;
                case 2:val='2';break;
                case 3:val='3';break;
                case 4:val='4';break;
                case 5:val='5';break;
                case 6:val='6';break;
                case 7:val='7';break;
                case 8:val='8';break;
                case 9:val='9';break;
                case 10:val='A';break;
                case 11:val= 'B';break;
                case 12:val= 'C';break;
                case 13:val= 'D';break;
                case 14:val= 'E';break;
                case 15:val= 'F';break;
                default:cout<<result;break;
            }
            hex+=val;
        }
    }
    return hex;
}


