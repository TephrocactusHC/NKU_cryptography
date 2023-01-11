#include <winsock2.h>
#include <iostream>
#include<ctime>
#include<cstring>
#include<string>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include"BigInt.h"
#include"rsa.h"
#include "AES.h"
#include <cstdint>
using namespace std;
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

const int BUF_SIZE=1024;
char send_buf1[BUF_SIZE];//发送缓冲区
string clientAESkey;
string serverAESkey="IMNKUPSL20011227";
uint16_t OutLength;
char InBuff[1024];
char OutBuff[1024];
void SetColor(int fore=7,int back=0)
{
    unsigned char m_color = fore;
    m_color += (back << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_color);
    return;
}
BigInt RSAEncode(BigInt &m, Rsa &R){return PowerMode(m, R.d, R.n);}
BigInt RSADecode(BigInt &c, Rsa &R){return PowerMode(c, R.e, R.n);}
string sendAESkey() {
    BigInt cn, ce, cd;
    ifstream openc("ServerRsa.txt");
    openc >> cn;
    openc >> ce;
    openc >> cd;
    openc.close();
    Rsa ClientRsa(cn, ce, cd);	// for encode
    cout<<"我的AES密钥为:"<<serverAESkey<<endl<<endl;
    BigInt m1= StringToBigInt(serverAESkey);	// message to BigInt
    BigInt c1 = RSAEncode(m1, ClientRsa);	// encode
    string text = BigIntToHex(c1);    // text to send
    cout<<"加密后发出的AES密钥:"<<text<<endl<<endl;
    return text;
}
string getAESkey(string s) {
    BigInt  cn, ce;
    ifstream openc("ClientPk.txt");
    openc >> cn;
    openc >> ce;
    openc.close();
    Rsa ClientRsa(cn, ce);	// for decode
    BigInt c = HexToBigInt(s);
    BigInt m = RSADecode(c, ClientRsa);
    string message = BigIntToString(m);
    cout<<"解密后对方的AES密钥为:"<<message<<endl<<endl;
    return message;
}


DWORD WINAPI Send(LPVOID thesocket) {
    SOCKET * sock = (SOCKET*)thesocket;
    char sendBuf[BUF_SIZE] = {};
    char inputBuf[BUF_SIZE] = {};
    while (1) {
        //printf("Input a string: ");
        cin.getline(inputBuf, 1024, '\n');
        strcpy(sendBuf, inputBuf);
        AES_Init(16, (unsigned char*)serverAESkey.c_str());
        OutLength = OnAesEncrypt(sendBuf, strlen(sendBuf), OutBuff);
        strcpy(sendBuf, OutBuff);
        int t = send(*sock, sendBuf, strlen(sendBuf), 0);
        if (strcmp(inputBuf, "imquit") == 0)
        {
            SetColor(12,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            closesocket(*sock);
            cout << "您已于" << st.wMonth << "月"<< st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒选择结束聊天了！再见哟！（//▽//）" << endl;
            Sleep(100);
            system("pause");
            exit (0);
        }
        if (t > 0) {
            SetColor(1,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            cout << "消息已于" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒成功发送\n";
            cout << "-------------------------------------------------------------" << endl;
        }
        memset(sendBuf, 0, BUF_SIZE);
    }
}


DWORD WINAPI Recv(LPVOID thesocket) {
    char recvBuf[BUF_SIZE] = {};
    SOCKET *sock = (SOCKET*)thesocket;
    while (1) {
        int t = recv(*sock, recvBuf, BUF_SIZE, 0);
        AES_Init(16, (unsigned char*)clientAESkey.c_str());
        OutLength = OnAesUncrypt(recvBuf, strlen(recvBuf), OutBuff);
        strcpy(recvBuf, OutBuff);
        if (strcmp(recvBuf, "imquit") == 0)
        {
            SetColor(12,0);
            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);
            closesocket(*sock);
            cout << "客户端已于" << st.wMonth << "月"<< st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒选择结束聊天了！再见哟！（//▽//）" << endl;
            system("pause");
            exit (0);
            return 0L;
        }
        if (t > 0) {
            time_t now_time = time(NULL);
            tm *t_tm = localtime(&now_time);
            SetColor(14,0);
            cout << asctime(t_tm) << "收到您的小可爱(服务端)发来的消息:"<<endl;
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
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) //指定版本wVersionRequested=MAKEWORD(a,b)。MAKEWORD()是一个宏把两个数字组合成一个WORD，无符号的短整型
    {
        SetColor(12,0);
        cout << "初始化socket成功了亲" << endl;
    }
    else {
        SetColor(12,0);
        cout << "初始化socket都失败了宝贝儿，你穆哥建议还是先回家再好好学学吧！(￢_￢)" << endl;
        return 0;
    }

    //创建套接字
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addrSrv;
    memset(&addrSrv, 0, sizeof(addrSrv));  //每个字节都用0填充
    addrSrv.sin_family = AF_INET;  //使用IPv4地址
    addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");  //把我们本机的地址转换成网络字节二进制值序
    addrSrv.sin_port = htons(8000);  //端口,好像是在一个区间之内就可以.//转换函数，也是转换成网络字节序
    int z=bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv));
    if (z == -1) {
        SetColor(12,0);
        cout << "绑定这一步都失败了宝贝儿，建议还是先回家再好好学学吧！(￢_￢)" << endl;
        return 0;
    }
    else{
        SetColor(12,0);
        cout<<"绑定成功了亲(^_^)" << endl;
    }
    //进入监听状态
    if (listen(sockSrv, 5) == 0) {
        SetColor(12,0);
        cout << "正在监听之中哦亲(^_^)" << endl;
    }
    else {
        SetColor(12,0);
        cout << "监听都失败了宝贝儿，你穆哥建议还是先回家再好好学学吧！(￢_￢)" << endl;
        return 0;
    }

    //接收客户端请求
    SOCKADDR addrClient;
    int nSize = sizeof(SOCKADDR);
    SOCKET ClientSocket = accept(sockSrv, (SOCKADDR*)&addrClient, &nSize);
    char AESBuf[BUF_SIZE] = {};
    if (ClientSocket > 0) {
        SetColor(12,0);
        cout << "您的小宝贝(客户端)已上线(^_^)" << endl;
    }
    else {
        SetColor(12,0);
        cout << "连接失败了宝贝儿，快查查是不是没启动客户端呢？|_(._.)_|" << endl;
        return 0;
    }
    recv(ClientSocket, AESBuf, BUF_SIZE, 0);

    string tmp=AESBuf;
    clientAESkey=getAESkey(tmp);
    Sleep(10);

    string msg=sendAESkey();
    strcpy(send_buf1, msg.c_str());
    send(ClientSocket, send_buf1, BUF_SIZE, 0);
    cout<<"密钥分发完成，接下来可以开始加密聊天了！"<<endl;

    //开启多线程
    HANDLE hThread[2];
//    while(1) {
    hThread[0] = CreateThread(NULL, 0, Recv, (LPVOID) &ClientSocket, 0, NULL);
    hThread[1] = CreateThread(NULL, 0, Send, (LPVOID) &ClientSocket, 0, NULL);
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);

//    }
    closesocket(ClientSocket);  //关闭套接字

    //关闭套接字
    closesocket(sockSrv);

    //终止 DLL 的使用
    WSACleanup();

    return 0;

}


