// uva10716 贪心
// 先判断是否两两一对，奇数个最多有一个
// 然后遍历前半部分，比如（1），取出第i个字符，然后从length-i处往前搜索相同字符的索引j。
// 如果 i==j，那么表明是奇数，需要把i和i+1元素移动一下。然后再从length-i处往前搜索相同字符的索引j，
//        这次i必定不会等于j，因为奇数已经移动走了。
// 如果 i!=j，那么从j移动到length-i-1处。
// 回到（1）。

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

#define len 101

// 从后往前寻找
int find_str_reverse(char* pstr, char c, int end)
{
    for (int i = end-1; i >= 0; i--)
    {
        if (pstr[i] == c)
            return i;
    }
    return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        char letters[256];
        memset(letters, 0, sizeof(letters));

        char str[len];
        scanf("%s", str);
        int str_len = strlen(str);
        // 判断是否两两一对，奇数个最多有一个
        char* p = str;
        while (*p)
        {
            letters[*p]++;
            p++;
        }
        char ji = 0;
        bool valid = true;
        for (int i = 0; i < 256; i++)
        {
            if (letters[i] & 0x01)
            {
                if (ji!=0)
                {
                    valid = false;
                    break;
                }
                ji = i;
            }
        }

        if (!valid)
            printf("Impossible\n");
        else
        {
            int moves = 0;
            // 遍历一半长度
            for (int i = 0; i < str_len>>1; i++)
            {
                // 反向寻找和str[i]相同字符
                int idx = find_str_reverse(str, str[i], str_len-i);
                // 如果找到是自己，即是奇数
                if (i == idx)
                {
                    // 那么向后交换一下
                    char t = str[i];
                    str[i] = str[i+1];
                    str[i+1] = t;
                    moves++;
                    // 此处可以保证i != idx
                    idx = find_str_reverse(str, str[i], str_len-i);
                }
                // 移动到回文对应位置
                for (int k = idx; k < str_len-1-i; k++)
                {
                    char t = str[k];
                    str[k] = str[k+1];
                    str[k+1] = t;
                    moves++;
                }
            }

            printf("%d\n", moves);
        }

    }



    return 0;
}