#include "Reteta.h"

Reteta::Reteta() : vegan{false} {
}

Reteta::Reteta(std::string numeReteta_) : numeReteta{std::move(numeReteta_)}, vegan{false} {
    nr++;
}

Reteta::Reteta(std::string &numeReteta_, const std::vector<Ingredient> &ingrediente_,
               const std::vector<Instructiune> &instructiuni_, bool vegan_)
    : numeReteta{std::move(numeReteta_)}, ingrediente{ingrediente_}, instructiuni{instructiuni_}, vegan{vegan_} {
    nr++;
}

Reteta &Reteta::operator=(const Reteta &other) {
    if (this == &other) {
        return *this;
    }
    numeReteta = other.numeReteta;
    ingrediente = other.ingrediente;
    instructiuni = other.instructiuni;
    return *this;
}

void Reteta::addIngredient(const std::string &num, int can, const std::string &um, int cal) {
    ingrediente.emplace_back(num, can, um, cal);
}

void Reteta::addInstructiune(std::string instruct) {
    instructiuni.emplace_back(instruct);
}

std::ostream &operator<<(std::ostream &os, const Reteta &reteta) {
    os << "Nume reteta: " << reteta.numeReteta << '\n';
    os << (reteta.vegan ? "Este vegana." : "Nu este vegana.") << '\n';
    os << "Ingrediente:" << '\n';
    for (const Ingredient &it: reteta.ingrediente)
        os << it << '\n';

    os << "Instructiuni:\n";
    for (const Instructiune &it: reteta.instructiuni)
        os << "- " << it << '\n';

    return os;
}

void Reteta::setVegan(const bool vegan_) {
    vegan = vegan_;
}

const std::string &Reteta::getnumeReteta() const {
    return numeReteta;
}

const std::vector<Ingredient> &Reteta::getIngrediente() const {
    return ingrediente;
}
