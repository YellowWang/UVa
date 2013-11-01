// uva 784
// 基本图dfs遍历，主要是题目的例子显示有点悲催，要粘到txt里看就行了

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

#define line_len 30
#define col_len 80

char d[line_len][col_len];
int g[line_len][col_len];

bool dfs(int i, int k);
int m,n;
int main()
{
    //ifstream cin("1.txt");
    //freopen("1.txt", "r", stdin);

    int cases;
    //cin >> cases;
    scanf("%d\n", &cases);
    while (cases--)
    {
        int x = -1,y;
        m=0;
        memset(g, 0, sizeof(g));
        memset(d, 0, sizeof(d));
        for (int i = 0; i < line_len; i++)
        {
            //cin.getline(d[i], col_len);
            gets(d[i]);
            if (d[i][0] == '_')
                break;
            if (x == -1)
                for (int k = 0; k < col_len; k++)
                {
                    if (d[i][k] == '*')
                    {
                        x = i;
                        y = k;
                    }
                }
            ++m;
        }

        d[x][y] = ' ';
        dfs(x,y);
        for (int i = 0; i < m; i++)
        {
            printf("%s\n", d[i]);
        }
        printf("%s\n", d[m]);
    }

    return 0;
}

bool dfs(int i, int k)
{
    if (i < 0 || k < 0 || i >= line_len || k >= col_len || g[i][k] || d[i][k]!=' ')
        return false;

    g[i][k] = 1;
    d[i][k] = '#';
    dfs(i-1, k);
    dfs(i, k+1);
    dfs(i+1, k);
    dfs(i, k-1);
    return true;
}