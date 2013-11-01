// uva 458
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
    char s[1024];
    while (gets(s))
    {
        char* p = s;
        while (*p)
        {
            *p = *p++-7;
        }
        printf("%s\n", s);
    }

    return 0;
}