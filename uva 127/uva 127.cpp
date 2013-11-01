// uva 127
// 优化方案：转换函数调用开销取消；递归改为循环；栈改为自己实现

#include <fstream>
#include <iostream>
#include <memory.h>
#include <stack>
using namespace std;

struct node 
{
    int num;
    int color;
};

struct s_node
{
    stack<node> sn; // 链表每个节点是一个栈，用来堆叠牌
    s_node* pre;
    s_node* next;
};

s_node* head; // 双向链表

int g_curIdx = 0;
// 将数字转化为阿拉伯数字，例如：A -> 1  J -> 10
int convert_num(char c);
// 重排哪个节点，看看优先向前第3个，然后是向前第1个。移动结束后，递归调用当前位置向后一个位置的节点
void pile(s_node* sn);

int main()
{
//     char s[][3] = {"A5", "22", "33", "24", "25"};
//       int num = 5;

//     char s[][3] = {
//         "QD", "AD", "8H", "5S", "3H", "5H", "TC", "4D", "JH", "KS", "6H", "8S", "JS",
//         "AC", "AS", "8D", "2H", "QS", "TS", "3S", "AH", "4H", "TH", "TD", "3C", "6S",
//         "8C", "7D", "4C", "4S", "7S", "9H", "7C", "5D", "2S", "KD", "2D", "QH", "JD",
//         "6D", "9D", "JC", "2C", "KH", "3D", "QC", "6C", "9S", "KC", "7H", "9C", "5C"
//     };
//      int num = 52;

    // 测试用文件
    //ifstream cin("1.txt");

    char s[53][3];
    int  num = 52;

    while (true)
    {
        // head，用来判断是否为结束符，并且创建链表头
        cin >> s[0];
        if (s[0][0] == '#')
        {
            break;
        }
        node n;
        n.num = convert_num(s[0][0]);
        n.color = (int)s[0][1];
        head = new s_node;
        head->sn.push(n);
        head->pre = NULL;
        head->next = NULL;
        s_node* pre = head;

        // 每次插入一个节点，就进行一次判断
        for (int i = 1; i < num; i++)
        {
            cin >> s[i];
            s_node* sn = new s_node;
            node n;
            n.num = convert_num(s[i][0]);
            n.color = (int)s[i][1];
            sn->sn.push(n);
            sn->pre = pre;
            pre->next = sn;
            sn->next = NULL;

            pile(sn);

            s_node* next = head;
            while (next->next)
            {
                next = next->next;
            }
            pre = next;
        }

        // 根据链表，计算最后堆叠结果
        int piles_num = 0;
        s_node* ph = head;
        int a[52];
        memset(a, 0, sizeof(a));
        int a_i = 0;
        while (ph)
        {
            if (ph->sn.size())
            {
                piles_num++;
                a[a_i++] = ph->sn.size();
            }
            else
                break;
            s_node* t = ph;
            ph = ph->next;
            delete t; // 释放内存
        }

        // 输出结果
        if (piles_num == 1)
        {
            cout << piles_num << " pile remaining:";
        }
        else
            cout << piles_num << " piles remaining:";
        for (int i = 0; i < piles_num; i++)
        {
            cout << " " << a[i];
        }
        cout << endl;
    }


    return 0;
}

int convert_num(char c)
{
    if (c == 'A')
    {
        return 1;
    }
    else if (c >= '2' && c <= '9')
    {
        return c-'0';
    }
    else if (c == 'T')
    {
        return 10;
    }
    else if (c == 'J')
    {
        return 11;
    }
    else if (c == 'Q')
    {
        return 12;
    }
    else if (c == 'K')
    {
        return 13;
    }
}

void pile(s_node* sn)
{
    if (!sn)
    {
        return;
    }

    s_node* cursn = sn;
    while (true)
    {
        node& cur = cursn->sn.top();
        if (cursn->pre && cursn->pre->pre && cursn->pre->pre->pre)
        {
            node& n = cursn->pre->pre->pre->sn.top();
            if (n.num == cur.num || n.color == cur.color)
            {
                cursn->pre->pre->pre->sn.push(cur);
                cursn->sn.pop();
                s_node* tsn = cursn;
                cursn = cursn->pre->pre->pre;
                if (tsn->sn.size() == 0)
                {
                    tsn->pre->next = tsn->next;
                    if (tsn->next)
                        tsn->next->pre = tsn->pre;
                    delete tsn;
                }
                continue;
            }
        }
        if (cursn->pre)
        {
            node& n = cursn->pre->sn.top();
            if (n.num == cur.num || n.color == cur.color)
            {
                cursn->pre->sn.push(cur);
                cursn->sn.pop();
                s_node* tsn = cursn;
                cursn = cursn->pre;
                if (tsn->sn.size() == 0)
                {
                    tsn->pre->next = tsn->next;
                    if (tsn->next)
                        tsn->next->pre = tsn->pre;
                    delete tsn;
                }
                continue;
            }
        }
        break;
    }

    if (cursn->next)
    {
        pile(cursn->next);
    }


    return;
}