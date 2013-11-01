// uva704 ˫��bfs
// ˫���8�Σ�������ĿҪ�󣬲���С�ڵ���16��

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

#define len 24
int g_final_state[len];
deque<int> g_qMove;
deque<int> g_qMove_reverse;
//����bfs
bool bfs(int first_state[len]);
//����bfs�����浱ǰ״̬�Ͳ��衣
bool bfs_reverse(int first_state[len]);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    freopen("2.txt","w",stdout);
#endif

    set<int> ss;
    ss.insert(99);
    ss.count(99);
    ss.count(88);
    ss.count(100);
    // ����״̬
    int final_state[len] = {
        0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1
    };
    memcpy(g_final_state, final_state, sizeof(g_final_state));
    // �Ƚ��з����bfs����Ϊ�ǲ���ġ�
    bfs_reverse(g_final_state);
    // ����תΪ�������ת����
    int rot_reverse[5]={0,3,4,1,2};

    int data[len];
    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        for (int i = 0; i < len; i++)
        {
            scanf("%d", &data[i]);
        }

        if (bfs(data))
        {
            if (g_qMove.size() > 0 || g_qMove_reverse.size() > 0)
            {
                for (int i = 0; i < g_qMove.size(); i++)
                {
                    printf("%d", g_qMove[i]);
                }
                // ��������Ҫ�������
                for (int i = g_qMove_reverse.size()-1; i >= 0; i--)
                {
                    printf("%d", rot_reverse[g_qMove_reverse[i]]);
                }
                printf("\n");
            }
            else
                printf("PUZZLE ALREADY SOLVED\n");
        }
        else
        {
            printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
        }
    }

    return 0;
}


struct Node
{
    int state[len]; // ״̬
    long long sum1,sum2; // �м�ֵ
    deque<int> qMove; // ����
    // stl set��Ҫ
    friend bool operator<(const Node& lhs, const Node& rhs)
    {
        if (&lhs == &rhs)
            return false;
        if (lhs.sum1 < rhs.sum1)
        {
            return true;
        }
        else if (lhs.sum1 == rhs.sum1 && lhs.sum2 < rhs.sum2)
        {
            return true;
        }
        return false;
    }
    // ����Ƚ�
    void calc()
    {
        sum1 = 0;
        sum2 = 0;
        for (int i = 0; i < 12; i++)
        {
            sum1 += state[i]<<(4*i);
            sum2 += state[i+12]<<(4*i);
        }
    }
    Node(){qMove.clear();}
    Node(int state[len], deque<int> qMove)
    {
        this->qMove = qMove;
        for (int i = 0; i < len; i++)
            this->state[i] = state[i];
        calc();
    }
};
set<Node> g_set;
set<Node> g_set_reverse;

// ��ת����
void rotate(int rot_type, int in_state[len], int out_state[len])
{
    int half_len = len>>1;
    if (rot_type == 1)
    {
        memcpy(out_state+2, in_state, sizeof(int)*(half_len-2));
        memcpy(out_state, in_state+(half_len-2), sizeof(int)*2);
        memcpy(out_state+len-3, out_state+(half_len-3), sizeof(int)*3);
    }
    else if (rot_type == 2)
    {
        memcpy(out_state+half_len, in_state+half_len+2, sizeof(int)*(half_len-2));
        memcpy(out_state+len-2, in_state+half_len, sizeof(int)*2);
        memcpy(out_state+(half_len-3), out_state+len-3, sizeof(int)*3);
    }
    else if (rot_type == 3)
    {
        memcpy(out_state, in_state+2, sizeof(int)*(half_len-2));
        memcpy(out_state+half_len-2, in_state, sizeof(int)*2);
        memcpy(out_state+len-3, out_state+(half_len-3), sizeof(int)*3);
    }
    else
    {
        memcpy(out_state+half_len+2, in_state+half_len, sizeof(int)*(half_len-2));
        memcpy(out_state+half_len, in_state+len-2, sizeof(int)*2);
        memcpy(out_state+(half_len-3), out_state+len-3, sizeof(int)*3);
    }
}

bool bfs(int first_state[len])
{
    g_set.clear();
    g_qMove.clear();
    deque<Node> q;
    q.push_back(Node(first_state, g_qMove));

    while (!q.empty())
    {
        Node& node = q.front();

        // �Ƿ����
        if (g_set.count(node))
        {
            q.pop_front();
            continue;
        }
        g_set.insert(node);

        // �Ƿ��յ�
        if (memcmp(g_final_state, node.state, len*4) == 0)
        {
            g_qMove = node.qMove;
            return true;
        }

        // �������Ƿ���
        set<Node>::iterator it = g_set_reverse.find(node);
        if (it != g_set_reverse.end())
        {
            g_qMove = node.qMove;
            g_qMove_reverse = (*it).qMove;
            return true;
        }

        // �Ƿ񵽴�8��
        if (node.qMove.size() >= 8)
        { 
            q.pop_front();
            continue;
        }

        // �����������
        Node new_node;
        for (int i = 1; i <= 4; i++)
        {
            new_node = node;
            new_node.qMove.push_back(i);
            rotate(i, node.state, new_node.state);
            new_node.calc();
            if (!g_set.count(new_node))
                q.push_back(new_node);
        }

        q.pop_front();
    }

    return false;
}

bool bfs_reverse(int first_state[len])
{
    g_set_reverse.clear();
    g_qMove_reverse.clear();
    deque<Node> q;
    q.push_back(Node(first_state, g_qMove_reverse));

    while (!q.empty())
    {
        Node& node = q.front();
        int qsize = q.size();

        // �Ƿ����
        if (g_set_reverse.count(node))
        {
            q.pop_front();
            continue;
        }
        g_set_reverse.insert(node);

        // �Ƿ񵽴�8��
        if (node.qMove.size() >= 8)
        {
            q.pop_front();
            continue;
        }

        // �����������
        Node new_node;
        for (int i = 1; i <= 4; i++)
        {
            new_node = node;
            new_node.qMove.push_back(i);
            rotate(i, node.state, new_node.state);
            new_node.calc();
            if (!g_set_reverse.count(new_node))
                q.push_back(new_node);
        }

        q.pop_front();
    }
    return true;
}