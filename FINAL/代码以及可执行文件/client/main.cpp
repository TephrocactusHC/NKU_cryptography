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
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

const int BUF_SIZE=1024;
char send_buf1[BUF_SIZE];//发送缓冲区
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
    cout<<"我的AES密钥为:"<<clientAESkey<<endl<<endl;
    BigInt m1= StringToBigInt(clientAESkey);	// message to BigInt
    BigInt c1 = RSAEncode(m1, ClientRsa);	// encode
    string text = BigIntToHex(c1);    // text to send
    cout<<"加密后发出的AES密钥:"<<text<<endl<<endl;
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
    cout<<"解密后对方的AES原文为:"<<message<<endl<<endl;
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
            cout << "您已于" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒选择结束聊天了！再见哟！（//▽//）" << endl;
            system("pause");
            exit(0);
        }
        if (t > 0) {
            SetColor(1,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            cout << "消息已于" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒成功发送\n" ;
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
            cout << "您的小宝贝(服务端)已于" << st.wMonth <<"月"<< st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒选择结束聊天了！再见哟！（//▽//）" << endl;
            system("pause");
            exit(0);
            return 0L;
        }
        if (t > 0) {
            time_t now_time = time(NULL);
            tm *t_tm = localtime(&now_time);
            SetColor(14,0);
            cout << asctime(t_tm) << "收到您的小可爱(客户端)发来的消息:"<<endl;
            cout <<"十六进制密文：";
            for(int i = 0; i < OutLength; i++)
            {
                printf(" %02x ", OutBuff[i]);
            }
            cout <<endl<<"明文："<< recvBuf << endl;
            cout << "-------------------------------------------------------------" << endl;
        }
        memset(recvBuf, 0, BUF_SIZE);
    }
}


int main() {
    SetColor();
    //初始化DLL
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
    {
        SetColor(12,0);
        cout << "初始化socket成功了亲(^_^)" << endl;
    }
    else {
        SetColor(12,0);
        cout << "初始化socket都失败了宝贝儿，你穆哥建议还是先回家再好好学学吧！(￢_￢)" << endl;
        return 0;
    }
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(8000);//好像是在一个区间之内就可以
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == 0)
    {
        SetColor(12,0);
        cout << "亲您已成功上线了哦(^_^) 快开始和可爱的服务端聊天吧！#(^o^)#" << endl;
        string msg=sendAESkey();
        strcpy(send_buf1, msg.c_str());
        send(sock, send_buf1, 1024, 0);
    }
    else {
        SetColor(12,0);
        cout << "连接失败了宝贝儿，快查查是不是没启动服务端呢？|_(._.)_|" << endl;
        return 0;
    }
    char AESBuf[BUF_SIZE] = {};
    Sleep(1000);
    recv(sock, AESBuf, BUF_SIZE, 0);
    string tmp=AESBuf;
    serverAESkey=getAESkey(tmp);
    cout<<"密钥分发完成，接下来可以开始加密聊天了！"<<endl;
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