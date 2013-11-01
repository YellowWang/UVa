// uva10047 ͼ
// �ȽϷ�����ͼ�⣬Ҳ�Ƚϵ��͡�ÿ���ڵ�Ҫ����λ�á�������ɫ3��״̬����bfs��������·����
// �����ȶ��У�ÿ�δ���С��ʱ����չ���˴���û���á�
// imba���ǣ���βcase�����пհ׻��С�

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define len 27
#define color_len 5
#define dir_len 4

char g[len][len];
int visit[len][len][color_len][dir_len];
int rows,cols;
int dir_data[8]={0,-1, -1,0, 0,1, 1,0}; // �ֱ������ϡ��ҡ��µı���

int bfs(int x, int y, int color, int dir, int sec);
int main()
{
    //freopen("1.txt", "r", stdin);
    int cases = 1;
    while (scanf("%d %d", &rows, &cols) && rows)
    {
        memset(visit, 0, sizeof(visit));

        int x=-1,y=0;
        for (int i = 0; i < rows; i++)
        {
            scanf("%s", g[i]);
            if (x == -1)
                for (int k = 0; k < cols; k++)
                {
                    if (g[i][k] == 'S')
                    {
                        x = i;
                        y = k;
                    }
                }
        }

        // ĩβ�������л��У�������case֮���пհ���
        if (cases != 1)
        {
            printf("\n"); 
        }
        printf("Case #%d\n",cases++);
        // ��ʼʱ��0����ɫ�����򱱡�
        int sec = bfs(x, y, 0, 1, 0);
        if (sec)
        {
            printf("minimum time = %d sec\n", sec);
        }
        else
            printf("destination not reachable\n");

    }
    return 0;
}
struct node 
{
    int x,y;
    int color;
    int dir;
    int sec;
    node(int x,int y,int color,int dir,int sec)
    {
        this->x = x;
        this->y = y;
        this->color = color;
        this->dir = dir;
        this->sec = sec;
    }
};

int bfs(int x, int y, int color, int dir, int sec)
{
    deque<node> q;
    q.push_back(node(x,y,color,dir,sec));
    while (!q.empty())
    {
        node& n = q.front();
        if (n.x < 0 || n.x >= rows ||
            n.y < 0 || n.y >= cols ||
            visit[n.x][n.y][n.color][n.dir] ||
            g[n.x][n.y] == '#')
        {
            q.pop_front();
            continue;
        }
        visit[n.x][n.y][n.color][n.dir] = 1;
        // ȷ����0����ɫ��Ҳ�ǳ�ʼ��ɫ�����յ�
        if (g[n.x][n.y] == 'T' && n.color == 0)
        {
            return n.sec;
        }
        // move
        q.push_back(node(n.x+dir_data[n.dir*2], n.y+dir_data[n.dir*2+1], (n.color+1)%color_len, n.dir, n.sec+1));
        // change dir
        q.push_back(node(n.x, n.y, n.color, (n.dir+1)%dir_len, n.sec+1));
        // ÿ��ֻ����һ��״̬���������ע�͵�
        //q.push_back(node(n.x, n.y, n.color, (n.dir+2)%dir_len, n.sec+2));
        q.push_back(node(n.x, n.y, n.color, (n.dir+3)%dir_len, n.sec+1));
        q.pop_front();
    }
    return 0;
}