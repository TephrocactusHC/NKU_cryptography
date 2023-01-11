#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "BigInt.h"
#include "PrimerTable.h"
#include "PrimerGen.h"
#include<ctime>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	ofstream outfile("test.txt");

	cout << "***************************************************************************" << endl;
	cout << "*                                  RSA测试                                *" << endl;
	cout << "***************************************************************************" << endl;
	cout << "开始测试" << endl;

	cout << "***************************************************************************" << endl;
	cout << "生成大素数 p" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	//记录生成了多少次大奇数
	int time = 0;

	//开始计时
	clock_t start = clock();

	//产生大素数
	BigInt p = GeneratePrime(time);

	//结束计时
	clock_t finish = clock();

	cout <<"生成512比特素数p成功！"<< endl;
	cout << "生成大素数p耗时（含I/O耗时）: " << (double)(finish - start) / CLOCKS_PER_SEC << "s." << endl;
	cout << "生成大奇数次数： " << time<< "次" << endl;
	cout << "生成大素数p为： "<< endl;

	//16进制形式显示
	p.display();
	outfile << "大素数p:" << endl;
	outfile << p;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "生成大素数 q" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	//记录生成了多少次大奇数
	int time2 = 0;

	//开始计时
	clock_t start2 = clock();

	//产生大素数
	BigInt q = GeneratePrime(time2);

	//结束计时
	clock_t finish2 = clock();

	cout <<"生成512比特素数q成功！"<< endl;
	cout << "生成大素数q耗时（含I/O耗时）: " << (double)(finish2 - start2) / CLOCKS_PER_SEC << "s." << endl;
	cout << "生成大奇数次数： " << time2<< "次" << endl;
	cout << "生成大素数q为： "<< endl;

	//16进制形式显示
	p.display();
	outfile << "大素数q:" << endl;
	outfile << q;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "计算公开钥n = p * q" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt n = p*q;

	cout << "公开钥n为： "<< endl;
	//16进制形式显示
	n.display();
	outfile << "公开钥n为：" << endl;
	outfile << n;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "计算公开钥e 和秘密钥d " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt t = (p - 1)*(q - 1);

	//e为公开钥
	BigInt e;

	//d为秘密钥，即e模t的乘法逆元
	BigInt d;

	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;

	BigInt temp;

	while (1)
	{
		//产生与t互质的e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}

		//用扩展欧几里德算法试图求出e模t的乘法逆元
		temp = ExtendedGcd(e, t, d, y);

		//e*d模t结果为1，说明d确实是e模t的乘法逆元
		temp = (e*d) % t;
		if (temp == 1)
			break;

		//否则重新生成e
	}

	
	cout << "公开钥e为： "<< endl;
	//16进制形式显示
	e.display();
	outfile << "公开钥e:" << endl;
	outfile << e;
	cout << endl;

	cout << "秘密钥d为： "<< endl;
	//16进制形式显示
	d.display();
	outfile << "秘密钥d:" << endl;
	outfile << d;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "随机生成明文分组m " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt m;
	m.Random();
	cout << "明文分组m为："<< endl;
	//16进制形式显示
	m.display();
	outfile << "明文分组m为：" << endl;
	outfile << m;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "用秘密钥e对m加密,得到密文分组c " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt c = PowerMode(m, e, n);
	cout << "密文分组c为："<< endl;
	//16进制形式显示
	c.display();
	outfile << "密文分组c为：" << endl;
	outfile << c;
	cout << endl;

	cout << "***************************************************************************" << endl;
	cout << "用公开钥d对c解密，得到明文分组m2 " << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	BigInt m2 = PowerMode(c, d, n);
	cout << "明文分组m2为："<< endl;
	//16进制形式显示
	m2.display();
	outfile << "明文分组m2为：" << endl;
	outfile << m2;
	cout << endl;

	system("pause");
	return 0;
}
