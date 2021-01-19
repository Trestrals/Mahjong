#include "widget.h"
#include "debug.cpp"
#include "card.h"
#include "cardset.h"
#include <QDebug>

#include <iostream>
#include <QApplication>

namespace qqqwq{

    Widget *Main_widget;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w(0);
    qqqwq::Main_widget = &w;
    w.setFixedSize(800, 1000);
    w.show();
    return a.exec();
}
