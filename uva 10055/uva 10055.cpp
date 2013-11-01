// uva 10055
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;
int main()
{
    long num1, num2;
    while (cin >> num1)
    {
        cin >> num2;
        cout << (num1>num2?num1-num2:num2-num1) << endl;
    }
    return 0;
}