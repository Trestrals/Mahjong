#ifndef CARDSETUI_H
#define CARDSETUI_H

#include <QWidget>
#include "cardset.h"
#include "cardui.h"
#include <vector>
#include <QVector>
#include <QHBoxLayout>

class cardsetui : public QWidget
{
    Q_OBJECT
public:
    //explicit cardsetui(QWidget *parent = nullptr);
    cardsetui(cardset* cardsettmp, bool ishiden = false);

    bool is_hiden();
    void reset();
    void set_permit(bool per);

    void set_hiden(bool hi);


private:
    cardset *cardseta;
    QVector<cardui> *cardsetuia;
    QHBoxLayout *cs_layout;

    bool ishiden;

signals:

};

#endif // CARDSETUI_H
