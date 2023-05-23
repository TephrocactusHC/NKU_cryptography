const unsigned int T[64] =
{
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
	0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
	0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
	0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05, 0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
	0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
	0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};

//轮移位
const int FN[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22 };
const int GN[] = { 5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20 };
const int HN[] = { 4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23 };
const int IN[] = { 6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21 };
//轮hash函数
unsigned int F(unsigned int b, unsigned int c, unsigned int d) { return ((b & c) | ((~b) & d)); }
unsigned int G(unsigned int b, unsigned int c, unsigned int d) { return ((b & d) | (c & ~d)); }
unsigned int H(unsigned int b, unsigned int c, unsigned int d) { return b^c^d; }
unsigned int I(unsigned int b, unsigned int c, unsigned int d) { return c ^ (b | (~d)); }
//初始值的little-endian
unsigned int a = 0x67452301;
unsigned int b = 0xefcdab89;
unsigned int c = 0x98badcfe;
unsigned int d = 0x10325476;
//初始值
unsigned int a1 = 0x01234567;
unsigned int b1 = 0x89abcdef;
unsigned int c1 = 0xfedcba98;
unsigned int d1 = 0x76543210;

int longtonum(long long t);
int leftShift(unsigned int& dst, int num);
unsigned int Plus32(unsigned int a,unsigned int b);
unsigned int LittleEnd(unsigned int a);
int trans(unsigned int t[],unsigned char s[],int l);
int trans(unsigned int t[], char s[], int l);
void functionF(unsigned int& a,unsigned int& b,unsigned int& c,unsigned int& d,unsigned int x[]);
void functionG(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int x[]);
void functionH(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int x[]);
void functionI(unsigned int& a, unsigned int& b, unsigned int& c, unsigned int& d, unsigned int x[]);
