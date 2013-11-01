// uva 540 stl版本
// 开始用map，人员编号对应队伍编号。后来看网上其他人的，因为人员编号范围0-99999，所以
// 用一个数组int belongteam[100000]，存储人员的队伍，这样更快捷。
// 耗时0.26s

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
        // 建立map，人员id对应队伍id
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
        // 读入指令
        while (cin >> com && com[0] != 'S')
        {
            if (com[0] == 'E') // 进队列
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
            else // 出队列
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
        cout << endl; // 在每个case后面加一个换行，这搞死我了

        for (int i = 0; i < team_id+1; i++)
        {
            d[i].q.clear();
            d[i].next = 0;
        }
    }

    return 0;
}