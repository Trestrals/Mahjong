#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cardui.h"
#include "cardsetui.h"
#include "playerinfoui.h"
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "player.h"
#include <QTimer>
#include <QGridLayout>
#include <QPushButton>
#include <QMediaPlayer>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    playerinfoui *getui(int i);

    bool check_end();

    //bool gameset();
    bool next_player();

    bool phrase_cardin();
    bool phrase_cardprocess();
    bool phrase_cardout(int type);
    bool phrase_check_peng(int player_id);
    bool phrase_end();
    bool phrase_peng(int player_id);
    bool phrase_check_chi(int player_id);
    bool phrase_chi(int player_id, int first); //从first开始吃
    bool check_can_eat(int player_id, int first);
    bool choise_player_chi();

    bool card_out_to_inhand(int sender, int receiver, int tp);
    bool card_out_to_in(int sender, int receiver, int tp);
   // bool card_hu_show(int num);   //num号选手的胡牌展示

    inline int player_nexk(int k){
        return (nowplayer + k) % 4;
    }

    void down_layout_del();


private:
    player *pl[4];
    playerinfoui *plu[4];
    cardset *card_all;

    int nowplayer;
    bool on_process;
    int last_process;
    int last_card;

    QVBoxLayout *wmain_layout;
    QTimer *timer;

    QGridLayout *wdown_layout;
    cardsetui *card_ck[3];
    QPushButton *button[4];

    QHBoxLayout *wup_layout;
    QLabel *card_remain;
    QLabel *last_card_info;
    cardui *last_card_pic;

    void win_end(int player_id);
    void ping_end();
    QPalette pal;

    QMediaPlayer *music;



signals:
    void peng_signal();

public slots:
    void checkProcess();
    void player_peng();
    void player_phrase_peng();
    void player_not_peng();
    void player_chi(int first);
    void player_not_chi();
    void game_end();


};
#endif // WIDGET_H
