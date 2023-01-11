#include <WinSock2.h>
#include <iostream>
#include <thread>
#include<string>
#include <cstdint>
#include <chrono>
#include"BigInt.h"
#include"rsa.h"
#include "AES.h"
#include<cstdio>
using namespace std;
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

const int BUF_SIZE=1024;
char send_buf1[BUF_SIZE];//���ͻ�����
string clientAESkey="20011227IMNKUPSL";
string serverAESkey;
uint16_t OutLength;
char InBuff[1024];
char OutBuff[1024];
BigInt RSAEncode(BigInt &m, Rsa &R){return PowerMode(m, R.d, R.n);}
BigInt RSADecode(BigInt &c, Rsa &R){return PowerMode(c, R.e, R.n);}

string sendAESkey() {
    BigInt cn, ce, cd;
    ifstream openc("ClientRsa.txt");
    openc >> cn;
    openc >> ce;
    openc >> cd;
    openc.close();
    Rsa ClientRsa(cn, ce, cd);	// for encode
    cout<<"�ҵ�AES��ԿΪ:"<<clientAESkey<<endl<<endl;
    BigInt m1= StringToBigInt(clientAESkey);	// message to BigInt
    BigInt c1 = RSAEncode(m1, ClientRsa);	// encode
    string text = BigIntToHex(c1);    // text to send
    cout<<"���ܺ󷢳���AES��Կ:"<<text<<endl<<endl;
    return text;
}
string getAESkey(string s) {
    BigInt  sn, se;
    ifstream opens("ServerPk.txt");
    opens >> sn;
    opens >> se;
    opens.close();
    Rsa ServerRsa(sn, se);	// for decode
    BigInt c = HexToBigInt(s);
    BigInt m = RSADecode(c, ServerRsa);
    string message = BigIntToString(m);
    cout<<"���ܺ�Է���AESԭ��Ϊ:"<<message<<endl<<endl;
    return message;
}

void SetColor(int fore=7,int back=0)
{
    unsigned char m_color = fore;
    m_color += (back << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
    return;
}


DWORD WINAPI Send(LPVOID thesocket) {
    SOCKET * sock = (SOCKET*)thesocket;
    char sendBuf[BUF_SIZE] = {};
    char inputBuf[BUF_SIZE] = {};
    while (1) {
        //printf("Input a string: ");
        cin.getline(inputBuf, 1024, '\n');
        strcpy(sendBuf, inputBuf);
        AES_Init(16, (unsigned char*)clientAESkey.c_str());
        OutLength = OnAesEncrypt(sendBuf, strlen(sendBuf), OutBuff);
        strcpy(sendBuf, OutBuff);
        int t = send(*sock, sendBuf, strlen(sendBuf), 0);
        if (strcmp(inputBuf, "imquit") == 0)
        {
            SetColor(12,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            closesocket(*sock);
            cout << "������" << st.wHour << "ʱ" << st.wMinute << "��" << st.wSecond << "��ѡ����������ˣ��ټ�Ӵ����//��//��" << endl;
            system("pause");
            exit(0);
        }
        if (t > 0) {
            SetColor(1,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            cout << "��Ϣ����" << st.wHour << "ʱ" << st.wMinute << "��" << st.wSecond << "��ɹ�����\n" ;
            cout << "-------------------------------------------------------------" << endl;
        }
        memset(sendBuf, 0, BUF_SIZE);
    }
}


DWORD WINAPI Recv(LPVOID thesocket) {
    char recvBuf[BUF_SIZE] = { 0 };
    SOCKET *sock = (SOCKET*)thesocket;
    while (1) {
        SetColor();
        int t = recv(*sock, recvBuf, BUF_SIZE, 0);
        AES_Init(16, (unsigned char*)serverAESkey.c_str());
        OutLength = OnAesUncrypt(recvBuf, strlen(recvBuf), OutBuff);
        strcpy(recvBuf, OutBuff);
        if (strcmp(recvBuf, "imquit") == 0)
        {
            SetColor(12,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            closesocket(*sock);
            cout << "����С����(�����)����" << st.wMonth <<"��"<< st.wDay << "��" << st.wHour << "ʱ" << st.wMinute << "��" << st.wSecond << "��ѡ����������ˣ��ټ�Ӵ����//��//��" << endl;
            system("pause");
            exit(0);
            return 0L;
        }
        if (t > 0) {
            time_t now_time = time(NULL);
            tm *t_tm = localtime(&now_time);
            SetColor(14,0);
            cout << asctime(t_tm) << "�յ�����С�ɰ�(�ͻ���)��������Ϣ:"<<endl;
            cout <<"ʮ���������ģ�";
            for(int i = 0; i < OutLength; i++)
            {
                printf(" %02x ", OutBuff[i]);
            }
            cout <<endl<<"���ģ�"<< recvBuf << endl;
            cout << "-------------------------------------------------------------" << endl;
        }
        memset(recvBuf, 0, BUF_SIZE);
    }
}


int main() {
    SetColor();
    //��ʼ��DLL
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
    {
        SetColor(12,0);
        cout << "��ʼ��socket�ɹ�����(^_^)" << endl;
    }
    else {
        SetColor(12,0);
        cout << "��ʼ��socket��ʧ���˱����������¸罨�黹���Ȼؼ��ٺú�ѧѧ�ɣ�(�V_�V)" << endl;
        return 0;
    }
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(8000);//��������һ������֮�ھͿ���
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == 0)
    {
        SetColor(12,0);
        cout << "�����ѳɹ�������Ŷ(^_^) �쿪ʼ�Ϳɰ��ķ��������ɣ�#(^o^)#" << endl;
        string msg=sendAESkey();
        strcpy(send_buf1, msg.c_str());
        send(sock, send_buf1, 1024, 0);
    }
    else {
        SetColor(12,0);
        cout << "����ʧ���˱������������ǲ���û����������أ�|_(._.)_|" << endl;
        return 0;
    }
    char AESBuf[BUF_SIZE] = {};
    Sleep(1000);
    recv(sock, AESBuf, BUF_SIZE, 0);
    string tmp=AESBuf;
    serverAESkey=getAESkey(tmp);
    cout<<"��Կ�ַ���ɣ����������Կ�ʼ���������ˣ�"<<endl;
    HANDLE hThread[2];
//    while(1) {
    hThread[0] = CreateThread(NULL, 0, Recv, (LPVOID) &sock, 0, NULL);
    hThread[1] = CreateThread(NULL, 0, Send, (LPVOID) &sock, 0, NULL);
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
//    }
    closesocket(sock);
    WSACleanup();

    return 0;
}