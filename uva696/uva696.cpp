// uva696
// 找规律，然后归纳公式

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;


int main()
{
    //freopen("1.txt", "r", stdin);


    int rows,cols;

    while (scanf("%d %d", &rows, &cols) && rows)
    {
        int m = rows*cols;
        int ans = 0;
        if (rows == 1 || cols == 1)
        {
            ans = rows>cols?rows:cols;
        }
        else if (rows == 2 || cols == 2)
        {
            int big=rows>cols?rows:cols;
            ans = big/4*4+min(big%4, 2)*2;
        }
        else
        {
            ans = (m+1) >> 1;
        }


        printf("%d knights may be placed on a %d row %d column board.\n", ans, rows, cols);
    }
    return 0;
}