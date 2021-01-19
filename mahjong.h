#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

class card
{
private:
    int type;
public:
    card(int tp); //构造新牌，类型参见 “readme.md”
    //~card();

    const int get_type()const;

    bool operator <(const card& a)const;

    void print()const;
};

class cardset
{
private:
    vector<card> cards;

public:
    //cardset();
    //virtual ~cardset();

    const int sum()const; //牌组的牌数
    void add(int tp); //将一张牌加入牌组（参数为牌的类型，类型参见 “readme.md”）
    void del(int tp); //从牌组里删除一张牌（参数为牌的类型，类型参见 “readme.md”）

    const bool check()const; //判断胡牌，如果胡牌返回 true。check之前请排序

    void arrange();//整理牌 或 排序

    vector<card> get_cardset()const;

    void print()const;
};
//AI 函数
int AI_play(const cardset& hand, const cardset& ring, const cardset& dust, const cardset& odust, const int& leftcard);
//返回选择的牌的type 如果已经和牌返回-1；
//hand为手牌，ring为鸣牌，dust为己方弃牌，odust为其他玩家弃牌，leftcard为牌堆余牌数
bool AI_crash(int type, const cardset& hand, const cardset& bright, const int& leftcard);
//返回是否碰type牌操作
//hand为手牌，bright为场上亮明的牌(不包括type），leftcard为牌堆余牌数
bool AI_dark_gang(int type, const cardset& hand, const cardset& bright, const int& leftcard);
//返回是否暗杠type牌操作（手牌中应恰好有3张type牌）
//hand为手牌，bright为场上亮明的牌(不包括type），leftcard为牌堆余牌数
bool AI_add_gang(int type,const cardset &hand,const cardset &bright,const int &leftcard);
//返回是否加杠type牌操作（己方鸣牌应恰有type的刻子，此处不作判断）
//hand为手牌，bright为场上亮明的牌(不包括type），leftcard为牌堆余牌数
int AI_eat(int type,const cardset &hand,const cardset &bright,const int &leftcard);
//返回是否吃type牌操作，1为吃前两张，2为吃前后各一张，3为吃后两张，0为不吃
//hand为手牌，bright为场上亮明的牌(不包括type），leftcard为牌堆余牌数
