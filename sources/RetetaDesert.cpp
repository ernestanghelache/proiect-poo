#include "RetetaDesert.h"

RetetaDesert::RetetaDesert() : Reteta(), coacere(false) {
}

RetetaDesert::RetetaDesert(std::string numeReteta_) : Reteta(std::move(numeReteta_)), coacere(false) {
}

void RetetaDesert::setCoacere(const bool coacere_) {
    coacere = coacere_;
}

unsigned long long RetetaDesert::estimaretimp() {
    return instructiuni.size() * 10 + coacere * 60;
}
