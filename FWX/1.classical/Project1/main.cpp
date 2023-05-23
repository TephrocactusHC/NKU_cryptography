#include<iostream>
#include<string>
using namespace std;

// ����������ĵ���󳤶�
#define MAX_SIZE_OF_M 1000

/*
* 1����λ����
��λ���룺��Ӣ����ĸ��ǰ������ƶ�һ���̶�λ�á���������ƶ�3��λ
�ã�������ĸ�����û������ִ�Сд����
A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  A  B  C
    ������Ϊ��public keys,�򾭹������û��ͱ���ˣ�sxeolf nhbv��
    �����26��Ӣ����ĸ���б��룺A��0��B��1������Z��25�������ϼ��ܹ��̿ɼ򵥵�д�ɣ�
        ���ģ�m��m1m2��mi��, ����
        ���ģ�c=c1c2��ci��, ���� ci=(mi+key mod26)��i��1��2������

ASCII:
A:65 Z:90
a:97 z:122

��1������ʵ��ԭ���ֶ���λ�����㷨�Ľ��ܣ��Լ�����������Ϣ����ѡ��һ����Կ����д��λ�����㷨ʵ�ֳ���ʵ�ּ��ܺͽ��ܲ�����
*/

void ShiftCipher() {
    // ��������
    cout << "Please input message:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);
    //cout << M;

    // ���ü�����Կkey
    int key;
    cout << "Please input key(1-25):";
    cin >> key;

    // ���Ľ����ʼ��
    char* C = new char[MAX_SIZE_OF_M];
    // ��λ����
    int index = 0;
    while (M[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // ����Ǵ�д��ĸ
            int i = (ASCII - 65 + key) % 26;
            C[index] = char(65 + i);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = (ASCII - 97 + key) % 26;
                C[index] = char(97 + i);
            }
            else {
                // ����Ƿ���ĸ
                C[index] = M[index];
            }
        }
        // �½Ǳ�����+1
        index += 1;
    }
    // ��β���������
    C[index] = '\0';

    // ������ܽ��
    cout << "Encrypted ciphertext is: ";
    cout << C << endl;

    // ��ʼ����
    // ���ܽ����ʼ��
    char* AM = new char[MAX_SIZE_OF_M];
    index = 0;
    while (C[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // ����Ǵ�д��ĸ
            int i = (ASCII - 65 - key + 26) % 26;
            AM[index] = char(65 + i);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = (ASCII - 97 - key + 26) % 26;
                AM[index] = char(97 + i);
            }
            else {
                // ����Ƿ���ĸ
                AM[index] = C[index];
            }
        }
        // �½Ǳ�����+1
        index += 1;
    }
    // ��β���������
    AM[index] = '\0';

    // ������ܽ��
    cout << "After decryption, the plaintext is: " << AM << endl;
}



/*
* 2������λ����Ĺ���
��λ������һ����򵥵����룬����Ч��Կ�ռ��СΪ25����ˣ�����������ٵķ������ơ�
�����Կ������ָ�����߶Կ��ܵ���Կ����٣�Ҳ���������п��ܵ���Կ�������ģ�ֱ���õ�����������ģ��ɴ�ȷ������ȷ����Կ�����ĵĹ���������
����λ������������Կ���������ֻҪ����25�ξͿ��Եõ���ȷ����Կ�����ġ�

��2������ͬѧΪһ�飬���๥���Է�����λ������ܻ�õ����ģ��ָ��������ĺ���Կ��
*/

