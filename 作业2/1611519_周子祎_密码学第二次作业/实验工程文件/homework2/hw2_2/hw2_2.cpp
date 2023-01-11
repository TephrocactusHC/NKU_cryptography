#include "hw2_2.h"

int main() 
{
    //用户输入密钥
	string String_Key_Input;
    cout <<"请以16进制数形式输入64bit密钥(包含奇偶校验位)：" ;
    cin >> String_Key_Input;

	//根据用户输入的string获得char数组
	char * Char_Key = get_Key(String_Key_Input);

	//检查密钥输入是否合法
	while(true)
	{
		if(is_input_valid(Char_Key))
		{
			cout<<"64bit 密钥为："<< Char_Key<<endl;
			break;
		}
		else
		{
			cout<<"输入16进制数不合法"<<endl;
			cout <<"请以16进制数形式输入64bit密钥(包含奇偶校验位)：" ;
			cin >> String_Key_Input;
			Char_Key = get_Key(String_Key_Input);
		}
	}

	//用户输入密文
	string String_CipherText_Input;
    cout <<"请以16进制数形式输入64bit密文：" ;
    cin >> String_CipherText_Input;

	//根据用户输入的string获得char数组
	char * Char_CipherText = get_CipherText(String_CipherText_Input); 

	//检查密文输入是否合法
	while(true)
	{
		if(is_input_valid(Char_CipherText))
		{
			cout<<"64bit 密文为："<< Char_CipherText<<endl;
			break;
		}
		else
		{
			cout<<"输入16进制数不合法"<<endl;
			cout <<"请以16进制数形式输入64bit密文：" ;
			cin >> String_CipherText_Input;
			Char_CipherText = get_CipherText(String_CipherText_Input);
		}
	}

	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"开始解密处理"<<endl;
	cout<<"**************************************************************************************************"<<endl;

	//用于保存用户输入的64bit二进制密钥
	int Bit_Key_Init[64];

	//将输入的十六进制密钥char数组转换为二进制int数组
	Hex_to_Bin(Char_Key, Bit_Key_Init);
	cout<<"二进制初始密钥为：";
	for(int i=0;i<64;i++)
		cout<<Bit_Key_Init[i];
	cout<<endl;

	//用于保存用户输入的64bit二进制密文
	int Bit_CipherText_Init[64];

	//将输入的十六进制密文char数组转换为二进制int数组
	Hex_to_Bin(Char_CipherText, Bit_CipherText_Init);
	cout<<"二进制输入密文为：";
	for(int i=0;i<64;i++)
		cout<<Bit_CipherText_Init[i];
	cout<<endl;

	//-----------------子密钥获取------------------------------
	//先要获得16轮子密钥

	//PC-1置换后的二进制密钥数组(56bit)
	int Bit_Key_aft_PC1[56];

	//密钥完成初始置换PC-1
	for(int m=0;m<56;m++)
	{
		Bit_Key_aft_PC1[m]=Bit_Key_Init[PC1_Table[m]-1];
	}

	//把密钥分为左右两半
	int Bit_Key_l1[28],Bit_Key_r1[28];
	for(int m=0;m<56;m++)
	{
		if(m<28)
			Bit_Key_l1[m]=Bit_Key_aft_PC1[m];
		else
			Bit_Key_r1[m-28]=Bit_Key_aft_PC1[m];
	}

	//存储每轮子密钥用于解密
	int Round_Key_Store[16][48];

	//存储每轮移位后的左右密钥
	int Bit_Key_l2[28],Bit_Key_r2[28];

	//16轮次结构
	for(int round=0;round<16;round++)
	{
		//密钥左移位
		for(int m=0;m<28;m++)
		{
			Bit_Key_l2[m]=Bit_Key_l1[(m+LOOP_Table[round])%28];
			Bit_Key_r2[m]=Bit_Key_r1[(m+LOOP_Table[round])%28];
		}

		//更新左右密钥，用于下次循环使用
		for(int m=0;m<28;m++)
		{
			Bit_Key_l1[m]=Bit_Key_l2[m];
			Bit_Key_r1[m]=Bit_Key_r2[m];
		}

		//密钥完成PC-2置换
		for(int m=0;m<48;m++)
		{
			if(PC2_Table[m]<29)
			{
				Round_Key_Store[round][m]=Bit_Key_l2[PC2_Table[m]-1];
			}
			else
			{
				Round_Key_Store[round][m]=Bit_Key_r2[PC2_Table[m]-29];
			}
		}
	}
	//-----------------子密钥获取结束--------------------------


	//IP置换后的二进制密文数组(64bit)
	int Bit_CipherText_aft_IP[64];

	//密文完成初始IP置换
	for(int m=0;m<64;m++)
	{
		Bit_CipherText_aft_IP[m]=Bit_CipherText_Init[IP_Table[m]-1];
	}

	//把密文分为左右两半
	int Bit_CipherText_l1[32],Bit_CipherText_r1[32];
	for(int m=0;m<64;m++)
	{
		if(m<32)
			Bit_CipherText_l1[m]=Bit_CipherText_aft_IP[m];
		else
			Bit_CipherText_r1[m-32]=Bit_CipherText_aft_IP[m];
	}

	//存储左右明文
	int Bit_CipherText_l2[32],Bit_CipherText_r2[32];
	int Bit_CipherText_l3[32],Bit_CipherText_r3[48];

	//16轮次结构
	for(int round=0;round<16;round++)
	{

		//对右明文备份
		for(int m=0;m<32;m++)
		{
			Bit_CipherText_r2[m]=Bit_CipherText_r1[m];
		}

		//对右明文进行E扩展运算
		for(int m=0;m<48;m++)
		{
			Bit_CipherText_r3[m]=Bit_CipherText_r1[E_Table[m]-1];
		}

		//右明文与对应的轮密钥做异或运算
		for(int m=0;m<48;m++)
		{
			Bit_CipherText_r3[m]=Bit_CipherText_r3[m]^Round_Key_Store[15-round][m];
		}

		//右明文S盒代换
		for(int m=0;m<8;m++)
		{
			//根据右明文的值从S_Box中选出值
			int s;
			s=S_Box[(Bit_CipherText_r3[m*6]*2+Bit_CipherText_r3[5+m*6])+m*4][Bit_CipherText_r3[1+m*6]*8+Bit_CipherText_r3[2+m*6]*4+Bit_CipherText_r3[3+m*6]*2+Bit_CipherText_r3[4+m*6]];


			//将S_Box中选中的值表示为二进制 并 赋值到Bit_PlainText_r3中
			for(int n=1;n<=4;n++)
			{
				Bit_CipherText_r3[(4-n)+4*m]=s%2;
				s=s/2;
			}
		}

		//右明文完成P置换,与左明文异或,并将备份的本轮原始右明文传给左明文，用于下次循环使用
		for(int m=0;m<32;m++)
		{
			Bit_CipherText_r1[m]=Bit_CipherText_r3[P_Table[m]-1]^Bit_CipherText_l1[m];
			Bit_CipherText_l1[m]=Bit_CipherText_r2[m];
		}
	}

	//逆初始置换IPR置换前的二进制明文数组(64bit)
	int Bit_PlainText_bfr_IPR[64];

	//16轮后密文左右交换得到明文
	for(int m=0;m<64;m++)
	{
		if(m<32)
			Bit_PlainText_bfr_IPR[m]=Bit_CipherText_r1[m];
		else
			Bit_PlainText_bfr_IPR[m]=Bit_CipherText_l1[m-32];
	}

	//逆初始置换IPR置换后的二进制明文数组(64bit)
	int Bit_PlainText_aft_IPR[64];

	//明文完成逆初始置换
	for(int m=0;m<64;m++)
	{
		Bit_PlainText_aft_IPR[m]=Bit_PlainText_bfr_IPR[IPR_Table[m]-1];
	}

	cout<<"二进制结果明文为：";
	for(int m=0;m<64;m++)
	{
		cout<<Bit_PlainText_aft_IPR[m];
	}
	cout<<endl;

	//存储明文十六进制char数组
	char Char_PlainText[17];

	//将得到的二进制明文int数组转化为十六进制char数组
	Bin_to_Hex(Bit_PlainText_aft_IPR, Char_PlainText);

	//输出16进制密钥、明文、密文，方便对比结果
	cout<<"**************************************************************************************************"<<endl;
	
	//输出密钥
	cout<<"十六进制 密钥为："<<Char_Key<<endl;
	
	//输出密文
	cout<<"十六进制 密文为："<<Char_CipherText<<endl;

	//输出明文
	cout<<"十六进制 明文为："<<Char_PlainText<<endl;

	cout<<"**************************************************************************************************"<<endl;
    system("pause");
    return 0;
}

