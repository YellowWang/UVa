// uva 439
// æ≠µ‰Õºbfs±È¿˙À„∑®

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 8
int g[len][len];
int bfs(int x1, int y1, int x2, int y2);

int main()
{
    //ifstream cin("1.txt");
    //freopen("1.txt", "r", stdin);

    char s[16],e[16];
    while (scanf("%s %s", s, e)!=EOF)
    {
        memset(g, 0, sizeof(g));
        int x1,y1,x2,y2;
        x1 = s[0]-'a';
        y1 = s[1]-'1';
        x2 = e[0]-'a';
        y2 = e[1]-'1';
        int moves = bfs(x1, y1, x2, y2);
        printf("To get from %s to %s takes %d knight moves.\n", s, e, moves);
    }

    return 0;
}

struct node
{
    int x,y;
    int moves;
};
int bfs(int x1, int y1, int x2, int y2)
{
    deque<node> q;
    node n;
    n.x = x1;
    n.y = y1;
    n.moves = 0;
    g[x1][y1]=1;
    q.push_back(n);

    int dir[] = {-1,-2, -2,-1, -2,1, -1,2, 1,2, 2,1, 2,-1, 1,-2};
    while (!q.empty())
    {
        node& n = q.front();
        if (n.x == x2 && n.y == y2)
            return n.moves;

        // 8 dir
        for (int i = 0; i < len; i++)
        {
            int tx = n.x+dir[i+i];
            int ty = n.y+dir[i+i+1];
            if (tx >= 0 && tx < len && ty >= 0 && ty < len && !g[tx][ty])
            {
                node tn;
                tn.x = tx;
                tn.y = ty;
                tn.moves = n.moves+1;
                g[tx][ty]=1;
                q.push_back(tn);
            }
        }
        q.pop_front();
    }
    return 0;
}