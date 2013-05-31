// uva11129 ̰�� ����
// ��ϸ
// ���⣺Ҫ���ܺ���3����3�����ϵĵȲ����С��м������������Ҳ������
// ���־���������6��
// ��ż������������Ϊ���ѡ������0 2 4 �� 1 3 5.
// �� 0 2 4������Ϊż���������ѡ������0 4 �� 2��0 4���Ϊ4 0, 2 ֱ�������
// �� 1 3 5������Ϊż���������ѡ������1 5 �� 3.���Ϊ5 1 3.
// �����Ϊ��4 0 2 5 1 3.
// �ܽ᣺��һ���������У�������ż���֣�ʣ��2����1����ʱ�����������

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <queue>  
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

#define len 10000
int g_n[len];
void binary_proc(int start_i, int num, int inter);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    for (int i = 0; i < len; i++)
    {
        g_n[i] = i;
    }

    int num;
    while (scanf("%d", &num) && num)
    {
        printf("%d:", num);
        binary_proc(0, num, 1);
        printf("\n");
    }

    return 0;
}

void binary_proc(int start_i, int num, int inter)
{
    if (num <= 0)
        return;
    if (num == 1)
    {
        printf(" %d", g_n[start_i]);
        return;
    }
    if (num == 2)
    {
        printf(" %d %d", g_n[start_i+inter], g_n[start_i]);
        return;
    }

    if (num & 0x01)
        binary_proc(start_i, (num>>1)+1, inter<<1);
    else
        binary_proc(start_i, num>>1, inter<<1);

    binary_proc(start_i+inter, num>>1, inter<<1);
}