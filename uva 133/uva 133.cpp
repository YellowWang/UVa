// uva 133
// ��Ŀ����������http://www.nocow.cn/index.php/UVA_133
// ��˫������ɾ���ȽϿ���

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

// ˫������ڵ�
struct node
{
    int no;
    node* next;
    node* pre;
};

int main()
{
//    ifstream cin("1.txt");

    int n , k, m; //n������С��20��k��˳ʱ���߶��٣�m����ʱ���߶���

    node* head = new node[20]; // ��ǰ����ýڵ����飬�Ժ�Ͳ��������ڴ���

    while ((cin >> n >> k >> m) && n) // ����0,0,0���˳�
    {
        // ��������������һ������˫������
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

        // ��ʼ����
        int left = n; // leftΪ�ڵ�ʣ������
        node* pk = head; // һ��ָ��ͷ
        node* pm = head->pre; // һ��ָ��β
        bool  isfirst = true; // ��ʽ��
        while (left)
        {
            if (!isfirst)
            {
                cout << ",";
            }
            isfirst = false;
            if (left == 1) // ʣ��һ�����Ǿ�ֱ�����
            {
                //cout << "  " << pk->no;
                printf("%3d", pk->no);
                break;
            }
            int kn = k % left; // �������ظ���·
            int mn = m % left; // �������ظ���·
            pk = pk->pre;
            pm = pm->next;
            // ǰ�������
            while (kn--)
            {
                pk = pk->next;
            }
            while (mn--)
            {
                pm = pm->pre;
            }
            // ����ҵ���ͬһ��
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
            // �ҵ�����ͬ
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