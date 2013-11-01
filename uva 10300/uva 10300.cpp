// uva 10300
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
    //ifstream cin("1.txt");
    int cases;
    cin >> cases;
    while (cases--)
    {
        int n;
        cin >> n;
        int sum = 0;
        while (n--)
        {
            int f, a, e;
            cin >> f >> a >> e;
            sum += f*e;
        }
        cout << sum << endl;
    }
    return 0;
}