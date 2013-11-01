// uva562 dp
// ����������Ρ�ͳ�Ƹ�����һ���˵�Ǯ����f(i)��������Ƿ�����������Ŀ��Ǯ��
// f(i) = f(i - g(j)); g(j)�ǵ�j��Ǯ�ı�ֵ��Ǯ������
// ��ʽ����˼�ǣ�������ڵ�Ǯ��-��ǰӲ�ҵı�ֵ�ǿ����е�Ǯ������ô���ڵ�Ǯ��Ҳ�ǿ����еġ�
// �����д������Ǯ����Ŀ�ǺϷ��ġ����2��Ӳ��1��5.��ô4�Ͳ��Ϸ���
 
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
 
#define len 100
int g_n[len];
int f[50001];
void dp(int num, int total);
 
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
        int num;
        scanf("%d", &num);
        int total = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &g_n[i]);
            total += g_n[i];
        }
 
        dp(num, total);
    }
 
    return 0;
}
 
void dp(int num, int total)
{
    memset(f, 0, sizeof(int)*total);
 
    f[0] = 1;
    for (int i = 0; i < num; i++)
    {
        for (int k = total; k >= g_n[i]; k--)
        {
            if (!f[k])
                f[k] = f[k - g_n[i]];
        }
    }
 
    for (int i = (total>>1); i >= 0; i--)
    {
        if (f[i])
        {
            printf("%d\n", total - (i<<1));
            break;
        }
    }
}