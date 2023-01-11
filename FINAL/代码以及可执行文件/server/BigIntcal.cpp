#pragma once
#include <stdlib.h>
#include "BigInt.h"
using namespace std;

// 竖式相加法实现BigInt求和
BigInt operator+ (const BigInt& a, const BigInt& b)
{
    BigInt result;
    unsigned __int64 sum;	// 64位数据,存放每两位数相加的临时和
    unsigned int carry = 0;	// 进位标志
    unsigned int sub;	// 两数符号相异，时存放每两位数相减的临时差

    int length = (a.GetLenth() >= b.GetLenth() ? a.GetLenth() : b.GetLenth());

    // 当两数符号相同时,进行加法运算
    if (a.sign == b.sign)
    {
        // 每一位进行竖式相加
        for (int i = 0; i < length; i++)
        {
            sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
            result.data[i] = (unsigned int)sum;
            // sum的高位为进位
            carry = (sum >> 32);
        }

        result.sign = a.sign;
        return result;
    }
    else	// 两数符号不同时,进行减法运算
    {
        BigInt tempa, tempb;

        //取出a,b中绝对值较大的作为被减数
        if (a < b)
        {
            tempa = b;
            tempb = a;
        }
        else
        {
            tempa = a;
            tempb = b;
        }

        //每一位进行竖式减
        for (int i = 0; i < length; i++)
        {
            sub = tempb.data[i] + carry;
            if (tempa.data[i] >= sub)
            {
                result.data[i] = tempa.data[i] - sub;
                carry = 0;
            }
            else
            {
                //借位减
                result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
                carry = 1;
            }
        }
        result.sign = tempa.sign;
        return result;
    }
}

// 竖式相减法BigInt求差
BigInt operator- (const BigInt& a, const BigInt& b)
{
    BigInt result;
    unsigned __int64 sum;	// 存放每两位数相加的临时和
    unsigned int carry = 0;	// 进位标志
    unsigned int sub;	// 两数符号相异时存放每两位数相减的临时差

    //符号相同时,进行减法运算
    if (a.sign == b.sign)
    {
        BigInt tempa, tempb;

        //取出a,b中绝对值较大的作为被减数
        if (a < b)
        {
            tempa = b;
            tempb = a;
            tempa.sign = !tempa.sign;
        }
        else
        {
            tempa = a;
            tempb = b;
        }

        // 每一位进行竖式减
        for (int i = 0; i < BIsize; i++)
        {
            sub = tempb.data[i] + carry;
            if (tempa.data[i] >= sub)
            {
                result.data[i] = tempa.data[i] - sub;
                carry = 0;
            }
            else
            {
                // 借位减
                result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
                carry = 1;
            }
        }
        result.sign = tempa.sign;
        return result;
    }
    else	// 两数符号不同时,进行加法运算
    {
        // 每一位进行竖式相加
        for (int i = 0; i < BIsize; i++)
        {
            sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
            result.data[i] = (unsigned int)sum;
            // sum的高位为进位
            carry = (sum >> 32);
        }
        result.sign = a.sign;
        return result;
    }
}

// BigInt - Int
BigInt operator- (const BigInt& a, const int& b)
{
    BigInt temp(b);
    BigInt result = a - temp;
    return result;
}

// BigInt * Int
BigInt operator* (const BigInt& a, const unsigned int& b)
{
    BigInt result;	// B乘以A的每一位的临时积
    unsigned __int64 sum;	// 进位
    unsigned int carry = 0;

    for (int i = 0; i < BIsize; i++)
    {
        sum = ((unsigned __int64)a.data[i]) * b + carry;
        result.data[i] = (unsigned int)sum;
        // 进位在SUM的高位中
        carry = (sum >> 32);
    }
    result.sign = a.sign;
    return result;
}

// 竖式相乘求BigInt乘积
BigInt operator* (const BigInt& a, const BigInt& b)
{
    // last存放竖式上一行的积，temp存放当前行的积
    BigInt result, last, temp;
    // sum存放当前行带进位的积
    unsigned __int64 sum;
    // 存放进位
    unsigned int carry;

    // 进行竖式乘
    for (int i = 0; i < b.GetLenth(); i++)
    {
        carry = 0;
        // B的每一位与A相乘
        for (int j = 0; j < a.GetLenth() + 1; j++)
        {
            sum = ((unsigned __int64)a.data[j]) * (b.data[i]) + carry;
            if ((i + j) < BIsize)
                temp.data[i + j] = (unsigned int)sum;
            carry = (sum >> 32);
        }
        result = (temp + last);
        last = result;
        temp.Clear();
    }

    // 判断积的符号
    result.sign=(a.sign==b.sign);
    return result;
}

