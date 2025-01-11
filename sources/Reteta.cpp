#include "Reteta.h"

Reteta::Reteta(const Reteta& other) : numeReteta(other.numeReteta) {
    for (const auto& ingredient : other.ingrediente) {
        ingrediente.emplace_back(ingredient->clone());
    }
    instructiuni = other.instructiuni;
}

Reteta& Reteta::operator=(const Reteta& other) {
    if (this == &other) return *this;

    numeReteta = other.numeReteta;

    ingrediente.clear();
    for (const auto& ingredient : other.ingrediente) {
        ingrediente.emplace_back(ingredient->clone());
    }

    instructiuni = other.instructiuni;

    return *this;
}

void Reteta::addIngredient(const AbstractIngredient& ingredient) {
    ingrediente.emplace_back(ingredient.clone());
}
void Reteta::addInstructiune(const std::string& instructiune) {
    instructiuni.push_back(instructiune);
}

double Reteta::calculValoareNutritiva() const {
    double total = 0;
    for (const auto& ingredient : ingrediente) {
        total += ingredient->getValoareNutritiva() * ingredient->getCantitate();
    }
    return total;
}

const std::string& Reteta::getNumeReteta() const {
    return numeReteta;
}

std::ostream& operator<<(std::ostream& os, const Reteta& reteta) {
    os << "Reteta: " << reteta.numeReteta << "\nIngrediente:\n";
    for (const auto& ingredient : reteta.ingrediente) {
        ingredient->afisare(); // Apelăm metoda virtuală `afisare`
    }
    os << "Instructiuni:\n";
    for (const auto& instructiune : reteta.instructiuni) {
        os << "- " << instructiune << "\n";
    }
    return os;
}

int Reteta::contorRetete = 0;

Reteta::Reteta() : numeReteta{}, ingrediente{}, instructiuni{} {
    ++contorRetete;
}

Reteta::Reteta(const std::string& numeReteta_) : numeReteta(numeReteta_), ingrediente{}, instructiuni{} {
    if (numeReteta_.empty()) {
        throw RetetaException("Numele retetei nu poate fi gol.");
    }
}
const std::vector<std::unique_ptr<AbstractIngredient>>& Reteta::getIngrediente() const {
    return ingrediente;
}

Reteta::~Reteta() {
    --contorRetete;
}

int Reteta::getContorRetete() {
    return contorRetete;
}
