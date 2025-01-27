#include "Stoc.h"

Stoc::Stoc() : zi_expirare(0), luna_expirare(0), an_expirare(0) {
}

Stoc::Stoc(const std::string &numeIngredient_, const int cantitate_, const std::string &unitateMasura_, const int zi_,
           const int luna_, const int an_)
    : Produs(numeIngredient_, cantitate_, unitateMasura_), zi_expirare(zi_), luna_expirare(luna_), an_expirare(an_) {
}

Stoc::Stoc(const std::string &numeIngredient_, const int cantitate_, const std::string &unitateMasura_)
    : Produs(numeIngredient_, cantitate_, unitateMasura_), zi_expirare(0), luna_expirare(0), an_expirare(0) {
}

std::ostream &operator<<(std::ostream &os, const Stoc &stoc) {
    os << stoc.numeIngredient << ':' << stoc.cantitate << ' ' << stoc.unitateMasura
            << " Expira la " << stoc.zi_expirare << '/' << stoc.luna_expirare << '/' << stoc.an_expirare << '\n';
    return os;
}

Stoc *Stoc::gasesteProdus(const std::string &numeProdus, std::vector<Stoc> &produse) {
    for (Stoc &it: produse) {
        if (it.getNumeIngredient() == numeProdus) {
            return &it;
        }
    }
    return nullptr;
}

int Stoc::getAn() const {
    return an_expirare;
}

void Stoc::setExpirare(const int zi, const int luna, const int an) {
    zi_expirare = zi;
    luna_expirare = luna;
    an_expirare = an;
}

void Stoc::addIngredient(std::string &num, std::string &um, std::vector<Stoc> &produse) {
    produse.emplace_back(num, 0, um);
}

void Stoc::addIngredientFull(const std::string &num, int can, const std::string &um, int z, int l, int a,
                             std::vector<Stoc> &produse) {
    produse.emplace_back(num, can, um, z, l, a);
}

bool Stoc::expirat() const {
    const time_t now = time(nullptr);
    const tm *ltm = localtime(&now);

    const int anCurent = 1900 + ltm->tm_year;
    const int lunaCurenta = 1 + ltm->tm_mon;
    const int ziCurenta = ltm->tm_mday;

    if (an_expirare < anCurent) {
        return true;
    }
    if (an_expirare == anCurent && luna_expirare < lunaCurenta) {
        return true;
    }
    if (an_expirare == anCurent && luna_expirare == lunaCurenta && zi_expirare < ziCurenta) {
        return true;
    }
    return false;
}

bool Stoc::recomandat() const {
    return !expirat();
}
