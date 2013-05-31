// uva10714 ̰��
// �ҹ��ɡ�
// ��Сʱ�䣺�ҵ������м����������ϣ����������˵���С������Ǵ𰸡�
// ���ʱ�䣺�����ϳ�ʼλ��Ϊx1��x2...xn��lenΪpole�ĳ��ȡ���ֻ���ϵ�ʱ�������������ʱ��ֱ�Ϊx2��len-x1��ֻҪ�Ƚ�����ʱ�䣬����Ϊ�𰸡�
// ��ֻ���ϵ�ʱ�����ǿ��Լ����ƶϳ���ʱ�����Ϊlen-x1��x2��x3���������û�����������迼�ǣ�����������Ҫ�Ƚ�len-x1��x3.�����ҵ�����ߺ����ұߵ����ϼ��ɡ�

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
        int x_mid=0,x_left=0,x_right=0;
        int pole_len, num;
        scanf("%d %d", &pole_len, &num);
        x_left = pole_len;
        int mid = pole_len >> 1;
        for (int i = 0; i < num; i++)
        {
            int n;
            scanf("%d", &n);
            // �ҵ���������
            if (n < x_left)
                x_left = n;
            // �ҵ���������
            if (n > x_right)
                x_right = n;
            // �ҵ����м�����
            if (abs(n-mid) < abs(x_mid-mid))
                x_mid = n;
        }

        printf("%d %d\n", x_mid>mid?pole_len-x_mid:x_mid, 
            (pole_len-x_left)>x_right?pole_len-x_left:x_right);
    }

    return 0;
}