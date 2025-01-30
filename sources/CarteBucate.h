#ifndef CARTE_BUCATE_H
#define CARTE_BUCATE_H

#include <vector>
#include <memory>
#include <string>
#include "Reteta.h"
#include "Stoc.h"

class CarteBucate {
    std::vector<std::unique_ptr<Reteta> > retete;

    CarteBucate() = default;

public:
    CarteBucate(const CarteBucate &) = delete;

    CarteBucate &operator=(const CarteBucate &) = delete;

    static CarteBucate &getInstance();

    void adaugaReteta(std::unique_ptr<Reteta> reteta);

    [[nodiscard]] Reteta *gasesteReteta(const std::string &numeReteta) const;

    friend std::ostream &operator<<(std::ostream &os, const CarteBucate &carte);

    void addReteta(std::vector<Stoc> &depozit);

    void afisRetete(std::vector<Stoc> &depozit) const;
};

#endif
