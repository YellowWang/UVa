// uva 112
// 正常逻辑：先生成树，然后深度遍历树，搜索是否符合的值
/* 优化逻辑：
*    1，因为生成树的过程就是深度遍历的过程，所以变生成变计算累加值，放到节点上。耗时0.164s
*    2，如果找到值了，那么忽略后面的节点，直到树结束。耗时0.148s
*    3，用了getchar来获得字符串，速度飙升。耗时0.044s
*/        
// 最快的人耗时0.01s
// 注意：可能为0或者负数

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

struct node 
{
    int d;//节点权重
    bool haveleft;
    node* f;//父节点
    node* l;//左孩子
    node* r;//右孩子
};

#define len 1000
node tree[len];
int treei;
node* s[len];// 栈
int si;

int main()
{
    //ifstream cin("1.txt");

    char c;
    char token[16];

    int match = 0;
    while (cin >> match)
    {
        treei = 0;
        si = 0;
        int token_idx = 0;
        bool bmatch = false;
        int ignore = 0;
        bool bIgnore = false;
        while (c = getchar()) // 以前是cin >> c，速度有点慢，就改为getchar()
        {
            //如果已经找到，那么忽略后面的字符
             if (bIgnore)
            {
                if (c == '(')
                {
                    ++ignore;
                }
                else if (c == ')')
                {
                    --ignore;
                }
                if (!ignore)
                {
                    bIgnore = false;
                    break;
                }
                token_idx = 0;
                continue;
             }

            //分解，注意负号
            if ((c >= '0' && c <= '9') || (c == '-') || (c == '+'))
            {
                if (token_idx > 0 && token[token_idx-1] == '(')
                    token_idx = 0;
                token[token_idx++] = c;
                continue;
            }
            else if (c == '(')
            {
                int num = 0;
                //如果token有值，那么转为整型。
                if (token_idx > 0)
                {
                    token[token_idx] = 0;
                    num = atoi(token);
                    token_idx = 0;

                    // 建立新节点
                    s[si] = &tree[treei++];
                    s[si]->d = num;
                    s[si]->haveleft = false;
                    s[si]->l = s[si]->r = 0;
                    //如果不是根节点，那么设置父子关系
                    if (si)
                    {
                        s[si]->f = s[si-1];
                        s[si]->d += s[si-1]->d; // 把遍历累加树的权值工作，放到建立树的时候来做。每个节点累加父亲的权值。
                        if (s[si-1]->haveleft)
                            s[si-1]->r = s[si];
                        else
                        {
                            s[si-1]->l = s[si];
                            s[si-1]->haveleft = true;
                        }
                    }
                    else
                        s[si]->f = 0;

                    si++;
                }

                token[token_idx++] = c;//'('
            }
            else if (c == ')')
            {
                // process
                if (token[token_idx-1] == '(')
                {
                    token_idx = 0;
                    // 把空树过滤过去
                    if (si > 0 && !s[si-1]->haveleft)
                        s[si-1]->haveleft = true;
                }
                // 回溯
                else
                {
                    // 匹配，并且是叶子节点
                    if (s[si-1]->d == match &&
                        s[si-1]->l == s[si-1]->r &&
                        s[si-1]->l == 0)
                    {
                        bmatch = true;
                         bIgnore = true;
                         ignore = si-1;
                         continue;
                    }
                    si--;
                }

                //如果上个树完成，那么建立新树
                if (si == 0)
                {
                    break;
                }
            }
        }

        if (bmatch)
        {
            cout << "yes" << endl;
        }
        else
            cout << "no" << endl;
    }


    return 0;
}