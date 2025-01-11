#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>
#include <utility>

class RetetaException : public std::exception {
    std::string mesaj;

public:
    explicit RetetaException(std::string  mesaj_) : mesaj(std::move(mesaj_)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class IngredientException final : public std::exception {
    std::string mesaj;

public:
    explicit IngredientException(std::string  mesaj_) : mesaj(std::move(mesaj_)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

#endif

