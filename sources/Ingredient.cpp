#include "Ingredient.h"

Ingredient::Ingredient() : numeIngredient{}, cantitate{0}, unitateMasura{}, valoareNutritiva{0.0} {}

Ingredient::Ingredient(const std::string& numeIngredient_, int cantitate_, const std::string& unitateMasura_, double valoareNutritiva_) {
    if (cantitate_ < 0) {
        throw IngredientException("Cantitatea nu poate fi negativa: " + std::to_string(cantitate_));
    }
    if (valoareNutritiva_ < 0) {
        throw IngredientException("Valoarea nutritiva nu poate fi negativa: " + std::to_string(valoareNutritiva_));
    }

    numeIngredient = numeIngredient_;
    cantitate = cantitate_;
    unitateMasura = unitateMasura_;
    valoareNutritiva = valoareNutritiva_;
}

void Ingredient::afisare() const {
    std::cout << numeIngredient << ": " << cantitate << unitateMasura
              << " (Valoare nutritiva: " << valoareNutritiva << " per unitate)\n";
}

AbstractIngredient* Ingredient::clone() const {
    return new Ingredient(*this);
}

void Ingredient::modificareCantitate(int cantitate_) {
    cantitate += cantitate_;
    if (cantitate < 0) {
        throw IngredientException("Cantitatea dupa modificare nu poate fi negativa.");
    }
}

int Ingredient::getCantitate() const {
    return cantitate;
}

const std::string& Ingredient::getNumeIngredient() const {
    return numeIngredient;
}

const std::string& Ingredient::getUnitateMasura() const {
    return unitateMasura;
}

double Ingredient::getValoareNutritiva() const {
    return valoareNutritiva;
}

void Ingredient::setCantitate(int cantitate_) {
    if (cantitate_ < 0) {
        throw IngredientException("Cantitatea setata nu poate fi negativa.");
    }
    cantitate = cantitate_;
}

std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
    os << ingredient.numeIngredient << ": " << ingredient.cantitate << ingredient.unitateMasura
       << " (Valoare nutritiva: " << ingredient.valoareNutritiva << " per unitate)";
    return os;
}

Ingredient::~Ingredient() = default;

