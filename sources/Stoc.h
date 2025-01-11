#ifndef STOC_H
#define STOC_H

#include "Ingredient.h"
#include <vector>
#include <memory>
#include <iostream>

class Stoc {
    std::vector<std::unique_ptr<AbstractIngredient>> produse;

public:
    Stoc();
    void adaugaIngredient(const AbstractIngredient& ingredient);
    [[nodiscard]] AbstractIngredient *gasesteProdus(const std::string &numeProdus) const;

    friend std::ostream& operator<<(std::ostream& os, const Stoc& stoc);
};

#endif
