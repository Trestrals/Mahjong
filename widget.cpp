#include "widget.h"
#include "ai.h"

#include <bits/stdc++.h>

#include "card.h"
#include "cardui.h"
#include "cardset.h"
#include "cardsetui.h"
#include "init.h"
#include "playerinfoui.h"

#include <QDebug>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/prefix1/image/majsoul.mp3"));
    //music->setVolume(50);
    music->play();
    //music.setMedia(QUrl::fromLocalFile("qrc:/new/prefix2/image/backmedia.mp3"));

    //music.play();

    QColor cl(34, 124, 85);
    pal.setColor(QPalette::Background, cl);
    setAutoFillBackground(true);
    setPalette(pal);

    setWindowTitle("简易人机麻将");

   // qDebug()<<"START";
    nowplayer = 3;

    card_all = new cardset();
    card_all->init_total();
    card_all->randsort();

   // qDebug()<<"CARD_ALL_SET";

    pl[0] = new player("Player");
    pl[0]->get_cardfixed()->print();

    //qDebug()<<"PLAYER0_ADD";
    pl[1] = new player("Computer_1");
    pl[2] = new player("Computer_2");
    pl[3] = new player("Computer_3");
   // emit phrase_cardout_end_signal();

    //qDebug()<<"PLAYER_ADDED";

    for(int i = 0; i < 4; i++){
        pl[i]->card_addto_inhand(card_all, 13);
      //  qDebug()<<"CARD_ADD_TO_INHAND_DONE"<<i;
    }

    plu[0] = new playerinfoui(true, "Player", pl[0]->get_cardout(), pl[0]->get_cardin(), pl[0]->get_cardinhand(), pl[0]->get_cardfixed());
   // qDebug()<<"PLU0_SET";
    plu[1] = new playerinfoui(false, "Computer_1", pl[1]->get_cardout(), pl[1]->get_cardin(), pl[1]->get_cardinhand(), pl[1]->get_cardfixed());
    plu[2] = new playerinfoui(false, "Computer_2", pl[2]->get_cardout(), pl[2]->get_cardin(), pl[2]->get_cardinhand(), pl[2]->get_cardfixed());
    plu[3] = new playerinfoui(false, "Computer_3", pl[3]->get_cardout(), pl[3]->get_cardin(), pl[3]->get_cardinhand(), pl[3]->get_cardfixed());

    on_process = false;
    last_process = 9; //need_to be changed

   // for(int i = 0; i < 4; i++)
   //    qDebug()<<i<<"-> hide:"<<plu[i]->get_cardinhand()->is_hiden();


    wup_layout = new QHBoxLayout;
    card_remain = new QLabel;
    last_card_info = new QLabel;
    card_remain->setText("牌堆剩余牌数:" + QString::number(card_all->sum()));
    last_card_info->setText("上一张出牌；");
    last_card_pic = new cardui(38);

    wup_layout->addWidget(card_remain);
    wup_layout->addWidget(last_card_info);
    wup_layout->addWidget(last_card_pic);

    wdown_layout = new QGridLayout;
    //for(int i = 0; i < 4; i++)
    //    button[i] = new QPushButton();

    wmain_layout = new QVBoxLayout;
    wmain_layout->addLayout(wup_layout);
    for(int i = 3; i >= 0; i--)
        wmain_layout->addWidget(getui(i));
    wmain_layout->addLayout(wdown_layout);
    this->setLayout(wmain_layout);

    for(int i = 0; i < 4; i++)
       qDebug()<<i<<"-> hide:"<<plu[i]->get_cardinhand()->is_hiden();

    last_card = 38;
    //player_peng();

    //connect
    connect(this, SIGNAL(peng_signal()), this, SLOT(player_peng()));
    //end_of_connect

//debug_delete
    timer =  new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkProcess()));
    timer->start(100);
//end delete

//debug_begin
    /*cardset *hand = new cardset;
    int hd[11] = {3, 15, 16, 16, 16, 18, 25, 26, 27, 27, 1};
    for(int i = 0; i < 11; i++) hand->add(hd[i]);

    cardset *ring = new cardset;
    int ri[] =*/
//debug_end

}

