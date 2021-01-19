
#ifndef CARDSET_H
#define CARDSET_H

#include "card.h"


class cardset
{
private:
    vector<card> *cards;

<<<<<<< HEAD
=======
    bool no_need_arrange;

>>>>>>> 上传最后成果
public:
    cardset();
    ~cardset();

<<<<<<< HEAD
=======
    cardset(const cardset &a);

>>>>>>> 上传最后成果
    const int sum()const; //牌组的牌数
    void add(int tp); //将一张牌加入牌组（参数为牌的类型，类型参见 “readme.md”）
    void del(int tp); //从牌组里删除一张牌（参数为牌的类型，类型参见 “readme.md”）

    const bool check()const; //判断胡牌，如果胡牌返回 true。check之前请排序

    void arrange();//整理牌 或 排序

    vector<card> get_cardset()const;

    void print()const;
<<<<<<< HEAD
=======
    void cprint()const;
>>>>>>> 上传最后成果

    void randsort(); //undone
    card get_top(); //取出最上方的牌 undone
    card pop_top(); //删除最上方的牌 undone

<<<<<<< HEAD
    void distribute_top(cardset *receiver, int num); //将最上方 num 张牌分配到 receiver（大概是在发牌摸牌用的）
    void distribute_by_type(cardset *receiver, int tp); //将排队里 type 为 tp 的一张牌分配到 receiver

    void init_total(); //将牌组设置成一套完整的麻将牌

=======
    bool distribute_top(cardset *receiver, int num); //将最上方 num 张牌分配到 receiver（大概是在发牌摸牌用的）
    bool distribute_by_type(cardset *receiver, int tp); //将排队里 type 为 tp 的一张牌分配到 receiver

    void init_total(); //将牌组设置成一套完整的麻将牌

    int get_num(int type); //判断type有几张；
    bool check_chi(int type, int first); //判断从first开头的三张牌能不能吃type
    bool check_peng(int type); //判断type能不能碰
    bool add_cardset(cardset *cardsa); //将cards复制加入当前cardset（AI用）

    void set_no_arrange();
>>>>>>> 上传最后成果
};

#endif // CARDSET_H