void AttackShiftCipher() {
    // ��������
    cout << "Please input encrypted message:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);

    for (int key = 1; key < 26; key++) {
        // ���Ľ����ʼ��
        char* M = new char[MAX_SIZE_OF_M];
        // ��λ����
        int index = 0;
        while (C[index] != '\0') {
            // ��ȡ��ǰλ�õ�ASCII
            int ASCII = int(C[index]);
            if (ASCII <= 90 && ASCII >= 65) {
                // ����Ǵ�д��ĸ
                int i = (ASCII - 65 - key + 26) % 26;
                M[index] = char(65 + i);
            }
            else {
                if (ASCII <= 122 && ASCII >= 97) {
                    // �����Сд��ĸ
                    int i = (ASCII - 97 - key + 26) % 26;
                    M[index] = char(97 + i);
                }
                else {
                    // ����Ƿ���ĸ
                    M[index] = C[index];
                }
            }
            // �½Ǳ�����+1
            index += 1;
        }
        // ��β���������
        M[index] = '\0';

        // ������ܽ��
        cout << "Key = " << key << "\tMessage = " << M << endl;
    }
}



/*
* 3�������û�����
�����û�������Ǹ�����ĸ����û������Ľ��б任�ķ��������磬�����û�

A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
H  K  W  T  X  Y  S  G  B  P  Q  E  J  A  Z  M  L  N  O  F  C  I  D  V  U  R
    ���ģ�public keys, ����
    ���ģ�mckebw qxuo��
    �����û�ʵ�ֵ�һ���ؼ������ǹ����û���Ĺ��졣�û���Ĺ�������и��ֲ�ͬ��;������Ҫ���ǵ��Ǽ���ķ��㡣
    ��ʹ��һ���������ӣ�ɾȥ���е��ظ����֣���Ϊ�û����ǰ��Ĳ��֣�Ȼ���û���õ�����ĸ����ĸ���˳�����η����û����С�

��3���Լ�����������Ϣ����ѡ��һ����Կ�������û�����д�û�����ļӽ���ʵ�ֳ���ʵ�ּ��ܺͽ��ܲ�����
*/

