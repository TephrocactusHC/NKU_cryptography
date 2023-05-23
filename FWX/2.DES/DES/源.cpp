#include<iostream>
#include<string>
#include<bitset>
using namespace std;

// ---------------------------DES�����㷨��Ҫ�õ����������----------------------------------

// �û�IP��
int IP[] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
              62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
              57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
              61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };

// ��Կ�û�����64λ��Կ���56λ
int PC_1[] = { 57,49,41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10,  2, 59, 51, 43, 35, 27,
              19, 11,  3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14,  6, 61, 53, 45, 37, 29,
              21, 13,  5, 28, 20, 12, 4 };

// ѹ���û�����56λ��Կѹ����48λ����Կ
int PC_2[] = { 14, 17, 11, 24,  1,  5,
               3, 28, 15,  6, 21, 10,
              23, 19, 12,  4, 26,  8,
              16,  7, 27, 20, 13,  2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 };

// ÿ�����Ƶ�λ��
int shiftBits[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// ��������
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

// β�û���
int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41,  9, 49, 17, 57, 25 };

// ��չ�û����� 32λ ��չ�� 48λ
int E[48] = { 32,  1,  2,  3,  4,  5,
            4,  5,  6,  7,  8,  9,
            8,  9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32,  1 };

// S�У�ÿ��S����4x16���û���6λ -> 4λ
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

// P�û���32λ -> 32λ
int P[] = { 16,  7, 20, 21,
           29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2,  8, 24, 14,
           32, 27,  3,  9,
           19, 13, 30,  6,
           22, 11,  4, 25 };



// ------------------------------��������м���̲������ݵ�ȫ�ֱ���---------------------------
bitset<64> m; // ��ǰ�����64λ����
bitset<64> c; // ��ǰ���ļ��ܹ���õ�������
bitset<64> key; // 64λ��Կ
bitset<48> subKey[16]; // ��������м�����У�������16������Կ
int numOfAcaM[20]; // ������¼�����Ľ��иı�ʱ��ɵĽ��
int numOfAcaK[20]; // ������¼����Կ���иı�ʱ��ɵĽ��



