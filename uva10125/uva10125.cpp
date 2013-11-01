// uva10125 hash
// ������1000^4��ʱ�����Ը���һ�·���Ϊa + b = d - c��������1000^2��ʱ�临�Ӷȡ�
// ����hash���洢����a+b��ֵ��
// ע�⣺d����ͬ������һ����

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

#define len 1001
int g_d[len];
struct Node
{
    int x,y;
    int sum;
    Node(int x, int y, int sum)
    {
        this->x = x;
        this->y = y;
        this->sum = sum;
    }
    friend bool operator<(const Node& l, const Node& r)
    {
        return l.sum < r.sum;
    }
};
set<Node> g_set;
bool add_insert(int num);
bool proc(int &s, int num);
int comp(const void* a, const void* b)
{
    return *((int*)b) - *((int*)a);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num) && num)
    {
        g_set.clear();
        for (int i = 1; i <= num; i++)
        {
            scanf("%d", &g_d[i]);
        }

        // ��֤d�����ġ��Ӵ�������
        qsort(g_d+1, num, sizeof(int), comp);

        // �Ȳ�������a+b
        add_insert(num);
        int sum;
        if (proc(sum, num))
        {
            printf("%d\n", sum);
        }
        else
            printf("no solution\n");
    }

    return 0;
}

bool add_insert(int num)
{
    for (int i = 1; i <= num; i++)
    {
        for (int k = i+1; k <= num; k++)
        {
            g_set.insert(Node(g_d[i], g_d[k], g_d[i]+g_d[k]));
        }
    }
    return true;
}

bool proc(int &s, int num)
{
    for (int i = 1; i <= num; i++)
    {
        for (int k = 1; k <= num; k++)
        {
            if (i == k)
                continue;

            int sum = g_d[i]-g_d[k];
            set<Node>::iterator it = g_set.find(Node(g_d[i], g_d[k], sum));
            if (it!=g_set.end() && 
                it->x != g_d[i] && it->x != g_d[k] &&
                it->y != g_d[i] && it->y != g_d[k])
            {
                s = g_d[i];
                return true;
            }
        }
    }
    return false;
}