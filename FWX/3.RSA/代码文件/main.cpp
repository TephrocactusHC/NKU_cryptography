#include<iostream>
#include<time.h>
#include<ctime>
#include<fstream>
#include"bigInt.h"
using namespace std;

// 产生一个待测素数,保证此数为奇数,且不能被小于5000的素数整除
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
		{
			divisor = prime[i];
			if ((n % divisor) == 0)
				break;
		}
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

	//随机产生一个小于N-1的检测数a
	a.RandomSmall();

	//y = a的r次幂模n
	y = PowerMode(a, r, n);

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
	BigInt n;
	int i = 0;
	// 记录总共产生了多少次素数
	int time = 0;

	//无限次循环，不断产生素数，直到i==5时（通过五轮RabinMiller测试）才会跳出while循环
	while (i < 5)
	{
		//记录生成了多少次大奇数
		time++;

		//产生一个待测素数
		cout << endl << endl;
		cout << "正在生成第" << time << "个大奇数：" << endl;
		SortPrime(n);
		n.display();

		i = 0;
		//进行五轮RABINMILLER测试,五轮全部通过则素数合格
		for (; i < 5; i++)
		{
			cout << "正在进行第" << i + 1 << "轮RabinMiller测试：";
			if (!RabinMiller(n))
			{
				cout << "…………测试失败" << endl << endl;
				break;
			}
			cout << "…………测试通过" << endl << endl;
		}
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
	//如果一个操作数为零则无法进行除法运算
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

// RSA加密
BigInt RSAEn(BigInt& m, BigInt& e, BigInt& n) {
	// 加密后的结果
	BigInt c;
	c = PowerMode(m, e, n);
	return c;
}

// RSA解密
BigInt RSADe(BigInt& c, BigInt& d, BigInt& n) {
	// 解密后的结果
	BigInt m;
	m = PowerMode(c, d, n);
	return m;
}

int main() {
	cout << "==================第一个素数p生成================\n";
	// 根据时间设置一个随机数
	srand((unsigned)time(NULL));

	BigInt randomP = GeneratePrime();
	cout << "==================素数p生成成功===================\np：\n";
	randomP.display();

	cout << "\n\n==================第二个素数q生成================\n";
	BigInt randomQ = GeneratePrime();
	cout << "==================素数q生成成功===================\nq：\n";
	randomQ.display();

	// 将生成的素数保存在prime.txt中
	ofstream outfile("./prime.txt");
	outfile << randomP;
	outfile << '\n';
	outfile << randomQ;
	outfile << '\n';
	// 关闭文件
	outfile.close();

	// 计算n
	BigInt n;
	n = randomP * randomQ;
	
	// 计算φ（n）
	BigInt fn = (randomP - 1) * (randomQ - 1);

	// 公钥e
	BigInt e;
	//d为秘密钥，即e模t的乘法逆元
	BigInt d;
	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;
	// 保存标志位，判断算法是否成功
	BigInt temp;
	// 计算产生互质的数
	while (1)
	{
		//产生与fn互质的e
		e.Random();
		while (!(Gcd(e, fn) == 1))
		{
			e.Random();
		}

		//用扩展欧几里德算法试图求出e模t的乘法逆元
		temp = ExtendedGcd(e, fn, d, y);

		//e*d模t结果为1，说明d确实是e模t的乘法逆元
		temp = (e * d) % fn;
		if (temp == 1)
			break;

		//否则重新生成e
	}
	cout << "\n\n===========================加密准备===========================\n";
	cout << "经过计算得到公钥(n,e)为：\n("; n.display(); cout << " ,\n"; e.display(); cout << ")\n";
	cout << "得到私钥(n,d)为：\n("; n.display(); cout << " ,\n"; d.display(); cout << ")\n";
	cout << endl << endl;

	cout << "\n\n===========================随机生成明文===========================\n";
	BigInt m;
	m.Random();
	cout << "生成的随机明文为：\n";
	m.display();

	// 加密后的密文
	BigInt c;
	c = RSAEn(m, e, n);
	cout << "加密后得到的密文为：\n";
	c.display();

	// 对加密的密文解密后得到的明文
	BigInt newm;
	newm = RSADe(c, d, n);
	cout << "对密文解密后得到的明文为：\n";
	newm.display();

	// 写文件，将RSA有关的内容都写入
	ofstream rsaResult("./rsaResult.txt");
	// 写入n,e,d,m,c,newm
	rsaResult << "n:\n";
	rsaResult << n;
	rsaResult << '\n';
	rsaResult << "e:\n";
	rsaResult << e;
	rsaResult << '\n';
	rsaResult << "d:\n";
	rsaResult << d;
	rsaResult << '\n';
	rsaResult << "m:\n";
	rsaResult << m;
	rsaResult << '\n';
	rsaResult << "c:\n";
	rsaResult << c;
	rsaResult << '\n';
	rsaResult << "newm:\n";
	rsaResult << newm;
	rsaResult << '\n';
	rsaResult.close();
	cout << "RSA相关内容已经写入rsaResult.txt中\n";

	return 0;
}