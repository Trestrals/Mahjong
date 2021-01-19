<<<<<<< HEAD
#include"mahjong.h"

using namespace std;

char outmap[40][5] = { "  ", "1w", "2w", "3w", "4w", "5w", "6w", "7w", "8w", "9w",\
                     "  ", "1t", "2t", "3t", "4t", "5t", "6t", "7t", "8t", "9t",\
                     "  ", "1b", "2b", "3b", "4b", "5b", "6b", "7b", "8b", "9b",\
                     "  ", "do", "na", "xi", "be", "zh", "fa", "ba", "  ", "  " };

/*class card
{
private:
    int type;
public:
    
    //~card() {}*/
    card::card(int tp = 0) :type(tp) {} //构造新牌，类型参见 “readme.md”
    const int card::get_type()const
    {
        return type;
    }

    bool card::operator <(const card& a)const {
        return type < a.type;
    }

    void card::print()const
    {
        printf("这张牌是 %s(%d)\n", outmap[type], type);
    }
//};

/*class cardset
{
private:
    vector<card> cards;

public:
    //cardset(){};
    //~cardset() {}*/

    //const int cardset::sum()const; //牌组的牌数
    //void cardset::add(int tp); //将一张牌加入牌组（参数为牌的类型，类型参见 “readme.md”）
    //void cardset::del(int tp); //从牌组里删除一张牌（参数为牌的类型，类型参见 “readme.md”）

    //const cardset::bool check()const; //判断胡牌，如果胡牌返回 true。check之前请排序

    //void cardset::arrange();//整理牌 或 排序

    vector<card> cardset::get_cardset()const {
        return cards;
    }

    void cardset::print()const
    {
        vector<card>::const_iterator it = cards.begin();
        printf("这个牌组如下：\n");
        for (; it != cards.end(); ++it)
        {
            printf("%s(%d) ", outmap[it->get_type()], it->get_type());
        }
        printf("\n");
    }
//};

const int cardset::sum()const
{
    return cards.size();
}

void cardset::add(int tp)
{
    //printf("add %d\n",tp);
    card tmp(tp);
    cards.push_back(tmp);
    return;
}

void cardset::del(int tp)
{
    //printf("del %d\n",tp);
    vector<card>::iterator it = cards.begin();
    for (; it != cards.end(); ++it)
    {
        if(it->get_type() == tp)
        {
            cards.erase(it);
            break;
        }
    }
    return;
}

void cardset::arrange() {
    sort(cards.begin(), cards.end());
=======
#include "card.h"
#include "init.h"


using namespace std;

card::card(int tp) :type(tp) {}   //构造新牌，类型参见 “readme.md”

card::~card(){}

const int card::get_type()const
{
    return type;
}

bool card::operator <(const card& a)const {
    return type < a.type;
}

void card::print()const
{
    printf("这张牌是 %s(%d)\n", outmap[type], type);
}

card::card(const card &a){
    type = a.type;
>>>>>>> 上传最后成果
}
