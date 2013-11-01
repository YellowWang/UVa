// uva639 ����
// ���Ա�����ע�ⲻһ����һ�����Ӿ���root

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;

#define len 5
int num;
char g_d[len][len];
int visit[len][len];
// �ӵڼ�����ʼ����
int seach_rook(int x, int y, int rook_num);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    while (scanf("%d", &num) && num)
    {
        for (int i = 0; i < num; i++)
        {
            scanf("%s", g_d[i]);
        }

        int rook_num = 0;
        // ÿ�����Ӷ����¼���
        for (int i = 0; i < num; i++)
        {
            for (int k = 0; k < num; k++)
            {
                if (g_d[i][k]!='X')
                {
                    memset(visit, 0, sizeof(visit));
                    rook_num = max(rook_num, seach_rook(i, k, 0));
                }
            }
        }

        printf("%d\n", rook_num);
    }

    return 0;
}

int seach_rook(int x, int y, int rook_num)
{
    int ignore = x*num+y;
    int t = ignore;

    // �ӵڼ�����ʼ����
    for (int i = 0; i < num; i++)
    {
        for (int k = 0; k < num; k++)
        {
            // ����ǰ���
            if (t)
            {
                t--;
                continue;
            }
            if (!visit[i][k] && g_d[i][k]!='X')
            {
                visit[i][k] = 1;

                rook_num++;

                // ��������Ϊ�߹����Ժ����ߣ�
                for (int m = i-1; m >= 0 && g_d[m][k]!='X'; m--)
                    visit[m][k] = 1;
                for (int m = i+1; m < num && g_d[m][k]!='X'; m++)
                    visit[m][k] = 1;
                for (int m = k-1; m >= 0 && g_d[i][m]!='X'; m--)
                    visit[i][m] = 1;
                for (int m = k+1; m < num && g_d[i][m]!='X'; m++)
                    visit[i][m] = 1;

                // �ָ�
                //visit[i][k] = 0;
            }
        }
    }

    // �ٴ�ͷ��ʼ����
    for (int i = 0; i < num; i++)
    {
        for (int k = 0; k < num; k++)
        {
            // ���������˳�
            if (!ignore)
                break;
            ignore--;

            if (!visit[i][k] && g_d[i][k]!='X')
            {
                visit[i][k] = 1;

                rook_num++;

                // ��������Ϊ�߹����Ժ����ߣ�
                for (int m = i-1; m >= 0 && g_d[m][k]!='X'; m--)
                    visit[m][k] = 1;
                for (int m = i+1; m < num && g_d[m][k]!='X'; m++)
                    visit[m][k] = 1;
                for (int m = k-1; m >= 0 && g_d[i][m]!='X'; m--)
                    visit[i][m] = 1;
                for (int m = k+1; m < num && g_d[i][m]!='X'; m++)
                    visit[i][m] = 1;

                // �ָ�
                //visit[i][k] = 0;
            }
        }
        if (!ignore)
            break;
    }

    return rook_num;
}