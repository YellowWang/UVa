// uva 548
// �ݹ飺ջ���
// ѭ����0.18s
// ��gets����getline����ʱ0.072s
// �������ڴ棬��ȫ�����飬��ʱ0.060s
// ���ٲ���Ҫ���жϣ���ʱ0.052s
// ������0.01s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
using namespace std;

#define len 10010
char d[len*5];

int inorder[len]; //��������
int inorder_ex[len]; //ֵ��Ӧ���������������
int post[len];    //��������
int post_ex[len]; //ֵ��Ӧ�������������

// ���ڵ�
struct node
{
    int d;
    int sumd;
    node* l;
    node* r;
};
node* head; //����ָ��
int tree_num = 0; //���ڵ�����
node  tree[len]; //������������Ľڵ㣬���������ڴ�
int   treei;//����

// ѭ���汾
int create_tree2(int l1, int r1, int l2, int r2); 
// �ݹ�汾
node* create_tree(int l1, int r1, int l2, int r2, int& min);
// ɾ�������ڴ����
void remove(node* n);

int main()
{
    //ifstream cin("1.txt");

    while (gets(d)/*cin.getline(d, len*5)*/)
    {
        // �������ݣ����ֲ�
        int idx = 0;
        char * tok = strtok(d, " ");
        while (tok)
        {
            inorder[idx] = atoi(tok);
            inorder_ex[inorder[idx]] = idx;
            ++idx;
            tok = strtok(NULL, " ");
        }
        tok = strtok(d, " ");

        idx = 0;
        /*cin.getline(d, len*5);*/
        gets(d);
        tok = strtok(d, " ");
        while (tok)
        {
            post[idx] = atoi(tok);
            post_ex[post[idx]] = idx;
            ++idx;
            tok = strtok(NULL, " ");
        }
        tree_num = idx;

        // �������򡢺��򣬽�����

        // �ݹ�汾
//         int min = 999999;
//         head = create_tree(0, idx-1, 0, idx-1, min);


        // ѭ���汾
        cout << create_tree2(0, idx-1, 0, idx-1) << endl;

        //�����ڴ�Ļ�����Ҫ�ͷ�
        //remove(head);
    }

    return 0;
}

void remove(node* n)
{
    if (n->l)
    {
        remove(n->l);
    }
    if (n->r)
    {
        remove(n->r);
    }
    delete n;
}

struct qnode 
{
    int l1,r1,l2,r2;
    node* d;
};

int create_tree2(int l1, int r1, int l2, int r2)
{
    int min = 9999999; //��������˳������С�ۼ�·��
    int minid = -1;
    treei = 0;

    head = &tree[treei++];//new node;
    deque<qnode> q;
    qnode qn1;
    qn1.l1 = l1;
    qn1.r1 = r1;
    qn1.l2 = l2;
    qn1.r2 = r2;
    qn1.d = head;
    qn1.d->sumd = 0;
    q.push_back(qn1);
    // �ö��У����������
    while (!q.empty())
    {
        qnode qn = q.front();
        qn.d->d = post[qn.r2]; 
        qn.d->sumd += qn.d->d; //�ۼ���
        qn.d->l = qn.d->r = 0;

        int left = qn.r1 - inorder_ex[qn.d->d];
        int tl1 = qn.l1;
        int tr1 = inorder_ex[qn.d->d]-1;
        int tl2 = qn.l2;
        int tr2 = qn.r2-left-1;
        if (tl1 <= tr1 && tl2 <= tr2)
        {
            qnode tqn;
            tqn.l1 = qn.l1;
            tqn.r1 = tr1;
            tqn.l2 = qn.l2;
            tqn.r2 = tr2;
            tqn.d = &tree[treei++];//new node;
            qn.d->l = tqn.d;
            tqn.d->sumd = qn.d->sumd; //�ۼ���
            q.push_back(tqn);
        }

        tl1 = inorder_ex[qn.d->d]+1;
        tr1 = qn.r1;
        tl2 = qn.r2-left;
        tr2 = post_ex[qn.d->d]-1;
        if (tl1 <= tr1 && tl2 <= tr2 )
        {
            qnode tqn;
            tqn.l1 = tl1;
            tqn.r1 = tr1;
            tqn.l2 = tl2;
            tqn.r2 = tr2;
            tqn.d = &tree[treei++];//new node;
            qn.d->r = tqn.d;
            tqn.d->sumd = qn.d->sumd; //�ۼ���
            q.push_back(tqn);
        }

        // Ҷ�ӽڵ�����ۼ�ֵ
        if (qn.d->l == qn.d->r && qn.d->l==0)
        {
            if (qn.d->sumd < min)
            {
                min = qn.d->sumd;
                minid = post[qn.r2];
            }
        }

        q.pop_front();
    }
    return minid;
}

node* create_tree(int l1, int r1, int l2, int r2, int& min)
{
    if (l1 > r1 || l1 < 0 || r1 >= tree_num ||
        l2 > r2 || l2 < 0 || r2 >= tree_num)
    {
        return 0;
    }

    node* nn = new node;
    nn->d = post[r2];

    int left = r1 - inorder_ex[nn->d];
    nn->l = create_tree(l1, inorder_ex[nn->d]-1, l2, r2-left-1,min);
    nn->r = create_tree(inorder_ex[nn->d]+1, r1,r2-left, post_ex[nn->d]-1,min);

    if (nn->l == nn->r && nn->l==0)
    {
        if (nn->d < min)
        {
            min = nn->d;
        }
    }
    return nn;
}