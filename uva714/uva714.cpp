// uva714 ̰�� ����
// ����

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

typedef long long ll;
#define len 500
int g_n[len];
vector<int> g_split;
void proc(int num, int k, ll r);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        int num,k;
        scanf("%d %d", &num, &k);
        ll sum = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
            sum += g_n[i];
        }

        proc(num, k, sum);

        // �����ע���ʽ
        for (int i = 0; i < num-1; i++)
        {
            printf("%d ", g_n[i]);
            for (int j = 0; j < g_split.size(); j++)
            {
                if (i == g_split[j])
                {
                    printf("/ ");
                    break;
                }
            }
        }
        if (num > 0)
            printf("%d", g_n[num-1]);
        printf("\n");
    }

    return 0;
}

// ÿ���˵������ܳ���m��
int match_min3(int num, int k, ll m, ll& minimum, vector<int>& split)
{
    int j = num-1;
    minimum = 0;
    // ����������
    for (int i = k-1; i >= 0; i--)
    {
        ll sum = 0;
        // �������⣬˵����ж�����ܣ���ô��һ���˵�����Ҫ��С��
        // ��ô����������󣬾����ܸ��ұߵ��˷���������
        while (j >= i)
        {
            if (sum + g_n[j] > m)
                break;
            sum += g_n[j];
            j--;
        }
        if (i > 0)
            split.push_back(j);
        if (i == 0 && j >= 0) // �����飬����������
            return 2;
        if (sum > minimum) // �ҵ�������������
            minimum = sum;
    }
    if (minimum == m)
        return 0;
    else if (minimum > m)
        return 2;
    else
        return 1;
}

void proc(int num, int k, ll r)
{
    ll l,m;
    l = 0;
    // ���֣���0�����ޣ�����ҳ���ͣ�
    while (l + 1 < r)
    {
        m = (l+r)>>1;

        vector<int> split;
        ll minimum;
        // �����֡���m�Ƿ������ĿҪ��
        int match_state = match_min3(num, k, m, minimum, split);
        if (match_state == 0)
        {
            g_split = split;
            return;
        }
        else if (match_state == 1)
            r = m;
        else
            l = m;
    }
    return;
}