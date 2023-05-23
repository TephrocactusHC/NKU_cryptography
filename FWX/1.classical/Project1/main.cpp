#include<iostream>
#include<string>
using namespace std;

// 可输入的明文的最大长度
#define MAX_SIZE_OF_M 1000

/*
* 1、移位密码
移位密码：将英文字母向前或向后移动一个固定位置。例如向后移动3个位
置，即对字母表作置换（不分大小写）。
A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  A  B  C
    设明文为：public keys,则经过以上置换就变成了：sxeolf nhbv。
    如果将26个英文字母进行编码：A→0，B→1，…，Z→25，则以上加密过程可简单地写成：
        明文：m＝m1m2…mi…, 则有
        密文：c=c1c2…ci…, 其中 ci=(mi+key mod26)，i＝1，2，…。

ASCII:
A:65 Z:90
a:97 z:122

（1）根据实验原理部分对移位密码算法的介绍，自己创建明文信息，并选择一个密钥，编写移位密码算法实现程序，实现加密和解密操作。
*/

void ShiftCipher() {
    // 输入明文
    cout << "Please input message:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);
    //cout << M;

    // 设置加密密钥key
    int key;
    cout << "Please input key(1-25):";
    cin >> key;

    // 密文结果初始化
    char* C = new char[MAX_SIZE_OF_M];
    // 移位加密
    int index = 0;
    while (M[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // 如果是大写字母
            int i = (ASCII - 65 + key) % 26;
            C[index] = char(65 + i);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = (ASCII - 97 + key) % 26;
                C[index] = char(97 + i);
            }
            else {
                // 如果是非字母
                C[index] = M[index];
            }
        }
        // 下角标索引+1
        index += 1;
    }
    // 结尾补充结束符
    C[index] = '\0';

    // 输出加密结果
    cout << "Encrypted ciphertext is: ";
    cout << C << endl;

    // 开始解密
    // 解密结果初始化
    char* AM = new char[MAX_SIZE_OF_M];
    index = 0;
    while (C[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // 如果是大写字母
            int i = (ASCII - 65 - key + 26) % 26;
            AM[index] = char(65 + i);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = (ASCII - 97 - key + 26) % 26;
                AM[index] = char(97 + i);
            }
            else {
                // 如果是非字母
                AM[index] = C[index];
            }
        }
        // 下角标索引+1
        index += 1;
    }
    // 结尾补充结束符
    AM[index] = '\0';

    // 输出解密结果
    cout << "After decryption, the plaintext is: " << AM << endl;
}



/*
* 2、对移位密码的攻击
移位密码是一种最简单的密码，其有效密钥空间大小为25。因此，很容易用穷举的方法攻破。
穷举密钥攻击是指攻击者对可能的密钥的穷举，也就是用所有可能的密钥解密密文，直到得到有意义的明文，由此确定出正确的密钥和明文的攻击方法。
对移位密码进行穷举密钥攻击，最多只要试译25次就可以得到正确的密钥和明文。

（2）两个同学为一组，互相攻击对方用移位密码加密获得的密文，恢复出其明文和密钥。
*/

void AttackShiftCipher() {
    // 输入密文
    cout << "Please input encrypted message:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);

    for (int key = 1; key < 26; key++) {
        // 明文结果初始化
        char* M = new char[MAX_SIZE_OF_M];
        // 移位解密
        int index = 0;
        while (C[index] != '\0') {
            // 获取当前位置的ASCII
            int ASCII = int(C[index]);
            if (ASCII <= 90 && ASCII >= 65) {
                // 如果是大写字母
                int i = (ASCII - 65 - key + 26) % 26;
                M[index] = char(65 + i);
            }
            else {
                if (ASCII <= 122 && ASCII >= 97) {
                    // 如果是小写字母
                    int i = (ASCII - 97 - key + 26) % 26;
                    M[index] = char(97 + i);
                }
                else {
                    // 如果是非字母
                    M[index] = C[index];
                }
            }
            // 下角标索引+1
            index += 1;
        }
        // 结尾补充结束符
        M[index] = '\0';

        // 输出解密结果
        cout << "Key = " << key << "\tMessage = " << M << endl;
    }
}



