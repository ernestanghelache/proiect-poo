#include "RetetaBautura.h"

RetetaBautura::RetetaBautura() : Reteta(), alcoolic(false) {
}

RetetaBautura::RetetaBautura(std::string numeReteta_) : Reteta(std::move(numeReteta_)), alcoolic(false) {
}

void RetetaBautura::setAlcoolic(const bool alcoolic_) {
    alcoolic = alcoolic_;
}

unsigned long long RetetaBautura::estimaretimp() {
    return instructiuni.size() * 2;
}
