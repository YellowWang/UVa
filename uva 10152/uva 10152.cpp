// uva 10152
// http://www.2cto.com/kf/201207/139123.html
/* �������������:
*    1��������������Ϊ�����ڲ����пո�ģ�����Ŀ���԰�һ��������
*    2����׼���ȡһ��Ĭ�����ҵ�'\n'������windows���ļ��Ļ��в����Ǹ������Ծ�������
*    3��runtime error����������ˡ���������Խ��д�������ʷǷ��ڴ��ַ�ȡ�
*    4��wrong anser������������⡣Ҳ�п������鿪�ٵĲ�����Ҫ��ϸ���⡣
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

        // ��ǰ���ջ��Ȩֵ
        // �����������
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

        // ��������
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

            // �ҵ���СȨֵ��Ԫ��
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

            // ��Ȩֵ��С��Ԫ���ȷŵ���β
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