// uva10129 ͼ �� ŷ����·
// �γ�һ������ͷ�������-����=1��β�ڵ�ĳ���-���=1���м�ڵ���Ⱥͳ��ȱ���һ����

#include <stdio.h>
#include <stdlib.h>

#include <memory.h>
#include <deque>

#define word_len 1001
char word[word_len];

#define letter_len 256
int g[letter_len][letter_len];
int din[letter_len]; // ���
int dout[letter_len];// ����
// visit ���ִ����м��ο����ߣ�ÿ�η��ʺ��һ��0�����ܷ��ʡ�
// ��Ϊ��ͬ�ĵ��ʿ����ж�������ұ���ȫ������ʹ��
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

        // �жϻ���
        int odd_start = 0;
        int start = 0;
        int end = 0; // �����β�ĵ㣬�����ظ�
        int letter_num = 0; // ��ĸ������dfs������������������ĸ
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

                // ����ǻ��Ļ�����ô���ѡ��һ�����ȴ���0��
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

        //�Ƿ������������ĸ
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