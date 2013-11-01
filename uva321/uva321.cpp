// uva321 隐式图遍历 bfs
// 

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
#include <math.h>
#include <set>
using namespace std;


struct Move
{
    int state;//1 move to room; 2 turn on; 3 turn off
    int room;
    Move(int state, int room)
    {
        this->state = state;
        this->room = room;
    }
};
#define len 11
int g_door[len][len];
int g_light[len][len];
int final_state;
int g_min;
deque<Move> g_qMove;
int g_rooms;
set<int> g_set;
int combind(int room, int light);
bool bfs(int start_room, int start_light, int moves);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int cases = 1;
    int door_cons,light_cons;
    while (scanf("%d %d %d", &g_rooms, &door_cons, &light_cons)!=EOF && g_rooms)
    {
        memset(g_door, 0, sizeof(g_door));
        memset(g_light, 0, sizeof(g_light));

        for (int i = 0; i < door_cons; i++)
        {
            int x,y;
            scanf("%d %d", &x, &y);
            g_door[x][y]=1;
            g_door[y][x]=1;
        }

        for (int i = 0; i < light_cons; i++)
        {
            int x,y;
            scanf("%d %d", &x, &y);
            g_light[x][y]=1;
        }

        int final_room = g_rooms;
        int light = (1<<g_rooms);
        final_state = combind(final_room, light);

        printf("Villa #%d\n", cases++);
        if (bfs(1, 2, 0))
        {
            printf("The problem can be solved in %d steps:\n", g_min);
            for (int i = 0; i < g_qMove.size(); i++)
            {
                Move &m = g_qMove[i];
                if (m.state == 1)
                    printf("- Move to room %d.\n", m.room);
                else if (m.state == 2)
                    printf("- Switch on light in room %d.\n", m.room);
                else if (m.state == 3)
                    printf("- Switch off light in room %d.\n", m.room);
            }

        }
        else
            printf("The problem cannot be solved.\n");
        printf("\n");
    }

    return 0;
}

int combind(int room, int light)
{
    return (room<<(g_rooms+1)) + light;
}


struct Node
{
    int cur_room;
    int light;
    int moves;
    deque<Move> qMove;
    Node(int cur_room, int light, int moves, deque<Move>& qMove)
    {
        this->cur_room = cur_room;
        this->light = light;
        this->qMove = qMove;
        this->moves = moves;
    }
};

bool bfs(int start_room, int start_light, int moves)
{
    g_set.clear();
    g_qMove.clear();
    g_min = 99999;

    deque<Node> q;
    deque<Move> qMove;
    q.push_back(Node(start_room, start_light, moves, qMove));

    while (!q.empty())
    {
        Node& node = q.front();
        int state = combind(node.cur_room, node.light);

        // 匹配最终状态
        if (state == final_state)
        {
            g_min = node.moves;
            g_qMove = node.qMove;
            return true;
        }

        // 已经走过
        if (g_set.count(state) > 0)
        {
            q.pop_front();
            continue;
        }
        g_set.insert(state);

        // 遍历各种状态
        // 去下一个room
        for (int i = 1; i <= g_rooms; i++)
        {
            if (g_door[node.cur_room][i] && ((1<<i)&node.light) &&
                g_set.count(combind(i, node.light)) == 0)
            {
                node.qMove.push_back(Move(1, i));
                q.push_back(Node(i, node.light, node.moves+1, node.qMove));
                node.qMove.pop_back();
            }
        }
        // 开关灯
        for (int i = 1; i <= g_rooms; i++)
        {
            if (g_light[node.cur_room][i])
            {
                if (((1<<i)&node.light) && node.cur_room != i &&
                    g_set.count(combind(i, node.light^(1<<i))) == 0)
                {
                    node.qMove.push_back(Move(3, i));
                    q.push_back(Node(node.cur_room, node.light^(1<<i), node.moves+1, node.qMove));
                    node.qMove.pop_back();
                }
                else if (((1<<i)&node.light)==0 && 
                    g_set.count(combind(i, node.light|(1<<i))) == 0)
                {
                    node.qMove.push_back(Move(2, i));
                    q.push_back(Node(node.cur_room, node.light|(1<<i), node.moves+1, node.qMove));
                    node.qMove.pop_back();
                }
            }
        }

        q.pop_front();
    }

    return false;
}