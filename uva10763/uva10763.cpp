// uva10763
//
 
 
#include <stdio.h>
#include <map>
#include <iostream>
 
using namespace std;
 
int main()
{
    int input_data1 = 0;
    int input_data2 = 0;
    int input_num = 0;
    while (1)
    {
        cin >> input_num;
        if (!input_num)
        {
            break;
        }
 
        map<int , map<int, int> > m;
        for (int i = 0; i < input_num; i++)
        {
            cin >> input_data1 >> input_data2;
 
            if (m.find(input_data1) != m.end())
            {
                map<int, int> & v = m[input_data1];
                if (v.find(input_data2) != v.end())
                {
                    v[input_data2]--;
                    if (v[input_data2] == 0)
                    {
                        v.erase(input_data2);
                    }
                }
                else
                {
                    m[input_data2][input_data1] += 1;
                }
            }
            else
            {
                m[input_data2][input_data1] += 1;
            }
        }
 
        map<int , map<int, int> >::iterator it;
        for (it = m.begin(); it != m.end(); it++)
        {
            if (it->second.size() > 0)
            {
                cout << "NO" << endl;
                break;
            }
        }
        if (it == m.end())
        {
            cout << "YES" << endl;
        }
    }
 
    return 0;
}
 