//将用户输入String 转换为 char数组Char_Key
char * get_Key(string String_Key_Input)
{
	//截取前16位十六进制数作为密钥
	string String_Key = String_Key_Input.substr(0,16);

	//不足16位十六进制数则末尾补0至16位十六进制数
	if(String_Key.size()<16)
	{
		int temp_String_Key_size = String_Key.size();
		for(int i=1;i<=16 - temp_String_Key_size;i++)
		{
			String_Key = String_Key + '0';
		}
	}

	char* Char_Key = new char[17];
	String_Key.copy(Char_Key, 16, 0);
	Char_Key[16] = '\0';

	return Char_Key;
}

//将用户输入String 转换为 char数组Char_CipherText
char * get_CipherText(string String_CipherText_Input)
{
	//截取前16位十六进制数作为明文
	string String_CipherText = String_CipherText_Input.substr(0,16);

	//不足16位十六进制数则末尾补0至16位十六进制数
	if(String_CipherText.size()<16)
	{
		int temp_String_CipherText_size = String_CipherText.size();
		for(int i=1;i<=16 - temp_String_CipherText_size;i++)
		{
			String_CipherText = String_CipherText + '0';
		}
	}

	char* Char_CipherText = new char[17];
	String_CipherText.copy(Char_CipherText, 16, 0);
	Char_CipherText[16] = '\0';

	return Char_CipherText;
}

