// uva311 贪心
// 根据size从大到小，在背包从左到右填充即可。
// 矩阵填充矩阵问题，游戏中用于把琐碎小纹理拼成一张大纹理

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

#define len 6
#define pack_len 400
// 不同尺寸的数量
int g_n[len];
// 所有背包
int g_pack[pack_len][len][len];
int parcel_pack(int idx, int pack[len][len]);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    while (scanf("%d %d %d %d %d %d", 
        &g_n[0], &g_n[1], &g_n[2], &g_n[3], &g_n[4], &g_n[5]) && 
        (g_n[0] || g_n[1] || g_n[2] || g_n[3] || g_n[4] || g_n[5]))
    {
        int pack_total_num = 0;
        memset(g_pack, 0, sizeof(int)*len*len*pack_len);
        for (int i = len-1; i >= 0; i--)
        {
            int reqPack = 0;
            while (g_n[i])
            {
                reqPack++;
                g_n[i] = parcel_pack(i, g_pack[reqPack]);
            }
            if (pack_total_num < reqPack)
                pack_total_num = reqPack;
        }

        printf("%d\n", pack_total_num);
    }

    return 0;
}

// 矩形填充
void fill_rect(int start_r, int start_c, int sz, int pack[len][len])
{
    for (int row = start_r; row < start_r+sz; row++)
    {
        for (int col = start_c; col < start_c+sz; col++)
        {
            pack[row][col]=1;
        }
    }
}

// 根据size，填充某一个背包
int parcel_pack(int idx, int pack[len][len])
{
    int left = g_n[idx];
    int sz = idx+1;
    if (!left)
        return 0;

    for (int row = 0; row < len; row++)
    {
        for (int col = 0; col < len; col++)
        {
            if (!pack[row][col] && 
                col + sz - 1 < len && row + sz - 1 < len)
            {
                fill_rect(row, col, sz, pack);
                left--;
                if (!left)
                    return 0;
            }
        }
    }

    return left;
}