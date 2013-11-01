// uva 572 
// 基本图dfs遍历
// 不知道输入中间可以有空白，所以不能直接getline。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

#define len 105
char d[len][len];
int g[len][len];
int m,n;
bool dfs(int i, int k);

int main()
{
    //ifstream cin("1.txt");

    while (cin>>m>>n)
    {
        if (!m)
            break;
        memset(d, 0, sizeof(d));
        memset(g, 0, sizeof(g));

        for (int i = 0; i < m; i++)
        {
            for (int k = 0; k < n; k++)
                 cin >> d[i][k];
            //cin.getline(d[i],len); 
        }

        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            for (int k = 0; k < n; k++)
            {
                if (d[i][k] == '@')
                    sum += dfs(i,k)==true;
            }
        }
        cout << sum << endl;
    }
    return 0;
}

bool dfs(int i, int k)
{
    if (i < 0 || k < 0 || i >= m || k >= n || g[i][k] || d[i][k]!='@')
        return false;

    g[i][k] = 1;
    dfs(i-1, k-1);
    dfs(i-1, k);
    dfs(i-1, k+1);
    dfs(i, k+1);
    dfs(i+1, k+1);
    dfs(i+1, k);
    dfs(i+1, k-1);
    dfs(i, k-1);
    return true;
}