// uva131 枚举子集
// 简单运用枚举子集，但是德州扑克牌型可真伤不起，让我又去看了一遍规则。
// imba点：A 2 3 4 5是最小的顺子, T J Q K A是最大的顺子。 J Q K A 2不是顺子。

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <deque>
#include <vector>
using namespace std;

// 枚举子集函数
void collection(int start, int idx, int num, int max, int* p);

#define len 5
#define str_len 3
#define card_len 13

// 手上牌
char hand[len][str_len];
// 桌上牌
char deck[len][str_len];


// 临时中间变量
char tcard[len][str_len];
int t[len];
// 每次最终结果
int g_best; 

// 方便运算的映射
int mCard[256];
int mColor[256];
char *mValue[10];


int main()
{
    //freopen("1.txt", "r", stdin);

    memset(mCard, 0, sizeof(mCard));
    memset(mColor, 0, sizeof(mColor));
    mCard['A'] = 14;
    mCard['2'] = 2;mCard['3'] = 3;mCard['4'] = 4;mCard['5'] = 5;mCard['6'] = 6;mCard['7'] = 7;mCard['8'] = 8;mCard['9'] = 9;
    mCard['T'] = 10;
    mCard['J'] = 11;
    mCard['Q'] = 12;
    mCard['K'] = 13;
    mColor['C'] = 1;mColor['D'] = 2;mColor['H'] = 3;mColor['S'] = 4;
    mValue[1] = "straight-flush";
    mValue[2] = "four-of-a-kind";
    mValue[3] = "full-house";
    mValue[4] = "flush";
    mValue[5] = "straight";
    mValue[6] = "three-of-a-kind";
    mValue[7] = "two-pairs";
    mValue[8] = "one-pair";
    mValue[9] = "highest-card";

    while (scanf("%s %s %s %s %s", hand[0], hand[1], hand[2], hand[3], hand[4])!=EOF)
    {
        scanf("%s %s %s %s %s", deck[0], deck[1], deck[2], deck[3], deck[4]);

        g_best = 9;
        // 枚举所有集合
        for (int i = 1; i <= len; i++)
        {
            collection(0, 0, i, len, t);
        }

        printf("Hand: %s %s %s %s %s ", hand[0], hand[1], hand[2], hand[3], hand[4]);
        printf("Deck: %s %s %s %s %s ", deck[0], deck[1], deck[2], deck[3], deck[4]);
        printf("Best hand: %s\n", mValue[g_best]);
    }

    return 0;
}

struct node
{
    int card;
    int color;
};

int comp(const void* a,const void* b)
{
    return ((node*)a)->card > ((node*)b)->card;
}

// 计算牌型
int calc_card_value(char p[len][str_len])
{
    node card[len];
    memset(card, 0, sizeof(card));
    for (int i = 0; i < len; i++)
    {
        card[i].card = mCard[p[i][0]];
        card[i].color = mColor[p[i][1]];
    }

    qsort(card, 5, sizeof(node), comp);
    // straight-flush
    bool match = true;
    for (int i = 0; i < len-1; i++)
    {
        if (card[i].card + 1 != card[i+1].card)
        {
            match = false;
            break;
        }
    }
    if (!match && card[4].card == mCard['A'])
    {
        if (card[0].card == mCard['2'] && card[1].card == mCard['3'] &&
            card[2].card == mCard['4'] && card[3].card == mCard['5'])
            match = true;
    }

    for (int i = 0; i < len-1; i++)
    {
        if (card[i].color != card[i+1].color)
        {
            match = false;
            break;
        }
    }
    if (match)
        return 1;

    // four-of-a-kind
    match = true;
    int error = 0;
    for (int i = 0; i < len-1; i++)
    {
        if (card[i].card != card[i+1].card)
        {
            if (i != 0 && i != len-1)
            {
                match = false;
                break;
            }
            error++;
        }
    }
    if (error >= 2)
        match= false;
    if (match)
        return 2;

    //full-house
    match = false;
    if (card[0].card == card[1].card && card[3].card == card[4].card)
    {
        if ((card[1].card == card[2].card && card[2].card != card[3].card) ||
            (card[1].card != card[2].card && card[2].card == card[3].card))
            match = true;
    }
    if (match)
        return 3;

    //flush
    match = true;
    for (int i = 0; i < len-1; i++)
    {
        if (card[i].color != card[i+1].color)
        {
            match = false;
            break;
        }
    }
    if (match)
        return 4;

    //straight
    match = true;
    for (int i = 0; i < len-1; i++)
    {
        if (card[i].card + 1 != card[i+1].card)
        {
            match = false;
            break;
        }
    }
    if (!match && card[4].card == mCard['A'])
    {
        if (card[0].card == mCard['2'] && card[1].card == mCard['3'] &&
            card[2].card == mCard['4'] && card[3].card == mCard['5'])
            match = true;
    }
    if (match)
        return 5;

    //three-of-a-kind
    match = false;
    for (int i = 0; i < len-2; i++)
    {
        if (card[i].card == card[i+1].card && 
            card[i+1].card == card[i+2].card)
        {
            match = true;
            break;
        }
    }
    if (match)
        return 6;

    //two-pairs
    match = false;
    int pairs=0;
    for (int i = 0; i < len-1; i++)
    {
        if (card[i].card == card[i+1].card)
        {
            pairs++;
        }
    }
    if (match || pairs >= 2)
        return 7;

    //one-pair
    match = false;
    for (int i = 0; i < len-1; i++)
    {
        if (card[i].card == card[i+1].card)
        {
            match = true;
            break;
        }
    }
    if (match)
        return 8;

    // highest-card
    match = true;
    if (match)
        return 9;
}

// 换牌
int change_card(int num)
{
    memcpy(tcard, hand, sizeof(tcard));

    for (int i = 0; i < num; i++)
    {
        tcard[t[i]][0] = deck[i][0];
        tcard[t[i]][1] = deck[i][1];
    }

    return calc_card_value(tcard);
}

void collection(int start, int idx, int num, int max, int* p)
{
    if (idx == num)
    {
        g_best = min(g_best, change_card(num));
        return;
    }

    for (int i = start; i < max; i++)
    {
        p[idx] = i;
        collection(i+1, idx+1, num, max, p);
        p[idx] = -1;
    }

}