#include "cardsetui.h"
#include <QDebug>

cardsetui::cardsetui(cardset *cardsettmp, bool ishidentmp){
    ishiden = ishidentmp;

    this->cardseta = cardsettmp;
    this->cardsetuia = new QVector<cardui>;

    vector<card> cardstmp = cardsettmp->get_cardset();
    for(vector<card>::iterator it = cardstmp.begin(); it != cardstmp.end(); ++it){
    //    qDebug()<<"now_card_id:"<<it->get_type()<<endl;
        cardsetuia->push_back(cardui(it->get_type(), ishidentmp));
    }

   // vector<card> *tmpp = &cardstmp;
   // delete tmpp;
    //delete &cardstmp; 如何删除？？？


    cs_layout = new QHBoxLayout;
    for(QVector<cardui>::iterator it = cardsetuia->begin(); it != cardsetuia->end(); ++it){
        //qDebug()<<"now_card_id:"<<it->get_type()<<endl;
        cs_layout->addWidget(it);
    }

    cs_layout->setSpacing(1);

    this->setLayout(cs_layout);
}

void cardsetui::reset(){
    vector<card> cardstmp = cardseta->get_cardset();
    cardsetuia->clear();
    //qDebug()<<"cardset_ishiden："<<ishiden;
    for(vector<card>::iterator it = cardstmp.begin(); it != cardstmp.end(); ++it){
    //    qDebug()<<"now_card_id:"<<it->get_type()<<endl;
        cardsetuia->push_back(cardui(it->get_type(), ishiden));
    }

    delete cs_layout;
    cs_layout = new QHBoxLayout;
    for(QVector<cardui>::iterator it = cardsetuia->begin(); it != cardsetuia->end(); ++it){
    //    qDebug()<<"now_card_id:"<<it->get_type()<<endl;
        cs_layout->addWidget(it);
    }
    cs_layout->setSpacing(1);

    this->setLayout(cs_layout);

    update();
}

void cardsetui::set_permit(bool per){
    for(QVector<cardui>::iterator it = cardsetuia->begin(); it != cardsetuia->end(); ++it)
        it->set_permit(per);
}

bool cardsetui::is_hiden(){
    return ishiden;
}

void cardsetui::set_hiden(bool hi){
    ishiden = hi;
}
