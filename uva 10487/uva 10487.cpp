// 算法有错误，带验证
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
using namespace std;

int query_sum_min(int in_query, int* d, int n);
int query_sum_min2(int in_query, int* d, int n);
int cmp(const void* a,const void* b)
{
    return *((int*)(a)) > *((int*)(b));
}

int main()
{
    int input_num = 0;
    int input_data[1000];

    int case_num = 1;
    while (cin >> input_num && input_num)
    {
        memset(input_data, 0, sizeof(input_data));
        for (int i = 0; i < input_num; i++)
        {
            cin >> input_data[i];
        }

        qsort(input_data, input_num, sizeof(int), cmp);

        int input_qnum = 0;
        int input_query = 0;

        cout << "Case " << case_num++ << ":" << endl;
        cin >> input_qnum;
        while (input_qnum--)
        {
            cin >> input_query;
            cout << "Closest sum to " << input_query << " is " 
                << query_sum_min2(input_query, input_data, input_num) << "." << endl;
        }


    }

    return 0;
}

int query_sum_min2(int in_query, int* d, int n)
{
    if (n == 1)
    {
        return d[0];
    }

    int l = 0;
    int u = n-1;
    while (l + 1 < u)
    {
        if (d[l]+d[u] == in_query)
        {
            return in_query;
        }

        if (d[l]+d[u] < in_query)
        {
            if (d[l+1]+d[u] < in_query)
            {
                l++;
            }
            else
            {
                if (abs(in_query-d[l]-d[u-1]) < abs(in_query-d[l+1]-d[u]))
                {
                    u--;
                }
                else
                    l++;
            }
        }
        else
        {
            if (d[l]+d[u-1] > in_query)
            {
                u--;
            }
            else
            {
                if (abs(in_query-d[l]-d[u-1]) < abs(in_query-d[l+1]-d[u]))
                {
                    u--;
                }
                else
                    l++;
            }
        }
    }

    return d[l]+d[u];
}

int query_sum_min(int in_query, int* d, int n)
{
    if (n == 1)
    {
        return d[0];
    }

    int s1 = d[0];
    int s2 = d[1];
    int m = s1+s2;
    int m1 = 0;

    int ui = 0;
    s2 = 0;
    int i = 0;
    for (i = 2; i < n; i++)
    {
        int &t = d[i];
        if (abs(in_query-m) <= abs(in_query-s1-t))
        {
            m1 = m;
            ui = i - 2;
            s2 = d[i-2];
            break;
        }
        else
        {
            m = s1 + t;
        }
    }
    if (i == n)
    {
        ui = i - 2;
        s2 = d[i-2];
    }

    for (i = 1; i < ui; i++)
    {
        if (abs(in_query-m) <= abs(in_query-s2-d[i]))
        {
            if (abs(in_query-m) < abs(in_query-m1))
            {
                return m;
            }
            else
                return m1;
        }
        else
        {
            m = s2 + d[i];
        }
    }

    return m;
}