// uva 673
// ��ʱ0.18������0.0
// ��Ϊ������128��������λ������64�ı����Ϳ��ԡ�

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

#define len 256
char a[len];

char s[len];

int main()
{
    //ifstream cin("1.txt");
    int num;

    char temp[64];
    cin.getline(temp, 64);
    num= atoi(temp);
    //cin >> num;

    long long st;

    while (num--)
    {
        cin.getline(a, len);
        //cin >> a;

        st = 0;
        int si = 0;
        char* p = a;
        bool y = true;
        while (*p != 0)
        {
            if (*p=='(')
            {
                st <<= 1;
                st |= 1;
                si++;
            }
            else if (*p=='[')
            {
                st <<= 1;
                si++;
                //st |= 0;
            }
            else if (*p == ')')
            {
                if (si == 0)
                {
                    y = false;
                    break;
                }
                if (st & 0x01 == 0)
                {
                    y = false;
                    break;
                }
                st >>= 1;
                si--;
            }
            else if (*p == ']')
            {
                if (si == 0)
                {
                    y = false;
                    break;
                }
                if (st & 0x01 > 0)
                {
                    y = false;
                    break;
                }
                st >>= 1;
                si--;
            }
            p++;
        }
        if (si == 0 && y)
        {
            cout << "Yes" << endl;
        }
        else
            cout << "No" << endl;
    }

    return 0;
}