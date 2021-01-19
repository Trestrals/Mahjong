#include "player.h"
#include "playerinfoui.h"
#include <QDebug>

player::player()
{
    card_in = new cardset();
    card_out = new cardset();
    card_inhand = new cardset();
    card_fixed = new cardset();
    card_out->set_no_arrange();
    name = "";
}

player::player(string nametmp){
    card_in = new cardset();
    card_out = new cardset();
    card_inhand = new cardset();
    card_fixed = new cardset();
    name = nametmp;
    card_out->set_no_arrange();
 //   qDebug()<<"BEFORE_NEW_PUI";
 //   qDebug()<<"AFTER_NEW_PUI";
}

bool player::card_addto_in(cardset *from){
    if(from->distribute_top(card_in, 1)) return true;
    return false;
}   //加入摸牌堆

bool player::card_inhand_to_out(int type){
    if(card_inhand->distribute_by_type(card_out, type)) return true;
    return false;
}                //手牌到出牌堆

bool player::card_in_to_inhand(){
    if(card_in->distribute_top(card_inhand, 1)) return true;
    return false;
}                             //摸牌堆到手牌堆

bool player::card_addto_inhand(cardset *from, int num){
    if(from->distribute_top(card_inhand, num)) return true;
    return false;
}       //加入手牌堆

bool player::card_out_to_fixed_by_type(int type){
    if(card_out->distribute_by_type(card_fixed, type)) return true;
    return false;
}   //出牌堆加入固定堆（根据type）

bool player::card_inhand_to_fixed(int type){
    if(card_inhand->distribute_by_type(card_fixed, type)) return true;
    return false;
}                 //手牌加入固定堆（根据type）

cardset *player::get_cardin(){
    return card_in;
}

cardset *player::get_cardout(){
    return card_out;
}

cardset *player::get_cardfixed(){
    return card_fixed; //no delete
}

cardset *player::get_cardinhand(){
    return card_inhand;
}

const cardset *player::get_cardinhand_const(){
    cardset *cardsettmp = new cardset();
    cardsettmp->add_cardset(card_inhand);
    return cardsettmp;
}

bool player::check_to_hu(int tp){
    cardset *cardsettmp = new cardset();
    cardsettmp->add_cardset(card_inhand);
    cardsettmp->add_cardset(card_fixed);
    cardsettmp->add(tp);
    cardsettmp->arrange();
    bool ans  = cardsettmp->check();
    delete cardsettmp;
    return ans;
}

bool player::check_hu(){
    cardset *cardsettmp = new cardset();
    cardsettmp->add_cardset(card_inhand);
    cardsettmp->add_cardset(card_in);
    cardsettmp->arrange();
    //if(cardsettmp->sum() != 14){
    //    delete cardsettmp;
    //    return false;
    //}

    bool ans  = cardsettmp->check();
    delete cardsettmp;
    return ans;
}

bool player::card_out_del(int tp){
    card_out->del(tp);
}

bool player::card_inhand_add(int tp){
    card_inhand->add(tp);
}


bool player::card_in_add(int tp){
    card_in->add(tp);
}
