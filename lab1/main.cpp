#include<iostream>
#include<string>
using namespace std;
#define MAX_SIZE_OF_M 1000// 可输入的明文的最大长度

void function_num1() {
    cout << "输入明文:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);

    // 设置加密密钥key
    int key;
    cout << "请输入key，取值范围是(1-25):";
    cin >> key;
    cout << "------------------------------------------------" <<endl;
    cout << "开始加密！" <<endl;
    // 密文结果初始化
    char* C = new char[MAX_SIZE_OF_M];
    // 移位加密
    int index = 0;
    //处理大小写的东西
    while (M[index] != '\0') {
        // 获取当前位置的ASCII
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            int i = (ASCII - 65 + key) % 26;C[index] = char(65 + i);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                int i = (ASCII - 97 + key) % 26;C[index] = char(97 + i);
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
    cout << "加密结束！" <<endl;
    cout << "输出加密结果: ";
    cout << C << endl;
    cout << "------------------------------------------------" <<endl;

    cout << "------------------------------------------------" <<endl;
    cout << "开始解密！" <<endl;
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
    cout << "解密结束！" <<endl;

    cout << "输出解密结果: " << AM << endl;
    cout << "------------------------------------------------" <<endl;
}

void function_num2() {

    cout << "输入密文:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);
    cout << "------------------------------------------------" <<endl;
    cout << "开始解密！" <<endl;
    for (int key = 1; key < 26; key++) {
        // 明文结果初始化
        char* M = new char[MAX_SIZE_OF_M];
        // 移位解密
        int index = 0;
        //处理大小写的东西
        while (C[index] != '\0') {
            // 获取当前位置的ASCII
            int ASCII = int(C[index]);
            if (ASCII <= 90 && ASCII >= 65) {
                int i = (ASCII - 65 - key + 26) % 26;M[index] = char(65 + i);
            }
            else {
                if (ASCII <= 122 && ASCII >= 97) {
                    int i = (ASCII - 97 - key + 26) % 26;M[index] = char(97 + i);
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

        cout << "Key = " << key << "  输出解密结果 = " << M << endl;
    }
    cout << "解密结束！" <<endl;
}

void function_num3() {
    char R_Table[26] = { 'h','k','w','t','x','y','s','g','b','p','q','e','j','a','z','m','l','n','o','f','c','i','d','v','u','r'};
    cout << "输入明文:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);
    cout << "------------------------------------------------" <<endl;
    cout << "开始加密！" <<endl;
    // 密文结果初始化
    char* C = new char[MAX_SIZE_OF_M];
    // 循环代换
    int index = 0;
    //处理大小写的东西
    while (M[index] != '\0') {
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            int i = ASCII - 65;C[index] = char(int(R_Table[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                int i = ASCII - 97;C[index] = R_Table[i];
            }
            else {

                C[index] = M[index];
            }
        }
        // 下角标索引+1
        index += 1;
    }
    // 结尾补充结束符
    C[index] = '\0';
    cout << "加密结束！" <<endl;
    cout << "加密结果: ";
    cout << C << endl;
    cout << "------------------------------------------------" <<endl;
    cout << "------------------------------------------------" <<endl;
    cout << "开始解密！" <<endl;
    char RTable[26];
    for (int i = 0; i < 26; i++) {
        // 首先获取当前位置字符的ASCII
        int temp_ascii = int(R_Table[i]);
        // ASCII映射到26位置空间之后，填入到相关位置
        RTable[temp_ascii - 97] = char(i + 97);
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
            AM[index] = char(int(RTable[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = ASCII - 97;
                // 找到他在逆转之后的表的位置
                AM[index] = RTable[i];
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
    cout << "解密结束！" <<endl;
    cout << "解密结果: " << AM << endl;
    cout << "------------------------------------------------" <<endl;
}

void function_num4() {
    cout << "输入要统计的密文:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);
    cout << "------------------------------------------------" <<endl;
    cout << "开始解密！" <<endl;
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
        }
        // 下角标索引+1
        index += 1;
    }

    cout << "输出统计的频次:";
    for (int i = 0; i < 26; i++) {
        if (i % 10 != 0)
            cout << char(97 + i) << ": " << frequency[i] << '\t';
        else
            cout << endl << char(97 + i) << ": " << frequency[i] << '\t';
    }
    // 根据分析结果得到正向代换表
    char R_Table[26] = { 'n','h','g','d','c','f','e','i','j','0','0','a','q','b','m','x','0','p','r','s','z','t','v','0','y','o' };

    // 首先对代换表进行一个逆转操作，预处理
    char RTable[26];
    // 初始化
    for (int i = 0; i < 26; i++) {
        RTable[i] = '0';
    }
    for (int i = 0; i < 26; i++) {
        // 首先获取当前位置字符的ASCII
        int temp_ascii = int(R_Table[i]);
        // ASCII映射到26位置空间之后，填入到相关位置
        // 检查ASCII是不是在正确的范围内
        if (temp_ascii >= 97 && temp_ascii <= 122) {
            // 如果是，则放入到对应的表中
            RTable[temp_ascii - 97] = char(i + 97);
        }
    }

    // 检查逆向代换表，如果位置上是0的就自己代换为自己，并且设置为大写，以和成功替换的区分开
    for (int i = 0; i < 26; i++) {
        if (RTable[i] == '0')
            RTable[i] = char(i + 65);
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
            AM[index] = RTable[i];
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // 如果是小写字母
                int i = ASCII - 97;
                // 找到他在逆转之后的表的位置
                AM[index] = RTable[i];
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
    cout << "解密结束！" <<endl;
    cout << "\n输出解密结果:\n" << AM << endl;
    cout << "------------------------------------------------" <<endl;
}

int main() {
    cout << "选择功能：\ncase1:移位密码加密解密\ncase2:移位密码攻击\ncase3:单表置换密码加密解密\ncase4:单表置换密码攻击\n注意，只需要输入数字，不需要输入case\n";
    int caseNumber;
    cin >> caseNumber;
    cin.get();
    switch (caseNumber) {
        case 1:
            function_num1();
            break;
        case 2:
            function_num2();
            break;
        case 3:
            function_num3();
            break;
        case 4:
            function_num4();
            break;
        default:
            cout << "输入序号有误，请检查并重新输入\n";
    }
    system("pause");
    return 0;
}
