// uva620 回溯或dp
// 题意理解是难点。空集 => A ;  O => OA ; O不是空集。所以O=>OAB，O必须有值。然后就是回溯，每步有三种行进方式。
 
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
 
#define len 128
char str[len];
int dp(int l, int r);
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int cases;
    scanf("%d", &cases);
 
 
    while (cases--)
    {
        scanf("%s", str);
 
        int ans = dp(0, strlen(str)-1);
        if (ans == 0)
            printf("MUTANT\n");
        else if (ans == 1)
            printf("SIMPLE\n");
        else if (ans == 2)
            printf("FULLY-GROWN\n");
        else if (ans == 3)
            printf("MUTAGENIC\n");
    }
 
    return 0;
}
 
int dp(int l, int r)
{
    int ans = 0;
 
    if (str[l] == 'B' && str[r] == 'A')
    {
        if (dp(l+1, r-1) > 0)
            ans = 3;
    }
 
    if (r-l > 1 && str[r] == 'B' && str[r-1] == 'A')
    {
        if (dp(l, r-2) > 0)
            ans = 2;
    }
 
    if (str[r] == 'A')
    {
        if (l == r)
            return 1;
        if (dp(l, r-1) > 0)
            ans = 1;
    }
 
    return ans;
}