#include"rsa.h"

// 产生一个奇数作为待测素数
void SortPrime(BigInt& n)
{
    int i = 0;
    BigInt divisor;
    const int length = sizeof(prime) / sizeof(int);

    while (i != length)
    {
        n.Random();
        while (!n.IsOdd())
            n.Random();

        i = 0;
        for (; i < length; i++)
            if ((n % prime[i]) == 0)
                break;
    }
}

// RabinMiller检测某个数是否是素数
bool RabinMiller(const BigInt& n)
{
    BigInt r, a, y;
    unsigned int s, j;
    r = n - 1;
    s = 0;

    while (!r.IsOdd())
    {
        s++;
        r >> 1;
    }

    a.RandomSmall();	// 随机产生一个小于N-1的检测数a

    y = PowerMode(a, r, n);	//y = a的r次幂模n

    //检测J=2至J<S轮
    if ((!(y == 1)) && (!(y == (n - 1))))
    {
        j = 1;

        while ((j <= s - 1) && (!(y == (n - 1))))
        {
            y = (y * y) % n;
            if (y == 1)
                return false;
            j++;
        }

        if (!(y == (n - 1)))
            return false;
    }
    return true;
}

//产生一个素数
BigInt GeneratePrime()
{
    srand((unsigned)time(NULL));
    BigInt n;
    int time = 0;	// 记录产生素数次数
    bool success=false;

    // 循环产生素数，通过5轮RabinMiller测试
    while (!success)
    {
        time++;
        //产生一个待测素数
        cout << "生成第" << time << "个大奇数：" << endl;
        SortPrime(n);
        n.display();

        //进行五轮RABINMILLER测试,五轮全部通过则素数合格
        for (int i=0; i < 5; i++)
        {
            cout << "第" << i + 1 << "轮RabinMiller测试：";
            if (!RabinMiller(n))
            {
                cout << "Fail.." << endl;
                break;
            }
            cout << "Pass!" << endl;
            success=true;
        }
        cout<<endl;
    }
    return n;
}

// 辗转相除法求两个大数的最大公约数
BigInt Gcd(const BigInt& m, const BigInt& n)
{
    if (n == 0)
        return m;
    else
        return Gcd(n, m % n);
}

// 扩展欧几里德求乘法逆元
BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
    BigInt t, d;

    // 如果一个操作数为零则无法进行除法运算
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    d = ExtendedGcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - ((a / b) * y);
    return d;
}

BigInt StringToBigInt(string str)
{
    BigInt a(0);
    for(int i=str.length()-1;i>=0;i--)
    {
        int x=str[i]+128;
        BigInt temp=a*256;
        a=temp+x;
    }
    //cout << "a" << a.GetLenth() << endl;
    return a;
}

string BigIntToString(BigInt num)
{
    string str="";
    while(!(num==0))
    {
        BigInt temp=num%256;
        int x=temp.ToInt();
        num=num/256;
        str+=(char)(x-128);
    }
    return str;
}

string BigIntToHex(BigInt &num)
{
    return num.ToHex();
}

BigInt HexToBigInt(string hex)
{
    BigInt result(0);
    for(int i=0;i<hex.length();i++)
    {
        int val;
        switch (hex[i])
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
        result = result * 16 + val;
    }
    return result;
}

Rsa::Rsa()
{
    BigInt p = GeneratePrime();
    BigInt q = GeneratePrime();
    n = p * q;
    BigInt f = (p - 1) * (q - 1);
    BigInt x,temp;

    // 循环生成e，直到满足条件
    while (1)
    {
        //产生与fn互质的e
        e.Random();
        while (!(Gcd(e, f) == 1))
            e.Random();

        //用扩展欧几里德算法试图求出e模t的乘法逆元
        temp = ExtendedGcd(e, f, d, x);

        // e*d模t结果为1 -> d是e模t的乘法逆元，计算完成
        temp = (e * d) % f;
        if (temp == 1)
            break;
    }
}

Rsa::Rsa(BigInt &N, BigInt &E)
{
    n=N;
    e=E;
}

Rsa::Rsa(BigInt &N, BigInt &E, BigInt &D)
{
    n=N;
    e=E;
    d=D;
}
