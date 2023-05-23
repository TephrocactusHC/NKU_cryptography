#include<iostream>
#include<string>
#include<bitset>
using namespace std;

// ---------------------------DES加密算法需要用到的相关数据----------------------------------

// 置换IP表
int IP[] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
              62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
              57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
              61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };

// 密钥置换表，将64位密钥变成56位
int PC_1[] = { 57,49,41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10,  2, 59, 51, 43, 35, 27,
              19, 11,  3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14,  6, 61, 53, 45, 37, 29,
              21, 13,  5, 28, 20, 12, 4 };

// 压缩置换，将56位密钥压缩成48位子密钥
int PC_2[] = { 14, 17, 11, 24,  1,  5,
               3, 28, 15,  6, 21, 10,
              23, 19, 12,  4, 26,  8,
              16,  7, 27, 20, 13,  2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 };

// 每轮左移的位数
int shiftBits[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// 测试用例
static const struct des_test_case {
    int num, mode; // mode 1 = encrypt
    unsigned char key[8], txt[8], out[8];
} cases[] = {
    { 1, 1,     { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 } },
    { 2, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 },
                { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 3, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 },
                { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 4, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA },
                { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 5, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F },
                { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 6, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 },
                { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 7, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF },
                { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 8, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F },
                { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 9, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 },
                { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    {10, 1,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A },
                { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },

    { 1, 0,     { 0x10, 0x31, 0x6E, 0x02, 0x8C, 0x8F, 0x3B, 0x4A },
                { 0x82, 0xDC, 0xBA, 0xFB, 0xDE, 0xAB, 0x66, 0x02 },
                { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } },
    { 2, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x95, 0xF8, 0xA5, 0xE5, 0xDD, 0x31, 0xD9, 0x00 } },
    { 3, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0xDD, 0x7F, 0x12, 0x1C, 0xA5, 0x01, 0x56, 0x19 } },
    { 4, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x2E, 0x86, 0x53, 0x10, 0x4F, 0x38, 0x34, 0xEA } },
    { 5, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x4B, 0xD3, 0x88, 0xFF, 0x6C, 0xD8, 0x1D, 0x4F } },
    { 6, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x20, 0xB9, 0xE7, 0x67, 0xB2, 0xFB, 0x14, 0x56 } },
    { 7, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x55, 0x57, 0x93, 0x80, 0xD7, 0x71, 0x38, 0xEF } },
    { 8, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x6C, 0xC5, 0xDE, 0xFA, 0xAF, 0x04, 0x51, 0x2F } },
    { 9, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0x0D, 0x9F, 0x27, 0x9B, 0xA5, 0xD8, 0x72, 0x60 } },
    {10, 0,     { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },
                { 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
                { 0xD9, 0x03, 0x1B, 0x02, 0x71, 0xBD, 0x5A, 0x0A } }
};

// 尾置换表
int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41,  9, 49, 17, 57, 25 };

// 扩展置换表，将 32位 扩展至 48位
int E[48] = { 32,  1,  2,  3,  4,  5,
            4,  5,  6,  7,  8,  9,
            8,  9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32,  1 };

