#include "hw2_1.h"

int main() 
{
    //�û�������Կ
	string String_Key_Input;
    cout <<"����16��������ʽ����64bit��Կ(������żУ��λ)��" ;
    cin >> String_Key_Input;

	//�����û������string���char����
	char * Char_Key = get_Key(String_Key_Input);

	//�����Կ�����Ƿ�Ϸ�
	while(true)
	{
		if(is_input_valid(Char_Key))
		{
			cout<<"64bit ��ԿΪ��"<< Char_Key<<endl;
			break;
		}
		else
		{
			cout<<"����16���������Ϸ�"<<endl;
			cout <<"����16��������ʽ����64bit��Կ(������żУ��λ)��" ;
			cin >> String_Key_Input;
			Char_Key = get_Key(String_Key_Input);
		}
	}

	//�û���������
	string String_PlainText_Input;
    cout <<"����16��������ʽ����64bit���ģ�" ;
    cin >> String_PlainText_Input;

	//�����û������string���char����
	char * Char_PlainText = get_PlainText(String_PlainText_Input); 

	//������������Ƿ�Ϸ�
	while(true)
	{
		if(is_input_valid(Char_PlainText))
		{
			cout<<"64bit ����Ϊ��"<< Char_PlainText<<endl;
			break;
		}
		else
		{
			cout<<"����16���������Ϸ�"<<endl;
			cout <<"����16��������ʽ����64bit���ģ�" ;
			cin >> String_PlainText_Input;
			Char_PlainText = get_PlainText(String_PlainText_Input);
		}
	}

	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"��ʼ���ܴ���"<<endl;
	cout<<"**************************************************************************************************"<<endl;

	//���ڱ����û������64bit��������Կ
	int Bit_Key_Init[64];

	//�������ʮ��������Կchar����ת��Ϊ������int����
	Hex_to_Bin(Char_Key, Bit_Key_Init);
	cout<<"�����Ƴ�ʼ��ԿΪ��";
	for(int i=0;i<64;i++)
		cout<<Bit_Key_Init[i];
	cout<<endl;

	//���ڱ����û������64bit����������
	int Bit_PlainText_Init[64];

	//�������ʮ����������char����ת��Ϊ������int����
	Hex_to_Bin(Char_PlainText, Bit_PlainText_Init);
	cout<<"��������������Ϊ��";
	for(int i=0;i<64;i++)
		cout<<Bit_PlainText_Init[i];
	cout<<endl;

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

	cout<<"�����ƽ������Ϊ��";
	for(int m=0;m<64;m++)
	{
		cout<<Bit_CipherText_aft_IPR[m];
	}
	cout<<endl;

	//�洢����ʮ������char����
	char Char_CipherText[17];

	//���õ��Ķ���������int����ת��Ϊʮ������char����
	Bin_to_Hex(Bit_CipherText_aft_IPR, Char_CipherText);

	//���16������Կ�����ġ����ģ�����ԱȽ��
	cout<<"**************************************************************************************************"<<endl;
	
	//�����Կ
	cout<<"ʮ������ ��ԿΪ��"<<Char_Key<<endl;

	//�������
	cout<<"ʮ������ ����Ϊ��"<<Char_PlainText<<endl;

	//�������
	cout<<"ʮ������ ����Ϊ��"<<Char_CipherText<<endl;

	cout<<"**************************************************************************************************"<<endl;
    system("pause");
    return 0;
}

