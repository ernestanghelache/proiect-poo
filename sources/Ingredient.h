#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "Produs.h"
#include <string>
#include <iostream>

class Ingredient final : public Produs {
    int calorii;

public:
    Ingredient();

    Ingredient(const std::string &numeIngredient_, int cantitate_, const std::string &unitateMasura_,
               int calorii_);

    Ingredient &operator=(const Ingredient &other);

    friend std::ostream &operator<<(std::ostream &os, const Ingredient &ingredient);

    [[nodiscard]] bool recomandat() const override;

    ~Ingredient() override = default;
};

#endif
