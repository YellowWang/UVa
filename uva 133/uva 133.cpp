// uva 133
// 题目中文描述：http://www.nocow.cn/index.php/UVA_133
// 用双向链表，删除比较快速

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

// 双向链表节点
struct node
{
    int no;
    node* next;
    node* pre;
};

int main()
{
//    ifstream cin("1.txt");

    int n , k, m; //n数量，小于20；k是顺时针走多少；m是逆时针走多少

    node* head = new node[20]; // 提前申请好节点数组，以后就不用申请内存了

    while ((cin >> n >> k >> m) && n) // 输入0,0,0就退出
    {
        // 根据数量，生成一个环形双向链表
        head->no = 1;
        node* cur = head;
        for (int i = 1; i < n; i++)
        {
            cur->next = &head[i];
            head[i].pre = cur;
            cur = cur->next;
            cur->no = i+1;
        }
        head->pre = cur;
        cur->next = head;

        // 开始处理
        int left = n; // left为节点剩余数量
        node* pk = head; // 一个指向头
        node* pm = head->pre; // 一个指向尾
        bool  isfirst = true; // 格式用
        while (left)
        {
            if (!isfirst)
            {
                cout << ",";
            }
            isfirst = false;
            if (left == 1) // 剩下一个，那就直接输出
            {
                //cout << "  " << pk->no;
                printf("%3d", pk->no);
                break;
            }
            int kn = k % left; // 不能走重复的路
            int mn = m % left; // 不能走重复的路
            pk = pk->pre;
            pm = pm->next;
            // 前进或后退
            while (kn--)
            {
                pk = pk->next;
            }
            while (mn--)
            {
                pm = pm->pre;
            }
            // 如果找到是同一个
            if (pk == pm)
            {
                pk = pk->next;
                pm = pm->pre;

                //cout << " " << pk->pre->no;
                printf("%3d", pk->pre->no);

                // delete
                pm->next = pm->next->next;
                pk->pre  = pk->pre->pre;
                left--;
            }
            // 找到不相同
            else
            {
                node* tk = pk;
                node* tm = pm;
                pk = pk->next;
                if (pk == tm)
                    pk = pk->next;
                pm = pm->pre;
                if (pm == tk)
                    pm = pm->pre;

                //cout << "  " << tk->no << "  " << tm->no;
                printf("%3d%3d", tk->no,tm->no);

                // delete
                tk->pre->next = tk->next;
                tk->next->pre = tk->pre;
                tm->pre->next = tm->next;
                tm->next->pre = tm->pre;
                left = left-2;
            }
        }
        cout << endl;
    }


    delete []head;
    return 0;
}