#include "md5.h"

//将32位int型整数，转化为大端寻址模式，以16进制字符串形式输出
//输入：int类型变量 
//输出：string类型变量 
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

//核心函数：
//输入：string类型变量 任意长待处理消息 message
//输出：string类型变量 128比特消息摘要
string md5(string message)
{
	//初始化MD缓冲区
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;
	
	int lengthInByte = message.length();
	//预留长度，8byte=64bit，用于保存消息被填充前的长度
	//分组长度，64byte=512bit
	//整除：余数部分被忽略
	//+1：如果原始消息长度恰好满足模512为448，也需要进行填充
	int groupNum = ((lengthInByte + 8) / 64) + 1;

	// messageByte数组中的每一个元素，对应消息二进制表示中的32bit（4字节）
	//每个分组的长度为 16 * 32bit = 512bit
	unsigned int *messageByte = new unsigned int[groupNum * 16];

	//清零
	memset(messageByte, 0, sizeof(unsigned int)*groupNum * 16);

	//将string类型变量 保存进 messageByte数组中
	for (int i = 0; i < lengthInByte; i++) 
	{
		//每个字中对应存储4个字节的数据
		messageByte[i / 4] |= message[i] << ((i % 4) * 8);
	}

	//进行填充
	messageByte[lengthInByte >> 2] |= 0x80 << ((lengthInByte % 4) * 8);
	
	//附加信息
	messageByte[groupNum * 16 - 2] = lengthInByte * 8;

	unsigned int a, b, c, d;
	
	//循环处理每个分组
	for (int i = 0; i < groupNum; i++) 
	{
		//转存缓冲区寄存器的值
		a = A; 
		b = B; 
		c = C; 
		d = D;
		unsigned int g;
		int k;

		//对每个分组进行64轮压缩
		for (int j = 0; j < 64; j++) 
		{
			//根据轮数不同，使用不同的压缩函数
			if ( j < 16 )  
			{
				//对B C D进行基本逻辑函数运算
				g = F(b, c, d);
				//计算k，以从消息分组中取出对应的字
				k = j;
			}
			else if ( j>=16 && j < 32 ) 
			{
				//对B C D进行基本逻辑函数运算
				g = G(b, c, d);
				//计算k，以从消息分组中取出对应的字
				k = (1 + 5 * j) % 16;
			}
			else if ( j>=32 && j < 48 ) 
			{
				//对B C D进行基本逻辑函数运算
				g = H(b, c, d);
				//计算k，以从消息分组中取出对应的字
				k = (5 + 3 * j) % 16;
			}
			else if ( j>=48 && j < 64 )
			{
				//对B C D进行基本逻辑函数运算
				g = I(b, c, d);
				//计算k，以从消息分组中取出对应的字
				k = (7 * j) % 16;
			}

			unsigned tempd = d;
			d = c;
			c = b;
			b = b + shift(a + g + messageByte[i * 16 + k] + T[j], s[j]);
			a = tempd;
		}
		A = a + A;
		B = b + B;
		C = c + C;
		D = d + D;
	}
	//返回16进制形式字符串
	return Int2HexString(A) + Int2HexString(B) + Int2HexString(C) + Int2HexString(D);
}

int BitCmp(string NewSumry,string OrigiSumry)
{
	int BitDiff = 0;

	//NewSumry、OrigiSumry均为包含32个字符的字符串，每个字符代表一个16进制数，4比特
	//将其分别分为8部分，分别进行比较，方便处理
	for(int part=0;part<8;part++)
	{
		//新摘要取出4个char，转为1个long
		string NewSumry_temp =NewSumry.substr(0+4*part, 4);
		char * end_1;
		long NewSumry_Int = static_cast<long>(strtol(NewSumry_temp.c_str(),&end_1,16));

		//原始摘要取出4个char，转为1个long
		string OrigiSumry_temp =OrigiSumry.substr(0+4*part, 4);
		char * end_2;
		long OrigiSumry_Int = static_cast<long>(strtol(OrigiSumry_temp.c_str(),&end_2,16));
				
		//对两个long整数，比较其二进制表示中相差的位数
		for(int round = 0;round <16;round++ )
		{
			if( NewSumry_Int%2 != OrigiSumry_Int%2)
			{
				BitDiff++;
			}
			NewSumry_Int /= 2;
			OrigiSumry_Int /= 2;
		}
	}

	 return BitDiff;
}
