// uva 297
// 四叉树
// 基础版本，耗时0.008s
/* 优化：
*    1，把字符转换为int，用数组映射代替函数；根据层级得到权值，用数组映射代替函数；耗时0.008s，没变
*    2，将c++ io换为 c io。耗时0.008s 没变
*    3，将用索引的create_tree，换成用指针的create_tree2.耗时0.008s，没变
*    原因：可能是递归的整体规模比较耗时。可以用循环来尝试。或者因为没有在计算权值的时候，没有剪枝，可以通过如果是父亲是白色，下面都是叶子节点，并且也是白色，就返回0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define len 1400

int tree1[len];
int tree2[len];

char d[len];

int getnum[6];
int convert[256];
//int convert(char c);
int calc(int i, int layer);
int create_tree(int i, int* tree, int treei, int layer);
char* create_tree2(char* p, int* tree, int treei, int layer);
int main()
{
    //ifstream cin("1.txt");

    getnum[0] = 1024;
    getnum[1] = 256;
    getnum[2] = 64;
    getnum[3] = 16;
    getnum[4] = 4;
    getnum[5] = 1;

    memset(convert, 0, sizeof(convert));
    convert['f'] = 1;

    gets(d);
    int input_n = atoi(d);
    //cin >> input_n;
    //scanf("%d", &input_n);
    while (input_n--)
    {
        memset(tree1, 0, sizeof(tree1));
        memset(tree2, 0, sizeof(tree2));
        //建立第一个树
        //cin >> d;
        gets(d);
        if (strlen(d) == 1)
        {
            tree1[0] = convert[*d];
        }
        else
            create_tree2(d, tree1, 0, 0);
            //create_tree(0, tree1, 0, 0);
        //建立第二个树
        //cin >> d;
        gets(d);
        if (strlen(d) == 1)
        {
            tree2[0] = convert[*d];
        }
        else
            create_tree2(d, tree2, 0, 0);
            //create_tree(0, tree2, 0, 0);

        //组合。有黑色的是1，白色的0.两个数结合，就是于的关系。结果保存在tree1里。
        for (int i = 0; i < len; i++)
        {
            tree1[i] = tree1[i] | tree2[i];
        }

        //结果
        int total = calc(0, 0);
        printf("There are %d black pixels.\n", total);
        //cout << "There are " << total << " black pixels." << endl;

    }

    return 0;
}

// int convert(char c)
// {
//     if (c == 'e')
//         return 0;
//     if (c == 'f')
//         return 1;
// 
//     return 0;
// }

// int getnum(int layer)
// {
//     switch (layer)
//     {
//     case 0:
//         return 1024;
//     case 1:
//         return 256;
//     case 2:
//         return 64;
//     case 3:
//         return 16;
//     case 4:
//         return 4;
//     case 5:
//         return 1;
//     }
// 
//     return 0;
// }

int calc(int i, int layer)
{
    if (tree1[i] == 1)
    {
        return getnum[layer];
    }
    if (layer == 5)
    {
        if (tree1[i])
        {
            return 1;
        }
        return 0;
    }


    int sum = 0;
    int idx = i*4;
    sum += calc(idx+1, layer+1);
    sum += calc(idx+2, layer+1);
    sum += calc(idx+3, layer+1);
    sum += calc(idx+4, layer+1);
    return sum;
}

char* create_tree2(char* p, int* tree, int treei, int layer)
{
    if (*p == 0)
    {
        return p;
    }

    tree[treei] = convert[*p++];

    int idx =  treei*4;
    if (*p == 'p')
    {
        p = create_tree2(p, tree,idx+1, layer+1);
    }
    else
        tree[idx+1] = convert[*p++];

    if (*p == 'p')
    {
        p = create_tree2(p, tree, idx+2, layer+1);
    }
    else
        tree[idx+2] = convert[*p++];

    if (*p == 'p')
    {
        p = create_tree2(p, tree, idx+3, layer+1);
    }
    else
        tree[idx+3] = convert[*p++];

    if (*p == 'p')
    {
        p = create_tree2(p, tree, idx+4, layer+1);
    }
    else
        tree[idx+4] = convert[*p++];

    return p;
}

int create_tree(int i, int* tree, int treei, int layer)
{
    if (d[i] == 0)
    {
        return i;
    }

    tree[treei] = convert[d[i]];
    i++;

    if (d[i] == 'p')
    {
        i = create_tree(i, tree, treei*4+1, layer+1);
    }
    else
        tree[treei*4+1] = convert[d[i++]];

    if (d[i] == 'p')
    {
        i = create_tree(i, tree, treei*4+2, layer+1);
    }
    else
        tree[treei*4+2] = convert[d[i++]];

    if (d[i] == 'p')
    {
        i = create_tree(i, tree, treei*4+3, layer+1);
    }
    else
        tree[treei*4+3] = convert[d[i++]];

    if (d[i] == 'p')
    {
        i = create_tree(i, tree, treei*4+4, layer+1);
    }
    else
        tree[treei*4+4] = convert[d[i++]];

    return i;
}