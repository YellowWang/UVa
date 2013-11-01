// uva 494
// ºÚµ•Ã‚

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

int main()
{
    char d[256];
    memset(d, 0, sizeof(d));
    for (char c = 'a'; c <= 'z'; c++)
    {
        d[c] = 1;
    }
    for (char c = 'A'; c <= 'Z'; c++)
    {
        d[c] = 1;
    }

    char s[1024];
    while (gets(s))
    {
        char* p = s;
        bool line = false;
        int total = 0;
        while (*p)
        {
            if (!line)
            {
                if (d[*p++])
                {
                    ++total;
                    line = true;
                }
            }
            else
            {
                if (!d[*p++])
                    line = false;
            }
        }
        printf("%d\n", total);
    }

    return 0;
}