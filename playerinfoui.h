#ifndef PLAYERINFOUI_H
#define PLAYERINFOUI_H

#include <QWidget>
#include <QGLWidget>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include "cardsetui.h"
#include "cardui.h"

class playerinfoui : public QWidget
{
    Q_OBJECT
public:
    playerinfoui(bool isme, QString tp_name, cardset *tcard_out, cardset *tcard_in,
                 cardset *tcard_inhand, cardset *tcard_fixed, QWidget *parent = nullptr);

    QGLWidget *wid1;

    void reset();
    void set_permit(bool per);

    cardsetui *get_cardinhand();
    cardsetui *get_cardout();
    cardsetui *get_cardin();


private:
    QLabel *p_name;
    cardsetui *card_out;       //出牌牌组
    cardsetui *card_in;        //摸牌牌组
    cardsetui *card_inhand;    //手牌牌组
    cardsetui *card_fixed;     //固定牌组（吃/碰/杠）

    QHBoxLayout *pmain_layout;         //主界面布局
    QVBoxLayout *pcard_layout;         //牌组整体布局
    QHBoxLayout *pcard_down_layout;    //下方牌组布局
  //  QHBoxLayout *pcard_up_layout;

    QLabel *label_aa;
    QLabel *label_bb;

    QGLWidget *pcard_widget;


signals:

};

#endif // PLAYERINFO_H
