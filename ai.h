#ifndef AI_H
#define AI_H

#include "cardset.h"

//AI 函数
//int AI_play(const cardset& hand, const cardset& ring, const cardset& dust, const cardset& odust, const int& leftcard);
int AI_play(const cardset &hand,const cardset &bright,const cardset &dust,const cardset &odust,const int &leftcard);
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

#endif // AI_H
