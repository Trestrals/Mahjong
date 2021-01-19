#include "playerinfoui.h"
#include "cardsetui.h"
#include <QDebug>


playerinfoui::playerinfoui(bool isme, QString tp_name, cardset *tcard_out, cardset *tcard_in,
                       cardset *tcard_inhand, cardset *tcard_fixed, QWidget *parent)
{
    this->setParent(parent);

    label_aa = new QLabel;
    label_bb = new QLabel;
    //pcard_up_layout = new QHBoxLayout;
    pcard_widget = new QGLWidget;
    pcard_layout = new QVBoxLayout;
    pcard_down_layout = new QHBoxLayout;
    pmain_layout = new QHBoxLayout;

    p_name = new QLabel;
    p_name->setText(tp_name);
    p_name->setAlignment(Qt::AlignCenter);

    card_in = new cardsetui(tcard_in, !isme);
    card_out = new cardsetui(tcard_out, false);
    card_inhand = new cardsetui(tcard_inhand, !isme);qDebug()<<isme<<" "<<card_inhand->is_hiden();
    card_fixed = new cardsetui(tcard_fixed, false);

    pcard_down_layout->addWidget(card_fixed);
    pcard_down_layout->addWidget(card_inhand);
    pcard_down_layout->addWidget(card_in);


    pcard_layout->addWidget(card_out);
    pcard_layout->addLayout(pcard_down_layout);

    pmain_layout->addWidget(p_name);
    pmain_layout->addLayout(pcard_layout);
    this->setLayout(pmain_layout);

}

void playerinfoui::reset(){
    card_in->reset();
    card_out->reset();
    card_inhand->reset();
    card_fixed->reset();
    update();
}

void playerinfoui::set_permit(bool per){
    card_in->set_permit(per);
    card_inhand->set_permit(per);
}

cardsetui * playerinfoui::get_cardinhand(){
    return card_inhand;
}

cardsetui * playerinfoui::get_cardout(){
    return card_out;
}

cardsetui * playerinfoui::get_cardin(){
    return card_in;
}
