#ifndef CARTEBUCATE_H
#define CARTEBUCATE_H

#include "Reteta.h"
#include <vector>

class CarteBucate {
    std::vector<Reteta> retete;

public:
    void adaugaReteta(const Reteta& reteta);
    Reteta* gasesteReteta(const std::string& numeReteta);

    friend std::ostream& operator<<(std::ostream& os, const CarteBucate& carte);
};

#endif

