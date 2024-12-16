#include "CarteBucate.h"
#include "Reteta.h"

void CarteBucate::adaugaReteta(Reteta &reteta, std::vector<Reteta>& carte) {
    carte.emplace_back(reteta);
}

Reteta* CarteBucate::gasesteReteta(const std::string& numeReteta, std::vector<Reteta> &carte) {
    for (Reteta& reteta : carte) {
        if (reteta.getnumeReteta() == numeReteta) {
            return &reteta;
        }
    }
    return nullptr;
}
