// uva10716 ̰��
// ���ж��Ƿ�����һ�ԣ������������һ��
// Ȼ�����ǰ�벿�֣����磨1����ȡ����i���ַ���Ȼ���length-i����ǰ������ͬ�ַ�������j��
// ��� i==j����ô��������������Ҫ��i��i+1Ԫ���ƶ�һ�¡�Ȼ���ٴ�length-i����ǰ������ͬ�ַ�������j��
//        ���i�ض��������j����Ϊ�����Ѿ��ƶ����ˡ�
// ��� i!=j����ô��j�ƶ���length-i-1����
// �ص���1����

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <queue>  
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

#define len 101

// �Ӻ���ǰѰ��
int find_str_reverse(char* pstr, char c, int end)
{
    for (int i = end-1; i >= 0; i--)
    {
        if (pstr[i] == c)
            return i;
    }
    return -1;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
#endif

    int cases;
    scanf("%d", &cases);
    while (cases--)
    {
        char letters[256];
        memset(letters, 0, sizeof(letters));

        char str[len];
        scanf("%s", str);
        int str_len = strlen(str);
        // �ж��Ƿ�����һ�ԣ������������һ��
        char* p = str;
        while (*p)
        {
            letters[*p]++;
            p++;
        }
        char ji = 0;
        bool valid = true;
        for (int i = 0; i < 256; i++)
        {
            if (letters[i] & 0x01)
            {
                if (ji!=0)
                {
                    valid = false;
                    break;
                }
                ji = i;
            }
        }

        if (!valid)
            printf("Impossible\n");
        else
        {
            int moves = 0;
            // ����һ�볤��
            for (int i = 0; i < str_len>>1; i++)
            {
                // ����Ѱ�Һ�str[i]��ͬ�ַ�
                int idx = find_str_reverse(str, str[i], str_len-i);
                // ����ҵ����Լ�����������
                if (i == idx)
                {
                    // ��ô��󽻻�һ��
                    char t = str[i];
                    str[i] = str[i+1];
                    str[i+1] = t;
                    moves++;
                    // �˴����Ա�֤i != idx
                    idx = find_str_reverse(str, str[i], str_len-i);
                }
                // �ƶ������Ķ�Ӧλ��
                for (int k = idx; k < str_len-1-i; k++)
                {
                    char t = str[k];
                    str[k] = str[k+1];
                    str[k+1] = t;
                    moves++;
                }
            }

            printf("%d\n", moves);
        }

    }



    return 0;
}