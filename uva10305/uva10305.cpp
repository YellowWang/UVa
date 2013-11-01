// uva10305 ͼ�㷨
// ����ֱ����bfs�����������¸��ڵ���������ǰ��

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 101

int g[len][len];
int visit[len];
int din[len];
int dout[len];

int task_num;
void bfs(deque<int>& q);

int main()
{
    //freopen("1.txt", "r", stdin);

    int m;
    while (scanf("%d %d", &task_num, &m)!=EOF && task_num)
    {
        memset(g, 0, sizeof(g));
        memset(din, 0, sizeof(din));
        memset(dout, 0, sizeof(dout));
        memset(visit, 0, sizeof(visit));

        for (int i = 0; i < m; i++)
        {
            int n1,n2;
            scanf("%d %d", &n1, &n2);
            g[n1][n2]=1;
            dout[n1]++;
            din[n2]++;
        }

        // �ҵ�����ֻ�г��ȵĽڵ㣬����bfs��
        deque<int> q;
        for (int i = 1; i <= task_num; i++)
        {
            if (din[i] == 0)
            {
                q.push_back(i);
            }
        }

        //bfs
        bfs(q);
    }
    return 0;
}

void bfs(deque<int>& q)
{
    while (!q.empty())
    {
        int node = q.front();
        visit[node] = 1;

        for (int i = 1; i <= task_num; i++)
        {
            if (g[node][i] && !visit[i])
            {
                //�������ڵ�û������ǰ�ã���ô�ͼ��룬����ͼ�һ
                if (din[i]==1)
                    q.push_back(i);
                else
                    din[i]--;
            }
        }

        printf("%d ", node);
        q.pop_front();
    }
    printf("\n");
}