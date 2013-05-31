// uva10954 贪心
// 优先队列，每次加最小的两个

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

struct comp{  
    bool operator()(int x, int y){  
        return x > y;  
    }  
};  

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int num;
    while (scanf("%d", &num) && num)
    {
        priority_queue <int, vector<int>, comp> q;
        int n = 0;
        for (int i = 0; i < num; i++)
        {
            scanf("%d", &n);
            q.push(n);
        }

        int sum = q.top();
        q.pop();
        sum += q.top();
        q.pop();
        q.push(sum);

        int total = sum;
        while (q.size() > 1)
        {
            sum = q.top();
            q.pop();
            sum += q.top();
            q.pop();
            q.push(sum);
            total += sum;
        }
        printf("%d\n", total);
    }

    return 0;
}