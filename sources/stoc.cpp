#include "Stoc.h"

Stoc* Stoc::gasesteProdus(const std::string &numeProdus, std::vector<Stoc> &produse) {
    for (Stoc& it : produse) {
        if (it.getNume() == numeProdus) {
            return &it;
        }
    }
    return nullptr;
}

void Stoc::modificareCantitate(const int cantitate_) {
    cantitate = cantitate_;
}

void Stoc::inventar(std::vector<Stoc> &produs) {
    std::cout << "Atentie! Urmeaza sa introduceti cantitatea fiecarui produs din stoc, doriti sa continuati?\n1. Da\n2. Nu. ";
    int caz;
    std::cin >> caz;
    if (caz < 1 or caz > 2) {
        throw eroare_intrare("optiune invalida");
    }
    int cantitate_;
    for (Stoc& it : produs) {
        std::cout << it << "\nIntroduceti cantitatea corecta: ";
        std::cin >> cantitate_;
        it.modificareCantitate(cantitate_);
    }
}

void Stoc::addIngredient(std::string num, std::string um, std::vector<Stoc>& produse) {
    produse.emplace_back(num, 0, um);
}

void Stoc::addIngredientFull(std::string num, const int can, std::string um, std::vector<Stoc>& produse) {
    produse.emplace_back(num, can, um);
}

std::ostream& operator<<(std::ostream& os, const std::vector<Stoc>& stoc) {
    for (const Stoc &it : stoc)
        os << it << '\n';

    return os;
}
