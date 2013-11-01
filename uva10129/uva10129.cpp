// uva10129 图 环 欧拉回路
// 形成一条链，头结点的入度-出度=1，尾节点的出度-入度=1，中间节点入度和出度必须一样。

#include <stdio.h>
#include <stdlib.h>

#include <memory.h>
#include <deque>

#define word_len 1001
char word[word_len];

#define letter_len 256
int g[letter_len][letter_len];
int din[letter_len]; // 入度
int dout[letter_len];// 出度
// visit 数字代表有几次可以走，每次访问后减一，0代表不能访问。
// 因为相同的单词可以有多个，而且必须全部都得使用
int visit[letter_len];

int dfs(int word_h);
int main()
{
     //freopen("1.txt", "r", stdin);

     int cases;
     scanf("%d", &cases);

    while (cases--)
    {
        memset(g, 0, sizeof(g));
        memset(din, 0, sizeof(din));
        memset(dout, 0, sizeof(dout));
        memset(visit, 0, sizeof(visit));

        int word_num;
        scanf("%d", &word_num);

        for (int i = 0; i < word_num; i++)
        {
            scanf("%s", word);
            int t = strlen(word);
            g[word[0]][word[t-1]]++;
            dout[word[0]]++;
            din[word[t-1]]++;
        }

        // 判断基数
        int odd_start = 0;
        int start = 0;
        int end = 0; // 计算结尾的点，不可重复
        int letter_num = 0; // 字母数量，dfs必须遍历这个数量的字母
        bool error = false;
        for (char c = 'a'; c <= 'z'; c++)
        {
            if (din[c] || dout[c])
            {
                if (dout[c]-din[c] > 0)
                {
                    letter_num += dout[c];
                    visit[c] = dout[c];
                }
                else
                {
                    letter_num += din[c];
                    visit[c] = din[c];
                }

                // 如果是环的话，那么随便选择一个出度大于0的
                if (dout[c])
                    start = c;

                if ((dout[c]-din[c]) == 1)
                {
                    if (odd_start != 0)
                    {
                        error = true;
                        break;
                    }
                    odd_start = c;
                }
                else if ((din[c]-dout[c]) == 1)
                {
                    if (end != 0)
                    {
                        error = true;
                        break;
                    }
                    end = c;
                }
                else
                {
                    if (din[c]-dout[c] != 0)
                    {
                        error = true;
                        break;
                    }
                }
            }
        }

        if (error)
        {
            printf("The door cannot be opened.\n");
            continue;
        }

        //是否遍历了所有字母
        if (letter_num != dfs(odd_start==0?start:odd_start))
        {
            printf("The door cannot be opened.\n");
            continue;
        }

        printf("Ordering is possible.\n");
    }

    return 0;
}

int dfs(int word_h)
{
    visit[word_h]--;

    int num = 1;
    for (char c = 'a'; c <= 'z'; c++)
    {
        if (g[word_h][c] && visit[c] > 0)
        {
            num += dfs(c);
        }
    }
    return num;
}