void SingleTableReplacement() {
    // �����û���
    // �û�֮ǰ�����ݾ�ʹ��ASCII������������ASCII��ȥ��һ����λ���������ƫ��
    // ����Ǵ�д��ascii�Ͻ��д���ͺ�
    char ReplaceTable[26] = { 'h','k','w','t','x','y','s','g','b','p','q','e','j','a','z','m','l','n','o','f','c','i','d','v','u','r'};

    // ��������
    cout << "Please input message:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);

    // ���Ľ����ʼ��
    char* C = new char[MAX_SIZE_OF_M];

    // ѭ������
    int index = 0;
    while (M[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // ����Ǵ�д��ĸ
            int i = ASCII - 65;
            // ��ȡ���Ĵ��������ĸ��Сд��ĸ����Ҫ����ASCII�Ĺ�ϵת���ɴ�д��ĸ
            C[index] = char(int(ReplaceTable[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = ASCII - 97;
                C[index] = ReplaceTable[i];
            }
            else {
                // ����Ƿ���ĸ
                C[index] = M[index];
            }
        }
        // �½Ǳ�����+1
        index += 1;
    }
    // ��β���������
    C[index] = '\0';

    // ������ܽ��
    cout << "Encrypted ciphertext is: ";
    cout << C << endl;


    // ��ʼ����
    // ���ȶԴ��������һ����ת������Ԥ����
    char reverseTable[26];
    for (int i = 0; i < 26; i++) {
        // ���Ȼ�ȡ��ǰλ���ַ���ASCII
        int temp_ascii = int(ReplaceTable[i]);
        // ASCIIӳ�䵽26λ�ÿռ�֮�����뵽���λ��
        reverseTable[temp_ascii - 97] = char(i + 97);
    }

    // �������ݳ�ʼ��
    char* AM = new char[MAX_SIZE_OF_M];

    index = 0;
    while (C[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // ����Ǵ�д��ĸ
            int i = ASCII - 65;
            // �ҵ����Ƕ�Ӧ��Сд��ĸ������ASCIIת���ɴ�д����
            AM[index] = char(int(reverseTable[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = ASCII - 97;
                // �ҵ�������ת֮��ı��λ��
                AM[index] = reverseTable[i];
            }
            else {
                // ����Ƿ���ĸ
                AM[index] = C[index];
            }
        }
        // �½Ǳ�����+1
        index += 1;
    }
    // ��β���������
    AM[index] = '\0';

    // ������ܽ��
    cout << "After decryption, the plaintext is: " << AM << endl;
}



/*
* 4���Ե����û�����Ĺ�������
�ڵ����û������У������û�����ĸ��Ϸ�ʽ��26���֣�ԼΪ4.03��1026��
���Բ��������Կ�ķ�������һ������Ч�ķ�����
�Ե����û���������Ч�Ĺ���������������Ȼ���Ե�ʹ��Ƶ�ʣ�����ĸ��˫��ĸ��/����ĸ�顢�����ͷ/��β�ȣ����������Ӣ�ĵ������
Ӣ�ĵ�һЩ������������[1]:
    �̵���(small words)����Ӣ����ֻ�к��ټ����ǳ��̵ĵ��ʡ���ˣ������һ�����ܵ��ı��п���ȷ�����ʵķ�Χ����ô���ܵó����ԵĽ����
    һ����ĸ�ĵ���ֻ��a��I��
    ������Ƶ��ʵ���д���ڴӵ����ʼ���ѡȡ500k�ֽڵ������У�ֻ��������ĸ�ĵ��ʽ�����35�Σ���������ĸ���������Ϊ26��26��676�֡�
    ���ң��������Ǹ������У�ֻ��������ĸ�ĵ��ʳ���196�Σ���������ĸ���������Ϊ26��26��26��17576�֡�
    ���õ���(common words):�ٴη���500k�ֽڵ��������ܹ���5000�����ͬ�ĵ��ʳ��֡�
    �����9����õĵ��ʳ��ֵ��ܴ���ռ�ܵ�������21����20����õĵ��ʳ��ֵ��ܴ���ռ�ܵ�������30����104����õĵ���ռ50����
    247����õĵ���ռ60������������õ�9������ռ�ܴ����İٷֱ�Ϊ��
     the 4.65     to   3.02    of    2.61   I    2.2   a    1.95
     and 1.82     is   1.68    that  1.62   in   1.57
����ϸ��ͳ�ƽ�����������[1]��
    ��ĸƵ��(character frequency):��1M�ֽھɵĵ����ı��У�����ĸ��A������Z�������Դ�Сд���ֱ����ͳ�ơ����ֽ���Ƶ�ʣ��԰ٷֱȱ�ʾ����
    e  11.67   t  9.53   o  8.22   i  7.81   a  7.73   n  6.71  s  6.55
    r  5.97    h  4.52   l  4.3    d  3.24   u  3.21   c  3.06  m  2.8
    p  2.34    y  2.22   f  2.14   g  2.00   w  1.69   b  1.58  v  1.03
    k  0.79    x  0.30   j  0.23   q  0.12   z  0.09
     �Ӹñ��п��Կ�������õĵ���ĸӢ����e��t��������ĸʹ��Ƶ�������˵��С�öࡣ
     ����������һ�������û����룬����ͳ������������ֵ���ĸ�����ݴ˲³�������õ���ĸ��
     ������Ӣ��ͳ�Ƶ���������������ĸ��ϵȣ��������롣


��4����Ƶ��ͳ�Ʒ��������������õ����û����ܵ�һ�����ģ�
SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N 
XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC 
MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC 
SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC 
MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC
д����õ�������Ϣ���û���

SIC GCBSPNA XPMHACQ JB GPYXSMEPNXIY JR SINS MF SPNBRQJSSJBE JBFMPQNSJMB FPMQ N XMJBS N SM N XMJBS H HY QCNBR MF N XMRRJHAY JBRCGZPC GINBBCA JB RZGI N VNY SINS SIC MPJEJBNA QCRRNEC GNB MBAY HC PCGMTCPCD HY SIC PJEISFZA PCGJXJCBSR SIC XNPSJGJXNBSR JB SIC SPNBRNGSJMB NPC NAJGC SIC MPJEJBNSMP MF SIC QCRRNEC HMH SIC PCGCJTCP NBD MRGNP N XMRRJHAC MXXMBCBS VIM VJRICR SM ENJB ZBNZSIMPJOCD GMBSPMA MF SIC QCRRNEC
*/

void AttackSingleTableReplacement() {
    // ����Ҫͳ�Ƶ�����
    cout << "Please input encrypted message:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);

    // ��¼ͳ�������������ʼ��
    int frequency[26] = { 0 };

    // �������ģ�ͳ��Ƶ��
    int index = 0;
    while (C[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // ����Ǵ�д��ĸ
            int i = ASCII - 65;
            // ��ȡ���Ĵ��������ĸ��Сд��ĸ����Ҫ����ASCII�Ĺ�ϵת���ɴ�д��ĸ
            frequency[i] += 1;
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = ASCII - 97;
                frequency[i] += 1;
            }
            else {
                // ����Ƿ���ĸ
                // ��ʱ�����κ���Ϊ
            }
        }
        // �½Ǳ�����+1
        index += 1;
    }

    // ���ͳ�Ƶ�Ƶ��
    cout << "After statistics, the occurrence frequency of each letter is:";
    for (int i = 0; i < 26; i++) {
        if (i % 10 != 0)
            cout << char(97 + i) << ": " << frequency[i] << '\t';
        else
            cout << endl << char(97 + i) << ": " << frequency[i] << '\t';
    }

    // ���ݷ�������õ����������
    char replaceTable[26] = { 'n','h','g','d','c','f','e','i','j','0','0','a','q','b','m','x','0','p','r','s','z','t','v','0','y','o' };

    // ��ʼ����
    // ���ȶԴ��������һ����ת������Ԥ����
    char reverseTable[26];
    // ��ʼ��
    for (int i = 0; i < 26; i++) {
        reverseTable[i] = '0';
    }

    for (int i = 0; i < 26; i++) {
        // ���Ȼ�ȡ��ǰλ���ַ���ASCII
        int temp_ascii = int(replaceTable[i]);
        // ASCIIӳ�䵽26λ�ÿռ�֮�����뵽���λ��
        // ���ASCII�ǲ�������ȷ�ķ�Χ��
        if (temp_ascii >= 97 && temp_ascii <= 122) {
            // ����ǣ�����뵽��Ӧ�ı���
            reverseTable[temp_ascii - 97] = char(i + 97);
        }
        else {
            // ������ǣ�Ҳ����˵����ԭ����ʼ��ʱ�����ݣ�ʲô������
        }
    }

    // ���������������λ������0�ľ��Լ�����Ϊ�Լ�����������Ϊ��д���Ժͳɹ��滻�����ֿ�
    for (int i = 0; i < 26; i++) {
        if (reverseTable[i] == '0')
            reverseTable[i] = char(i + 65);
    }

    // �������ݳ�ʼ��
    char* AM = new char[MAX_SIZE_OF_M];

    index = 0;
    while (C[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(C[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            // ����Ǵ�д��ĸ
            int i = ASCII - 65;
            AM[index] = reverseTable[i];
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = ASCII - 97;
                // �ҵ�������ת֮��ı��λ��
                AM[index] = reverseTable[i];
            }
            else {
                // ����Ƿ���ĸ
                AM[index] = C[index];
            }
        }
        // �½Ǳ�����+1
        index += 1;
    }
    // ��β���������
    AM[index] = '\0';

    // ������ܽ��
    cout << "\nAfter decryption, the plaintext is:\n" << AM << endl;
}

int main() {
    cout << "�������ѡ����Ӧʵ�����ݣ�\n1����λ������ܺͽ���\n2������λ����Ĺ���\n3�������û�������ܺͽ���\n4���Ե����û�����Ĺ�������\n";
    int chooseNumber;
    cin >> chooseNumber;
    // �Ե�����Ǹ��س�
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
        cout << "��������������鲢��������\n";
    }

    return 0;
}