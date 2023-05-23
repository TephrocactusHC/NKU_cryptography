#include "hw2_2.h"

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
	string String_CipherText_Input;
    cout <<"����16��������ʽ����64bit���ģ�" ;
    cin >> String_CipherText_Input;

	//�����û������string���char����
	char * Char_CipherText = get_CipherText(String_CipherText_Input); 

	//������������Ƿ�Ϸ�
	while(true)
	{
		if(is_input_valid(Char_CipherText))
		{
			cout<<"64bit ����Ϊ��"<< Char_CipherText<<endl;
			break;
		}
		else
		{
			cout<<"����16���������Ϸ�"<<endl;
			cout <<"����16��������ʽ����64bit���ģ�" ;
			cin >> String_CipherText_Input;
			Char_CipherText = get_CipherText(String_CipherText_Input);
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
	int Bit_CipherText_Init[64];

	//�������ʮ����������char����ת��Ϊ������int����
	Hex_to_Bin(Char_CipherText, Bit_CipherText_Init);
	cout<<"��������������Ϊ��";
	for(int i=0;i<64;i++)
		cout<<Bit_CipherText_Init[i];
	cout<<endl;

	//-----------------����Կ��ȡ------------------------------
	//��Ҫ���16������Կ

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

	//�洢ÿ������Կ���ڽ���
	int Round_Key_Store[16][48];

	//�洢ÿ����λ���������Կ
	int Bit_Key_l2[28],Bit_Key_r2[28];

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
	}
	//-----------------����Կ��ȡ����--------------------------


	//IP�û���Ķ�������������(64bit)
	int Bit_CipherText_aft_IP[64];

	//������ɳ�ʼIP�û�
	for(int m=0;m<64;m++)
	{
		Bit_CipherText_aft_IP[m]=Bit_CipherText_Init[IP_Table[m]-1];
	}

	//�����ķ�Ϊ��������
	int Bit_CipherText_l1[32],Bit_CipherText_r1[32];
	for(int m=0;m<64;m++)
	{
		if(m<32)
			Bit_CipherText_l1[m]=Bit_CipherText_aft_IP[m];
		else
			Bit_CipherText_r1[m-32]=Bit_CipherText_aft_IP[m];
	}

	//�洢��������
	int Bit_CipherText_l2[32],Bit_CipherText_r2[32];
	int Bit_CipherText_l3[32],Bit_CipherText_r3[48];

	//16�ִνṹ
	for(int round=0;round<16;round++)
	{

		//�������ı���
		for(int m=0;m<32;m++)
		{
			Bit_CipherText_r2[m]=Bit_CipherText_r1[m];
		}

		//�������Ľ���E��չ����
		for(int m=0;m<48;m++)
		{
			Bit_CipherText_r3[m]=Bit_CipherText_r1[E_Table[m]-1];
		}

		//���������Ӧ������Կ���������
		for(int m=0;m<48;m++)
		{
			Bit_CipherText_r3[m]=Bit_CipherText_r3[m]^Round_Key_Store[15-round][m];
		}

		//������S�д���
		for(int m=0;m<8;m++)
		{
			//���������ĵ�ֵ��S_Box��ѡ��ֵ
			int s;
			s=S_Box[(Bit_CipherText_r3[m*6]*2+Bit_CipherText_r3[5+m*6])+m*4][Bit_CipherText_r3[1+m*6]*8+Bit_CipherText_r3[2+m*6]*4+Bit_CipherText_r3[3+m*6]*2+Bit_CipherText_r3[4+m*6]];


			//��S_Box��ѡ�е�ֵ��ʾΪ������ �� ��ֵ��Bit_PlainText_r3��
			for(int n=1;n<=4;n++)
			{
				Bit_CipherText_r3[(4-n)+4*m]=s%2;
				s=s/2;
			}
		}

		//���������P�û�,�����������,�������ݵı���ԭʼ�����Ĵ��������ģ������´�ѭ��ʹ��
		for(int m=0;m<32;m++)
		{
			Bit_CipherText_r1[m]=Bit_CipherText_r3[P_Table[m]-1]^Bit_CipherText_l1[m];
			Bit_CipherText_l1[m]=Bit_CipherText_r2[m];
		}
	}

	//���ʼ�û�IPR�û�ǰ�Ķ�������������(64bit)
	int Bit_PlainText_bfr_IPR[64];

	//16�ֺ��������ҽ����õ�����
	for(int m=0;m<64;m++)
	{
		if(m<32)
			Bit_PlainText_bfr_IPR[m]=Bit_CipherText_r1[m];
		else
			Bit_PlainText_bfr_IPR[m]=Bit_CipherText_l1[m-32];
	}

	//���ʼ�û�IPR�û���Ķ�������������(64bit)
	int Bit_PlainText_aft_IPR[64];

	//����������ʼ�û�
	for(int m=0;m<64;m++)
	{
		Bit_PlainText_aft_IPR[m]=Bit_PlainText_bfr_IPR[IPR_Table[m]-1];
	}

	cout<<"�����ƽ������Ϊ��";
	for(int m=0;m<64;m++)
	{
		cout<<Bit_PlainText_aft_IPR[m];
	}
	cout<<endl;

	//�洢����ʮ������char����
	char Char_PlainText[17];

	//���õ��Ķ���������int����ת��Ϊʮ������char����
	Bin_to_Hex(Bit_PlainText_aft_IPR, Char_PlainText);

	//���16������Կ�����ġ����ģ�����ԱȽ��
	cout<<"**************************************************************************************************"<<endl;
	
	//�����Կ
	cout<<"ʮ������ ��ԿΪ��"<<Char_Key<<endl;
	
	//�������
	cout<<"ʮ������ ����Ϊ��"<<Char_CipherText<<endl;

	//�������
	cout<<"ʮ������ ����Ϊ��"<<Char_PlainText<<endl;

	cout<<"**************************************************************************************************"<<endl;
    system("pause");
    return 0;
}

//���û�����String ת��Ϊ char����Char_Key
char * get_Key(string String_Key_Input)
{
	//��ȡǰ16λʮ����������Ϊ��Կ
	string String_Key = String_Key_Input.substr(0,16);

	//����16λʮ����������ĩβ��0��16λʮ��������
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

//���û�����String ת��Ϊ char����Char_CipherText
char * get_CipherText(string String_CipherText_Input)
{
	//��ȡǰ16λʮ����������Ϊ����
	string String_CipherText = String_CipherText_Input.substr(0,16);

	//����16λʮ����������ĩβ��0��16λʮ��������
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

//����û�����16�������Ƿ�Ϸ�
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

//ʮ������char����ת��Ϊ������int����
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

//������int����ת��Ϊʮ������char����
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