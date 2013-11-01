// uva 11234
// ͨ���沨��ʽ�Ķ������������У���������Ȼ���ٲ㼶����

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define len 10000

char d[len]; // �������ݴ洢

struct node
{
    char  c;
    node* l;
    node* r;
};

node tree[len];//������������
int  s[len]; // ����ʱ��ʱ�õ�ջ

node* out[len]; // ��ѭ���㼶����ʱ����ʱջ
char outc[len]; // ������

int main()
{
    //fstream cin("1.txt");

    int num = 0;
    cin >> num;

    while (num--)
    {
        cin >> d;
        char* head = d;
        char* tail = head;
        while (*tail){tail++;} // ��βָ��������

        int si = 0; // ��ʱ����ջ����
        int streei = 0; // ��������Ϣ����
        while (--tail && tail != (head-1))
        {
            node n;
            n.c = *tail;
            n.l = n.r = 0;
            tree[streei++] = n; // ����������浽������

            if (si == 0) // ����Ǹ��ڵ�
            {
                s[si++] = streei-1;
                continue;
            }
            else
            {
                int preop = si-1;
                while (tree[s[preop]].c > 'Z') // ������һ����Ҷ�ӽڵ㣬Ҳ���ǲ�����
                {
                    preop--;
                }

                if (tree[s[preop]].r == 0) // ����ڵ�û���Һ���
                {
                    tree[s[preop]].r = &tree[streei-1];
                    s[si++] = streei-1;
                    continue;
                }
                else if (tree[s[preop]].l == 0)// ���û������
                {
                    tree[s[preop]].l = &tree[streei-1];

                    if (tree[streei-1].c > 'Z') // �����Ҷ�ӽڵ㣬��ô��Ҷ�Ӻ�Ҷ�ӵĸ��׶�����ջ 
                    {
                        si = preop;
                    }
                    else // ����ǲ������ڵ㣬��ô�ѵ�ǰ���ϸ��������ڵ㵯����Ȼ����Լ��ŵ�ջ��
                    {
                        si = preop;
                        s[si++] = streei-1;
                    }
                    continue;
                }
            }
        }

        // ������
        int outi1 = 0;
        int outi2 = 0;
        int outci = 0;
        out[outi2++] = &tree[0];
        while (outi1 < outi2) // �㼶��������ȣ�����
        {
            outc[outci++] = out[outi1]->c;
            if (out[outi1]->l)
                out[outi2++] = out[outi1]->l;
            if (out[outi1]->r)
                out[outi2++] = out[outi1]->r;
            outi1++;
        }

        // �������Ϊ��ȷ���
        for (int i = outci-1; i >= 0; i--)
        {
            cout << outc[i];
        }
        cout << endl;
    }

    return 0;
}