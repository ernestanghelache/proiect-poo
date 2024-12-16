#include "Reteta.h"

Reteta::Reteta() : numeReteta{}, ingrediente{}, instructiuni{} {}

Reteta::Reteta(std::string numeReteta_) : numeReteta{std::move(numeReteta_)} {}

Reteta::Reteta(std::string& numeReteta_, const std::vector<Ingredient>& ingrediente_, const std::vector<Instructiune>& instructiuni_)
    : numeReteta{std::move(numeReteta_)}, ingrediente{ingrediente_}, instructiuni{instructiuni_} {}

Reteta::Reteta(const Reteta& other) : numeReteta{other.numeReteta}, ingrediente{other.ingrediente}, instructiuni{other.instructiuni} {}

Reteta& Reteta::operator=(const Reteta& other) {
    if (this == &other) {
        return *this;
    }
    numeReteta = other.numeReteta;
    ingrediente = other.ingrediente;
    instructiuni = other.instructiuni;
    return *this;
}

void Reteta::addIngredient(std::string num, int can, std::string um) {
    ingrediente.emplace_back(num, can, um);
}

void Reteta::addInstructiune(std::string instruct) {
    instructiuni.emplace_back(instruct);
}

std::ostream& operator<<(std::ostream& os, const Reteta& reteta) {
    os << "Nume reteta: " << reteta.numeReteta << '\n';
    os << "Ingrediente:" << '\n';
    for (const Ingredient& it : reteta.ingrediente)
        os << it << '\n';

    os << "Instructiuni:\n";
    for (const Instructiune& it : reteta.instructiuni)
        os << "- " << it << '\n';

    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Reteta>& carte) {
    os << "Retete: \n";
    for (const Reteta& reteta : carte) {
        os << "- " << reteta.getnumeReteta() << '\n';
    }
    return os;
}

const std::string& Reteta::getnumeReteta() const {
    return numeReteta;
}

const std::vector<Ingredient>& Reteta::getIngrediente() const {
    return ingrediente;
}

Reteta::~Reteta() {}