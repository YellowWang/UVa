// uva 442
// ��ʱ0.08s �����0s
// ջ���÷�

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;


struct node
{
    int x;
    int y;
    int sum; // x*y �������ظ������ֵ
};

// ��Ϊ��Ŀ˵��26����д��ĸ���������������������
#define len 26
node input[len];

// �ַ����ĳ���
#define len_str 256
char a[len_str];

int main()
{
    //ifstream cin("1.txt");

    //��������
    int num = 0;
    cin >> num;

    char c;
    for (int i = 0; i < num; i++)
    {
        cin >> c;
        cin >> input[c-'A'].x >> input[c-'A'].y;
        input[c-'A'].sum = input[c-'A'].x * input[c-'A'].y;
    }

    //��ջ������
    int si = 0; // ջ��λ��
    node st[len_str];//ֻ����ÿ�����������
    while (cin >> a)
    {
        // ���ֻ��һ��Ԫ�أ�ֱ�ӷ���0
        if (a[0] != '(')
        {
            cout << 0 << endl;
            continue;;
        }

        int total = 0;// ��¼���м������
        char* p = a;
        si = 0;
        while (*p)
        {
            if (*p == ')')
            {
                // ����
                int tsi = si-2;
                // ����ƥ�䣬�����error
                if (st[tsi].y != st[tsi+1].x)
                {
                    cout << "error" << endl;
                    break;
                }


                total += st[tsi].sum * st[tsi+1].y;
                // �����������ջ��
                st[tsi].sum = st[tsi].x * st[tsi+1].y;
                st[tsi].x = st[tsi].x;
                st[tsi].y = st[tsi+1].y;

                // ���ж��������
                if (tsi == 0 && *(p+1) == 0)
                {
                    cout << total << endl;
                    break;
                }

                // ����ջ��
                si = tsi+1;
                p++;
                continue;
            }

            // ����ջ����
            if (*p != '(' && *p != ')')
            {
                st[si].x = input[*p-'A'].x;
                st[si].y = input[*p-'A'].y;
                st[si].sum = input[*p-'A'].sum;
                si++;
            }
            p++;
        }
    }

    return 0;
}