#include "CarteBucate.h"

void CarteBucate::adaugaReteta(const Reteta& reteta) {
    retete.push_back(reteta);
}

Reteta* CarteBucate::gasesteReteta(const std::string& numeReteta) {
    for (auto& reteta : retete) {
        if (reteta.getNumeReteta() == numeReteta) {
            return &reteta;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const CarteBucate& carte) {
    for (const auto& reteta : carte.retete) {
        os << reteta << '\n';
    }
    return os;
}

