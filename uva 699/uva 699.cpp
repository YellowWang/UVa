// uva 699
// 题的输入有特点，不是一行一个树，是连续不断的输入，直到树建立好
// 没有优化 耗时0.152s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

struct node
{
    int d;
    node* l;
    node* r;
};
node* root;
int  node_num;

ifstream cin1;
node* create_btree(int n);
void falling(node* pn, int i, int* fall);
void remove_tree(node* pn);
int main()
{
    //cin1.open("1.txt");

    int n = 0;
    int cases = 0;
    while (cin >> n && n != -1)
    {
        cases++;

        node_num = 0;
        root = create_btree(n);

        int max = node_num*2+1;
        int *fall = new int[max];
        memset(fall, 0, sizeof(int)*max);
        falling(root, node_num+1, fall);
        remove_tree(root);

        cout << "Case " << cases << ":" << endl;
        bool first = true;
        for (int i = 0; i < max; i++)
        {
            if (fall[i])
            {
                if (first)
                {
                    cout << fall[i];
                    first = false;
                }
                else
                    cout << " " << fall[i];
            }
        }
        delete []fall;
        cout << endl << endl;
    }

    //cin1.close();
    return 0;
}

node* create_btree(int n)
{
    node* p = new node;
    p->d = n;
    p->l = p->r = 0;
    ++node_num;

    cin >> n;
    if (n != -1)
        p->l = create_btree(n);
    cin >> n;
    if (n != -1)
        p->r = create_btree(n);
    return p;
}

void falling(node* pn, int i, int* fall)
{
    fall[i] += pn->d;
    if (pn->l)
    {
        falling(pn->l, i-1, fall);
    }
    if (pn->r)
    {
        falling(pn->r, i+1, fall);
    }
    return;
}

void remove_tree(node* pn)
{
    if (pn->l)
    {
        remove_tree(pn->l);
    }
    if (pn->r)
    {
        remove_tree(pn->r);
    }
    delete pn;
}