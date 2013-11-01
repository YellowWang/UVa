// uva10887 hash
// ¾­µäµ¥´Êhash

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

#define len 21

struct Node
{
    char d[len];
    friend bool operator<(const Node& l, const Node& r)
    {
        if (&l == &r)
            return false;
        const char* p1 = l.d;
        const char* p2 = r.d;
        while (*p1 && *p2)
        {
            if (*p1 > *p2)
                return false;
            else if (*p1 < *p2)
                return true;
            p1++;
            p2++;
        }

        if (*p2)
            return true;
        return false;

    }
};

Node g_node1[1500];
Node g_node2[1500];
set<Node> g_set;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    int num;
    scanf("%d", &num);
    for (int cases = 0; cases < num; cases++)
    {
        g_set.clear();
        int lang1num,lang2num;
        scanf("%d %d", &lang1num, &lang2num);
        gets(g_node1[0].d);
        for (int i = 0; i < lang1num; i++)
        {
            gets(g_node1[i].d);
        }
        for (int i = 0; i < lang2num; i++)
        {
            gets(g_node2[i].d);
        }

        int totoal = 0;
        Node newWord;
        for (int i = 0; i < lang1num; i++)
        {
            for (int k = 0; k < lang2num; k++)
            {
                strcpy(newWord.d, g_node1[i].d);
                strcat(newWord.d, g_node2[k].d);
                if (g_set.count(newWord) == 0)
                {
                    totoal++;
                    g_set.insert(newWord);
                }
            }
        }

        printf("Case %d: %d\n", cases+1, totoal);
    }
    return 0;
}