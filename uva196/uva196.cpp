// uva196 图
// 算法来说比较简单的图递归题
// 但是数字巨大，所以很容易就跪了。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

#define col_len 18279
#define row_len 1001

struct node
{
    short x;
    int y;
};

struct cell
{
    int d;
    vector<node> v;
};

cell d[row_len][col_len];
void parse(vector<node>& v, char* p);
int get(cell& c);

int main()
{
    //freopen("1.txt", "r", stdin);

    int sheets;
    scanf("%d", &sheets);
    while (sheets--)
    {
        // 十分耗时
        //memset(d, 0, sizeof(d));

        int cols,rows;
        scanf("%d %d", &cols, &rows);

        char str[1024];
        cell* pc = &d[0][0];
        for (int i = 0; i < rows; i++)
        {
            pc = &d[i][0];
            for (int k = 0; k < cols; k++)
            {
                scanf("%s", str);
                pc->d = 0;
                pc->v.clear();
                if (str[0] == '=')
                {
                    // 解析
                    parse(pc->v, &str[1]);
                }
                else
                {
                    pc->d = atoi(str);
                }
                ++pc;
            }
        }

        // 输出
        for (int i = 0; i < rows; i++)
        {
            for (int k = 0; k < cols; k++)
            {
                if (k==cols-1)
                    printf("%d", get(d[i][k]));
                else
                    printf("%d ", get(d[i][k]));
            }
            printf("\n");
        }
    }

    return 0;
}

int get(cell& c)
{
    if (c.d)
    {
        return c.d;
    }

    int sz = c.v.size();
    if (!sz)
    {
        return 0;
    }

    int sum=0;
    for (int i = 0; i < sz; i++)
    {
        if (d[c.v[i].x][c.v[i].y].d)
            sum += d[c.v[i].x][c.v[i].y].d;
         else
             sum += get(d[c.v[i].x][c.v[i].y]);
    }
    c.d = sum;
    return sum;
}

void parse(vector<node>& v, char* p)
{
    int state = 0;
    int num = 0;
    node n;
    while (*p)
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            num = num*26+(*p-'A'+1);
            state = 0;
        }
        else if (*p >= '0' && *p <= '9')
        {
            if (state == 0)
            {
                n.y = num-1;
                state = 1;
                num = 0;
            }
            num = num*10+(*p-'0');
        }
        else if (*p == '+' && state == 1)
        {
            n.x = num-1;
            v.push_back(n);
            state = 0;
            num = 0;
        }
        p++;
    }

    if (num > 0);
    {
        n.x = num-1;
        v.push_back(n);
    }

    return;
}