// uva825 dp
// ¼ÇÒäËÑË÷
 
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
 
#define len 20
int block[len][len];
int f[len][len];
int rows,cols;
int dp(int i, int k);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases;
    scanf("%d\n", &cases);
 
    while (cases--)
    {
 
        scanf("%d %d\n", &rows, &cols);
        char str[512];
 
        memset(block, 0, sizeof(block));
 
        for (int i = 0; i < rows; i++)
        {
            gets(str);
            char* tok = strtok(str, " ");
            int no_i = atoi(tok);
            tok = strtok(NULL, " ");
            while (tok)
            {
                block[no_i-1][atoi(tok)-1]=1;
                tok = strtok(NULL, " ");
            }
        }
 
        memset(f, -1, sizeof(f));
        printf("%d\n", dp(0, 0));
        if (cases!=0)
            printf("\n");
    }
 
    return 0;
}
 
int dp(int i, int k)
{
    if (i >= rows || k >= cols)
        return 0;
 
    if (f[i][k] >= 0)
        return f[i][k];
 
    if (block[i][k] == 1)
    {
        f[i][k] = 0;
        return 0;
    }
 
    if (i == rows-1 && k == cols-1)
    {
        f[i][k] = 1;
        return 1;
    }
 
    int sum = 0;
    sum += dp(i+1, k);
    sum += dp(i, k+1);
 
    f[i][k] = sum;
    return sum;
}