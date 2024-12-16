
#ifndef CARTE_BUCATE_H
#define CARTE_BUCATE_H

#include <vector>
#include "reteta.h"

class CarteBucate : public Reteta {
public:
    static void adaugaReteta(Reteta &reteta, std::vector<Reteta>& carte);
    static Reteta* gasesteReteta(const std::string& numeReteta, std::vector<Reteta> &carte);
};

#endif