// uva 10050
// ��Ҫ���ҳ���ͬparty��hartal֮�����ϵ�͹���
// ��ʱ0.008s�����0s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define  len 3650
int d[len]; // ÿһ���Ƿ��ǰչ�������

int main()
{
    //ifstream cin("1.txt");

    // ��Ŀ������7�ı��������Լ�����1��6.
    // ÿ�����ۼ�����7�Σ��ֻص���Ӧ�����ڣ�Ҳ����һ��ѭ��
    // 0�����ܼ���չ�����Ϊ���塢�������ݼ٣���1��չ�
    // ����h=1���ֱ��Ӧ���� 7,1,2,3,4,5,6������������
    int h[6][7] = {
        {1,1,1,1,1,0,0},
        {1,1,0,1,1,1,0},
        {1,0,1,1,1,1,0},
        {1,1,1,1,0,1,0},
        {1,1,1,0,1,1,0},
        {0,1,1,1,1,1,0}
    }; 

    int cases = 0;
    cin >> cases;
    while (cases--)
    {
        memset(d, 0, sizeof(d));// ���
        int days = 0;
        cin >> days;

        int p = 0;
        cin >> p;
        // ����ÿ��party�İչ�����
        int input= 0;
        for (int i = 0; i < p; ++i)
        {
            cin >> input;
            int base = input % 7;
            int cur = input;
            int base_idx = 0;
            while (cur <= days)
            {
                d[cur-1] = h[base-1][base_idx++];
                if (base_idx >= 7)
                    base_idx = 0;
                cur += input;
            }
        }

        // �ۼ����аչ�����
        int sum = 0;
        for (int i = 0; i < len; ++i)
        {
            if (d[i])
                ++sum;
        }

        // ���
        cout << sum << endl;
    }

    return 0;
}