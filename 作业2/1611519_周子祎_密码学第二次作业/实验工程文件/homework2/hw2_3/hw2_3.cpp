//�������ļ����ڲ��Ըı���Կ�е�1λ������ѩ��ЧӦ
#include "hw2_3.h"

int main() 
{

	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"��ʼ���ܴ���"<<endl;
	cout<<"**************************************************************************************************"<<endl;

	//���ڱ���ԭ����64bit��������Կ
	int Bit_Key_Init_former[64] = { 0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0} ;

	//���ڱ���ԭ����64bit����������
	int Bit_PlainText_Init_former[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//���ڱ���ԭ����64bit����������
	int Bit_CipherText_aft_IPR_former[64] = {1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0};


	//ʵ��ʹ�õ���Կ
	int Bit_Key_Init[64] = { 0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0} ;

	//ʵ��ʹ�õ�����
	int Bit_PlainText_Init[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//-------------------���������Կ�ı�һλ������ѩ��ЧӦ�����θı������е�ÿһλ��ͳ�����ķ����ı��λ��-------------------

	cout<<"��ʼ������Կ�ı�һλ������ѩ��ЧӦ��"<<endl;

	//�ı������Կ�ĵڼ�λ
	int Key_ChangedBit = 0;

	//��¼�ı���Կÿһλ�����ķ����仯��λ��
	int Avalanche_Record_Key[64] = {0};

	//���θı���Կ�ĵ�0λ--��63λ��ͳ�����ĸı��λ��
	for(;Key_ChangedBit<64;Key_ChangedBit++)
	{
		//��ת��Key_ChangedBitλ
		Bit_Key_Init[Key_ChangedBit] = 1-Bit_Key_Init[Key_ChangedBit];

		//PC-1�û���Ķ�������Կ����(56bit)
		int Bit_Key_aft_PC1[56];

		//��Կ��ɳ�ʼ�û�PC-1
		for(int m=0;m<56;m++)
		{
			Bit_Key_aft_PC1[m]=Bit_Key_Init[PC1_Table[m]-1];
		}

		//����Կ��Ϊ��������
		int Bit_Key_l1[28],Bit_Key_r1[28];
		for(int m=0;m<56;m++)
		{
			if(m<28)
				Bit_Key_l1[m]=Bit_Key_aft_PC1[m];
			else
				Bit_Key_r1[m-28]=Bit_Key_aft_PC1[m];
		}

		//IP�û���Ķ�������������(64bit)
		int Bit_PlainText_aft_IP[64];

		//������ɳ�ʼIP�û�
		for(int m=0;m<64;m++)
		{
			Bit_PlainText_aft_IP[m]=Bit_PlainText_Init[IP_Table[m]-1];
		}

		//�����ķ�Ϊ��������
		int Bit_PlainText_l1[32],Bit_PlainText_r1[32];
		for(int m=0;m<64;m++)
		{
			if(m<32)
				Bit_PlainText_l1[m]=Bit_PlainText_aft_IP[m];
			else
				Bit_PlainText_r1[m-32]=Bit_PlainText_aft_IP[m];
		}

		//�洢ÿ������Կ���ڽ���
		int Round_Key_Store[16][48];

		//�洢ÿ����λ���������Կ
		int Bit_Key_l2[28],Bit_Key_r2[28];

		//�洢��������
		int Bit_PlainText_l2[32],Bit_PlainText_r2[32];
		int Bit_PlainText_l3[32],Bit_PlainText_r3[48];

		//16�ִνṹ
		for(int round=0;round<16;round++)
		{
			//��Կ����λ
			for(int m=0;m<28;m++)
			{
				Bit_Key_l2[m]=Bit_Key_l1[(m+LOOP_Table[round])%28];
				Bit_Key_r2[m]=Bit_Key_r1[(m+LOOP_Table[round])%28];
			}

			//����������Կ�������´�ѭ��ʹ��
			for(int m=0;m<28;m++)
			{
				Bit_Key_l1[m]=Bit_Key_l2[m];
				Bit_Key_r1[m]=Bit_Key_r2[m];
			}

			//��Կ���PC-2�û�
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

			//�������ı���
			for(int m=0;m<32;m++)
			{
				Bit_PlainText_r2[m]=Bit_PlainText_r1[m];
			}

			//�������Ľ���E��չ����
			for(int m=0;m<48;m++)
			{
				Bit_PlainText_r3[m]=Bit_PlainText_r1[E_Table[m]-1];
			}

			//����������Կ���������
			for(int m=0;m<48;m++)
			{
				Bit_PlainText_r3[m]=Bit_PlainText_r3[m]^Round_Key_Store[round][m];
			}

			//������S�д���
			for(int m=0;m<8;m++)
			{
				//���������ĵ�ֵ��S_Box��ѡ��ֵ
				int s;
				s=S_Box[(Bit_PlainText_r3[m*6]*2+Bit_PlainText_r3[5+m*6])+m*4][Bit_PlainText_r3[1+m*6]*8+Bit_PlainText_r3[2+m*6]*4+Bit_PlainText_r3[3+m*6]*2+Bit_PlainText_r3[4+m*6]];


				//��S_Box��ѡ�е�ֵ��ʾΪ������ �� ��ֵ��Bit_PlainText_r3��
				for(int n=1;n<=4;n++)
				{
					Bit_PlainText_r3[(4-n)+4*m]=s%2;
					s=s/2;
				}
			}

			//���������P�û�,�����������,�������ݵı���ԭʼ�����Ĵ��������ģ������´�ѭ��ʹ��
			for(int m=0;m<32;m++)
			{
				Bit_PlainText_r1[m]=Bit_PlainText_r3[P_Table[m]-1]^Bit_PlainText_l1[m];
				Bit_PlainText_l1[m]=Bit_PlainText_r2[m];
			}
		}

		//���ʼ�û�IPR�û�ǰ�Ķ�������������(64bit)
		int Bit_CipherText_bfr_IPR[64];

		//16�ֺ��������ҽ����γ�����
		for(int m=0;m<64;m++)
		{
			if(m<32)
				Bit_CipherText_bfr_IPR[m]=Bit_PlainText_r1[m];
			else
				Bit_CipherText_bfr_IPR[m]=Bit_PlainText_l1[m-32];
		}

		//���ʼ�û�IPR�û���Ķ�������������(64bit)
		int Bit_CipherText_aft_IPR[64];

		//����������ʼ�û�
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

		//�仯λ����¼��Avalanche_Record_Key������
		Avalanche_Record_Key[Key_ChangedBit] = ChangedBit_temp;

		cout<<"--------------------------------------------------------------------------------------------------"<<endl;
		cout<<"�ı���Կ��"<<Key_ChangedBit<<"λ"<<endl;

		cout<<"������Ϊ��";
		for(int m=0;m<64;m++)
		{
			cout<<Bit_CipherText_aft_IPR[m];
		}
		cout<<endl;

		cout<<"ԭ����Ϊ��";
		for(int m=0;m<64;m++)
		{
			cout<<Bit_CipherText_aft_IPR_former[m];
		}
		cout<<endl;

		cout<<"���ĸı�λ��Ϊ��"<<Avalanche_Record_Key[Key_ChangedBit]<<endl;

		cout<<"**************************************************************************************************"<<endl;
	}

	cout<<"�ı���Կ�ڼ�λ"<<'\t'<<"���������ĸı�λ��"<<'\t'<<endl;
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

	cout<<"�ı���Կ�е�һλ���������ĸı��ƽ��λ��Ϊ"<<Average_changed<<endl;

    system("pause");
    return 0;
}