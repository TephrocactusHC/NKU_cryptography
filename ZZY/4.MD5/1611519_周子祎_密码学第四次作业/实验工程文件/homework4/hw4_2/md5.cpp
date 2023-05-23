#include "md5.h"

//��32λint��������ת��Ϊ���Ѱַģʽ����16�����ַ�����ʽ���
//���룺int���ͱ��� 
//�����string���ͱ��� 
string Int2HexString(int origin)
{
	const char str16[] = "0123456789abcdef";
	unsigned hexNum;

	string temp;
	string hexString = "";

	for (int i = 0; i < 4; i++) 
	{
		//�����е�4���ֽ���һ������
		temp = "";

		//��origin��ȡ��Ӧ��8bit���õ����ֽ�����ʾ��ֵ
		hexNum = (origin >> (i * 8)) & 0xff;
		
		for (int j = 0; j < 2; j++) 
		{
			//ÿ��λ��Ӧһ��16������
			//��temp��0������1�� str16[hexNum % 16]
			temp.insert(0, 1, str16[hexNum % 16]);
			hexNum /= 16;
		}

		hexString += temp;
	}
	return hexString;
}

//���ĺ�����
//���룺string���ͱ��� ���ⳤ��������Ϣ message
//�����string���ͱ��� 128������ϢժҪ
string md5(string message)
{
	//��ʼ��MD������
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;
	
	int lengthInByte = message.length();
	//Ԥ�����ȣ�8byte=64bit�����ڱ�����Ϣ�����ǰ�ĳ���
	//���鳤�ȣ�64byte=512bit
	//�������������ֱ�����
	//+1�����ԭʼ��Ϣ����ǡ������ģ512Ϊ448��Ҳ��Ҫ�������
	int groupNum = ((lengthInByte + 8) / 64) + 1;

	// messageByte�����е�ÿһ��Ԫ�أ���Ӧ��Ϣ�����Ʊ�ʾ�е�32bit��4�ֽڣ�
	//ÿ������ĳ���Ϊ 16 * 32bit = 512bit
	unsigned int *messageByte = new unsigned int[groupNum * 16];

	//����
	memset(messageByte, 0, sizeof(unsigned int)*groupNum * 16);

	//��string���ͱ��� ����� messageByte������
	for (int i = 0; i < lengthInByte; i++) 
	{
		//ÿ�����ж�Ӧ�洢4���ֽڵ�����
		messageByte[i / 4] |= message[i] << ((i % 4) * 8);
	}

	//�������
	messageByte[lengthInByte >> 2] |= 0x80 << ((lengthInByte % 4) * 8);
	
	//������Ϣ
	messageByte[groupNum * 16 - 2] = lengthInByte * 8;

	unsigned int a, b, c, d;
	
	//ѭ������ÿ������
	for (int i = 0; i < groupNum; i++) 
	{
		//ת�滺�����Ĵ�����ֵ
		a = A; 
		b = B; 
		c = C; 
		d = D;
		unsigned int g;
		int k;

		//��ÿ���������64��ѹ��
		for (int j = 0; j < 64; j++) 
		{
			//����������ͬ��ʹ�ò�ͬ��ѹ������
			if ( j < 16 )  
			{
				//��B C D���л����߼���������
				g = F(b, c, d);
				//����k���Դ���Ϣ������ȡ����Ӧ����
				k = j;
			}
			else if ( j>=16 && j < 32 ) 
			{
				//��B C D���л����߼���������
				g = G(b, c, d);
				//����k���Դ���Ϣ������ȡ����Ӧ����
				k = (1 + 5 * j) % 16;
			}
			else if ( j>=32 && j < 48 ) 
			{
				//��B C D���л����߼���������
				g = H(b, c, d);
				//����k���Դ���Ϣ������ȡ����Ӧ����
				k = (5 + 3 * j) % 16;
			}
			else if ( j>=48 && j < 64 )
			{
				//��B C D���л����߼���������
				g = I(b, c, d);
				//����k���Դ���Ϣ������ȡ����Ӧ����
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
	//����16������ʽ�ַ���
	return Int2HexString(A) + Int2HexString(B) + Int2HexString(C) + Int2HexString(D);
}

int BitCmp(string NewSumry,string OrigiSumry)
{
	int BitDiff = 0;

	//NewSumry��OrigiSumry��Ϊ����32���ַ����ַ�����ÿ���ַ�����һ��16��������4����
	//����ֱ��Ϊ8���֣��ֱ���бȽϣ����㴦��
	for(int part=0;part<8;part++)
	{
		//��ժҪȡ��4��char��תΪ1��long
		string NewSumry_temp =NewSumry.substr(0+4*part, 4);
		char * end_1;
		long NewSumry_Int = static_cast<long>(strtol(NewSumry_temp.c_str(),&end_1,16));

		//ԭʼժҪȡ��4��char��תΪ1��long
		string OrigiSumry_temp =OrigiSumry.substr(0+4*part, 4);
		char * end_2;
		long OrigiSumry_Int = static_cast<long>(strtol(OrigiSumry_temp.c_str(),&end_2,16));
				
		//������long�������Ƚ�������Ʊ�ʾ������λ��
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
