#include "RetetaMancare.h"

RetetaMancare::RetetaMancare() : Reteta(), prajire(false) {
}

RetetaMancare::RetetaMancare(std::string numeReteta_) : Reteta(std::move(numeReteta_)), prajire(false) {
}

void RetetaMancare::setPrajire(const bool prajire_) {
    prajire = prajire_;
}

unsigned long long RetetaMancare::estimaretimp() {
    return instructiuni.size() * 5 + prajire * 15;
}
