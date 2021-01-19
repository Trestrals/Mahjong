#ifndef INIT_H
#define INIT_H

#include <QString>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>


const char outmap[40][5] = { "  ", "1w", "2w", "3w", "4w", "5w", "6w", "7w", "8w", "9w",\
                             "  ", "1t", "2t", "3t", "4t", "5t", "6t", "7t", "8t", "9t",\
                             "  ", "1b", "2b", "3b", "4b", "5b", "6b", "7b", "8b", "9b",\
                             "  ", "do", "na", "xi", "be", "zh", "fa", "ba", "  ", "  " };

const QString urltext[60] = {
    "",
    ":/new/image_card/image/1w.png",
    ":/new/image_card/image/2w.png",
    ":/new/image_card/image/3w.png",
    ":/new/image_card/image/4w.png",
    ":/new/image_card/image/5w.png",
    ":/new/image_card/image/6w.png",
    ":/new/image_card/image/7w.png",
    ":/new/image_card/image/8w.png",
    ":/new/image_card/image/9w.png",

    "",
    ":/new/image_card/image/1t.png",
    ":/new/image_card/image/2t.png",
    ":/new/image_card/image/3t.png",
    ":/new/image_card/image/4t.png",
    ":/new/image_card/image/5t.png",
    ":/new/image_card/image/6t.png",
    ":/new/image_card/image/7t.png",
    ":/new/image_card/image/8t.png",
    ":/new/image_card/image/9t.png",

    "",
    ":/new/image_card/image/1b.png",
    ":/new/image_card/image/2b.png",
    ":/new/image_card/image/3b.png",
    ":/new/image_card/image/4b.png",
    ":/new/image_card/image/5b.png",
    ":/new/image_card/image/6b.png",
    ":/new/image_card/image/7b.png",
    ":/new/image_card/image/8b.png",
    ":/new/image_card/image/9b.png",

    "",
    ":/new/image_card/image/do.png",
    ":/new/image_card/image/na.png",
    ":/new/image_card/image/xi.png",
    ":/new/image_card/image/be.png",
    ":/new/image_card/image/zh.png",
    ":/new/image_card/image/fa.png",
    ":/new/image_card/image/ba.png",

    ":/new/image_card/image/backside.png",
    ":/new/image_card/image/side.png"
};

void setGame();

#endif // INIT_H
