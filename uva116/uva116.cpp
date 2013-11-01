// uva116 dp
// ע���������һ������dp�����ܱ�֤�ֵ���
/*
������
#\
#-#
#/
 
���ҵ��󣬷�������
/#
#-#
\#
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <queue> 
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;
 
#define INT_MAX 9999999
#define row_len 10
#define col_len 100
int g_d[row_len][col_len];
struct Node
{
    int d;
    int pre;
};
Node g_f[row_len][col_len];
void dp(int rows, int cols); // �����ң�����
void dp2(int rows, int cols); // ���ҵ�����ȷ
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif
 
    int rows, cols;
    while (scanf("%d %d", &rows, &cols)!=EOF)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int k = 0; k < cols; k++)
            {
                scanf("%d", &g_d[i][k]);
            }
        }
 
        dp2(rows, cols);
    }
 
    return 0;
}
 
void dp2(int rows, int cols)
{
    memset(g_f, 0, sizeof(g_f));
 
    // ��ʼ�����ұߵ��ݴ�����
    for (int i = 0; i < rows; i++)
    {
        g_f[i][cols-1].d = g_d[i][cols-1];
        g_f[i][cols-1].pre = -1;
    }
 
    // ������������
    int pre_arr[] = {-1, 0, 1};
    // �д��ҵ���
    for (int k = cols-2; k >= 0; k--)
    {
        // �д��ϵ���
        for (int i = 0; i < rows; i++)
        {
            int d = INT_MAX;
            int min_row;
            // ����ÿ��ȡ���ҵ���С��Ȩֵ
            for (int t = 0; t < 3; t++)
            {
                int pre_row = i+pre_arr[t];
                int pre_col = k+1;
                if (pre_row == -1)
                    pre_row = rows-1;
                else if (pre_row == rows)
                    pre_row = 0;
 
                if (g_f[pre_row][pre_col].d == d)
                {
                    min_row = min(min_row, pre_row);
                }
                if (g_f[pre_row][pre_col].d < d)
                {
                    d = g_f[pre_row][pre_col].d;
                    min_row = pre_row;
                }
            }
            // ����Сֵ�浽�ݴ�������
            g_f[i][k].d = d + g_d[i][k];
            g_f[i][k].pre = min_row;
        }
    }
 
    // ���
    int min_col_last, min_d = INT_MAX;
    for (int i = 0; i < rows; i++)
    {
        if (g_f[i][0].d < min_d)
        {
            min_d = g_f[i][0].d;
            min_col_last = i;
        }
    }
 
    deque<int> q;
    q.push_front(min_col_last);
    int pre_min_row = min_col_last;
    for (int k = 0; k < cols-1; k++)
    {
        pre_min_row = g_f[pre_min_row][k].pre;
        q.push_back(pre_min_row);
    }
 
    printf("%d", q[0]+1);
    for (int i = 1; i < q.size(); i++)
    {
        printf(" %d", q[i]+1);
    }
    printf("\n");
    printf("%d\n", min_d);
}
 
void dp(int rows, int cols)
{
    memset(g_f, 0, sizeof(g_f));
 
    for (int i = 0; i < rows; i++)
    {
        g_f[i][0].d = g_d[i][0];
        g_f[i][0].pre = -1;
    }
 
    int pre_arr[] = {-1, 0, 1};
    for (int k = 1; k < cols; k++)
    {
        for (int i = 0; i < rows; i++)
        {
            int d = INT_MAX;
            int min_row;
            for (int t = 0; t < 3; t++)
            {
                int pre_row = i+pre_arr[t];
                int pre_col = k-1;
                if (pre_row == -1)
                    pre_row = rows-1;
                else if (pre_row == rows)
                    pre_row = 0;
 
                if (g_f[pre_row][pre_col].d == d)
                {
                    min_row = min(min_row, pre_row);
                }
                if (g_f[pre_row][pre_col].d < d)
                {
                    d = g_f[pre_row][pre_col].d;
                    min_row = pre_row;
                }
            }
            g_f[i][k].d = d + g_d[i][k];
            g_f[i][k].pre = min_row;
        }
    }
 
    // ���
    int min_col_last, min_d = INT_MAX;
    for (int i = 0; i < rows; i++)
    {
        if (g_f[i][cols-1].d < min_d)
        {
            min_d = g_f[i][cols-1].d;
            min_col_last = i;
        }
    }
 
    deque<int> q;
    q.push_front(min_col_last);
    int pre_min_row = min_col_last;
    for (int k = cols-1; k > 0; k--)
    {
        pre_min_row = g_f[pre_min_row][k].pre;
        q.push_front(pre_min_row);
    }
 
    printf("%d", q[0]+1);
    for (int i = 1; i < q.size(); i++)
    {
        printf(" %d", q[i]+1);
    }
    printf("\n");
    printf("%d\n", min_d);
}