Widget::~Widget()
{

}

playerinfoui *Widget::getui(int i){
    return plu[i];
}

bool Widget::check_end(){
    //undone
    return false;
}

bool Widget::next_player(){
    nowplayer++;
    nowplayer %= 4;
    return true;
}

/*bool Widget::gameset(){
    nowplayer = 0;
    pl[nowplayer]->card_addto_in(card_all);
    plu[nowplayer]->reset();
    plu[nowplayer]->set_permit(true);
    return true;
}*/

bool Widget::phrase_cardin(){
    qDebug()<<"cardin";
    pl[nowplayer]->card_addto_in(card_all);
    plu[nowplayer]->reset();

    on_process = false;

    return true;
}

bool Widget::phrase_cardprocess(){
    if(nowplayer != 0){
        cardset *hand = new cardset();
        hand->add_cardset(pl[nowplayer]->get_cardinhand());
        hand->add_cardset(pl[nowplayer]->get_cardin());

        cardset *odust = new cardset();
        for(int i = 0; i < 4; i++){
            if(i == nowplayer) continue;
            odust->add_cardset(pl[i]->get_cardout());
        }

        cardset *bright = new cardset();
        for(int i = 0; i < 4; i++)
            bright->add_cardset(pl[i]->get_cardfixed());

        //qDebug()<<"HAND PAIZU";
        //hand->print();

        int tp = AI_play(*hand, *bright, *pl[nowplayer]->get_cardout(), *odust, card_all->sum());
        pl[nowplayer]->get_cardinhand()->print();
        qDebug()<<"AI_TP"<<tp;
        printf("AI选择打出：%d\n", tp);
        phrase_cardout(tp);

        //emit phrase_cardprocess_end_signal(tp);
    }
    else plu[nowplayer]->set_permit(true);
    return true;
}

bool Widget::phrase_cardout(int type){
    pl[nowplayer]->card_in_to_inhand();
    pl[nowplayer]->card_inhand_to_out(type);
    plu[nowplayer]->reset();
    //emit phrase_cardout_end_signal();

    last_card = type;
    on_process = false;

    return true;
}

bool Widget::phrase_check_peng(int player_id){
    if(!pl[player_id]->get_cardinhand()->check_peng(last_card)){
        on_process = false; return false;
    }
    if(player_id != 0){
        cardset *cardsettmp = new cardset();
        for(int i = 0; i < 4; i++)
            cardsettmp->add_cardset(pl[i]->get_cardout());
        qDebug()<<"Player "<<player_id<<" card "<<pl[player_id]->get_cardinhand()->sum();

        if(AI_crash(last_card, *pl[player_id]->get_cardinhand_const(), *cardsettmp, card_all->sum()))
            return phrase_peng(player_id);
        else{
            qDebug()<<"Player "<<player_id<<" not PENG!"<<" card:"<<pl[player_id]->get_cardinhand()->sum();
            on_process = false; return false;
        }
    }
    else emit peng_signal();
    return true;
}

bool Widget::phrase_end(){
    return true;
    //undone
}

