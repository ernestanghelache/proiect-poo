#include "RetetaBautura.h"

RetetaBautura::RetetaBautura() : Reteta(), fierbere(false) {
}

RetetaBautura::RetetaBautura(std::string numeReteta_) : Reteta(std::move(numeReteta_)), fierbere(false) {
}

void RetetaBautura::setFierbere(const bool fierbere_) {
    fierbere = fierbere_;
}

unsigned long long RetetaBautura::estimaretimp() {
    return instructiuni.size() * 2 + fierbere*10;
}
