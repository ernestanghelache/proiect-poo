#include "Produs.h"

Produs::Produs() : cantitate{} {
}

Produs::Produs(std::string numeIngredient_, const int cantitate_, std::string unitateMasura_)
    : numeIngredient{std::move(numeIngredient_)}, cantitate{cantitate_}, unitateMasura{std::move(unitateMasura_)} {
}


void Produs::modificareCantitate(const int cantitate_) {
    cantitate = cantitate + cantitate_;
}


int Produs::getCantitate() const {
    return cantitate;
}


void Produs::setCantitate(const int cantitate_) {
    cantitate = cantitate_;
}


const std::string &Produs::getNumeIngredient() const {
    return numeIngredient;
}


const std::string &Produs::getUnitateMasura() const {
    return unitateMasura;
}