void Widget::checkProcess(){
    //qDebug()<<"CHECK";
    if(on_process) return;
    on_process = true;

    for(int i = 0; i < 4; i++){
        qDebug()<<"CKHU"<<i;
        if(pl[i]->check_hu()){
           qDebug()<<"PLAYER "<<i<<" WINS!"<<endl;
           timer->stop();
           win_end(i);
        }
    }

    if(card_all->sum() == 0) timer->stop(), ping_end();

    qDebug()<<"CHECK_IN player:"<<nowplayer<<"  process:"<<last_process<<"   card:"<<pl[nowplayer]->get_cardinhand()->sum()<<"   card_fixed:"<<pl[nowplayer]->get_cardfixed()->sum();
    //if(last_process != 1 && pl[nowplayer]->get_cardinhand()->sum() + pl[nowplayer]->get_cardfixed()->sum() > 13) timer->stop();

    card_remain->setText("牌堆剩余牌数:" + QString::number(card_all->sum()));
    last_card_pic ->reset(last_card);

    if(last_process == 1){//now 2
        last_process = 2;
        phrase_cardprocess();
    }

    else if(last_process == 2){//now 3
        last_process = 3;
        if(pl[player_nexk(1)]->check_to_hu(last_card))
           card_out_to_in(nowplayer, player_nexk(1), last_card);
        on_process = false;
    }

    else if(last_process == 3){//now 4
        last_process = 4;
        if(pl[player_nexk(2)]->check_to_hu(last_card))
           card_out_to_in(nowplayer, player_nexk(2), last_card);
        on_process = false;
    }

    else if(last_process == 4){//now 5
        last_process = 5;
        if(pl[player_nexk(3)]->check_to_hu(last_card))
           card_out_to_in(nowplayer, player_nexk(3), last_card);
        on_process = false;
    }

    else if(last_process == 5){ //now 6
        last_process = 6;
        phrase_check_peng(player_nexk(1));
        if(player_nexk(1) != 0) on_process = false;
    }

    else if(last_process == 6){ //now 7
        last_process = 7;
        phrase_check_peng(player_nexk(2));
        if(player_nexk(2) != 0) on_process = false;
    }

    else if(last_process == 7){ //now 8
        last_process = 8;
        phrase_check_peng(player_nexk(3));
        if(player_nexk(3) != 0) on_process = false;
    }

    else if(last_process == 8){
        last_process = 9;
        phrase_check_chi(player_nexk(1));
        if(player_nexk(1) != 0) on_process = false;
    }

    else if(last_process == 9){
        last_process = 1;
        next_player();
        qDebug()<<"cards_after_nextplayer:"<<pl[nowplayer]->get_cardinhand()->sum();
        phrase_cardin();
        qDebug()<<"cards_after_cardin:"<<pl[nowplayer]->get_cardinhand()->sum();
        on_process = false;
    }
}

bool Widget::card_out_to_inhand(int sender, int receiver, int tp){
    pl[sender]->card_out_del(tp);
    plu[sender]->reset();

    pl[receiver]->card_inhand_add(tp);
    plu[receiver]->reset();
}

bool Widget::card_out_to_in(int sender, int receiver, int tp){
    pl[sender]->card_out_del(tp);
    plu[sender]->reset();

    pl[receiver]->card_in_add(tp);
    plu[receiver]->reset();
}


bool Widget::phrase_peng(int player_id){
    qDebug()<<"PENG! "<<player_id;

    card_out_to_inhand(nowplayer, player_id, last_card);
    for(int i = 1; i <= 3; i++)
        pl[player_id]->card_inhand_to_fixed(last_card);
    //pl[player_id]->get_cardfixed()->print();
    plu[player_id]->reset();
    nowplayer = player_id;
    last_process = 1;
    on_process = false;
    return true;
}

void Widget::player_peng(){

    qDebug()<<"ssss";
    cardset *cardsettmp = new cardset();
    for(int i = 1; i <= 3; i++)
        cardsettmp->add(last_card);
    card_ck[0] = new cardsetui(cardsettmp, false);

    button[0] = new QPushButton();
    button[1] = new QPushButton();

    button[0]->setText("碰");
    button[1]->setText("取消");

    wdown_layout->addWidget(card_ck[0], 1, 1);
    wdown_layout->addWidget(button[0], 1, 2);
    wdown_layout->addWidget(button[1], 2, 2);

    connect(button[0], &QPushButton::clicked, this, &Widget::player_phrase_peng);
    connect(button[1], &QPushButton::clicked, this, &Widget::player_not_peng);

    qDebug()<<"ssss";

    //wmain_layout->addLayout(wdown_layout);
    update();

}

void Widget::player_phrase_peng(){
    //disconnect(button[0], &QPushButton::clicked, this, &Widget::player_phrase_peng);
   // disconnect(button[1], &QPushButton::clicked, this, &Widget::player_not_peng);
    down_layout_del();
    phrase_peng(0);

}

void Widget::player_not_peng(){
   // disconnect(button[0], &QPushButton::clicked, this, &Widget::player_phrase_peng);
   // disconnect(button[1], &QPushButton::clicked, this, &Widget::player_not_peng);
    down_layout_del();
    on_process = false;
}

