#include "cardui.h"
#include <QPainter>
#include <QPixmap>
#include "widget.h"
#include "init.h"
#include <QDebug>
#include "card.h"

namespace qqqwq{
    extern Widget *Main_widget;
}

cardui::cardui(card *cardtmp, bool ishiden)
{
    click_permit = false;
    //cardlabel = new QLabel(this);
//    this->type = cardtmp->get_type();
    if(!ishiden) this->setPixmap(QPixmap(urltext[this->type]));
    else this->setPixmap(urltext[38]);

//    this->setPixmap(QPixmap(urltext[this->type]));
}

cardui::cardui(int tp, bool ishiden):type(tp), ishiden(ishiden)
{
    click_permit = false;
    //qDebug()<<"card_ishiden "<<ishiden;
    if(!ishiden) this->setPixmap(QPixmap(urltext[this->type]));
    else this->setPixmap(urltext[38]);

//    this->setPixmap(QPixmap(urltext[this->type]));

}

cardui::cardui(const cardui &a)
{
    click_permit = false;
    type = a.type, ishiden = a.ishiden;
    if(!ishiden) this->setPixmap(QPixmap(urltext[this->type]));
    else this->setPixmap(urltext[38]);

//å    this->setPixmap(QPixmap(urltext[this->type]));
}

cardui::cardui(){ //ishiden = false
    type = 0;
    click_permit = false;
    ishiden = false;
//    this->setPixmap(QPixmap(urltext[this->type]));
}

void cardui::operator=(const cardui &a)const{
    cardui aa(a.type, a.ishiden);
}

int cardui::get_type(){
    return type;
}

bool cardui::is_hiden(){
    return ishiden;
}

bool cardui::get_click_permit(){
    return click_permit;
}

void cardui::set_permit(bool per){
    click_permit = per;
}

void cardui::mousePressEvent(QMouseEvent *event){
    qDebug()<<"CLICKCC";
    if(!click_permit) return;
    //card_out_signal(type);
    qqqwq::Main_widget->phrase_cardout(type);
}

void cardui::reset(int tp){
    type = tp;
    this->setPixmap(QPixmap(urltext[this->type]));
}
