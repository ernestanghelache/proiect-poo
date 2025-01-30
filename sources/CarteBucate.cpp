#include "CarteBucate.h"

#include "Exceptii.h"
#include "RetetaBautura.h"
#include "RetetaDesert.h"
#include "RetetaMancare.h"
#include "Stoc.h"

CarteBucate &CarteBucate::getInstance() {
    static CarteBucate instance;
    return instance;
}

void CarteBucate::adaugaReteta(std::unique_ptr<Reteta> reteta) {
    retete.push_back(std::move(reteta));
}

Reteta *CarteBucate::gasesteReteta(const std::string &numeReteta) const {
    for (const std::unique_ptr<Reteta> &reteta: retete) {
        if (reteta->getnumeReteta() == numeReteta) {
            return reteta.get();
        }
    }
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const CarteBucate &carte) {
    os << "Retete: \n";
    for (const std::unique_ptr<Reteta> &reteta: carte.retete) {
        os << "- " << reteta->getnumeReteta() << '\n';
    }
    return os;
}

void CarteBucate::addReteta(std::vector<Stoc> &depozit) {
    std::string numeReteta, numeIngredient, unitateMasura, instructiune;
    int nrIngrediente, nrInstructiuni, cantitate, tip;
    std::cin.ignore();
    std::cout << "Tipuri retete\n1.Mancare\n2.Prajitura\n3. Bautura\nIntroduceti tipul retetei: ";
    std::cin >> tip;
    std::cin.ignore();
    if (tip != 1 and tip != 2 and tip != 3) {
        throw eroare_intrare("Optiune invalida la tipul retetei");
    }
    std::cout << "Introduceti numele retetei: ";
    std::getline(std::cin, numeReteta);
    std::unique_ptr<Reteta> nouaReteta;
    if (tip == 1) {
        nouaReteta = std::make_unique<RetetaMancare>(numeReteta);
    } else if (tip == 2) {
        nouaReteta = std::make_unique<RetetaDesert>(numeReteta);
    } else if (tip == 3) {
        nouaReteta = std::make_unique<RetetaBautura>(numeReteta);
    }
    bool veg;
    std::cout << "Reteta este vegana?\n0. Nu\n1. Da\nIntroduceti optiunea:";
    std::cin >> veg;
    std::cout << "Cate ingrediente are reteta? ";
    std::cin >> nrIngrediente;
    std::cin.ignore();

    int optiune;
    for (int i = 0; i < nrIngrediente; ++i) {
        std::cout << "Introduceti numele ingredientului " << i + 1 << ": ";
        std::getline(std::cin, numeIngredient);
        std::cout << "Introduceti cantitatea pentru " << numeIngredient << ": ";
        std::cin >> cantitate;
        std::cout << "Selectati unitatea de masura pentru " << numeIngredient << '\n';
        std::cout << "1. g\n";
        std::cout << "2. ml\n";
        std::cout << "3. buc\n";
        std::cin >> optiune;
        std::cin.ignore();
        if (optiune < 1 or optiune > 3) {
            throw eroare_intrare("optiune gresita");
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
        if (nouaReteta)
            nouaReteta->addIngredient(numeIngredient, cantitate, unitateMasura, nrCalorii);
        else
            throw eroare_reteta("Eroare la crearea retetei");
        if (Stoc::gasesteProdus(numeIngredient, depozit) == nullptr)
            Stoc::addIngredient(numeIngredient, unitateMasura, depozit);
    }

    std::cout << "Cate instructiuni are reteta? ";
    std::cin >> nrInstructiuni;
    std::cin.ignore();

    for (int i = 0; i < nrInstructiuni; ++i) {
        std::cout << "Introduceti instructiunea " << i + 1 << ": ";
        std::getline(std::cin, instructiune);
        if (nouaReteta)
            nouaReteta->addInstructiune(instructiune);
        else
            throw eroare_reteta("Eroare la crearea retetei.");
    }
    if (tip == 1) {
        std::cout << "Pentru aceasta reteta este nevoie de prajire?\n0. Nu\n1. Da\n Introduceti optiunea: ";
    }
    if (tip == 2) {
        std::cout << "Pentru aceasta reteta este nevoie de coacere?\n0. Nu\n1. Da\n Introduceti optiunea: ";
    }
    if (tip == 3) {
        std::cout << "Pentru aceasta reteta este nevoie de fierbere?\n0. Nu\n1. Da\n Introduceti optiunea: ";
    }
    bool opt;
    std::cin >> opt;
    if (auto *retetaMancare = dynamic_cast<RetetaMancare *>(nouaReteta.get())) {
        retetaMancare->setPrajire(opt);
    } else if (auto *retetaDesert = dynamic_cast<RetetaDesert *>(nouaReteta.get())) {
        retetaDesert->setCoacere(opt);
    } else if (auto *retetaBautura = dynamic_cast<RetetaBautura *>(nouaReteta.get())) {
        retetaBautura->setFierbere(opt);
    }

    adaugaReteta(std::move(nouaReteta));
}

void CarteBucate::afisRetete(std::vector<Stoc> &depozit) const {
    std::cout << "Exista " << Reteta::nr << ' ';
    std::cout << *this;
    std::cout << "\nDoriti sa vedeti o reteta?\n";
    std::cout << "1. Da\n";
    std::cout << "2. Nu\n";
    int caz;
    std::cin >> caz;
    std::cin.ignore();


    while (caz < 1 or caz > 2) {
        std::cout << "Optiune invalida. Introduceti o valoare:";
        std::cin >> caz;
        std::cin.ignore();
    }

    if (caz == 1) {
        std::string nume;
        std::cout << "Ce reteta doriti sa vedeti?\n";
        std::getline(std::cin, nume);

        if (Reteta *reteta = gasesteReteta(nume); reteta == nullptr) {
            throw eroare_reteta("Reteta aleasa nu exista.");
        } else {
            std::cout << *reteta;
            std::cout << "Reteta va dura aproximativ " << reteta->estimaretimp() << " minute.\n";
            bool realizabil = true;
            bool recomand = true;
            const std::vector<Ingredient> &ingredients = reteta->getIngrediente();
            for (const Ingredient &ingredient: ingredients) {
                if (const Stoc *stoc = Stoc::gasesteProdus(ingredient.getNumeIngredient(), depozit);
                    stoc == nullptr) {
                    realizabil = false;
                } else {
                    if (ingredient.recomandat() == false or stoc->recomandat() == false) {
                        recomand = false;
                    }
                    if (stoc->getCantitate() < ingredient.getCantitate()) {
                        std::cout << "Mai aveti nevoie de " << ingredient.getCantitate() - stoc->getCantitate() <<
                                ingredient.getUnitateMasura() << ' ' << ingredient.getNumeIngredient() <<
                                " pentru a gati reteta.\n";
                        realizabil = false;
                    }
                }
            }

            if (recomand == false)
                std::cout << "Reteta nu este recomandata\n";
            else
                std::cout << "Reteta este recomandata\n";
            if (realizabil) {
                std::cout << "\nAti gatit reteta?\n1. Da\n2. Nu\n";
                int optiune;
                std::cin >> optiune;

                if (optiune != 1 and optiune != 2) {
                    throw eroare_intrare("Optiune invalida.");
                }

                if (optiune == 1) {
                    for (const Ingredient &ingredient: ingredients) {
                        Stoc::gasesteProdus(ingredient.getNumeIngredient(), depozit)->modificareCantitate(
                            -ingredient.getCantitate());
                    }
                    std::cout << "Cantitatile au fost actualizate.\n";
                }
            }
        }
    }
}
