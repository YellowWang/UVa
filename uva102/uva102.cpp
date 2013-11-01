// uva102 简单题
// 32位整型加法会溢出，所以用64位就没事了

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;
#define len 3
struct Bin
{
    long long int glass[len];
};
int main()
{
    //freopen("1.txt", "r", stdin);
    Bin b[len];
    while (scanf("%lld %lld %lld", &b[0].glass[0], &b[0].glass[1], &b[0].glass[2])!=EOF)
    {
        scanf("%lld %lld %lld", &b[1].glass[0], &b[1].glass[1], &b[1].glass[2]);
        scanf("%lld %lld %lld", &b[2].glass[0], &b[2].glass[1], &b[2].glass[2]);
        long long int total = 0;
        long long int mini = 0;
        char color[len+1];
        long int sort = 0;
        color[len]=0;
        // BGC 012
        total += b[1].glass[0]+b[2].glass[0];
        total += b[0].glass[1]+b[2].glass[1];
        total += b[0].glass[2]+b[1].glass[2];
        mini = total;
        color[0]='B';color[1]='G';color[2]='C';
        sort = 273;
        // BCG 021
        total = 0;
        total += b[1].glass[0]+b[2].glass[0];
        total += b[0].glass[2]+b[2].glass[2];
        total += b[0].glass[1]+b[1].glass[1];
        if (total < mini)
        {
            mini = total;
            sort = 237;
            color[0]='B';color[1]='C';color[2]='G';
        }
        else if (total == mini)
        {
            if (237 < sort)
            {
                color[0]='B';color[1]='C';color[2]='G';
                sort = 237;
            }
        }
        // BCG 102
        total = 0;
        total += b[1].glass[1]+b[2].glass[1];
        total += b[0].glass[0]+b[2].glass[0];
        total += b[0].glass[2]+b[1].glass[2];
        if (total < mini)
        {
            mini = total;
            color[0]='G';color[1]='B';color[2]='C';
            sort = 723;
        }
        else if (total == mini)
        {
            if (723 < sort)
            {
                color[0]='G';color[1]='B';color[2]='C';
                sort = 723;
            }
        }
        // BCG 120
        total = 0;
        total += b[1].glass[1]+b[2].glass[1];
        total += b[0].glass[2]+b[2].glass[2];
        total += b[0].glass[0]+b[1].glass[0];
        if (total < mini)
        {
            mini = total;
            color[0]='G';color[1]='C';color[2]='B';
            sort = 732;
        }
        else if (total == mini)
        {
            if (732 < sort)
            {
                color[0]='G';color[1]='C';color[2]='B';
                sort = 732;
            }
        }
        // BCG 201
        total = 0;
        total += b[1].glass[2]+b[2].glass[2];
        total += b[0].glass[0]+b[2].glass[0];
        total += b[0].glass[1]+b[1].glass[1];
        if (total < mini)
        {
            mini = total;
            color[0]='C';color[1]='B';color[2]='G';
            sort = 327;
        }
        else if (total == mini)
        {
            if (327 < sort)
            {
                color[0]='C';color[1]='B';color[2]='G';
                sort = 327;
            }
        }
        // BCG 210
        total = 0;
        total += b[1].glass[2]+b[2].glass[2];
        total += b[0].glass[1]+b[2].glass[1];
        total += b[0].glass[0]+b[1].glass[0];
        if (total < mini)
        {
            mini = total;
            color[0]='C';color[1]='G';color[2]='B';
            sort = 372;
        }
        else if (total == mini)
        {
            if (372 < sort)
            {
                color[0]='C';color[1]='G';color[2]='B';
                sort = 372;
            }
        }
        printf("%s %lld\n", color, mini);
    }
    return 0;
}