void Widget::down_layout_del(){
    QLayoutItem *child;
    while(child = wdown_layout->takeAt(0))
    {
        if(child->widget()){
            child->widget()->setParent(NULL);
        }
        delete child;
    }

    update();
}

bool Widget::phrase_check_chi(int player_id){
    if(player_id != 0){
        cardset *cardsettmp = new cardset();
        for(int i = 0; i < 4; i++)
            cardsettmp->add_cardset(pl[i]->get_cardout());
        qDebug()<<"Player "<<player_id<<" card "<<pl[player_id]->get_cardinhand()->sum();

        int optmp = AI_eat(last_card, *pl[player_id]->get_cardinhand_const(), *cardsettmp, card_all->sum());
        if(optmp != 0)
            return phrase_chi(player_id, last_card - 3 + optmp);
        else{
            qDebug()<<"Player "<<player_id<<" not PENG!"<<" card:"<<pl[player_id]->get_cardinhand()->sum();
            on_process = false; return false;
        }
    }
    else{
        bool ok_chi = false;
        for(int i = 0; i < 3; i++){
            if(check_can_eat(player_id, last_card - i)) ok_chi = true;
        }
        if(ok_chi) return choise_player_chi();
        else{
            on_process = false;
            return false;
        }
    }
}

bool Widget::phrase_chi(int player_id, int first){
    card_out_to_inhand(nowplayer, player_id, last_card);
    for(int i =  0; i < 3; i++)
        pl[player_id]->card_inhand_to_fixed(i + first);
    plu[player_id]->reset();
    nowplayer = player_id;
    last_process = 1;
    on_process = false;
    return true;
}

bool Widget::check_can_eat(int player_id, int first){
    if(first > 30) return false;
    for(int i = 0; i < 3; i++){
        if(first + i == last_card) continue;
        if(pl[player_id]->get_cardinhand()->get_num(first + i) < 1) return false;
    }
    return true;
}

bool Widget::choise_player_chi(){
    int opnum = 0;
    for(int i = 2; i >= 0; i--){
        if(check_can_eat(0, last_card - i)){
            qDebug()<<"CAN_EAT!!!! "<<last_card - i;
            cardset *cardsettmp = new cardset();
            for(int j = 0; j < 3; j++)
                cardsettmp->add(last_card - i + j);
            card_ck[opnum] = new cardsetui(cardsettmp, false);
            button[opnum] = new QPushButton;
            button[opnum]->setText("吃");
            wdown_layout->addWidget(card_ck[opnum], opnum + 1, 1);
            wdown_layout->addWidget(button[opnum], opnum + 1, 2);

            connect(button[opnum], &QPushButton::clicked, this, [=](){player_chi(last_card - i);});
            opnum++;
        }
    }
    button[opnum + 1] = new QPushButton;
    button[opnum + 1]->setText("取消");
    connect(button[opnum + 1], &QPushButton::clicked, this, &Widget::player_not_chi);
    wdown_layout->addWidget(button[opnum + 1], opnum + 2, 2);
    update();
    return true;
}

void Widget::player_chi(int first){
    qDebug()<<"CHI!"<<endl;
    down_layout_del();
    phrase_chi(0, first);
}

void Widget::player_not_chi(){
    qDebug()<<"BUCHI!"<<endl;
    down_layout_del();
    on_process = false;
}

void Widget::win_end(int player_id){
    for(int i = 0; i < 4; i++){
       plu[i]->get_cardinhand()->set_hiden(false);
       plu[i]->get_cardin()->set_hiden(false);
       plu[i]->reset();
    }

    QMessageBox msgBox;
    msgBox.setText("游戏结束");
    msgBox.setInformativeText(pl[player_id]->get_name() + "胜利");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes) game_end();
}

void Widget::ping_end(){
    for(int i = 0; i < 4; i++){
       plu[i]->get_cardinhand()->set_hiden(false);
       plu[i]->get_cardin()->set_hiden(false);
       plu[i]->reset();
    }

    QMessageBox msgBox;
    msgBox.setText("游戏结束");
    msgBox.setInformativeText("和局");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes) game_end();
}

void Widget::game_end(){
    QApplication::exit(0);
    music->stop();
}
