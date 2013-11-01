// uva 112
// �����߼�������������Ȼ����ȱ������������Ƿ���ϵ�ֵ
/* �Ż��߼���
*    1����Ϊ�������Ĺ��̾�����ȱ����Ĺ��̣����Ա����ɱ�����ۼ�ֵ���ŵ��ڵ��ϡ���ʱ0.164s
*    2������ҵ�ֵ�ˣ���ô���Ժ���Ľڵ㣬ֱ������������ʱ0.148s
*    3������getchar������ַ������ٶ��������ʱ0.044s
*/        
// �����˺�ʱ0.01s
// ע�⣺����Ϊ0���߸���

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

struct node 
{
    int d;//�ڵ�Ȩ��
    bool haveleft;
    node* f;//���ڵ�
    node* l;//����
    node* r;//�Һ���
};

#define len 1000
node tree[len];
int treei;
node* s[len];// ջ
int si;

int main()
{
    //ifstream cin("1.txt");

    char c;
    char token[16];

    int match = 0;
    while (cin >> match)
    {
        treei = 0;
        si = 0;
        int token_idx = 0;
        bool bmatch = false;
        int ignore = 0;
        bool bIgnore = false;
        while (c = getchar()) // ��ǰ��cin >> c���ٶ��е������͸�Ϊgetchar()
        {
            //����Ѿ��ҵ�����ô���Ժ�����ַ�
             if (bIgnore)
            {
                if (c == '(')
                {
                    ++ignore;
                }
                else if (c == ')')
                {
                    --ignore;
                }
                if (!ignore)
                {
                    bIgnore = false;
                    break;
                }
                token_idx = 0;
                continue;
             }

            //�ֽ⣬ע�⸺��
            if ((c >= '0' && c <= '9') || (c == '-') || (c == '+'))
            {
                if (token_idx > 0 && token[token_idx-1] == '(')
                    token_idx = 0;
                token[token_idx++] = c;
                continue;
            }
            else if (c == '(')
            {
                int num = 0;
                //���token��ֵ����ôתΪ���͡�
                if (token_idx > 0)
                {
                    token[token_idx] = 0;
                    num = atoi(token);
                    token_idx = 0;

                    // �����½ڵ�
                    s[si] = &tree[treei++];
                    s[si]->d = num;
                    s[si]->haveleft = false;
                    s[si]->l = s[si]->r = 0;
                    //������Ǹ��ڵ㣬��ô���ø��ӹ�ϵ
                    if (si)
                    {
                        s[si]->f = s[si-1];
                        s[si]->d += s[si-1]->d; // �ѱ����ۼ�����Ȩֵ�������ŵ���������ʱ��������ÿ���ڵ��ۼӸ��׵�Ȩֵ��
                        if (s[si-1]->haveleft)
                            s[si-1]->r = s[si];
                        else
                        {
                            s[si-1]->l = s[si];
                            s[si-1]->haveleft = true;
                        }
                    }
                    else
                        s[si]->f = 0;

                    si++;
                }

                token[token_idx++] = c;//'('
            }
            else if (c == ')')
            {
                // process
                if (token[token_idx-1] == '(')
                {
                    token_idx = 0;
                    // �ѿ������˹�ȥ
                    if (si > 0 && !s[si-1]->haveleft)
                        s[si-1]->haveleft = true;
                }
                // ����
                else
                {
                    // ƥ�䣬������Ҷ�ӽڵ�
                    if (s[si-1]->d == match &&
                        s[si-1]->l == s[si-1]->r &&
                        s[si-1]->l == 0)
                    {
                        bmatch = true;
                         bIgnore = true;
                         ignore = si-1;
                         continue;
                    }
                    si--;
                }

                //����ϸ�����ɣ���ô��������
                if (si == 0)
                {
                    break;
                }
            }
        }

        if (bmatch)
        {
            cout << "yes" << endl;
        }
        else
            cout << "no" << endl;
    }


    return 0;
}