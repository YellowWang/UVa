// uva 10054
// ��ʼ���ն��������ڵ��������ʱ�������ο����˵�˼·��������ɫ�����ڵ㣬��ŷ����·�����չ���

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 1001
#define b_len 51

int g[len][len];
int d[len];
int visit[b_len];

int dfs(int i);
void euler(int i);
int main()
{
    //freopen("1.txt", "r", stdin);

    int cases;
    scanf("%d", &cases);
    for (int k = 0; k < cases; k++)
    {
        memset(g, 0, sizeof(g));
        memset(d, 0, sizeof(d));
        memset(visit, 0, sizeof(visit));
        int num;
        scanf("%d", &num);
        for (int i = 0; i < num; i++)
        {
            int x,y;
            scanf("%d %d",&x, &y);
            g[x][y]++;
            g[y][x]++;
            d[x]++;
            d[y]++;
        }
        printf("Case #%d\n", k+1);

        bool cycle=true;
        int  colornum = 0;
        int  startid = 0;
        // �����ǻ�������ô�͹����ɻ�
        for (int i = 1; i <= b_len; i++)
        {
            if (cycle && (d[i] & 0x01))
            {
                cycle = false;
            }
            if (d[i])
            {
                colornum++;
                startid = i;
            }
        }
        if (!cycle)
        {
            printf("some beads may be lost\n\n");
            continue;
        }

        // ��ȱ��������Ƿ��ܱ������е�
        int dnum = dfs(startid);
        if (dnum != colornum)
        {
            printf("some beads may be lost\n\n");
            continue;
        }

        // ��ӡ���ж���
        euler(startid);
        printf("\n");
    }

    return 0;
}

void euler(int i)
{
    for(int k = 1; k < b_len; k++)
    {
        if(g[i][k])
        {
            g[i][k]--;
            g[k][i]--;
            euler(k);
            printf("%d %d\n", k, i);
        }
    }
    return ;
}

int dfs(int i)
{
    visit[i] = 1;
    int num = 1;
    for (int k = 1; k <= b_len; k++)
    {
        if (g[i][k] && !visit[k])
        {
            num += dfs(k);
        }
    }
    return num;
}