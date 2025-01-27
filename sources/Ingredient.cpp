#include "Ingredient.h"

Ingredient::Ingredient() : calorii{} {
}

Ingredient::Ingredient(const std::string &numeIngredient_, const int cantitate_, const std::string &unitateMasura_,
                       const int calorii_)
    : Produs(numeIngredient_, cantitate_, unitateMasura_), calorii(calorii_) {
}

Ingredient &Ingredient::operator=(const Ingredient &other) {
    if (this == &other) {
        return *this;
    }
    numeIngredient = other.numeIngredient;
    cantitate = other.cantitate;
    calorii = other.calorii;
    unitateMasura = other.unitateMasura;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Ingredient &ingredient) {
    os << ingredient.numeIngredient << ": " << ingredient.cantitate << ingredient.unitateMasura << "; "
            << ingredient.calorii * ingredient.cantitate << " calorii";
    return os;
}

bool Ingredient::recomandat() const {
    return calorii <= 50;
}
