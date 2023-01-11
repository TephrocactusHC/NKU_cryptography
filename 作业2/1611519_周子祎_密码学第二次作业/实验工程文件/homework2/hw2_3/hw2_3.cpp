//本程序文件用于测试改变密钥中的1位引发的雪崩效应
#include "hw2_3.h"

int main() 
{

	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"开始加密处理"<<endl;
	cout<<"**************************************************************************************************"<<endl;

	//用于保存原本的64bit二进制密钥
	int Bit_Key_Init_former[64] = { 0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0} ;

	//用于保存原本的64bit二进制明文
	int Bit_PlainText_Init_former[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//用于保存原本的64bit二进制密文
	int Bit_CipherText_aft_IPR_former[64] = {1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0};


	//实际使用的密钥
	int Bit_Key_Init[64] = { 0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0} ;

	//实际使用的明文
	int Bit_PlainText_Init[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//-------------------下面测试密钥改变一位引发的雪崩效应，依次改变明文中的每一位，统计密文发生改变的位数-------------------

	cout<<"开始测试密钥改变一位引发的雪崩效应："<<endl;

	//改变的是密钥的第几位
	int Key_ChangedBit = 0;

	//记录改变密钥每一位后密文发生变化的位数
	int Avalanche_Record_Key[64] = {0};

	//依次改变密钥的第0位--第63位，统计密文改变的位数
	for(;Key_ChangedBit<64;Key_ChangedBit++)
	{
		//反转第Key_ChangedBit位
		Bit_Key_Init[Key_ChangedBit] = 1-Bit_Key_Init[Key_ChangedBit];

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

		//IP置换后的二进制明文数组(64bit)
		int Bit_PlainText_aft_IP[64];

		//明文完成初始IP置换
		for(int m=0;m<64;m++)
		{
			Bit_PlainText_aft_IP[m]=Bit_PlainText_Init[IP_Table[m]-1];
		}

		//把明文分为左右两半
		int Bit_PlainText_l1[32],Bit_PlainText_r1[32];
		for(int m=0;m<64;m++)
		{
			if(m<32)
				Bit_PlainText_l1[m]=Bit_PlainText_aft_IP[m];
			else
				Bit_PlainText_r1[m-32]=Bit_PlainText_aft_IP[m];
		}

		//存储每轮子密钥用于解密
		int Round_Key_Store[16][48];

		//存储每轮移位后的左右密钥
		int Bit_Key_l2[28],Bit_Key_r2[28];

		//存储左右明文
		int Bit_PlainText_l2[32],Bit_PlainText_r2[32];
		int Bit_PlainText_l3[32],Bit_PlainText_r3[48];

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

			//对右明文备份
			for(int m=0;m<32;m++)
			{
				Bit_PlainText_r2[m]=Bit_PlainText_r1[m];
			}

			//对右明文进行E扩展运算
			for(int m=0;m<48;m++)
			{
				Bit_PlainText_r3[m]=Bit_PlainText_r1[E_Table[m]-1];
			}

			//右明文与密钥做异或运算
			for(int m=0;m<48;m++)
			{
				Bit_PlainText_r3[m]=Bit_PlainText_r3[m]^Round_Key_Store[round][m];
			}

			//右明文S盒代换
			for(int m=0;m<8;m++)
			{
				//根据右明文的值从S_Box中选出值
				int s;
				s=S_Box[(Bit_PlainText_r3[m*6]*2+Bit_PlainText_r3[5+m*6])+m*4][Bit_PlainText_r3[1+m*6]*8+Bit_PlainText_r3[2+m*6]*4+Bit_PlainText_r3[3+m*6]*2+Bit_PlainText_r3[4+m*6]];


				//将S_Box中选中的值表示为二进制 并 赋值到Bit_PlainText_r3中
				for(int n=1;n<=4;n++)
				{
					Bit_PlainText_r3[(4-n)+4*m]=s%2;
					s=s/2;
				}
			}

			//右明文完成P置换,与左明文异或,并将备份的本轮原始右明文传给左明文，用于下次循环使用
			for(int m=0;m<32;m++)
			{
				Bit_PlainText_r1[m]=Bit_PlainText_r3[P_Table[m]-1]^Bit_PlainText_l1[m];
				Bit_PlainText_l1[m]=Bit_PlainText_r2[m];
			}
		}

		//逆初始置换IPR置换前的二进制密文数组(64bit)
		int Bit_CipherText_bfr_IPR[64];

		//16轮后明文左右交换形成密文
		for(int m=0;m<64;m++)
		{
			if(m<32)
				Bit_CipherText_bfr_IPR[m]=Bit_PlainText_r1[m];
			else
				Bit_CipherText_bfr_IPR[m]=Bit_PlainText_l1[m-32];
		}

		//逆初始置换IPR置换后的二进制密文数组(64bit)
		int Bit_CipherText_aft_IPR[64];

		//密文完成逆初始置换
		for(int m=0;m<64;m++)
		{
			Bit_CipherText_aft_IPR[m]=Bit_CipherText_bfr_IPR[IPR_Table[m]-1];
		}

		int ChangedBit_temp = 0;

		for(int m=0;m<64;m++)
		{
			if(Bit_CipherText_aft_IPR[m] != Bit_CipherText_aft_IPR_former[m])
				ChangedBit_temp++;
		}

		//变化位数记录到Avalanche_Record_Key数组里
		Avalanche_Record_Key[Key_ChangedBit] = ChangedBit_temp;

		cout<<"--------------------------------------------------------------------------------------------------"<<endl;
		cout<<"改变密钥第"<<Key_ChangedBit<<"位"<<endl;

		cout<<"新密文为：";
		for(int m=0;m<64;m++)
		{
			cout<<Bit_CipherText_aft_IPR[m];
		}
		cout<<endl;

		cout<<"原密文为：";
		for(int m=0;m<64;m++)
		{
			cout<<Bit_CipherText_aft_IPR_former[m];
		}
		cout<<endl;

		cout<<"密文改变位数为："<<Avalanche_Record_Key[Key_ChangedBit]<<endl;

		cout<<"**************************************************************************************************"<<endl;
	}

	cout<<"改变密钥第几位"<<'\t'<<"引发的密文改变位数"<<'\t'<<endl;
	for(int m=0;m<64;m++)
	{
		cout<<'\t'<<m<<'\t'<<'\t'<<Avalanche_Record_Key[m]<<'\t'<<endl;
	}

	double Average_changed =0;
	for(int m=0;m<64;m++)
	{
		Average_changed+=Avalanche_Record_Key[m];
	}
	Average_changed /=64;

	cout<<"改变密钥中的一位，引发密文改变的平均位数为"<<Average_changed<<endl;

    system("pause");
    return 0;
}