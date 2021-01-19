#ifndef CARD_H
#define CARD_H

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

class card
{
private:
    int type;
public:
    card(int tp = 0); //构造新牌，类型参见 “readme.md”
    ~card();

<<<<<<< HEAD
=======
    card(const card &a);

>>>>>>> 上传最后成果
    const int get_type()const;

    bool operator <(const card& a)const;

    void print()const;
};


#endif // CARD_H
