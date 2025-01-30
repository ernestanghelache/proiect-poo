#include "Reteta.h"
#include "Exceptii.h"
#include "Stoc.h"

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

void Reteta::modificare(std::vector<Stoc> &depozit) {
    int c;
    std::cout << "Ce doriti sa modificati?\n";
    std::cout << "1. Adaugati ingrediente.\n";
    std::cout << "2. Adaugati instructiuni.\n";
    std::cin >> c;
    std::cin.ignore();
    if (c != 1 and c != 2) {
        throw eroare_intrare("Eroare la alegerea modificarii ");
    }
    if (c == 1) {
        int nmr;
        std::cout << "Cate ingrediente doriti sa adaugati? ";
        std::cin >> nmr;
        std::cin.ignore();

        for (int i = 0; i < nmr; ++i) {
            std::string ingredient, unitateMasura;
            int cantitate;
            std::cout << "Introduceti numele ingredientului " << i + 1 << ": ";
            std::getline(std::cin, ingredient);

            std::cout << "Introduceti cantitatea pentru " << ingredient << ": ";
            std::cin >> cantitate;
            std::cin.ignore();

            int optiune;
            std::cout << "Selectati unitatea de masura pentru " << ingredient << '\n';
            std::cout << "1. g\n2. ml\n3. buc\n";
            std::cin >> optiune;
            std::cin.ignore();
            while (optiune < 1 or optiune > 3) {
                std::cout << "Optiune invalida.\n Introduceti o optiune: ";
                std::cin >> optiune;
                std::cin.ignore();
            }
            switch (optiune) {
                case 1: {
                    unitateMasura = "g";
                    break;
                }
                case 2: {
                    unitateMasura = "ml";
                    break;
                }
                case 3: {
                    unitateMasura = "buc";
                    break;
                }
                default: {
                    unitateMasura = "";
                    break;
                }
            }
            int nrCalorii;
            std::cout << "Introduceti numarul de calorii: ";
            std::cin >> nrCalorii;
            std::cin.ignore();
            addIngredient(ingredient, cantitate, unitateMasura, nrCalorii);
            if (Stoc::gasesteProdus(ingredient, depozit) == nullptr)
                Stoc::addIngredient(ingredient, unitateMasura, depozit);
            std::cout << "Ingredientul a fost adaugat cu succes!\n";
        }
    } else if (c == 2) {
        int nrInstructiuni;
        std::cout << "Cate instructiuni doriti sa adaugati? ";
        std::cin >> nrInstructiuni;
        std::cin.ignore();

        for (int i = 0; i < nrInstructiuni; ++i) {
            std::string instructiune;
            std::cout << "Introduceti instructiunea " << i + 1 << ": ";
            std::getline(std::cin, instructiune);

            addInstructiune(instructiune);
        }
    }
}

int Reteta::nr = 0;
