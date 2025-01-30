#ifndef STOC_H
#define STOC_H

#include "Produs.h"
#include <string>
#include <vector>
#include <iostream>

class Stoc final : public Produs {
    int zi_expirare;
    int luna_expirare;
    int an_expirare;

public:
    Stoc();

    Stoc(const std::string &numeIngredient_, int cantitate_, const std::string &unitateMasura_, int zi_,
         int luna_, int an_);

    Stoc(const std::string &numeIngredient_, int cantitate_, const std::string &unitateMasura_);

    friend std::ostream &operator<<(std::ostream &os, const Stoc &stoc);

    static Stoc *gasesteProdus(const std::string &numeProdus, std::vector<Stoc> &produse);

    [[nodiscard]] int getAn() const;

    void setExpirare(int zi, int luna, int an);

    static void addIngredient(std::string &num, std::string &um, std::vector<Stoc> &produse);

    static void addIngredientFull(const std::string &num, int can, const std::string &um, int z, int l, int a,
                                  std::vector<Stoc> &produse);

    [[nodiscard]] bool expirat() const;

    [[nodiscard]] bool recomandat() const override;

    ~Stoc() override = default;

    void verificareData();

    void modificare();
};

#endif
