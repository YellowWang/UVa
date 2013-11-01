// uva105
// ��������΢�򵥵��⡣�о��кܶ�ⷨ�����Ϊ�˼��ٲ���Ҫ�Ĳ�������ĺܸ��ӡ�
// ���ɴ�ֱ�ӽ���һ���ܳ��ĵ�ƽ��line������¥����ӳ�䵽���line�ϣ�line�����ص�¥�������߶ȡ����������н����
// ��Ŀû����ȷ˵��line�ж೤�����Ի��Ƿ��յġ��������ac�ˡ�

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

// ��Ϊlen�ܴ�Ļ��ᳬʱ��������������û�кܱ�̬����ac��
#define len 100000
int line[len];

int main()
{
    //freopen("1.txt", "r", stdin);

    memset(line, 0, sizeof(line));
    int x,y,h;
    while (scanf("%d %d %d", &x, &h, &y)!=EOF)
    {
        for (int i = x; i <= y; i++)
        {
            line[i] = max(line[i], h);
        }
    }

    // �����Ϊ��һ�����һ��û�ж���ո����Դ��븴����һЩ
    int start = 0;
    for (int i = 0; i < len; i++)
    {
        if (line[i] > 0)
        {
            printf("%d %d", i, line[i]);
            start = i;
            break;
        }
    }
    bool join = true;
    int pre = line[start];
    for (int i = start; i < len; i++)
    {
        if (join && line[i] == pre)
        {
            continue;
        }
        else if (join && line[i] != pre && line[i] > 0)
        {
            if (line[i] > pre)
                printf(" %d %d", i, line[i]);
            else
                printf(" %d %d", i-1, line[i]);
            //join = false;
            pre = line[i];
        }
        else if (join && line[i]==0)
        {
            printf(" %d %d", i-1, 0);
            join = false;
        }
        else if (!join && line[i] > 0)
        {
            printf(" %d %d", i, line[i]);
            pre = line[i];
            join = true;
        }
    }

    printf("\n");
    return 0;
}