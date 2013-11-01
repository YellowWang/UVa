// uva141 hash
// 数据比较多，这里用一个没有优化的stl set版本

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

struct Step
{
    int x,y;
    char op;
};
int g_num;
void proc(deque<Step>& q, int& player_win, int& move);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int N = 0;
    while (scanf("%d", &N) && N)
    {
        int sz = N<<1;
        deque<Step> q;
        Step s;
        for (int i = 0; i < sz; i++)
        {
            scanf("%d %d %c", &s.x, &s.y, &s.op);
            q.push_back(s);
        }
        g_num = N;
        int player_win = 0, move;
        proc(q, player_win, move);
        if (player_win != 2)
            printf("Player %d wins on move %d\n", player_win+1, move);
        else
            printf("Draw\n");
    }

    return 0;
}

#define len 51
struct Node
{
    char d[len][len];
    friend bool operator<(const Node& l, const Node& r)
    {
        if (&l == &r)
            return false;

        for (int i = 1; i <= g_num; i++)
        {
            for (int k = 1; k <= g_num; k++)
            {
                if (l.d[i][k] < r.d[i][k])
                    return true;
                else if (l.d[i][k] > r.d[i][k])
                    return false;
            }
        }
        return false;
    }
};
set<Node> g_set;


void rotate_90(char out[len][len], char in[len][len])
{
    int idx_row = 1;
    int idx_col = 1;
    for (int col = 1; col <= g_num; col++)
    {
        idx_col = 1;
        for (int row = g_num; row >= 1; row--)
        {
            out[idx_row][idx_col++] = in[row][col];
        }
        idx_row++;
    }
}

void rotate_180(char out[len][len], char in[len][len])
{
    int idx_row = 1;
    int idx_col = 1;
    for (int row = g_num; row >= 1; row--)
    {
        idx_col = 1;
        for (int col = g_num; col >= 1; col--)
        {
            out[idx_row][idx_col++] = in[row][col];
        }
        idx_row++;
    }
}
void proc(deque<Step>& q, int& player_win, int& move)
{
    g_set.clear();
    // 空棋盘
    Node chessboard;
    memset(&chessboard, 0, sizeof(chessboard));
    g_set.insert(chessboard);

    int which_player = 0;
    move = 0;
    Node temp;
    while (!q.empty())
    {
        Step& s = q.front();

        // 下一步棋
        if (s.op == '+')
            chessboard.d[s.x][s.y]=1;
        else
            chessboard.d[s.x][s.y]=0;
        move++;

        // 当前是否存在过
        if (g_set.count(chessboard))
        {
            player_win = 1-which_player;
            return;
        }
        // 顺时旋转90度
        rotate_90(temp.d, chessboard.d);
        if (g_set.count(temp))
        {
            player_win = 1-which_player;
            return;
        }

        // 顺时旋转180度
        rotate_180(temp.d, chessboard.d);
        if (g_set.count(temp))
        {
            player_win = 1-which_player;
            return;
        }

        g_set.insert(chessboard);
        which_player = 1-which_player;
        q.pop_front();
    }
    // 平分秋色
    player_win = 2;
    move = 0;
}