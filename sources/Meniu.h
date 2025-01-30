#ifndef MENIU_H
#define MENIU_H

#include <vector>
#include "CarteBucate.h"
#include "Stoc.h"

class Meniu {
    CarteBucate &carte = CarteBucate::getInstance();
    std::vector<Stoc> depozit;

    Meniu();

    void exemple();

    void modificaReteta();

    void afisStoc();

public:
    Meniu(const Meniu &) = delete;

    Meniu &operator=(const Meniu &) = delete;

    static Meniu &getInstance();

    int program();
};

#endif
