#include "ingredient.h"

Ingredient::Ingredient() : nume{}, cantitate{}, unitateMasura{} {}

Ingredient::Ingredient(std::string& nume_, int cantitate_, std::string& unitateMasura_)
    : nume{std::move(nume_)}, cantitate{cantitate_}, unitateMasura{std::move(unitateMasura_)} {}

Ingredient::Ingredient(const Ingredient& other)
    : nume{other.nume}, cantitate{other.cantitate}, unitateMasura{other.unitateMasura} {}

Ingredient& Ingredient::operator=(const Ingredient& other) {
    if (this == &other) {
        return *this;
    }
    nume = other.nume;
    cantitate = other.cantitate;
    unitateMasura = other.unitateMasura;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Ingredient& produs) {
    os << produs.nume << ": " << produs.cantitate << produs.unitateMasura;
    return os;
}

void Ingredient::modificareCantitate(int cantitate_) {
    cantitate = cantitate + cantitate_;
}

int Ingredient::getCantitate() const {
    return cantitate;
}

const std::string& Ingredient::getNume() const {
    return nume;
}

const std::string& Ingredient::getUnitateMasura() const {
    return unitateMasura;
}

Ingredient::~Ingredient() {}