// BigInt除法，采用试商除法+二分查找法
BigInt operator/ (const BigInt& a, const BigInt& b)
{
    // mul为当前试商，low，high为二分查找试商时所用的标志
    unsigned int mul, low, high;
    // sub为除数与当前试商的积，subsequent为除数与下一试商的积
    // dividend存放临时被除数
    BigInt dividend, quotient, sub, subsequent;
    int lengtha = a.GetLenth(), lengthb = b.GetLenth();

    //如果被除数小于除数，返回0
    if (a < b)
    {
        quotient.sign =(a.sign == b.sign);
        return quotient;
    }

    // 把被除数按除数的长度从高位截位
    int i;
    for (i = 0; i < lengthb; i++)
        dividend.data[i] = a.data[lengtha - lengthb + i];

    for (i = lengtha - lengthb; i >= 0; i--)
    {
        //如果被除数小于除数,再往后补位
        if (dividend < b)
        {
            for (int j = lengthb; j > 0; j--)
                dividend.data[j] = dividend.data[j - 1];
            dividend.data[0] = a.data[i - 1];
            continue;
        }

        low = 0;
        high = 0xffffffff;

        // 二分查找法查找试商
        while (low < high)
        {
            mul = (((unsigned __int64)high) + low) / 2;
            sub = (b * mul);
            subsequent = (b * (mul + 1));

            if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
                break;

            if (subsequent == dividend)
            {
                mul++;
                sub = subsequent;
                break;
            }

            if ((sub < dividend) && (subsequent < dividend))
            {
                low = mul;
                continue;
            }

            if ((sub > dividend) && (subsequent > dividend))
            {
                high = mul;
                continue;
            }

        }

        // 试商结果保存到商中去
        quotient.data[i] = mul;
        // 临时被除数变为被除数与试商积的差
        dividend = dividend - sub;

        // 临时被除数往后补位
        if ((i - 1) >= 0)
        {
            for (int j = lengthb; j > 0; j--)
                dividend.data[j] = dividend.data[j - 1];
            dividend.data[0] = a.data[i - 1];
        }
    }

    // 判断商的符号
    quotient.sign = (a.sign == b.sign);
    return quotient;
}

// BigInt求模，与除法类似
BigInt operator% (const BigInt& a, const BigInt& b)
{
    unsigned int mul, low, high;
    BigInt dividend, quotient, sub, subsequent;
    int lengtha = a.GetLenth(), lengthb = b.GetLenth();

    // 如果被除数小于除数,返回被除数为模
    if (a < b)
    {
        dividend = a;
        // 余数的商永远与被除数相同
        dividend.sign = a.sign;
        return dividend;
    }

    // 进行除法运算
    int i;
    for (i = 0; i < lengthb; i++)
        dividend.data[i] = a.data[lengtha - lengthb + i];

    for (i = lengtha - lengthb; i >= 0; i--)
    {
        if (dividend < b)
        {
            for (int j = lengthb; j > 0; j--)
                dividend.data[j] = dividend.data[j - 1];
            dividend.data[0] = a.data[i - 1];
            continue;
        }

        low = 0;
        high = 0xffffffff;

        while (low <= high)
        {
            mul = (((unsigned __int64)high) + low) / 2;
            sub = (b * mul);
            subsequent = (b * (mul + 1));

            if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
                break;

            if (subsequent == dividend)
            {
                mul++;
                sub = subsequent;
                break;
            }

            if ((sub < dividend) && (subsequent < dividend))
            {
                low = mul;
                continue;
            }

            if ((sub > dividend) && (subsequent > dividend))
            {
                high = mul;
                continue;
            }
        }

        quotient.data[i] = mul;
        dividend = dividend - sub;
        if ((i - 1) >= 0)
        {
            for (int j = lengthb; j > 0; j--)
                dividend.data[j] = dividend.data[j - 1];
            dividend.data[0] = a.data[i - 1];
        }
    }

    //临时被除数即为所求模
    dividend.sign = a.sign;
    return dividend;
}

// 模幂运算——计算n的p次幂模m
// 利用Montgomery算法，
BigInt PowerMode(const BigInt &n, const BigInt &p, const BigInt &m)
{
    BigInt temp = p;
    BigInt base = n % m;
    BigInt result(1);

    //检测指数p的二进制形式的每一位
    while (!(temp <= 1))
    {
        //如果该位为1，则表示该位需要参与模运算
        if (temp.IsOdd())
            result = (result * base) % m;
        base = (base * base) % m;
        temp >> 1;
    }
    return (base * result) % m;
}

