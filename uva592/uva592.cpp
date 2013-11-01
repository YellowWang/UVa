// uva592.
// 全排列，3个种族和白天黑夜
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;
 
struct node
{
    int he;
    int is;
    int what;
};
 
struct person
{
    int who;
    deque<node> q;
};
 
deque<person> g_per;
int mPerindx[26];
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
 
    int cases = 1;
    int statments;
    while (scanf("%d", &statments) && statments)
    {
        //clear
        g_per.clear();
        memset(mPerindx, -1, sizeof(mPerindx));
 
        char str[16];
        while (statments--)
        {
            person per;
            node n;
            char who;
            char he[3];
            char is[16];
            scanf("%c: %s %s", &who, &he, &is);
            per.who = who-'A';
            if (he[0] == 'I' && he[1] == 't')
            {
                n.he = -1;
            }
            else
                n.he = he[0]-'A';
            n.is = 1;
            scanf("%s", is);
            if (is[0] == 'n')
            {
                n.is = 0;
                scanf("%s", is);
            }
            if (is[0] == 'd' && is[1] == 'i')
                n.what = 1;
            else if (is[0] == 'h')
                n.what = 2;
            else if (is[0] == 'e')
                n.what = 4;
            else if (is[0] == 'l')
                n.what = 8;
            else if (is[0] == 'd' && is[0] == '')
                n.what = 8;
 
            mPerindx[per.who] = g_per.size();
            per.q.push_back(n);
            g_per.push_back(per);
        }
 
 
    }
 
    return 0;
}
 
bool permutation_all(int cur, int num, int* arr)
{
    if (cur == max)
    {
        // 处理
        for (int i = 0; i < g_per.size(); i++)
        {
            deque<node> &q = g_per[i].q;
            for (int i = 0; i < q.size(); i++)
            {
                if (q[i].he != -1)
                {
                    int idx = mPerindx[q[i].he];
                    if (idx == -1)
                        return false;
                    if ((arr[idx] & q[i].what) != q[i].is)
                        return false;
                }
            }
        }
        return true;
    }
 
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            arr[i] = 1;
        else if (i == 1)
            arr[i] = 2;
        else if (i == 3)
            arr[i] = 4;
        permutation_all(cur+1, num, arr);
    }
}