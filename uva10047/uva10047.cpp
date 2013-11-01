// uva10047 图
// 比较繁琐的图题，也比较典型。每个节点要保存位置、方向、颜色3类状态。用bfs来获得最短路径。
// 用优先队列，每次从最小的时间扩展。此代码没有用。
// imba的是，结尾case后不能有空白换行。

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
int dir_data[8]={0,-1, -1,0, 0,1, 1,0}; // 分别是左、上、右、下的便宜

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

        // 末尾还不能有换行，必须是case之间有空白行
        if (cases != 1)
        {
            printf("\n"); 
        }
        printf("Case #%d\n",cases++);
        // 开始时是0号颜色，面向北。
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
        // 确保是0号颜色（也是初始颜色）到终点
        if (g[n.x][n.y] == 'T' && n.color == 0)
        {
            return n.sec;
        }
        // move
        q.push_back(node(n.x+dir_data[n.dir*2], n.y+dir_data[n.dir*2+1], (n.color+1)%color_len, n.dir, n.sec+1));
        // change dir
        q.push_back(node(n.x, n.y, n.color, (n.dir+1)%dir_len, n.sec+1));
        // 每次只能走一个状态，所以这句注释掉
        //q.push_back(node(n.x, n.y, n.color, (n.dir+2)%dir_len, n.sec+2));
        q.push_back(node(n.x, n.y, n.color, (n.dir+3)%dir_len, n.sec+1));
        q.pop_front();
    }
    return 0;
}