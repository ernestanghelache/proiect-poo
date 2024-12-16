#ifndef STOC_H
#define STOC_H

#include <iostream>
#include <string>
#include <vector>
#include "ingredient.h"

class Stoc : public Ingredient {
    using Ingredient::Ingredient;

public:
    static Stoc* gasesteProdus(const std::string &numeProdus, std::vector<Stoc> &produse);
    void modificareCantitate(int cantitate_) override;
    static void inventar(std::vector<Stoc> &produs);
    static void addIngredient(std::string num, std::string um, std::vector<Stoc>& produse);
    static void addIngredientFull(std::string num, int can, std::string um, std::vector<Stoc>& produse);

    friend std::ostream& operator<<(std::ostream& os, const std::vector<Stoc>& stoc);
};

#endif