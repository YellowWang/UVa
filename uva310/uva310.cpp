// uva310 ��ʽͼ���� dfs
// ��Ŀ������ѵ�

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

typedef long long ll;
#define len 17
set<ll> g_set;
bool bfs(string a, string b, string start, string end);


int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    string a,b,start,end;
    char str[len];
    while (scanf("%s", str)!=EOF)
    {
        a = str;
        scanf("%s", str);
        b = str;
        scanf("%s", str);
        start = str;
        scanf("%s", str);
        end = str;

        if (bfs(a, b, start, end))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}

struct Node
{
    string pro;
    Node(string pro)
    {
        this->pro = pro;
    }
};

bool is_visit(string pro)
{
    ll sum = 0;
    for (int i = 0; i < pro.size(); i++)
    {
        sum *= 10;
        sum += pro[i]-'a'+1;
    }

    if (g_set.count(sum) > 0)
        return true;

    return false;
}

void insert_visit(string pro)
{
    ll sum = 0;
    for (int i = 0; i < pro.size(); i++)
    {
        sum *= 10;
        sum += pro[i]-'a'+1;
    }

    g_set.insert(sum);
}

bool bfs(string a, string b, string start, string end)
{
    g_set.clear();
    int end_size = end.size();
    int start_size = start.size();
    deque<Node> q;
    string allStarts = start;
    // ��ʼ״̬���������
    for (int i = 0; i < start.size(); i++)
    {
        q.push_back(Node(start.substr(i, min(end_size, start_size-i))));
    }


    while (!q.empty())
    {
        Node& node = q.front();

        // �Ƿ���Ŀ��
        if (node.pro.compare(end) == 0)
        {
            return true;
        }

        // �Ƿ����
        if (is_visit(node.pro))
        {
            q.pop_front();
            continue;
        }
        insert_visit(node.pro);

        // ��չ��ÿ���ַ���������չ
        string newpro;
        for (int i = 0; i < node.pro.size(); i++)
        {
            if (node.pro[i] == 'a')
                newpro += a;
            else if (node.pro[i] == 'b')
                newpro += b;
        }

        // ����������������в���������״̬�ַ������ִ�
        int new_size = newpro.size();
        for (int i = 0; i < new_size; i++)
        {
            string sub_new = newpro.substr(i, min(end_size, new_size-i));
            if (!is_visit(sub_new))
                q.push_back(Node(sub_new));
        }

        q.pop_front();
    }
    return false;
}