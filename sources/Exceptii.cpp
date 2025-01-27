#include "Exceptii.h"

const char *eroare::what() const noexcept {
    return mesaj.c_str();
}

eroare::eroare() = default;

eroare::eroare(std::string mesaj) : mesaj(std::move(mesaj)) {
}

eroare_reteta::eroare_reteta(const std::string &mesaj) : eroare("eroare reteta: " + mesaj) {
}

eroare_stoc::eroare_stoc(const std::string &mesaj) : eroare("eroare stoc: " + mesaj) {
}

eroare_intrare::eroare_intrare(const std::string &mesaj) : eroare("eroare intrare: " + mesaj) {
}
