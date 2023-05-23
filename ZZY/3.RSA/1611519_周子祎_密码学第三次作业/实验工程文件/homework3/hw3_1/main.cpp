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
	cout << "*                               素数生成测试                              *" << endl;
	cout << "***************************************************************************" << endl;
	cout << "开始测试" << endl;
	cout << "---------------------------------------------------------------------------" << endl;
	
	//记录生成了多少次大奇数
	int time = 0;

	//开始计时
	clock_t start = clock();

	//产生大素数
	BigInt p = GeneratePrime(time);

	//结束计时
	clock_t finish = clock();

	cout <<"生成512比特素数成功！"<< endl;
	cout << "生成素数耗时（含I/O耗时）: " << (double)(finish - start) / CLOCKS_PER_SEC << "s." << endl;
	cout << "生成大奇数次数： " << time<< "次" << endl;
	cout << "生成大素数为： "<< endl;

	//16进制形式显示
	p.display();
	outfile << "大素数:" << endl;
	outfile << p;
	cout << endl;
	cout << "***************************************************************************" << endl;

	system("pause");
	return 0;
}
