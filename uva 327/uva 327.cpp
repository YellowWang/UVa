// uva 327
// ��Ŀ��ȥ���ַ����Ŀո�Ȼ��ע��ǰ++��++������
// ��ʱ0.036s�����0.012s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

#define  len 1024

int var[256];
int var_ans[256];

void calc(char* p);
int main()
{
    //ifstream cin("1.txt");
    int* pvar = &var['a'];

    for (int i = 1; i < 27; i++)
    {
        *pvar++ = i;
    }

    char s[len];
    while (gets(s)/*cin.getline(s, len)*/)
    {
        calc(s);
    }

    return 0;
}

void calc(char* p)
{
    char* savep = p;
    printf("Expression: %s\n", savep);

    //ȥ���ո�
    char* ps = p;
    while (*p)
    {
        if (*p != ' ')
            *ps++ = *p;
        ++p;
    }
    *ps = 0;

    // ����
    p = savep;
    int op = 0;
    int sum = 0;
    memset(var_ans, -1, sizeof(var_ans));
    while (*p)
    {
        int new_var = 0;
        if (*p == '+') //ǰ++
        {
            p = p + 2;
            new_var = var[*p]+1;
            var_ans[*p] = new_var;
        }
        else if (*p == '-') // ǰ--
        {
            p = p + 2;
            new_var = var[*p]-1;
            var_ans[*p] = new_var;
        }
        else if (*(p+1) == '+' && *(p+2) == '+') // ��++
        {
            new_var = var[*p];
            var_ans[*p] = new_var+1;
            p = p + 2;
        }
        else if(*(p+1) == '-' && *(p+2) == '-') // ��--
        {
            new_var = var[*p];
            var_ans[*p] = new_var-1;
            p = p + 2;
        }
        else
        {
            // ����
            new_var = var[*p];
            var_ans[*p] = new_var;
        }

        if (op == 1)
            sum += new_var;
        else if (op == 2)
            sum -= new_var;
        else 
            sum = new_var;
        ++p;

        if (*p == '+')
        {
            op = 1;
            ++p;
        }
        else if (*p == '-')
        {
            op = 2;
            ++p;
        }
    }

    //printf("Expression: %s\n", savep);
    printf("    value = %d\n", sum);

    for (char c = 'a'; c <= 'z'; c++)
    {
        if (var_ans[c] >= 0)
            printf("    %c = %d\n", c, var_ans[c]);
    }
}