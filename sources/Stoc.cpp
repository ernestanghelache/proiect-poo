#include "Stoc.h"

Stoc::Stoc() : produse{} {}

void Stoc::adaugaIngredient(const AbstractIngredient& ingredient) {
    produse.emplace_back(ingredient.clone());
}

AbstractIngredient* Stoc::gasesteProdus(const std::string& numeProdus) const {
    for (auto& produs : produse) {
        if (produs->getNumeIngredient() == numeProdus) {
            return produs.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<AbstractIngredient>>& Stoc::getProduse() const {
    return produse;
}

std::ostream& operator<<(std::ostream& os, const Stoc& stoc) {
    os << "Stocul curent:\n";
    for (const auto& produs : stoc.produse) {
        produs->afisare();
    }
    return os;
}

