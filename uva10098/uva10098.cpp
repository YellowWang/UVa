// uva10098 枚举排列、重复项
// 排列基础题

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

// 自己实现
void permutation(int idx, int num, int max, int* visit, int* p);
// 书上实现
void permutation(int n, int* visit, int cur);
void permutation_re(int n, char* visit, int cur, char* p);

#define len 11
char str[len];

int comp(const void* a, const void* b)
{
    return *((char*)a) > *((char*)b);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases;
    scanf("%d", &cases);


    char visit[len];
    int p[len];
    int repeat[len];
    while (cases--)
    {
        scanf("%s", str);
        int l = strlen(str);
        qsort(str, l, sizeof(char), comp);
        memset(visit, 0, sizeof(visit));

        permutation_re(l, visit, 0, str);
        printf("\n");
     }
    return 0;
}

void permutation_re(int n, char* visit, int cur, char* p)
{
    int i,j;
    if (cur == n)
    {
        //构造成串一起输出速度快
        visit[n]=0;
        printf("%s\n", visit);
//         for (i = 0; i < n; i++)
//         {
//             printf("%c", visit[i]);
//         }
//         printf("\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (!i || p[i]!=p[i-1])
        {
            int c1=0,c2=0;
            for (j = 0; j < cur; j++)
                if (visit[j] == p[i])
                    c1++;
            for (j = 0; j < n; j++)
                if (p[i] == p[j])
                    c2++;
            if (c1 < c2)
            {
                visit[cur] = p[i];
                permutation_re(n, visit, cur+1, p);
            }
        }
    }
}

void permutation(int n, int* visit, int cur)
{
    int i,j;
    if (cur == n)
    {
        for (i = 0; i < n; i++)
        {
            printf("%d", visit[i]);
        }
        printf("\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        int ok = 1;
        for (j = 0; j < cur; j++)
        {
            if (visit[j] == i)
                ok = 0;
        }
        if (ok)
        {
            visit[cur] = i;
            permutation(n , visit, cur+1);
        }
    }
}

void permutation(int idx, int num, int max, int* visit, int* p)
{
    if (idx == num)
    {
        for (int i = 0; i < num; i++)
        {
            printf("%c", str[p[i]]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < max; i++)
    {
        if (!visit[i])
        {
            p[idx] = i;
            visit[i] = 1;
            permutation(idx+1, num, max, visit, p);
            visit[i] = 0;
        }
    }
}