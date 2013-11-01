// uva10282 hash
// 用stl的map，没有自己实现hash


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <map>
using namespace std;

struct Node
{
    char word[32];
    friend bool operator<(const Node& lhs, const Node& rhs)
    {
        if (&lhs == &rhs)
            // 相等是false
            return false;

        const char* p1 = lhs.word;
        const char* p2 = rhs.word;
        while (*p1 && *p2)
        {
            if (*p1 > *p2)
                return false;
            else if (*p1 < *p2)
                return true;
            p1++;
            p2++;
        }
        // 相等是false
        return false;
    }
};
map<Node, Node> g_m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    char str[32];
    while (gets(str))
    {
        if (str[0] == 0)
            break;
        Node n1,n2;
        sscanf(str, "%s %s", n1.word, n2.word);
        g_m[n2] = n1;
    }

    Node ans;
    while (gets(ans.word))
    {
        if (g_m.find(ans) != g_m.end())
        {
            printf("%s\n", g_m[ans].word);
        }
        else
            printf("eh\n");
    }
    return 0;
}