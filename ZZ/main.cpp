#include<iostream>
#include"AES.h"
using namespace std;
void main()
{
	cout << "0.加密         1.解密           2.验证雪崩效应     " << endl;
	int i = 0;
	cin >> i;
	while (i == 0||i==1||i==2) {
		if (i == 0) {
			cout << "请选择密钥长度：" << endl;
			cout << "             0.128         1.192         2.256              " << endl;
			cout << "请输入0-2：" << endl;
			int op;
			cin >> op;
			if (op == 0) {
				cout << "请选择测试数据组号（0/1）" << endl;
				int num;
				cin >> num;
				unsigned char out[16];
				AES aes(cases[num].key, op);
				aes.encrypt(cases[num].txt, out);
				cout << "加密结果为：";
				for (int i = 0; i < 16; i++)
					printf("%x%x", out[i] / 16, out[i] % 16);
				cout << endl;
			}
			else if (op == 1) {
				unsigned char out[16];
				AES aes(cases1[0].key, op);
				aes.encrypt(cases1[0].txt, out);
				cout << "加密结果为：";
				for (int i = 0; i < 16; i++)
					printf("%x%x", out[i] / 16, out[i] % 16);
				cout << endl;
			}
			else if (op == 2) {
				unsigned char out[16];
				AES aes(cases2[0].key, op);
				aes.encrypt(cases2[0].txt, out);
				cout << "加密结果为：";
				for (int i = 0; i < 16; i++)
					printf("%x%x", out[i] / 16, out[i] % 16);
				cout << endl;
			}
		}
		if (i == 1) {
			cout << "请选择密钥长度：" << endl;
			cout << "             0.128         1.192         2.256              " << endl;
			int op;
			cin >> op;
			if (op == 0) {
				cout << "请选择测试数据组号：(0/1)" << endl;
				int num;
				cin >> num;
				unsigned char m[16];
				AES aes(cases[num].key, op);
				aes.decrypt(cases[num].out, m);
				cout << "解密结果为：";
				for (int i = 0; i < 16; i++)
					printf("%x%x", m[i] / 16, m[i] % 16);
				cout << endl;
			}
			else if (op == 1) {
				unsigned char m[16];
				AES aes(cases1[0].key, op);
				aes.decrypt(cases1[0].out, m);
				cout << "解密结果为：";
				for (int i = 0; i < 16; i++)
					printf("%x%x", m[i] / 16, m[i] % 16);
				cout << endl;
			}
			else if (op == 2) {
				unsigned char m[16];
				AES aes(cases2[0].key, op);
				aes.decrypt(cases2[0].out, m);
				cout << "解密结果为：";
				for (int i = 0; i < 16; i++)
					printf("%x%x", m[i] / 16, m[i] % 16);
				cout << endl;
			}
		}
		if (i == 2) {
			cout << "请选择测试数据组号:(0/1)" << endl;
			int num, count;
			count = 0;
			cin >> num;
			unsigned char out[16];
			if (num == 0) {
				AES aes(cases[0].key, 0);
				aes.encrypt(cases[0].txt, out);
			}
			else {
				AES aes(cases[1].key, 0);
				aes.encrypt(cases[1].txt, out);
			}
			cout << "初始加密结果为：";
			for (int i = 0; i < 16; i++)
				printf("%x%x", out[i] / 16, out[i] % 16);
			cout << endl;
			for (int i = 0; i < 8; i++) {
				unsigned char k[16];
				for (int j = 0; j < 16; j++)
					k[j] = cases[num].key[j];
				unsigned char temp = k[i] & 0xfe;
				unsigned char tem = k[i] & 0x01;
				if (tem == 0x01)
					tem = 0x00;
				else
					tem = 0x01;
				//每个字节的最后一位自动取反
				k[i] = temp + tem;
				unsigned char out1[16];
				AES aes(k, 0);
				aes.encrypt(cases[num].txt, out1);
				int sum = 0;
				sum = aes.compare(out, out1);
				cout << "改变密文位数：" << sum << "位" << endl << endl;
				count = count + sum;
			}
			cout << "平均每次改变" << (double)count / 8 << "位。" << endl;
			count = 0;
			for (int i = 0; i < 8; i++) {
				unsigned char m[16];
				for (int j = 0; j < 16; j++)
					m[j] = cases[num].txt[j];
				unsigned char temp = m[i] & 0xef;
				unsigned char tem = m[i] & 0x10;
				if (tem == 0x10)
					tem = 0x00;
				else
					tem = 0x10;
				m[i] = temp + tem;
				unsigned char out1[16];
				AES aes(cases[num].key, 0);
				aes.encrypt(m, out1);
				int sum = 0;
				sum = aes.compare(out, out1);
				cout << "改变密文位数：" << sum << "位" << endl << endl;
				count = count + sum;
			}
			cout << "平均每次改变" << (double)count / 8 << "位。" << endl;
		}
		cout << "0.加密         1.解密           2.验证雪崩效应     " << endl;
		cin >> i;
	}
	return;
}