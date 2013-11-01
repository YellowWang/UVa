// uva 540 stl�汾
// ��ʼ��map����Ա��Ŷ�Ӧ�����š����������������˵ģ���Ϊ��Ա��ŷ�Χ0-99999������
// ��һ������int belongteam[100000]���洢��Ա�Ķ��飬��������ݡ�
// ��ʱ0.26s

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <map>
#include <deque>
using namespace std;

int m[1000010];

#define len 1200
#define queue_len 1200

struct node 
{
//     int q[queue_len];
//     int h,t;
    deque<int> q;
    node* next;
};
node d[len];

int main()
{
    //ifstream cin("1.txt");

    int team_num = 0;
    int team_elmt = 0;
    int team_id = 0;
    int team_input = 0;
    char com[64];
    int com_no = 0;
    int case_idx = 0;
    while (cin >> team_num && team_num)
    {
        case_idx++;
        // ����map����Աid��Ӧ����id
        memset(m, 0, sizeof(m));

        team_id = 1;
        while (team_num--)
        {
            cin >> team_elmt;
            while (team_elmt--)
            {
                cin >> team_input;
                m[team_input] = team_id;
            }
            team_id++;
        }


        cout << "Scenario " << "#" << case_idx << endl;
        node* head = 0,*tail = 0;
        // ����ָ��
        while (cin >> com && com[0] != 'S')
        {
            if (com[0] == 'E') // ������
            {
                cin >> com_no;

                int teamid = m[com_no];
                if (!head)
                {
                    head = &d[teamid];
                    tail = head;
                }
                else if (d[teamid].q.empty())
                {
                    tail->next = &d[teamid];
                    tail = tail->next;
                }

                d[teamid].q.push_back(com_no);
            }
            else // ������
            {
                cout << head->q.front() << endl;
                head->q.pop_front();
                if (head->q.empty())
                {
                    //clear
                    node* t = head;
                    head = head->next;

                    t->q.clear();
                    t->next = 0;
                }
            }
        }
        cout << endl; // ��ÿ��case�����һ�����У����������

        for (int i = 0; i < team_id+1; i++)
        {
            d[i].q.clear();
            d[i].next = 0;
        }
    }

    return 0;
}