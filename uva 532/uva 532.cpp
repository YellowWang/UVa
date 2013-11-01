// uva 532
// 3DÕºbfs±È¿˙À„∑®

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 31
char d[len][len][len];
int g[len][len][len];
int bfs(int x1, int y1, int z1, int x2, int y2, int z2);

int main()
{
    //freopen("1.txt", "r", stdin);

    int l,r,c;
    while (scanf("%d %d %d\n", &l,&r,&c)!=EOF)
    {
        if (!l)
            break;

        memset(g, 0, sizeof(g));

        int x1=-1,y1,z1,x2=-1,y2,z2;
        for (int i = 0; i < l; i++)
        {
            for (int k = 0; k < r; k++)
            {
                gets(d[i][k]);
                if (x1 == -1)
                {
                    for (int m = 0; m < len && d[i][k][m]!=0; m++)
                    {
                        if (d[i][k][m] == 'S')
                        {
                            x1 = i;
                            y1 = k;
                            z1 = m;
                            break;
                        }
                    }
                }
                if (x2 == -1)
                {
                    for (int m = 0; m < len && d[i][k][m]!=0; m++)
                    {
                        if (d[i][k][m] == 'E')
                        {
                            x2 = i;
                            y2 = k;
                            z2 = m;
                            break;
                        }
                    }
                }
            }
            getchar();
        }

        d[x1][y1][z1]='.';
        d[x2][y2][z2]='.';
        int moves = bfs(x1,y1,z1,x2,y2,z2);
        if (moves)
            printf("Escaped in %d minute(s).\n", moves);
        else
            printf("Trapped!\n");
    }

    return 0;
}

struct node
{
    int x,y,z;
    int moves;
};
int bfs(int x1, int y1, int z1, int x2, int y2, int z2)
{
    deque<node> q;
    node n;
    n.x = x1;
    n.y = y1;
    n.z = z1;
    n.moves = 0;
    g[x1][y1][z1]=1;
    q.push_back(n);

    int dir[] = {-1,0,0, 1,0,0, 0,-1,0, 0,1,0, 0,0,-1, 0,0,1};
    while (!q.empty())
    {
        node& n = q.front();
        if (n.x == x2 && n.y == y2 && n.z == z2)
            return n.moves;

        // 6 dir
        for (int i = 0; i < 6; i++)
        {
            int tx = n.x+dir[i*3];
            int ty = n.y+dir[i*3+1];
            int tz = n.z+dir[i*3+2];
            if (tx >= 0 && tx < len && ty >= 0 && ty < len && tz >= 0 && tz < len
                && d[tx][ty][tz]=='.' && !g[tx][ty][tz])
            {
                node tn;
                tn.x = tx;
                tn.y = ty;
                tn.z = tz;
                tn.moves = n.moves+1;
                g[tx][ty][tz]=1;
                q.push_back(tn);
            }
        }
        q.pop_front();
    }
    return 0;
}