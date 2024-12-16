#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <iostream>
#include <string>

class Ingredient {
    std::string nume;

protected:
    int cantitate;

private:
    std::string unitateMasura;

public:
    Ingredient();
    Ingredient(std::string& nume_, int cantitate_, std::string& unitateMasura_);
    Ingredient(const Ingredient& other);
    Ingredient& operator=(const Ingredient& other);

    friend std::ostream& operator<<(std::ostream& os, const Ingredient& produs);

    virtual void modificareCantitate(int cantitate_);

    [[nodiscard]] int getCantitate() const;
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getUnitateMasura() const;

    virtual ~Ingredient();
};

#endif