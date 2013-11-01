// uva 297
// �Ĳ���
// �����汾����ʱ0.008s
/* �Ż���
*    1�����ַ�ת��Ϊint��������ӳ����溯�������ݲ㼶�õ�Ȩֵ��������ӳ����溯������ʱ0.008s��û��
*    2����c++ io��Ϊ c io����ʱ0.008s û��
*    3������������create_tree��������ָ���create_tree2.��ʱ0.008s��û��
*    ԭ�򣺿����ǵݹ�������ģ�ȽϺ�ʱ��������ѭ�������ԡ�������Ϊû���ڼ���Ȩֵ��ʱ��û�м�֦������ͨ������Ǹ����ǰ�ɫ�����涼��Ҷ�ӽڵ㣬����Ҳ�ǰ�ɫ���ͷ���0.
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
        //������һ����
        //cin >> d;
        gets(d);
        if (strlen(d) == 1)
        {
            tree1[0] = convert[*d];
        }
        else
            create_tree2(d, tree1, 0, 0);
            //create_tree(0, tree1, 0, 0);
        //�����ڶ�����
        //cin >> d;
        gets(d);
        if (strlen(d) == 1)
        {
            tree2[0] = convert[*d];
        }
        else
            create_tree2(d, tree2, 0, 0);
            //create_tree(0, tree2, 0, 0);

        //��ϡ��к�ɫ����1����ɫ��0.��������ϣ������ڵĹ�ϵ�����������tree1�
        for (int i = 0; i < len; i++)
        {
            tree1[i] = tree1[i] | tree2[i];
        }

        //���
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