// uva108 dp ����
// �������Ӿ�������
// ͨ��Ԥ�Ȱ�ÿ�е������ۼӣ���ʱO(n2)������֮��Ϳ���ͨ��O(n3)���������������
// �ο���http://www.knightzone.org/wordpress/archives/1140

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

#define len 101
int g_m[len][len];
int proc(int num);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
    memset(g_m, 0, sizeof(g_m));

    int num;
    while (scanf("%d", &num) !=EOF)
    {
        for (int i = 1; i <= num; i++)
        {
            for (int k = 1; k <= num; k++)
            {
                scanf("%d", &g_m[i][k]);
            }
        }

        printf("%d\n", proc(num));
    }


    return 0;
}

int proc(int num)
{
    // ����Ԥ����
    for (int i = 1; i <= num; i++)
    {
        for (int k = 2; k <= num; k++)
        {
            g_m[i][k] += g_m[i][k-1];
        }
    }

    // �����������
    int max_sum = 0;
    for (int i = 1; i <= num; i++)
    {
        for (int j = i; j <= num; j++)
        {
            int sum = 0;
            for (int k = 1; k <= num; k++)
            {
                sum += g_m[k][j] - g_m[k][i-1];
                if (sum < 0)
                    sum = 0;
                else if (max_sum < sum)
                    max_sum = sum;
            }
        }
    }
    return max_sum;
}