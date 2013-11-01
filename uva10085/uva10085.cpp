// uva10085 ���䱩��
// �������������
// ��ϰ�����ĺ���Ŀ������������ͨ�����ɵó���O��1��ʱ�䡣
// һ���Ǳ������

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

#define len 3
int g_arr[len*len]; // ��ȡ��������
set<int> g_set; // ��stl��set�����б�ĳһ������Ƿ��߹�
int g_res[len][len]; // �������
int g_max_moves; // �ҵ������
vector<int> g_v; // �������ƶ���������
// ������ȼ��㡣first_arr��ʼ������blankx��blanky�ǿհ׵����꣬moves��¼�ƶ�����
void bfs_move_most(int first_arr[len][len], int blankx, int blanky, int moves);

int main()
{
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif

    int case_num,cases=1;
    scanf("%d", &case_num);
    while (case_num--)
    {
        for (int i = 0; i < len; i++)
        {
            scanf("%d %d %d", &g_arr[i*len+0], &g_arr[i*len+1], &g_arr[i*len+2]);
        }

        // �ҵ��հ׵㣬�����������飨�ƶ����ƶ�������
        int blank_x = 0;
        int blank_y = 0;
        int first_arr[len][len];
        int first_idx = 0;
        for (int i = 0; i < len; i++)
            for (int k = 0; k < len; k++)
            {
                if (g_arr[first_idx]==0)
                {
                    blank_x = i;
                    blank_y = k;
                }
                first_arr[i][k]=first_idx++;
            }
        bfs_move_most(first_arr, blank_x, blank_y, 0);

        printf("Puzzle #%d\n", cases++);
        // ����������
        for (int i = 0; i < len; i++)
        {
            printf("%d %d %d\n", g_arr[g_res[i][0]], g_arr[g_res[i][1]], g_arr[g_res[i][2]]);
        }
        // ����ƶ�����
        for (int i = 0; i < g_v.size(); i++)
        {
            if (g_v[i] == 0)
                printf("%c", 'L');
            else if (g_v[i] == 1)
                printf("%c", 'U');
            else if (g_v[i] == 2)
                printf("%c", 'R');
            else if (g_v[i] == 3)
                printf("%c", 'D');
        }
        printf("\n\n");
    }

    return 0;
}

// �ڵ�
struct Node
{
    int arr[len][len]; //��ǰ����״̬
    int blankx,blanky; //�հ׵�����
    int moves; //�Ѿ��ƶ�����
    vector<int> v; //�Ѿ��߹�������
    Node(int arr[len][len], int blankx, int blanky, int moves, vector<int>& v)
    {
        memcpy(this->arr, arr, sizeof(this->arr));
        this->blankx = blankx;
        this->blanky = blanky;
        this->moves = moves;
        this->v = v;
    }
};

bool is_visit_insert(int arr[len][len])
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum *= 1000;
        sum += arr[i][0] + arr[i][1]*10 + arr[i][2]*100;
    }
    if (g_set.count(sum) > 0)
        return true;

    g_set.insert(sum);
    return false;
}

bool is_visit(int arr[len][len])
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum *= 1000;
        sum += arr[i][0] + arr[i][1]*10 + arr[i][2]*100;
    }
    if (g_set.count(sum) > 0)
        return true;
    return false;
}

void bfs_move_most(int first_arr[len][len], int blankx, int blanky, int moves)
{
    g_max_moves = 0;
    g_set.clear();
    int dir[] = {0,-1, -1,0, 0,1, 1,0};

    deque<Node> q;
    vector<int> v;
    q.push_back(Node(first_arr, blankx, blanky, moves, v));

    while (!q.empty())
    {
        Node& node = q.front();

        // �Ƿ����
        if (is_visit_insert(node.arr))
        {
            q.pop_front();
            continue;
        }

        // �Ƿ��յ㣬��������31�������
        if (node.moves == 31)
        {
            g_max_moves = node.moves;
            memcpy(g_res, node.arr, sizeof(g_res));
            g_v = node.v;
            return;
        }

        // �ҵ����õİ汾�������31�����
//         if (node.moves > g_max_moves)
//         {
//             g_max_moves = node.moves;
//             memcpy(g_res, node.arr, sizeof(g_res));
//         }

        // �������������4�������ϡ��ҡ���
        int blank_x = node.blankx;
        int blank_y = node.blanky;
        for (int i = 0; i < 4; i++)
        {
            int newx = blank_x + dir[i*2];
            int newy = blank_y + dir[i*2+1];
            if (newx >= 0 && newx < len && newy >= 0 && newy < len)
            {
                // �ƶ�һ��
                int t = node.arr[newx][newy];
                node.arr[newx][newy] = node.arr[blank_x][blank_y];
                node.arr[blank_x][blank_y] = t;
                if (!is_visit(node.arr))
                {
                    vector<int> tempv = node.v;
                    tempv.push_back(i);
                    q.push_back(Node(node.arr, newx, newy, node.moves+1, tempv));
                }
                // ��ԭ
                t = node.arr[newx][newy];
                node.arr[newx][newy] = node.arr[blank_x][blank_y];
                node.arr[blank_x][blank_y] = t;
            }
        }

        q.pop_front();
    }
}