// uva 11234
// 通过逆波兰式的二叉树逆序排列，生成树，然后再层级遍历

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define len 10000

char d[len]; // 输入数据存储

struct node
{
    char  c;
    node* l;
    node* r;
};

node tree[len];//保存树的数据
int  s[len]; // 处理时暂时用的栈

node* out[len]; // 树循环层级遍历时的临时栈
char outc[len]; // 输出结果

int main()
{
    //fstream cin("1.txt");

    int num = 0;
    cin >> num;

    while (num--)
    {
        cin >> d;
        char* head = d;
        char* tail = head;
        while (*tail){tail++;} // 从尾指针逆序处理

        int si = 0; // 临时处理栈索引
        int streei = 0; // 保存树信息索引
        while (--tail && tail != (head-1))
        {
            node n;
            n.c = *tail;
            n.l = n.r = 0;
            tree[streei++] = n; // 数据逐个保存到数组里

            if (si == 0) // 如果是根节点
            {
                s[si++] = streei-1;
                continue;
            }
            else
            {
                int preop = si-1;
                while (tree[s[preop]].c > 'Z') // 查找上一个非叶子节点，也就是操作符
                {
                    preop--;
                }

                if (tree[s[preop]].r == 0) // 如果节点没有右孩子
                {
                    tree[s[preop]].r = &tree[streei-1];
                    s[si++] = streei-1;
                    continue;
                }
                else if (tree[s[preop]].l == 0)// 如果没有左孩子
                {
                    tree[s[preop]].l = &tree[streei-1];

                    if (tree[streei-1].c > 'Z') // 如果是叶子节点，那么把叶子和叶子的父亲都弹出栈 
                    {
                        si = preop;
                    }
                    else // 如果是操作符节点，那么把当前到上个操作符节点弹出，然后把自己放到栈里
                    {
                        si = preop;
                        s[si++] = streei-1;
                    }
                    continue;
                }
            }
        }

        // 输出结果
        int outi1 = 0;
        int outi2 = 0;
        int outci = 0;
        out[outi2++] = &tree[0];
        while (outi1 < outi2) // 层级（广度优先）遍历
        {
            outc[outci++] = out[outi1]->c;
            if (out[outi1]->l)
                out[outi2++] = out[outi1]->l;
            if (out[outi1]->r)
                out[outi2++] = out[outi1]->r;
            outi1++;
        }

        // 反向输出为正确结果
        for (int i = outci-1; i >= 0; i--)
        {
            cout << outc[i];
        }
        cout << endl;
    }

    return 0;
}