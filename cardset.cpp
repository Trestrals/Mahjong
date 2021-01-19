#include "cardset.h"
#include "init.h"
#include <QDebug>
#include <bits/stdc++.h>

cardset::cardset(){
    cards = new vector<card>;
    no_need_arrange = false;
}

cardset::~cardset(){
    delete cards;
}

const int cardset::sum()const
{
    return cards->size();
}

void cardset::add(int tp)
{
    //printf("add %d\n",tp);
    card tmp(tp);
    cards->push_back(tmp);
    if(!no_need_arrange) arrange();
    return;
}

void cardset::del(int tp)
{
    //printf("del %d\n",tp);
    vector<card>::iterator it = cards->begin();
    for (; it != cards->end(); ++it)
    {
        if(it->get_type() == tp)
        {
            cards->erase(it);
            break;
        }
    }
    if(!no_need_arrange) arrange();
    return;
}

void cardset::arrange() {
    sort(cards->begin(), cards->end());
}


vector<card> cardset::get_cardset()const {//qDebug()<<cards->size()<<endl;
    vector<card> tmp_cards = *cards;
    return tmp_cards;
}

void cardset::print()const
{
    vector<card>::const_iterator it = cards->begin();
    qDebug()<<"这个牌组如下：\n";
    for (; it != cards->end(); ++it)
        qDebug()<<outmap[it->get_type()]<<"("<<it->get_type()<<")";
}

void cardset::cprint() const{
    vector<card>::const_iterator it = cards->begin();
    printf("这个牌组如下：\n");
    for (; it != cards->end(); ++it)
        printf("%s(%d), ", outmap[it->get_type()], it->get_type());
    printf("\n");
}

void cardset::randsort()
{
    //srand((uintptr_t)new (char));
    srand(time(0));
    //sleep(2000);
    std::random_shuffle(cards->begin(),cards->end());//请在之前srand好，此处直接调用random_shuffle函数
}

card cardset::get_top()//取出最上方的牌
{
    return *(cards->begin());
}

card cardset::pop_top()//删除最上方的牌
{
    if(cards->empty())return card(0);//空牌组没得删
    card __ret=*(cards->begin());
    cards->erase(cards->begin());
    return __ret;
}

bool cardset::distribute_top(cardset* receiver, int num) //将最上方 num 张牌分配到 receiver（大概是在发牌摸牌用的）
{
    if(cards->size()<num) return false;//没有num张牌，出现错误，不发了
    while(num-->0)
    {
        receiver->add(cards->begin()->get_type());
        cards->erase(cards->begin());//这个做法复杂度不是很优秀，不过数据量不大我就用最好写的了
    }
    return true;
}

bool cardset::distribute_by_type(cardset* receiver, int tp) //将排队里 type 为 tp 的一张牌分配到 receiver
{                                                   //楼上错字
    for(vector<card>::iterator i=cards->begin();i!=cards->end();++i)
    {
        if(i->get_type()==tp)
        {
            receiver->add(tp),
            cards->erase(i);//我认为分配是要删除原牌堆中的该牌
            return true;//成功找到
        }
    }
    return false;
}//建议用bool稍微改造一下，成功返回true，不成功返回false，方便debug

void cardset::init_total() //将牌组设置成一套完整的麻将牌
{
    cards->clear();
    for(int i=1;i<=37;i%10==9?i+=2:++i)
        for(int j=1;j<=4;++j)
            cards->push_back(card(i));

    //int cardset_num[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 1, 8, 8, 9, 9, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 11, 11, 12, 12, 13, 13, 14, 14
    //                    ,15 ,15, 16, 16, 1, 1, 2, 2, 7, 7, 8, 8, 9, 9, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
    //for(int i = 1;i <= 80; i++) cards->push_back(cardset_num[i]);
}


int cardset::get_num(int type){
    int sum = 0;
    for(vector<card>::iterator it = cards->begin(); it != cards->end(); ++it){
        if(it->get_type() == type) sum++;
    }
    return sum;
}

bool cardset::check_chi(int type, int first){
    for(int i = 0; i < 3; i++){
        if(i + first == type) continue;
        if(get_num(i + first) == 0) return false;
    }
    return true;
}

bool cardset::check_peng(int type){
    if(get_num(type) >= 2) return true;
    return false;
}

bool cardset::add_cardset(cardset *cardsa){
    for(vector<card>::iterator it = cardsa->cards->begin(); it != cardsa->cards->end(); ++it)
        cards->push_back(*it);
    return true;
}

cardset::cardset(const cardset &a){
    cards = new vector<card>;
    *cards = *a.cards;
    no_need_arrange = false;
}

void cardset::set_no_arrange(){
    no_need_arrange = true;
}
