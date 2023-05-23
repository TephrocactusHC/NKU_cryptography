#include<iostream>
#include<string>
#include<bitset>

using namespace std;

//基本逻辑函数
unsigned int F(unsigned int b, unsigned int c, unsigned int d) {
	return ((b & c) | ((~b) & (d)));
}
unsigned int G(unsigned int b, unsigned int c, unsigned int d) {
	return ((b & d) | (c & (~d)));
}
unsigned int H(unsigned int b, unsigned int c, unsigned int d) {
	return (b ^ c ^ d);
}
unsigned int I(unsigned int b, unsigned int  c, unsigned int d) {
	return (c ^ (b | (~d)));
}

//x循环左移n位
unsigned int shift(unsigned int x, unsigned int n) {
	return ((x << n) | (x >> (32 - n)));
}

// 需要用到的一些全局变量
//常数表T，用于参与A分块的运算
const unsigned T[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

//压缩函数每轮的每步中A分块循环左移的位数
static const unsigned s[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

/// <summary>
/// 将32位int型整数，转化为大端寻址模式，以16进制字符串形式输出
/// </summary>
/// <param name="origin">int类型变量 </param>
/// <returns>string类型变量</returns>
string Int2HexString(int origin)
{
	const char str16[] = "0123456789abcdef";
	unsigned hexNum;

	string temp;
	string hexString = "";

	for (int i = 0; i < 4; i++)
	{
		//对字中的4个字节逐一做处理
		temp = "";

		//从origin中取对应的8bit，得到该字节所表示的值
		hexNum = (origin >> (i * 8)) & 0xff;

		for (int j = 0; j < 2; j++)
		{
			//每四位对应一个16进制数
			//在temp的0处插入1个 str16[hexNum % 16]
			temp.insert(0, 1, str16[hexNum % 16]);
			hexNum /= 16;
		}

		hexString += temp;
	}
	return hexString;
}

/// <summary>
/// 计算MD5的值
/// </summary>
/// <param name="message">任意长度的待处理消息</param>
/// <returns>128比特MD5字符串</returns>
string myGetMD5(string message) {
	//初始化,，这里要按照大端字节序的方式进行存储
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;

	// 得到消息的长度，单位：字节
	int lengthInByte = message.length();
	// 计算分组数量，同时需要注意：如果一开始就刚好是message=448(mod 512)也需要进行10000填充，所以算出来的直接+1
	int groupNum = ((lengthInByte + 8) / 64) + 1;

	// messageByte数组中的每一个元素，对应消息二进制表示中的32bit（4字节）
	// 每个分组的长度为 16 * 32bit = 512bit
	unsigned int* messageByte = new unsigned int[groupNum * 16];

	// 初始化
	memset(messageByte, 0, sizeof(unsigned int) * groupNum * 16);

	//将string类型变量 保存进 messageByte数组中
	for (int i = 0; i < lengthInByte; i++)
	{
		//每个字中对应存储4个字节的数据
		messageByte[i / 4] |= message[i] << ((i % 4) * 8);
	}

	// 进行填充
	messageByte[lengthInByte >> 2] |= 0x80 << ((lengthInByte % 4) * 8);

	// 附加信息
	messageByte[groupNum * 16 - 2] = lengthInByte * 8;

	// 临时变量，用来保存每轮中每一步计算之后的abcd
	unsigned int a, b, c, d;

	// 循环处理每个分组
	for (int i = 0; i < groupNum; i++)
	{
		a = A;
		b = B;
		c = C;
		d = D;
		unsigned int g;
		int k;

		// 对每个分组进行64轮压缩
		for (int j = 0; j < 64; j++)
		{
			// 根据轮数不同，使用不同的压缩函数
			if (j < 16)
			{
				// 对B C D进行基本逻辑函数运算
				g = F(b, c, d);
				// 计算k，以从消息分组中取出对应的字
				k = j;
			}
			else if (j >= 16 && j < 32)
			{
				// 对B C D进行基本逻辑函数运算
				g = G(b, c, d);
				// 计算k，以从消息分组中取出对应的字
				k = (1 + 5 * j) % 16;
			}
			else if (j >= 32 && j < 48)
			{
				// 对B C D进行基本逻辑函数运算
				g = H(b, c, d);
				// 计算k，以从消息分组中取出对应的字
				k = (5 + 3 * j) % 16;
			}
			else if (j >= 48 && j < 64)
			{
				// 对B C D进行基本逻辑函数运算
				g = I(b, c, d);
				// 计算k，以从消息分组中取出对应的字
				k = (7 * j) % 16;
			}

			unsigned tempd = d;
			d = c;
			c = b;
			b = b + shift(a + g + messageByte[i * 16 + k] + T[j], s[j]);
			a = tempd;
		}
		// 更新值
		A = a + A;
		B = b + B;
		C = c + C;
		D = d + D;
	}
	//返回16进制形式字符串
	return Int2HexString(A) + Int2HexString(B) + Int2HexString(C) + Int2HexString(D);
}

/// <summary>
/// 雪崩效应测试时计算不同位数的函数
/// </summary>
/// <param name="NewSumry">改变过后的字符串</param>
/// <param name="OrigiSumry">原始字符串</param>
/// <returns>不同的位数</returns>
int getCmpVal(string newMd5, string originMd5) {
	int indexOfTemp = 0;
	bitset<128> newmd5;
	// 使用最笨的办法，switch case把16进制的字符表示转换成2进制的结果
	for (; indexOfTemp < 32; indexOfTemp++) {
		int startOfEdit = 127 - 4 * indexOfTemp;
		switch (newMd5[indexOfTemp]) {
		case '0':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 0;
			break;
		case '1':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 1;
			break;
		case '2':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 0;
			break;
		case '3':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 1;
			break;
		case '4':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 0;
			break;
		case '5':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 1;
			break;
		case '6':
			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 0;
			break;
		case '7':

			newmd5[startOfEdit] = 0;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 1;
			break;
		case '8':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 0;
			break;
		case '9':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 1;
			break;
		case 'A':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 0;
			break;
		case 'B':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 1;
			break;
		case 'C':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 0;
			break;
		case 'D':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 1;
			break;
		case 'E':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 0;
			break;
		case 'F':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 1;
			break;
		case 'a':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 0;
			break;
		case 'b':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 0;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 1;
			break;
		case 'c':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 0;
			break;
		case 'd':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 0;
			newmd5[startOfEdit - 3] = 1;
			break;
		case 'e':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 0;
			break;
		case 'f':

			newmd5[startOfEdit] = 1;
			newmd5[startOfEdit - 1] = 1;
			newmd5[startOfEdit - 2] = 1;
			newmd5[startOfEdit - 3] = 1;
			break;
		}
	}

	indexOfTemp = 0;
	bitset<128> origin;
	// 使用最笨的办法，switch case把16进制的字符表示转换成2进制的结果
	for (; indexOfTemp < 32; indexOfTemp++) {
		int startOfEdit = 127 - 4 * indexOfTemp;
		switch (originMd5[indexOfTemp]) {
		case '0':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 0;
			break;
		case '1':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 1;
			break;
		case '2':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 0;
			break;
		case '3':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 1;
			break;
		case '4':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 0;
			break;
		case '5':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 1;
			break;
		case '6':
			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 0;
			break;
		case '7':

			origin[startOfEdit] = 0;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 1;
			break;
		case '8':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 0;
			break;
		case '9':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 1;
			break;
		case 'A':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 0;
			break;
		case 'B':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 1;
			break;
		case 'C':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 0;
			break;
		case 'D':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 1;
			break;
		case 'E':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 0;
			break;
		case 'F':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 1;
			break;
		case 'a':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 0;
			break;
		case 'b':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 0;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 1;
			break;
		case 'c':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 0;
			break;
		case 'd':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 0;
			origin[startOfEdit - 3] = 1;
			break;
		case 'e':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 0;
			break;
		case 'f':

			origin[startOfEdit] = 1;
			origin[startOfEdit - 1] = 1;
			origin[startOfEdit - 2] = 1;
			origin[startOfEdit - 3] = 1;
			break;
		}
	}

	bitset<128> result;
	result = newmd5 ^ origin;

	return result.count();
}


int main() {
	cout << "=======================MD5计算程序=======================\n";
	cout << "请输入一个字符串(为了进行雪崩效应的测试，请输入的字符串长度>=8)：\n";
	string m;
	cin >> m;
	cout << "经过计算可以得到MD5值为：\n";
	string md5M = myGetMD5(m);
	cout << md5M << endl;

	// 进行雪崩测试
	// 进行改变之后的字符串
	string newM;
	// 记录翻转的位数
	int changeBit[8] = {0};
	// 计算雪崩效应的平均位数
	int averageBit;
	int sumBit = 0;

	for (int i = 0; i < 8; i++) {
		cout << "\n\n=========================第" << i + 1 << "轮雪崩效应测试=========================\n";
		cout << "字符串的第" << i + 1 << "个char的值+1，得到新的字符串为：\n";
		newM = m;
		newM[i] += 1;
		cout << newM << endl;
		// 计算新的md5
		string newMd5M = myGetMD5(newM);
		cout << "经过计算可以得到修改过后的字符串MD5值为：\n" << newMd5M << endl;
		
		changeBit[i] = getCmpVal(newMd5M, md5M);
		sumBit += changeBit[i];
		cout << "经过比较后发生变化的位数为：";
		cout << changeBit[i] << endl;
	}

	averageBit = sumBit / 8;
	cout << "\n\n经过计算得到平均改变的位数为：" << averageBit << endl;

	system("pause");
	return 0;
}