// -----------------------------------��������------------------------------------------
bitset<64> getM(string input) {
    // ������������ַ���input���н���������һ��64bit�Ĵ�
    int index = 0;
    // ��ʱ�ַ������洢�����16�����ַ���
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
    // ʹ����İ취��switch case��16���Ƶ��ַ���ʾת����2���ƵĽ��
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



// ------------------------------DES�йؼ��ĺ���ʵ��----------------------------------

// ѭ�����ƺ���
bitset<28> cycleLeftShift(bitset<28> a, int count) {
    bitset<28> tmp = a;
    for (int i = 0; i < 28; i++) {
        a[(i + count) % 28] = tmp[i];
    }
    return a;
}

// ����Կ���ɺ���
void generateSubKeys() {
    bitset<56> realKey; // 64λ���ھ����û��Ժ󣬻���56λ
    bitset<28> leftOfRealKey; // realKey�����28λ
    bitset<28> rightOfRealKey; // realKey���ұ�28λ
    // ȥ��8��У��λ����ֱ��ʹ��PC_1���д���
    for (int i = 0; i < 56; i++) {
        realKey[55 - i] = key[64 - PC_1[i]];
    }
    //cout << "realKey = " << realKey << endl;
    // ����������16�ֵ���λ��������������Կ
    for (int count = 0; count < 16; count++) {
        // �з���Կ���ֳ���28����28
        for (int i = 0; i < 28; i++) {
            leftOfRealKey[i] = realKey[28 + i];
            rightOfRealKey[i] = realKey[i];
        }
        //cout << "�зֺ�\nleft: " << leftOfRealKey << endl << "right: " << rightOfRealKey << endl;
        // ��������
        leftOfRealKey = cycleLeftShift(leftOfRealKey, shiftBits[count]);
        rightOfRealKey = cycleLeftShift(rightOfRealKey, shiftBits[count]);
        //cout << "ѭ�����ƺ�\nleft: " << leftOfRealKey << endl << "right: " << rightOfRealKey << endl;
        // ����λ֮������������֣�ƴ�ص�ԭ����realKey��
        for (int i = 0; i < 28; i++) {
            realKey[i] = rightOfRealKey[i];
            realKey[i + 28] = leftOfRealKey[i];
        }
        //cout << "ƴ�ӻ�realKey: " << realKey << endl;
        // ����ѹ���û����õ�48λ������Կ
        bitset<48> compressKey;
        for (int i = 0; i < 48; i++) {
            compressKey[47 - i] = realKey[56 - PC_2[i]];
        }
        //cout << count << ": " << compressKey << endl;
        // ���õ�������Կ����ֵ��������ȥ
        subKey[count] = compressKey;
    }
}

// ��ʼIP�û�
bitset<64> IPReplace(bitset<64> a) {
    bitset<64> result;
    for (int i = 0; i < 64; i++) {
        result[63 - i] = a[64 - IP[i]];
    }
    return result;
}

// DES�㷨�еĺ��ģ�S�еĴ�����
bitset<32> f(bitset<32> R, bitset<48> currentKey) {
    // 1. ������չ�û�����32λ��������չ��48λ
    bitset<48> expandR;
    for (int i = 0; i < 48; i++) {
        expandR[47 - i] = R[32 - E[i]];
    }
    // 2. �͵�ǰ��key�������
    expandR = expandR ^ currentKey;
    // 3. S���û�
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
    // 4. P�û�
    bitset<32> temp = result;
    for (int i = 0; i < 32; i++)
        result[31 - i] = temp[32 - P[i]];

    return result;
}

// β�û�IP
bitset<64> IPReplaceReverse(bitset<64> a) {
    bitset<64> result;
    for (int i = 0; i < 64; i++) {
        result[63 - i] = a[64 - IP_1[i]];
    }
    return result;
}

// ----------------------------���ܺͽ��ܹ��ܺ���--------------------------------
// ���ܺ���
bitset<64> encrypt(bitset<64> initial) {
    bitset<64> initialAfterIPReplace;

    // �����Ľ��г�ʼIP�û�
    initialAfterIPReplace = IPReplace(initial);

    // ��ȡLi��Ri
    bitset<32> Li, Ri;
    for (int i = 0; i < 32; i++) {
        Li[i] = initialAfterIPReplace[32 + i];
        Ri[i] = initialAfterIPReplace[i];
    }

    // ����������16�ֵĵ���
    bitset<32> tempLi;
    for (int round = 0; round < 16; round++) {
        tempLi = Ri;
        Ri = Li ^ f(Ri, subKey[round]);
        Li = tempLi;
    }

    // Ri||Li���ϲ�������
    bitset<64> tempC;
    for (int i = 0; i < 32; i++) {
        tempC[i] = Li[i];
        tempC[i + 32] = Ri[i];
    }

    // β�û�
    tempC = IPReplaceReverse(tempC);

    return tempC;
}

// ���ܺ������ͼ��ܺ���������ͬ������Ҫ��subKey����ʹ�ü��ɣ������м�Ĵ���ֱ�������ڼ��ܵĺ�����
bitset<64> decrypt(bitset<64> cipher) {
    bitset<64> initialAfterIPReplace;

    // �����Ľ��г�ʼIP�û�
    initialAfterIPReplace = IPReplace(cipher);

    // ��ȡLi��Ri
    bitset<32> Li, Ri;
    for (int i = 0; i < 32; i++) {
        Li[i] = initialAfterIPReplace[32 + i];
        Ri[i] = initialAfterIPReplace[i];
    }

    // ����������16�ֵĵ���
    bitset<32> tempLi;
    for (int round = 0; round < 16; round++) {
        tempLi = Ri;
        Ri = Li ^ f(Ri, subKey[15 - round]);
        Li = tempLi;
    }

    // Ri||Li���ϲ�������
    bitset<64> tempC;
    for (int i = 0; i < 32; i++) {
        tempC[i] = Li[i];
        tempC[i + 32] = Ri[i];
    }

    // β�û�
    tempC = IPReplaceReverse(tempC);

    return tempC;
}


int main() {
    //// һ����ʱ���ַ����������������
    //string input;
    //// ��ȡ����
    //cout << "��������\n";
    //getline(cin, input);
    //m = getM(input);

    //// ��ȡ��Կ
    //cout << "���������Կ\n";
    //getline(cin, input);
    //key = getM(input);


    // ������������е�struct
    for (int caseNumber = 0; caseNumber < 20; caseNumber++) {
        // ����һЩ��ʼ�������ݣ���Ȼ���num����û��ʲô�ã������������ʱ���������һЩ
        int num = cases[caseNumber].num;
        int type = cases[caseNumber].mode;

        // �����ͣ�type=1�Ǽ��ܣ�type=0�ǽ���
        if (type) {
            // ����
            
            if (num == 1)
                cout << "encrypt:\n";
            // ���ȴ���ṹ�е����ݣ���key��

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

            // ��������Կ��������ȫ�ֱ�����subKey[]��
            generateSubKeys();

            // DES����
            c = encrypt(m);
            cout << num << ":\t" << c << endl;



            // ͳ��ѩ��ЧӦ
            // ���ȸı��������
            // ����ͳ������
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // ����ͳ����Կ
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // ��¼Ӧ��������out
            bitset<64> currectOut;
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].out[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    currectOut[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // һ�����飬��������Ӧ�½Ǳ�����ݽ��б仯
            int indexOfTextAva[] = { 1,5,8,6,9,2,3,4 };
            // ��Ҫ�ı���½Ǳ������
            int lenth = sizeof(indexOfTextAva) / sizeof(indexOfTextAva[0]);
            // �����İ�λȡ��
            for (int ita = 0; ita < lenth; ita++) {
                m.flip(indexOfTextAva[ita]);
            }
            // DES����
            c = encrypt(m);
            // ���ͳ�ƽ��
            bitset<64> xOut = currectOut ^ c;
            int result = xOut.count();
            numOfAcaM[caseNumber] = result;
            cout << "�ı�����" << lenth << "λ�����ĸı��λ��Ϊ��" << result << endl;


            // ������ͳ�Ƹı���Կ��ѩ��ЧӦ
            // ����ͳ������
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // ����ͳ����Կ
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // ����Կ��λȡ��
            for (int ita = 0; ita < lenth; ita++) {
                key.flip(indexOfTextAva[ita]);
            }
            // ������������Կ
            generateSubKeys();
            // DES����
            c = encrypt(m);
            // ���ͳ�ƽ��
            xOut = currectOut ^ c;
            result = xOut.count();
            numOfAcaK[caseNumber] = result;
            cout << "�ı���Կ" << lenth << "λ�����ĸı��λ��Ϊ��" << result << endl;
        }
        else {
            // ���ܣ�����ͬ����
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

            // ��������Կ��������ȫ�ֱ�����subKey[]��
            generateSubKeys();

            // DES����
            m = decrypt(c);
            cout << num << ":\t" << m << endl;


            // ͳ��ѩ��ЧӦ
            // ���ȸı��������
            // ����ͳ������
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // ����ͳ����Կ
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // ��¼Ӧ��������out
            bitset<64> currectOut;
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].out[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    currectOut[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // һ�����飬��������Ӧ�½Ǳ�����ݽ��б仯
            int indexOfTextAva[] = { 1,5,8,6,9,2,3,4 };
            // ��Ҫ�ı���½Ǳ������
            int lenth = sizeof(indexOfTextAva) / sizeof(indexOfTextAva[0]);
            // �����İ�λȡ��
            for (int ita = 0; ita < lenth; ita++) {
                m.flip(indexOfTextAva[ita]);
            }
            // DES����
            c = encrypt(m);
            // ���ͳ�ƽ��
            bitset<64> xOut = currectOut ^ c;
            int result = xOut.count();
            numOfAcaM[caseNumber] = result;
            cout << "�ı�����" << lenth << "λ�����ĸı��λ��Ϊ��" << result << endl;


            // ������ͳ�Ƹı���Կ��ѩ��ЧӦ
            // ����ͳ������
            for (int countTxt = 0; countTxt < 8; countTxt++) {
                bitset<8> tempTxt(int(cases[caseNumber].txt[countTxt]));
                for (int countOfTxt = 0; countOfTxt < 8; countOfTxt++) {
                    m[63 - (countTxt * 8 + countOfTxt)] = tempTxt[7 - countOfTxt];
                }
            }
            // ����ͳ����Կ
            for (int countKey = 0; countKey < 8; countKey++) {
                bitset<8> tempKey(int(cases[caseNumber].key[countKey]));
                for (int countOfBit = 0; countOfBit < 8; countOfBit++) {
                    key[63 - (countKey * 8 + countOfBit)] = tempKey[7 - countOfBit];
                }
            }
            // ����Կ��λȡ��
            for (int ita = 0; ita < lenth; ita++) {
                key.flip(indexOfTextAva[ita]);
            }
            // ������������Կ
            generateSubKeys();
            // DES����
            c = encrypt(m);
            // ���ͳ�ƽ��
            xOut = currectOut ^ c;
            result = xOut.count();
            numOfAcaK[caseNumber] = result;
            cout << "�ı���Կ" << lenth << "λ�����ĸı��λ��Ϊ��" << result << endl;
        }
    }

    // ����ѩ��ЧӦ��ƽ��λ��
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
    cout << "\n��ͳ�ƣ�ѩ��ЧӦ��ƽ���ı�λ��Ϊ��\n�����ģ�" << aveOfChangeM << "\t��������Կ��" << aveOfChangeMK << "\t�����ģ�" 
        << aveOfChangeC << "\t��������Կ��" << aveOfChangeCK << endl;

    return 0;
}