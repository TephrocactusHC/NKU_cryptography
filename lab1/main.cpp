#include<iostream>
#include<string>
using namespace std;
#define MAX_SIZE_OF_M 1000// ����������ĵ���󳤶�

void function_num1() {
    cout << "��������:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);

    // ���ü�����Կkey
    int key;
    cout << "������key��ȡֵ��Χ��(1-25):";
    cin >> key;
    cout << "------------------------------------------------" <<endl;
    cout << "��ʼ���ܣ�" <<endl;
    // ���Ľ����ʼ��
    char* C = new char[MAX_SIZE_OF_M];
    // ��λ����
    int index = 0;
    //�����Сд�Ķ���
    while (M[index] != '\0') {
        // ��ȡ��ǰλ�õ�ASCII
        int ASCII = int(M[index]);
        if (ASCII <= 90 && ASCII >= 65) {
            int i = (ASCII - 65 + key) % 26;C[index] = char(65 + i);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                int i = (ASCII - 97 + key) % 26;C[index] = char(97 + i);
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
    cout << "���ܽ�����" <<endl;
    cout << "������ܽ��: ";
    cout << C << endl;
    cout << "------------------------------------------------" <<endl;

    cout << "------------------------------------------------" <<endl;
    cout << "��ʼ���ܣ�" <<endl;
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
    cout << "���ܽ�����" <<endl;

    cout << "������ܽ��: " << AM << endl;
    cout << "------------------------------------------------" <<endl;
}

void function_num2() {

    cout << "��������:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);
    cout << "------------------------------------------------" <<endl;
    cout << "��ʼ���ܣ�" <<endl;
    for (int key = 1; key < 26; key++) {
        // ���Ľ����ʼ��
        char* M = new char[MAX_SIZE_OF_M];
        // ��λ����
        int index = 0;
        //�����Сд�Ķ���
        while (C[index] != '\0') {
            // ��ȡ��ǰλ�õ�ASCII
            int ASCII = int(C[index]);
            if (ASCII <= 90 && ASCII >= 65) {
                int i = (ASCII - 65 - key + 26) % 26;M[index] = char(65 + i);
            }
            else {
                if (ASCII <= 122 && ASCII >= 97) {
                    int i = (ASCII - 97 - key + 26) % 26;M[index] = char(97 + i);
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

        cout << "Key = " << key << "  ������ܽ�� = " << M << endl;
    }
    cout << "���ܽ�����" <<endl;
}

void function_num3() {
    char R_Table[26] = { 'h','k','w','t','x','y','s','g','b','p','q','e','j','a','z','m','l','n','o','f','c','i','d','v','u','r'};
    cout << "��������:\n";
    char* M = new char[MAX_SIZE_OF_M];
    cin.getline(M, MAX_SIZE_OF_M);
    cout << "------------------------------------------------" <<endl;
    cout << "��ʼ���ܣ�" <<endl;
    // ���Ľ����ʼ��
    char* C = new char[MAX_SIZE_OF_M];
    // ѭ������
    int index = 0;
    //�����Сд�Ķ���
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
        // �½Ǳ�����+1
        index += 1;
    }
    // ��β���������
    C[index] = '\0';
    cout << "���ܽ�����" <<endl;
    cout << "���ܽ��: ";
    cout << C << endl;
    cout << "------------------------------------------------" <<endl;
    cout << "------------------------------------------------" <<endl;
    cout << "��ʼ���ܣ�" <<endl;
    char RTable[26];
    for (int i = 0; i < 26; i++) {
        // ���Ȼ�ȡ��ǰλ���ַ���ASCII
        int temp_ascii = int(R_Table[i]);
        // ASCIIӳ�䵽26λ�ÿռ�֮�����뵽���λ��
        RTable[temp_ascii - 97] = char(i + 97);
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
            AM[index] = char(int(RTable[i]) - 32);
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = ASCII - 97;
                // �ҵ�������ת֮��ı��λ��
                AM[index] = RTable[i];
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
    cout << "���ܽ�����" <<endl;
    cout << "���ܽ��: " << AM << endl;
    cout << "------------------------------------------------" <<endl;
}

void function_num4() {
    cout << "����Ҫͳ�Ƶ�����:\n";
    char* C = new char[MAX_SIZE_OF_M];
    cin.getline(C, MAX_SIZE_OF_M);
    cout << "------------------------------------------------" <<endl;
    cout << "��ʼ���ܣ�" <<endl;
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
        }
        // �½Ǳ�����+1
        index += 1;
    }

    cout << "���ͳ�Ƶ�Ƶ��:";
    for (int i = 0; i < 26; i++) {
        if (i % 10 != 0)
            cout << char(97 + i) << ": " << frequency[i] << '\t';
        else
            cout << endl << char(97 + i) << ": " << frequency[i] << '\t';
    }
    // ���ݷ�������õ����������
    char R_Table[26] = { 'n','h','g','d','c','f','e','i','j','0','0','a','q','b','m','x','0','p','r','s','z','t','v','0','y','o' };

    // ���ȶԴ��������һ����ת������Ԥ����
    char RTable[26];
    // ��ʼ��
    for (int i = 0; i < 26; i++) {
        RTable[i] = '0';
    }
    for (int i = 0; i < 26; i++) {
        // ���Ȼ�ȡ��ǰλ���ַ���ASCII
        int temp_ascii = int(R_Table[i]);
        // ASCIIӳ�䵽26λ�ÿռ�֮�����뵽���λ��
        // ���ASCII�ǲ�������ȷ�ķ�Χ��
        if (temp_ascii >= 97 && temp_ascii <= 122) {
            // ����ǣ�����뵽��Ӧ�ı���
            RTable[temp_ascii - 97] = char(i + 97);
        }
    }

    // ���������������λ������0�ľ��Լ�����Ϊ�Լ�����������Ϊ��д���Ժͳɹ��滻�����ֿ�
    for (int i = 0; i < 26; i++) {
        if (RTable[i] == '0')
            RTable[i] = char(i + 65);
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
            AM[index] = RTable[i];
        }
        else {
            if (ASCII <= 122 && ASCII >= 97) {
                // �����Сд��ĸ
                int i = ASCII - 97;
                // �ҵ�������ת֮��ı��λ��
                AM[index] = RTable[i];
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
    cout << "���ܽ�����" <<endl;
    cout << "\n������ܽ��:\n" << AM << endl;
    cout << "------------------------------------------------" <<endl;
}

int main() {
    cout << "ѡ���ܣ�\ncase1:��λ������ܽ���\ncase2:��λ���빥��\ncase3:�����û�������ܽ���\ncase4:�����û����빥��\nע�⣬ֻ��Ҫ�������֣�����Ҫ����case\n";
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
            cout << "��������������鲢��������\n";
    }
    system("pause");
    return 0;
}