//检查用户输入16进制数是否合法
bool is_input_valid(char * str)
{
	for(int i=0;i<=15;i++)
	{
		if(!( (str[i]>='A'&&str[i]<='F') || (str[i]>='a'&&str[i]<='f') ||(str[i]>='0'&&str[i]<='9') ))
		{
			return 0;
		}
	}
	return 1;
}

//十六进制char数组转换为二进制int数组
void Hex_to_Bin(char * Hex, int * Bin)
{
	int i=0,k=0,j=0;

	for(i=0;i<16;i++)
	{
		int val = 0;
		if(Hex[i] >= '0' && Hex[i] <= '9')
			val = Hex[i]-'0';
		else if (Hex[i] >= 'A' && Hex[i] <= 'F')
			val = Hex[i]-'A'+10;
		else if (Hex[i] >= 'a' && Hex[i] <= 'f')
			val = Hex[i]-'a'+10;

		for(int k=4*i+3;k>=4*i;k--)
		{
			Bin[k] = val % 2;
			val/=2;
		}
	}
}

//二进制int数组转换为十六进制char数组
void Bin_to_Hex(int * Bin, char * Hex)
{
	int i=0,k=0,j=0;

	for(i=0;i<16;i++)
	{
		int val = 0;

		for(int k=4*i;k<=4*i+3;k++)
		{
			val *= 2;
			val += Bin[k];
		}
		
		if( val<10 )
			Hex[i] = val+'0';
		else if (val >=10 && val <=15 )
			Hex[i] = val-10+'A';
	}

	Hex[16]='\0';
}