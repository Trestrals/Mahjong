#ifndef CARDUI_H
#define CARDUI_H

#include <QLabel>
#include <QWidget>
#include "card.h"

class cardui: public QLabel
{
public:
    cardui();
    cardui(card *cardtmp, bool ishiden = false);
    cardui(int tp, bool ishiden = false);
    cardui(const cardui &a);

    int get_type();
    bool is_hiden();
    bool get_click_permit();
    void set_permit(bool per);

    void operator=(const cardui &a)const;

    void reset(int tp);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    int type;
    bool ishiden;

    bool click_permit;
   // QLabel *cardlabel;

signals:
    void card_out_signal(int tp);
};

#endif // CARDUI_H
