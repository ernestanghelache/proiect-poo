#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "AbstractIngredient.h"
#include "Exceptii.h"
#include <iostream>
#include <string>

class Ingredient : public AbstractIngredient {
    std::string numeIngredient;
    int cantitate;
    std::string unitateMasura;
    double valoareNutritiva;

public:

    Ingredient();
    Ingredient(const std::string& numeIngredient_, int cantitate_, const std::string& unitateMasura_, double valoareNutritiva_);

    void afisare() const override;
    [[nodiscard]] AbstractIngredient* clone() const override;
    void modificareCantitate(int cantitate_) override;

    [[nodiscard]] int getCantitate() const override;
    [[nodiscard]] const std::string& getNumeIngredient() const override;
    [[nodiscard]] const std::string& getUnitateMasura() const override;
    [[nodiscard]] double getValoareNutritiva() const override;

    void setCantitate(int cantitate_);

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient);

    ~Ingredient() override;
};

#endif
