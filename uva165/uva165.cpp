// uva165 ö���Ӽ�������
// ��Ϊh+k<=9�����Կ����ñ�������
// �տ�ʼö���Ӽ���Ȼ��ͨ���Ӽ��ҵ�����С��о��ٶ��е�������ʱûע��h+k<=9�����ʵ����
// ��󷴹�������С����ö������У����Ӽ��Ƿ���ϡ�

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 9
#define seq_len 100

// sumΪ����У�search�Ǽ���ֽ��Ƿ��ܴﵽ�����
bool search(int stamps, int sum, int n, int* p);
// ö���Ӽ���1����ö�٣���ѡ��
void collection(int start, int idx, int num, int max, int* p);
// ͨ���Ӽ���������У�����û���õ�
int sequence(int stamps, int n, int sum, int* p, int* res);

int stamps,k;
int g_max;
int g_seq_max[seq_len];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif


    while (scanf("%d %d", &stamps, &k) && stamps)
    {
        int p[seq_len];
        g_max = 0;
        // ����ʵ������33�Ϳ��Է�������
        collection(2, 0, k-1, 33, p);

        for (int i = 0; i < seq_len && g_seq_max[i]!=0; i++)
        {
            printf("%3d", g_seq_max[i]);
        }
        printf(" ->%3d\n", g_max);
    }

    return 0;
}

void collection(int start, int idx, int num, int max, int* p)
{
    if (idx == num)
    {
        int seq_max[seq_len];
        memset(seq_max, 0, sizeof(seq_max));
        seq_max[0]=1;
        for (int i = 1; i <= num; i++)
        {
            seq_max[i] = p[i-1];
        }
        int t = 0;
        int sum_max1 = stamps;
        if (num != 0)
            sum_max1 = stamps*p[num-1];

        // ö�����п��ܵ��������г���
        for (int i = 1; i <= sum_max1; i++)
        {
            // ��;�жϾ���������
            if (!search(stamps, i, num+1, seq_max))
                break;
            t = i;
        }

        if (t > g_max)
        {
            g_max = t;
            memcpy(g_seq_max, seq_max, sizeof(seq_max));
        }
        return;
    }

    for (int i = start; i < max; i++)
    {
        p[idx] = i;
        collection(i+1, idx+1, num, max, p);
        p[idx] = -1;
    }

}

bool search(int stamps, int sum, int n, int* p)
{
    if (!stamps)
    {
        return false;
    }

    // ��֦
    if (sum > stamps * p[n-1])
        return false;

    for (int i = n-1; i >= 0; i--)
    {
        if (sum - p[i] > 0)
        {
            if (search(stamps-1, sum-p[i], n, p))
                return true;
        }
        else if (sum - p[i] == 0)
            return true;
    }
    return false;
}

int sequence(int stamps, int n, int sum, int* p, int* res)
{
    res[sum] = 1;
    if (!stamps)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        //if (!res[sum+sum+p[i]])
        sequence(stamps-1, n, sum+p[i], p, res);
    }
}