// S盒，每个S盒是4x16的置换表，6位 -> 4位
int S_BOX[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// P置换，32位 -> 32位
int P[] = { 16,  7, 20, 21,
           29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2,  8, 24, 14,
           32, 27,  3,  9,
           19, 13, 30,  6,
           22, 11,  4, 25 };



// ------------------------------用来存放中间过程产生数据的全局变量---------------------------
bitset<64> m; // 当前输入的64位明文
bitset<64> c; // 当前明文加密过后得到的密文
bitset<64> key; // 64位密钥
bitset<48> subKey[16]; // 用来存放中间过程中，产生的16个子密钥
int numOfAcaM[20]; // 用来记录对明文进行改变时造成的结果
int numOfAcaK[20]; // 用来记录对密钥进行改变时造成的结果



// -----------------------------------辅助函数------------------------------------------
bitset<64> getM(string input) {
    // 对输入的明文字符串input进行解析，返回一个64bit的串
    int index = 0;
    // 临时字符串，存储输入的16进制字符串
    char* temp = new char[16];
    int indexOfTemp = 0;
    while (input[index] != '\0') {
        if (index > 1 && (input[index - 1] == 'x' || input[index - 2] == 'x')) {
            if (indexOfTemp == 16)
                break;
            temp[indexOfTemp] = input[index];
            indexOfTemp++;
        }
        index += 1;
    }

    indexOfTemp = 0;
    bitset<64> result;
    // 使用最笨的办法，switch case把16进制的字符表示转换成2进制的结果
    for (; indexOfTemp < 16; indexOfTemp++) {
        int startOfEdit = 63 - 4 * indexOfTemp;
        switch (temp[indexOfTemp]) {
        case '0':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 0;
            break;
        case '1':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 1;
            break;
        case '2':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 0;
            break;
        case '3':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 1;
            break;
        case '4':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 0;
            break;
        case '5':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 1;
            break;
        case '6':
            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 0;
            break;
        case '7':

            result[startOfEdit] = 0;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 1;
            break;
        case '8':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 0;
            break;
        case '9':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 1;
            break;
        case 'A':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 0;
            break;
        case 'B':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 0;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 1;
            break;
        case 'C':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 0;
            break;
        case 'D':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 0;
            result[startOfEdit - 3] = 1;
            break;
        case 'E':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 0;
            break;
        case 'F':

            result[startOfEdit] = 1;
            result[startOfEdit - 1] = 1;
            result[startOfEdit - 2] = 1;
            result[startOfEdit - 3] = 1;
            break;
        }
    }
    return result;
}



// ------------------------------DES中关键的函数实现----------------------------------

// 循环左移函数
bitset<28> cycleLeftShift(bitset<28> a, int count) {
    bitset<28> tmp = a;
    for (int i = 0; i < 28; i++) {
        a[(i + count) % 28] = tmp[i];
    }
    return a;
}

// 子密钥生成函数
void generateSubKeys() {
    bitset<56> realKey; // 64位的在经过置换以后，会变成56位
    bitset<28> leftOfRealKey; // realKey的左边28位
    bitset<28> rightOfRealKey; // realKey的右边28位
    // 去掉8个校验位，并直接使用PC_1进行代换
    for (int i = 0; i < 56; i++) {
        realKey[55 - i] = key[64 - PC_1[i]];
    }
    //cout << "realKey = " << realKey << endl;
    // 接下来进行16轮的移位操作，生成子密钥
    for (int count = 0; count < 16; count++) {
        // 切分密钥，分成左28和右28
        for (int i = 0; i < 28; i++) {
            leftOfRealKey[i] = realKey[28 + i];
            rightOfRealKey[i] = realKey[i];
        }
        //cout << "切分后：\nleft: " << leftOfRealKey << endl << "right: " << rightOfRealKey << endl;
        // 进行左移
        leftOfRealKey = cycleLeftShift(leftOfRealKey, shiftBits[count]);
        rightOfRealKey = cycleLeftShift(rightOfRealKey, shiftBits[count]);
        //cout << "循环左移后：\nleft: " << leftOfRealKey << endl << "right: " << rightOfRealKey << endl;
        // 将移位之后的左右两部分，拼回到原本的realKey上
        for (int i = 0; i < 28; i++) {
            realKey[i] = rightOfRealKey[i];
            realKey[i + 28] = leftOfRealKey[i];
        }
        //cout << "拼接回realKey: " << realKey << endl;
        // 经过压缩置换，得到48位的子密钥
        bitset<48> compressKey;
        for (int i = 0; i < 48; i++) {
            compressKey[47 - i] = realKey[56 - PC_2[i]];
        }
        //cout << count << ": " << compressKey << endl;
        // 将得到的子密钥，赋值到数组中去
        subKey[count] = compressKey;
    }
}

// 初始IP置换
bitset<64> IPReplace(bitset<64> a) {
    bitset<64> result;
    for (int i = 0; i < 64; i++) {
        result[63 - i] = a[64 - IP[i]];
    }
    return result;
}

// DES算法中的核心：S盒的代换等
bitset<32> f(bitset<32> R, bitset<48> currentKey) {
    // 1. 进行扩展置换，将32位的数据扩展到48位
    bitset<48> expandR;
    for (int i = 0; i < 48; i++) {
        expandR[47 - i] = R[32 - E[i]];
    }
    // 2. 和当前的key进行异或
    expandR = expandR ^ currentKey;
    // 3. S盒置换
    bitset<32> result;
    int x = 0;
    for (int i = 0; i < 48; i+=6) {
        int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
        int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 + expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
        int num = S_BOX[i / 6][row][col];
        bitset<4> binary(num);
        result[31 - x] = binary[3];
        result[31 - x - 1] = binary[2];
        result[31 - x - 2] = binary[1];
        result[31 - x - 3] = binary[0];
        x += 4;
    }
    // 4. P置换
    bitset<32> temp = result;
    for (int i = 0; i < 32; i++)
        result[31 - i] = temp[32 - P[i]];

    return result;
}

// 尾置换IP
bitset<64> IPReplaceReverse(bitset<64> a) {
    bitset<64> result;
    for (int i = 0; i < 64; i++) {
        result[63 - i] = a[64 - IP_1[i]];
    }
    return result;
}

// ----------------------------加密和解密功能函数--------------------------------
// 加密函数
bitset<64> encrypt(bitset<64> initial) {
    bitset<64> initialAfterIPReplace;

    // 将明文进行初始IP置换
    initialAfterIPReplace = IPReplace(initial);

    // 获取Li和Ri
    bitset<32> Li, Ri;
    for (int i = 0; i < 32; i++) {
        Li[i] = initialAfterIPReplace[32 + i];
        Ri[i] = initialAfterIPReplace[i];
    }

    // 接下来进行16轮的迭代
    bitset<32> tempLi;
    for (int round = 0; round < 16; round++) {
        tempLi = Ri;
        Ri = Li ^ f(Ri, subKey[round]);
        Li = tempLi;
    }

    // Ri||Li（合并操作）
    bitset<64> tempC;
    for (int i = 0; i < 32; i++) {
        tempC[i] = Li[i];
        tempC[i + 32] = Ri[i];
    }

    // 尾置换
    tempC = IPReplaceReverse(tempC);

    return tempC;
}

// 解密函数（和加密函数过程相同，仅需要把subKey反向使用即可，所以中间的代码直接来自于加密的函数）
bitset<64> decrypt(bitset<64> cipher) {
    bitset<64> initialAfterIPReplace;

    // 将密文进行初始IP置换
    initialAfterIPReplace = IPReplace(cipher);

    // 获取Li和Ri
    bitset<32> Li, Ri;
    for (int i = 0; i < 32; i++) {
        Li[i] = initialAfterIPReplace[32 + i];
        Ri[i] = initialAfterIPReplace[i];
    }

    // 接下来进行16轮的迭代
    bitset<32> tempLi;
    for (int round = 0; round < 16; round++) {
        tempLi = Ri;
        Ri = Li ^ f(Ri, subKey[15 - round]);
        Li = tempLi;
    }

    // Ri||Li（合并操作）
    bitset<64> tempC;
    for (int i = 0; i < 32; i++) {
        tempC[i] = Li[i];
        tempC[i + 32] = Ri[i];
    }

    // 尾置换
    tempC = IPReplaceReverse(tempC);

    return tempC;
}


int main() {
    //// 一个临时的字符串，用来存放输入
    //string input;
    //// 获取明文
    //cout << "输入明文\n";
    //getline(cin, input);
    //m = getM(input);

    //// 获取密钥
    //cout << "输入加密密钥\n";
    //getline(cin, input);
    //key = getM(input);


    // 处理测试用例中的struct
    for (int caseNumber = 0; caseNumber < 20; caseNumber++) {
        // 导入一些初始化的数据，虽然这个num可能没有什么用，后面在输出的时候可以体现一些
        int num = cases[caseNumber].num;
        int type = cases[caseNumber].mode;

        // 看类型，type=1是加密，type=0是解密
        if (type) {
            // 加密
            
            if (num == 1)
                cout << "encrypt:\n";
            // 首先处理结构中的数据，如key等

            // key
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }

            // txt
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }

            // 生成子密钥，保存在全局变量的subKey[]中
            generateSubKeys();

            // DES加密
            c = encrypt(m);
            cout << num << ":\t" << c << endl;



            // 统计雪崩效应
            // 首先改变的是明文
            // 重新统计明文
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // 重新统计密钥
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // 记录应该正常的out
            bitset<64> currectOut;
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].out[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    currectOut[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // 一个数组，用来对相应下角标的内容进行变化
            int indexOfTextAva[] = { 1,5,8,6,9,2,3,4 };
            // 需要改变的下角标的数量
            int lenth = sizeof(indexOfTextAva) / sizeof(indexOfTextAva[0]);
            // 对明文按位取反
            for (int ita = 0; ita < lenth; ita++) {
                m.flip(indexOfTextAva[ita]);
            }
            // DES加密
            c = encrypt(m);
            // 异或，统计结果
            bitset<64> xOut = currectOut ^ c;
            int result = xOut.count();
            numOfAcaM[caseNumber] = result;
            cout << "改变明文" << lenth << "位后，密文改变的位数为：" << result << endl;


            // 接下来统计改变密钥的雪崩效应
            // 重新统计明文
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // 重新统计密钥
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // 对密钥按位取反
            for (int ita = 0; ita < lenth; ita++) {
                key.flip(indexOfTextAva[ita]);
            }
            // 重新生成子密钥
            generateSubKeys();
            // DES加密
            c = encrypt(m);
            // 异或，统计结果
            xOut = currectOut ^ c;
            result = xOut.count();
            numOfAcaK[caseNumber] = result;
            cout << "改变密钥" << lenth << "位后，密文改变的位数为：" << result << endl;
        }
        else {
            // 解密，方法同加密
            if (num == 1)
                cout << "decrypt:\n";
            
            // key
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }

            // txt
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    c[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }

            // 生成子密钥，保存在全局变量的subKey[]中
            generateSubKeys();

            // DES解密
            m = decrypt(c);
            cout << num << ":\t" << m << endl;


            // 统计雪崩效应
            // 首先改变的是密文
            // 重新统计密文
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // 重新统计密钥
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // 记录应该正常的out
            bitset<64> currectOut;
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].out[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    currectOut[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // 一个数组，用来对相应下角标的内容进行变化
            int indexOfTextAva[] = { 1,5,8,6,9,2,3,4 };
            // 需要改变的下角标的数量
            int lenth = sizeof(indexOfTextAva) / sizeof(indexOfTextAva[0]);
            // 对密文按位取反
            for (int ita = 0; ita < lenth; ita++) {
                m.flip(indexOfTextAva[ita]);
            }
            // DES加密
            c = encrypt(m);
            // 异或，统计结果
            bitset<64> xOut = currectOut ^ c;
            int result = xOut.count();
            numOfAcaM[caseNumber] = result;
            cout << "改变密文" << lenth << "位后，明文改变的位数为：" << result << endl;


            // 接下来统计改变密钥的雪崩效应
            // 重新统计密文
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // 重新统计密钥
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // 对密钥按位取反
            for (int ita = 0; ita < lenth; ita++) {
                key.flip(indexOfTextAva[ita]);
            }
            // 重新生成子密钥
            generateSubKeys();
            // DES加密
            c = encrypt(m);
            // 异或，统计结果
            xOut = currectOut ^ c;
            result = xOut.count();
            numOfAcaK[caseNumber] = result;
            cout << "改变密钥" << lenth << "位后，明文改变的位数为：" << result << endl;
        }
    }

    // 计算雪崩效应的平均位数
    int aveOfChangeM = 0, aveOfChangeMK = 0, aveOfChangeC = 0, aveOfChangeCK = 0;
    for (int i = 0; i < 10; i++) {
        aveOfChangeM += numOfAcaM[i];
        aveOfChangeMK += numOfAcaK[i];
    }
    for (int i = 10; i < 20; i++) {
        aveOfChangeC += numOfAcaM[i];
        aveOfChangeCK += numOfAcaK[i];
    }
    aveOfChangeM = aveOfChangeM / 10;
    aveOfChangeMK /= 10;
    aveOfChangeC /= 10;
    aveOfChangeCK /= 10;
    cout << "\n经统计，雪崩效应的平均改变位数为：\n改明文：" << aveOfChangeM << "\t改明文密钥：" << aveOfChangeMK << "\t改密文：" 
        << aveOfChangeC << "\t改密文密钥：" << aveOfChangeCK << endl;

    return 0;
}