/*
* 3、单表置换密码
单表置换密码就是根据字母表的置换对明文进行变换的方法，例如，给定置换

A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
H  K  W  T  X  Y  S  G  B  P  Q  E  J  A  Z  M  L  N  O  F  C  I  D  V  U  R
    明文：public keys, 则有
    密文：mckebw qxuo。
    单表置换实现的一个关键问题是关于置换表的构造。置换表的构造可以有各种不同的途径，主要考虑的是记忆的方便。
    如使用一个短语或句子，删去其中的重复部分，作为置换表的前面的部分，然后把没有用到的字母按字母表的顺序依次放入置换表中。

（3）自己创建明文信息，并选择一个密钥，构建置换表。编写置换密码的加解密实现程序，实现加密和解密操作。
*/

void SingleTableReplacement() {
    // 设置置换表
    // 置换之前的内容就使用ASCII进行索引，用ASCII减去第一个的位置来算相对偏移
    // 如果是大写，ascii上进行处理就好
    char ReplaceTable[26] = { 'h','k','w','t','x','y','s','g','b','p','q','e','j','a','z','m','l','n','o','f','c','i','d','v','u','r'};

    // 输入明文
    cout << "Please input message:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);

    // 密文结果初始化
    char* C = new char[MAX_SIZE_OF_M];

    // 循环代换
    int index = 0;
    while (M[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // 如果是大写字母
            int i = ASCII - 65;
            // 获取到的代换后的字母是小写字母，需要利用ASCII的关系转换成大写字母
            C[index] = char(int(ReplaceTable[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = ASCII - 97;
                C[index] = ReplaceTable[i];
            }
            else {
                // 如果是非字母
                C[index] = M[index];
            }
        }
        // 下角标索引+1
        index += 1;
    }
    // 结尾补充结束符
    C[index] = '\0';

    // 输出加密结果
    cout << "Encrypted ciphertext is: ";
    cout << C << endl;


    // 开始解密
    // 首先对代换表进行一个逆转操作，预处理
    char reverseTable[26];
    for (int i = 0; i < 26; i++) {
        // 首先获取当前位置字符的ASCII
        int temp_ascii = int(ReplaceTable[i]);
        // ASCII映射到26位置空间之后，填入到相关位置
        reverseTable[temp_ascii - 97] = char(i + 97);
    }

    // 解密内容初始化
    char* AM = new char[MAX_SIZE_OF_M];

    index = 0;
    while (C[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // 如果是大写字母
            int i = ASCII - 65;
            // 找到的是对应的小写字母，利用ASCII转换成大写即可
            AM[index] = char(int(reverseTable[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = ASCII - 97;
                // 找到他在逆转之后的表的位置
                AM[index] = reverseTable[i];
            }
            else {
                // 如果是非字母
                AM[index] = C[index];
            }
        }
        // 下角标索引+1
        index += 1;
    }
    // 结尾补充结束符
    AM[index] = '\0';

    // 输出解密结果
    cout << "After decryption, the plaintext is: " << AM << endl;
}



/*
* 4、对单表置换密码的攻击方法
在单表置换密码中，由于置换表字母组合方式有26！种，约为4.03×1026。
所以采用穷举密钥的方法不是一种最有效的方法。
对单表置换密码最有效的攻击方法是利用自然语言的使用频率：单字母、双字母组/三字母组、短语、词头/词尾等，这里仅考虑英文的情况。
英文的一些显著特征如下[1]:
    短单词(small words)：在英文中只有很少几个非常短的单词。因此，如果在一个加密的文本中可以确定单词的范围，那么就能得出明显的结果。
    一个字母的单词只有a和I。
    如果不计单词的缩写，在从电子邮件中选取500k字节的样本中，只有两个字母的单词仅出现35次，而两个字母的所有组合为26×26＝676种。
    而且，还是在那个样本中，只有三个字母的单词出现196次，而三个字母的所有组合为26×26×26＝17576种。
    常用单词(common words):再次分析500k字节的样本，总共有5000多个不同的单词出现。
    在这里，9个最常用的单词出现的总次数占总单词数的21％，20个最常用的单词出现的总次数占总单词数的30％，104个最常用的单词占50％，
    247个最常用的单词占60％。样本中最常用的9个单词占总词数的百分比为：
     the 4.65     to   3.02    of    2.61   I    2.2   a    1.95
     and 1.82     is   1.68    that  1.62   in   1.57
更详细的统计结果请参阅文献[1]。
    字母频率(character frequency):在1M字节旧的电子文本中，对字母”A”到“Z”（忽略大小写）分别进行统计。发现近似频率（以百分比表示）：
    e  11.67   t  9.53   o  8.22   i  7.81   a  7.73   n  6.71  s  6.55
    r  5.97    h  4.52   l  4.3    d  3.24   u  3.21   c  3.06  m  2.8
    p  2.34    y  2.22   f  2.14   g  2.00   w  1.69   b  1.58  v  1.03
    k  0.79    x  0.30   j  0.23   q  0.12   z  0.09
     从该表中可以看出，最常用的单字母英文是e和t，其他字母使用频率相对来说就小得多。
     这样，攻击一个单表置换密码，首先统计密文中最常出现的字母，并据此猜出两个最常用的字母，
     并根据英文统计的其他特征（如字母组合等）进行试译。


（4）用频率统计方法，试译下面用单表置换加密的一段密文：
SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N 
XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC 
MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC 
SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC 
MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC
写出获得的明文消息和置换表。

SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC
*/

void AttackSingleTableReplacement() {
    // 输入要统计的密文
    cout << "Please input encrypted message:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);

    // 记录统计熟练的数组初始化
    int frequency[26] = { 0 };

    // 遍历密文，统计频次
    int index = 0;
    while (C[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // 如果是大写字母
            int i = ASCII - 65;
            // 获取到的代换后的字母是小写字母，需要利用ASCII的关系转换成大写字母
            frequency[i] += 1;
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = ASCII - 97;
                frequency[i] += 1;
            }
            else {
                // 如果是非字母
                // 暂时不做任何行为
            }
        }
        // 下角标索引+1
        index += 1;
    }

    // 输出统计的频次
    cout << "After statistics, the occurrence frequency of each letter is:";
    for (int i = 0; i < 26; i++) {
        if (i % 10 != 0)
            cout << char(97 + i) << ": " << frequency[i] << '\t';
        else
            cout << endl << char(97 + i) << ": " << frequency[i] << '\t';
    }

    // 根据分析结果得到正向代换表
    char replaceTable[26] = { 'n','h','g','d','c','f','e','i','j','0','0','a','q','b','m','x','0','p','r','s','z','t','v','0','y','o' };

    // 开始解密
    // 首先对代换表进行一个逆转操作，预处理
    char reverseTable[26];
    // 初始化
    for (int i = 0; i < 26; i++) {
        reverseTable[i] = '0';
    }

    for (int i = 0; i < 26; i++) {
        // 首先获取当前位置字符的ASCII
        int temp_ascii = int(replaceTable[i]);
        // ASCII映射到26位置空间之后，填入到相关位置
        // 检查ASCII是不是在正确的范围内
        if (temp_ascii >= 97 && temp_ascii <= 122) {
            // 如果是，则放入到对应的表中
            reverseTable[temp_ascii - 97] = char(i + 97);
        }
        else {
            // 如果不是，也就是说这是原本初始化时的内容，什么都不动
        }
    }

    // 检查逆向代换表，如果位置上是0的就自己代换为自己，并且设置为大写，以和成功替换的区分开
    for (int i = 0; i < 26; i++) {
        if (reverseTable[i] == '0')
            reverseTable[i] = char(i + 65);
    }

    // 解密内容初始化
    char* AM = new char[MAX_SIZE_OF_M];

    index = 0;
    while (C[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // 如果是大写字母
            int i = ASCII - 65;
            AM[index] = reverseTable[i];
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = ASCII - 97;
                // 找到他在逆转之后的表的位置
                AM[index] = reverseTable[i];
            }
            else {
                // 如果是非字母
                AM[index] = C[index];
            }
        }
        // 下角标索引+1
        index += 1;
    }
    // 结尾补充结束符
    AM[index] = '\0';

    // 输出解密结果
    cout << "\nAfter decryption, the plaintext is:\n" << AM << endl;
}

int main() {
    cout << "输入序号选择相应实验内容：\n1、移位密码加密和解密\n2、对移位密码的攻击\n3、单表置换密码加密和解密\n4、对单表置换密码的攻击方法\n";
    int chooseNumber;
    cin >> chooseNumber;
    // 吃掉最后那个回车
    cin.get();
    switch (chooseNumber) {
    case 1:
        ShiftCipher();
        break;
    case 2:
        AttackShiftCipher();
        break;
    case 3:
        SingleTableReplacement();
        break;
    case 4:
        AttackSingleTableReplacement();
        break;
    default:
        cout << "输入序号有误，请检查并重新输入\n";
    }

    return 0;
}