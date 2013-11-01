// uva 839
// 比较简单的一个题目

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;

struct node 
{
    node* l;
    node* r;
};

ifstream cin1;

int calc(bool& b);
void remove_tree(node* n);
int main()
{
    //cin1.open("1.txt");


    int input_num;
    cin >> input_num;

    while (input_num--)
    {
        bool b = true;
        calc(b);
        if (b)
        {
            printf("YES\n");
        }
        else
            printf("NO\n");

        if (input_num)
            printf("\n");
    }

    return 0;
}

int calc(bool& b)
{
    int w1,d1,w2,d2;
    cin >> w1 >> d1 >> w2 >> d2;

    if (w1 == 0)
    {
        w1 = calc(b);
    }

    if (w2 == 0)
    {
        w2 = calc(b);
    }

    if (w1*d1 != w2*d2)
    {
        b = false;
    }

    return w1+w2;
}