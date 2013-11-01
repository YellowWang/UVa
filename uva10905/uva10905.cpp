// uva 10905
// special example�� 90 900; 12 122; 9 90; 1 12; 212 21212; 232 23232; 222 22212
// ���ַ�����int�������
// comp1�õ�std��string��,comp2���Լ���ָ��ʵ�ֵģ�comp1��ʱ0.296��comp2��ʱ0.100
 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
 
int comp1(const void *a,const void *b)
{
    char* x = (char*)a;
    char* y = (char*)b;
 
    string s1 = x;
    string s2 = y;
 
    string s3 = s1.append(y);
    string s4 = s2.append(x);
    return strcmp(s3.c_str(), s4.c_str()) < 0;
}
 
int comp2(const void *a,const void *b)
{
    char* x = (char*)a;
    char* y = (char*)b;
 
    while (*x && *y)
    {
        if (*x == *y)
        {
            x++;
            y++;
            continue;
        }
 
        if (*x > *y)
        {
            return -1;
        }
        else
            return 1;
    }
 
    if (*x == *y)
    {
        return 0;
    }
 
    if (*x == 0)
    {
        x = (char*)b;
        while (*x && *y)
        {
            if (*x == *y)
            {
                x++;
                y++;
                continue;
            }
            if (*x > *y)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
 
        y = (char*)a;
        while (*x && *y)
        {
            if (*x == *y)
            {
                x++;
                y++;
                continue;
            }
            if (*x > *y)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }
 
    if (*y == 0)
    {
        y = (char*)a;
        while (*x && *y)
        {
            if (*x == *y)
            {
                x++;
                y++;
                continue;
            }
            if (*x > *y)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
 
        x = (char*)b;
        while (*x && *y)
        {
            if (*x == *y)
            {
                x++;
                y++;
                continue;
            }
            if (*x > *y)
            {
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }
}
 
int main()
{
    char input_data[55][100];
 
    int input_number = 0;
    while (1)
    {
        cin >> input_number;
        if (!input_number)
        {
            break;
        }
 
        for (int i = 0; i < input_number; i++)
        {
            cin >> input_data[i];
        }
 
        qsort(input_data, input_number, 100, comp2);
 
        for (int i = 0; i < input_number; i++)
        {
            cout << input_data[i];
        }
        cout << endl;
    }
 
    return 0;
}