// uva657 图
// 深度遍历问题
// 就是需要两次遍历，第一次找到所有的X，第二次判断相连X。
// 因为没看清题，以为是8方向，所以一直wa。其实是4方向

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define len 51

char g[len][len];
int visit[len][len];

struct node
{
    node(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int x,y;
};
int rows,cols;

void dfs1(int x, int y, vector<node>& v);
bool dfs2(int x, int y);

int main()
{
    //freopen("1.txt", "r", stdin);


    int answer[7];
    int cases = 1;
    while (scanf("%d %d", &cols, &rows) && rows)
    {
        memset(visit, 0, sizeof(visit));
        memset(answer, 0, sizeof(answer));

        for (int i = 0; i < rows; i++)
        {
            scanf("%s", g[i]);
        }

        vector<node> v;
        for (int i = 0; i < rows; i++)
        {
            for (int k = 0; k < cols; k++)
            {
                if (!visit[i][k] &&
                    (g[i][k] == '*' || g[i][k] == 'X'))
                {
                    dfs1(i, k, v);

                    // visit恢复状态
                    for (int t = 0; t < v.size(); t++)
                    {
                        visit[v[t].x][v[t].y] = 0;
                    }

                    // 遍历，找出数字
                    int num = 0;
                    for (int t = 0; t < v.size(); t++)
                    {
                        if (dfs2(v[t].x, v[t].y))
                            num++;
                    }
                    answer[num]++;
                    v.clear();
                }
            }
        }

        // output
        printf("Throw %d\n",cases++);
        vector<int> vAns;
        for (int i = 1; i < 7; i++)
        {
            while (answer[i]--)
            {
                vAns.push_back(i);
                //printf("%d ", i);
            }
        }
        for (int i = 0; i < vAns.size(); i++)
        {
            if (i == 0)
                printf("%d",vAns[i]);
            else
                printf(" %d",vAns[i]);
        }
        printf("\n\n");
    }

    return 0;
}

void dfs1(int x, int y, vector<node>& v)
{
    if (x < 0 || x >= rows ||
        y < 0 || y >= cols ||
        visit[x][y] || g[x][y]=='.')
    {
        return;
    }

    visit[x][y]=1;
    if (g[x][y]=='X')
    {
        v.push_back(node(x,y));
    }

    dfs1(x, y-1, v);

    dfs1(x-1, y, v);

    dfs1(x, y+1, v);

    dfs1(x+1, y, v);

}

bool dfs2(int x, int y)
{
    if (x < 0 || x >= rows ||
        y < 0 || y >= cols || 
        visit[x][y] || g[x][y]=='.')
    {
        return false;
    }

    visit[x][y]=1;

    dfs2(x, y-1);

    dfs2(x-1, y);

    dfs2(x, y+1);

    dfs2(x+1, y);

    return true;
}