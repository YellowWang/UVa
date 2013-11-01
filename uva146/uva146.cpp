// uva146 ��һ��������
// ���⣬�ҹ���

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

#define len 51

int comp(const void* a, const void* b)
{
    return *((char*)a) > *((char*)b);
}

int main()
{
    //freopen("1.txt", "r", stdin);

    char d[len];

    while (scanf("%s", d)!=EOF && d[0] != '#')
    {

        int l = strlen(d);
        // �ҵ�������ĸ����ǰ����ĸ�ĵ�
        int start = -1;
        for (int i = l-1; i > 0; i--)
        {
            if (d[i] > d[i-1])
            {
                start = i-1;
                break;
            }
        }
        if (start == -1)
        {
            printf("No Successor\n");
            continue;
        }
        // �ҵ�����մ���ǰ����ĸ����ĸ
        int replace = -1;
        for (int i = l-1; i > start; i--)
        {
            if (d[i] > d[start])
            {
                replace = i;
                break;
            }
        }
        // ���������
        char t = d[start];
        d[start] = d[replace];
        d[replace] = t;
        qsort(&d[start+1], l-start-1, sizeof(char), comp);

        printf("%s\n", d);
    }

    return 0;
}