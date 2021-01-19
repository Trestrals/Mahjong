#ifndef PLAYER_H
#define PLAYER_H

#include "cardset.h"
#include "playerinfoui.h"

class player
{
public:
    player();
    player(string name_tmp);

    bool card_addto_in(cardset *from);                    //加入摸牌堆
    bool card_inhand_to_out(int type);                    //手牌到出牌堆
    bool card_in_to_inhand();                             //摸牌堆到手牌堆
    bool card_addto_inhand(cardset *from, int num);       //加入手牌堆
    bool card_out_to_fixed_by_type(int type);             //出牌堆加入固定堆（根据type）
    bool card_inhand_to_fixed(int type);                  //手牌加入固定堆（根据type）
    bool card_out_del(int tp);                            //删除out中的一张tp
    bool card_inhand_add(int tp);                         //加入inhand中一张tp
    bool card_in_add(int tp);                         //加入in中一张tp

    cardset * get_cardin();
    cardset * get_cardout();
    cardset * get_cardinhand();
    cardset * get_cardfixed();

    const cardset * get_cardinhand_const();

    bool check_to_hu(int tp); //加tp能不能胡
    bool check_hu();
   // bool card_hu_show(); //胡牌展示

    inline QString get_name(){
        return QString::fromStdString(name);
    }


private:
    string name;
    cardset *card_in;
    cardset *card_out;
    cardset *card_inhand;
    cardset *card_fixed;
};

#endif // PLAYER_H
