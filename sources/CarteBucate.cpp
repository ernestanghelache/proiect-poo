#include "CarteBucate.h"

CarteBucate &CarteBucate::getInstance() {
    static CarteBucate instance;
    return instance;
}

void CarteBucate::adaugaReteta(std::unique_ptr<Reteta> reteta) {
    retete.push_back(std::move(reteta));
}

Reteta *CarteBucate::gasesteReteta(const std::string &numeReteta) const {
    for (const std::unique_ptr<Reteta> &reteta: retete) {
        if (reteta->getnumeReteta() == numeReteta) {
            return reteta.get();
        }
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const CarteBucate &carte) {
    os << "Retete: \n";
    for (const std::unique_ptr<Reteta> &reteta: carte.retete) {
        os << "- " << reteta->getnumeReteta() << '\n';
    }
    return os;
}
