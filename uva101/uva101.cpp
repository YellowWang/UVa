// uva101 堆栈简单题
// 就是题目意思比较难理解。。
// 用stl的挺方便，比自己用指针来的便捷很多
/* 题目简单翻译
*  move a onto b a和b的之后的所有数必须还原到初始位置
*  move a over b a之后的要还原，然后放到b的队尾
*  pile a onto b b之后的要还原，a和a之后的一起放到b后面，a后的序列保持不变
*  pile a over b a和a之后的一起放到b后面，a后的序列保持不变
*  如果在一个pile的，就不做操作
*  然后打印的时候要注意
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;
#define len 25

int data[len];
deque<int> pile[len];

void pop(int d);
void pop(int d, vector<int>& v);
void push(int d, vector<int>& v);

int main()
{
    //freopen("1.txt", "r", stdin);

    int num;
    scanf("%d", &num);
    char cmd1[16];
    int n1,n2;
    char cmd2[16];

    memset(data, 0, sizeof(data));
    // init state
    for (int i = 0; i < num; i++)
    {
        data[i] = i;
        pile[i].push_back(i);
    }
    while (scanf("%s", cmd1) && cmd1[0]!='q')
    {

        scanf("%d %s %d", &n1, cmd2, &n2);
        if (data[n1] == data[n2] ||
            n1 >= num || n2 >= num)
        {
            continue;
        }
        // move onto
        if (cmd1[0] == 'm' && cmd2[1] == 'n')
        {
            pop(n1);
            pop(n2);
            pile[data[n1]].pop_back();
            pile[data[n2]].push_back(n1);
            data[n1] = data[n2];
        }
        // move over
        else if (cmd1[0] == 'm' && cmd2[1] == 'v')
        {
            pop(n1);
            pile[data[n1]].pop_back();
            pile[data[n2]].push_back(n1);
            data[n1] = data[n2];
        }
        // pile onto
        else if (cmd1[0] == 'p' && cmd2[1] == 'n')
        {
            vector<int> v;
            pop(n1, v);
            pop(n2);
            push(n2, v);
        }
        // pile over
        else if (cmd1[0] == 'p' && cmd2[1] == 'v')
        {
            vector<int> v;
            pop(n1, v);
            push(n2, v);
        }
    }

    // output
    for (int i = 0; i < num; i++)
    {
        printf("%d:", i);
        deque<int>& q = pile[i];
        if (!q.empty())
            printf(" ");

        while (!q.empty())
        {
            printf("%d", q.front());
            q.pop_front();
            if (!q.empty())
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

void return_init(int d)
{
    data[d] = d;
    pile[d].push_back(d);
}

void pop(int d)
{
    int idx = data[d];
    int t = pile[idx].back();
    while (t != d)
    {
        return_init(t);
        pile[idx].pop_back();
        t = pile[idx].back();
    }
    return;
}

void pop(int d, vector<int>& v)
{
    int idx = data[d];
    int t = pile[idx].back();
    while (t != d)
    {
        v.push_back(t);
        pile[idx].pop_back();
        t = pile[idx].back();
    }
    v.push_back(d);
    pile[idx].pop_back();
    return;
}

void push(int d, vector<int>& v)
{
    int idx = data[d];
    for (int i = v.size()-1; i >= 0; i--)
    {
        data[v[i]] = data[d];
        pile[idx].push_back(v[i]);
    }
}