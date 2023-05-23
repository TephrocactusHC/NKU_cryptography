#include<iostream>
#include<string>
#include<bitset>

using namespace std;

//�����߼�����
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

//xѭ������nλ
unsigned int shift(unsigned int x, unsigned int n) {
	return ((x << n) | (x >> (32 - n)));
}

// ��Ҫ�õ���һЩȫ�ֱ���
//������T�����ڲ���A�ֿ������
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

//ѹ������ÿ�ֵ�ÿ����A�ֿ�ѭ�����Ƶ�λ��
static const unsigned s[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

/// <summary>
/// ��32λint��������ת��Ϊ���Ѱַģʽ����16�����ַ�����ʽ���
/// </summary>
/// <param name="origin">int���ͱ��� </param>
/// <returns>string���ͱ���</returns>
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

/// <summary>
/// ����MD5��ֵ
/// </summary>
/// <param name="message">���ⳤ�ȵĴ�������Ϣ</param>
/// <returns>128����MD5�ַ���</returns>
string myGetMD5(string message) {
	//��ʼ��,������Ҫ���մ���ֽ���ķ�ʽ���д洢
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;

	// �õ���Ϣ�ĳ��ȣ���λ���ֽ�
	int lengthInByte = message.length();
	// �������������ͬʱ��Ҫע�⣺���һ��ʼ�͸պ���message=448(mod 512)Ҳ��Ҫ����10000��䣬�����������ֱ��+1
	int groupNum = ((lengthInByte + 8) / 64) + 1;

	// messageByte�����е�ÿһ��Ԫ�أ���Ӧ��Ϣ�����Ʊ�ʾ�е�32bit��4�ֽڣ�
	// ÿ������ĳ���Ϊ 16 * 32bit = 512bit
	unsigned int* messageByte = new unsigned int[groupNum * 16];

	// ��ʼ��
	memset(messageByte, 0, sizeof(unsigned int) * groupNum * 16);

	//��string���ͱ��� ����� messageByte������
	for (int i = 0; i < lengthInByte; i++)
	{
		//ÿ�����ж�Ӧ�洢4���ֽڵ�����
		messageByte[i / 4] |= message[i] << ((i % 4) * 8);
	}

	// �������
	messageByte[lengthInByte >> 2] |= 0x80 << ((lengthInByte % 4) * 8);

	// ������Ϣ
	messageByte[groupNum * 16 - 2] = lengthInByte * 8;

	// ��ʱ��������������ÿ����ÿһ������֮���abcd
	unsigned int a, b, c, d;

	// ѭ������ÿ������
	for (int i = 0; i < groupNum; i++)
	{
		a = A;
		b = B;
		c = C;
		d = D;
		unsigned int g;
		int k;

		// ��ÿ���������64��ѹ��
		for (int j = 0; j < 64; j++)
		{
			// ����������ͬ��ʹ�ò�ͬ��ѹ������
			if (j < 16)
			{
				// ��B C D���л����߼���������
				g = F(b, c, d);
				// ����k���Դ���Ϣ������ȡ����Ӧ����
				k = j;
			}
			else if (j >= 16 && j < 32)
			{
				// ��B C D���л����߼���������
				g = G(b, c, d);
				// ����k���Դ���Ϣ������ȡ����Ӧ����
				k = (1 + 5 * j) % 16;
			}
			else if (j >= 32 && j < 48)
			{
				// ��B C D���л����߼���������
				g = H(b, c, d);
				// ����k���Դ���Ϣ������ȡ����Ӧ����
				k = (5 + 3 * j) % 16;
			}
			else if (j >= 48 && j < 64)
			{
				// ��B C D���л����߼���������
				g = I(b, c, d);
				// ����k���Դ���Ϣ������ȡ����Ӧ����
				k = (7 * j) % 16;
			}

			unsigned tempd = d;
			d = c;
			c = b;
			b = b + shift(a + g + messageByte[i * 16 + k] + T[j], s[j]);
			a = tempd;
		}
		// ����ֵ
		A = a + A;
		B = b + B;
		C = c + C;
		D = d + D;
	}
	//����16������ʽ�ַ���
	return Int2HexString(A) + Int2HexString(B) + Int2HexString(C) + Int2HexString(D);
}

/// <summary>
/// ѩ��ЧӦ����ʱ���㲻ͬλ���ĺ���
/// </summary>
/// <param name="NewSumry">�ı������ַ���</param>
/// <param name="OrigiSumry">ԭʼ�ַ���</param>
/// <returns>��ͬ��λ��</returns>
int getCmpVal(string newMd5, string originMd5) {
	int indexOfTemp = 0;
	bitset<128> newmd5;
	// ʹ����İ취��switch case��16���Ƶ��ַ���ʾת����2���ƵĽ��
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
	// ʹ����İ취��switch case��16���Ƶ��ַ���ʾת����2���ƵĽ��
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
	cout << "=======================MD5�������=======================\n";
	cout << "������һ���ַ���(Ϊ�˽���ѩ��ЧӦ�Ĳ��ԣ���������ַ�������>=8)��\n";
	string m;
	cin >> m;
	cout << "����������Եõ�MD5ֵΪ��\n";
	string md5M = myGetMD5(m);
	cout << md5M << endl;

	// ����ѩ������
	// ���иı�֮����ַ���
	string newM;
	// ��¼��ת��λ��
	int changeBit[8] = {0};
	// ����ѩ��ЧӦ��ƽ��λ��
	int averageBit;
	int sumBit = 0;

	for (int i = 0; i < 8; i++) {
		cout << "\n\n=========================��" << i + 1 << "��ѩ��ЧӦ����=========================\n";
		cout << "�ַ����ĵ�" << i + 1 << "��char��ֵ+1���õ��µ��ַ���Ϊ��\n";
		newM = m;
		newM[i] += 1;
		cout << newM << endl;
		// �����µ�md5
		string newMd5M = myGetMD5(newM);
		cout << "����������Եõ��޸Ĺ�����ַ���MD5ֵΪ��\n" << newMd5M << endl;
		
		changeBit[i] = getCmpVal(newMd5M, md5M);
		sumBit += changeBit[i];
		cout << "�����ȽϺ����仯��λ��Ϊ��";
		cout << changeBit[i] << endl;
	}

	averageBit = sumBit / 8;
	cout << "\n\n��������õ�ƽ���ı��λ��Ϊ��" << averageBit << endl;

	system("pause");
	return 0;
}