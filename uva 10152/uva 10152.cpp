// uva 10152
// http://www.2cto.com/kf/201207/139123.html
/* 编程遇到的问题:
*    1，读入人名。因为名字内部是有空格的，此题目可以按一行来读。
*    2，标准库读取一行默认是找到'\n'。但是windows的文件的换行不是那个，所以就有问题
*    3，runtime error。程序崩溃了。可能数组越界写超，访问非法内存地址等。
*    4，wrong anser。输出的有问题。也有可能数组开辟的不够，要仔细读题。
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define len 90

struct node
{
    int w;
    char name[len];
    node* pre;
    node* next;
};

node g_d[400];
node* ai[200];
int idx;
node* tail;

int main()
{
    //fstream cin("1.txt");
    int case_n = 0;
    //cin >> case_n;

     char temp[64];
     cin.getline(temp, 64);
     case_n = atoi(temp);

    while (case_n--)
    {
        int num = 0;
        //cin >> num;
        cin.getline(temp, 64);
         num = atoi(temp);

        for (int i = 0; i < num; i++)
        {
            //cin >> g_d[i].name;
            cin.getline(g_d[i].name, len);
        }

        for (int i = 0; i < num; i++)
        {
            //cin >> g_d[i+num].name;
            cin.getline(g_d[i+num].name, len);
            g_d[i+num].w = num-i;
        }

        if (num == 1)
        {
            cout << endl;
            continue;
        }

        // 给前面的栈赋权值
        // 逐个遍历查找
        for (int i = 0; i < num; i++)
        {
            for (int k = 0; k < num; k++)
            {
                char* p = g_d[i].name;
                char* q = g_d[k+num].name;
                while (*p && *q && *p == *q) {
                    p++;
                    q++;
                }
                if (*p == *q)
                {
                    g_d[i].w = g_d[k+num].w;
                    break;
                }
            }
        }

        // 建立链表
        g_d[0].next = 0;
        node* cur = &g_d[num-1];
        for (int i = num-2; i >= 0; i--)
        {
            cur->next = &g_d[i];
            g_d[i].pre = cur;
            cur = cur->next;
        }
        g_d[num-1].pre = 0;
        tail = &g_d[0];

        while (true)
        {
            idx = 0;
            memset(ai, 0, sizeof(ai));
            int max = tail->w;
            node* cur = tail->pre;
            while (cur)
            {
                if (cur->w > max)
                    ai[idx++] = cur;
                else
                    max = cur->w;
                cur = cur->pre;
            }

            if (idx == 0)
            {
                break;
            }

            // 找到最小权值的元素
            int min = ai[0]->w;
            int minidx = 0;
            for (int i = 1; i < idx; i++)
            {
                if (ai[i]->w < min)
                {
                    min = ai[i]->w;
                    minidx = i;
                }
            }

            // 把权值最小的元素先放到队尾
            node* minai = ai[minidx];
            if (minai->pre)
            {
                minai->pre->next = minai->next;
                minai->next->pre = minai->pre;
            }
            else
            {
                minai->next->pre = 0;
            }

            tail->next = minai;
            minai->pre = tail;
            tail = minai;

            cout << tail->name << endl;
        }
        cout << endl;
    }
    return 0;
}