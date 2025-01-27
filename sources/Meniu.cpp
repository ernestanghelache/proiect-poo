#include "Meniu.h"
#include "Reteta.h"
#include "RetetaMancare.h"
#include "RetetaDesert.h"
#include "Exceptii.h"


Meniu::Meniu() = default;

Meniu &Meniu::getInstance() {
    static Meniu instance;
    return instance;
}

void Meniu::exemple() {
    auto clatite = std::make_unique<RetetaDesert>("clatite");
    clatite->addIngredient("ou", 3, "buc", 1);
    clatite->addIngredient("lapte", 250, "ml", 4);
    clatite->addIngredient("faina", 250, "g", 3);
    clatite->addIngredient("apa minerala", 300, "ml", 0);
    clatite->addIngredient("esenta de vanilie", 2, "ml", 1);
    clatite->addInstructiune("punem ingredientele intr-un bol si amestecam.");
    clatite->addInstructiune("punem compozitia cu polonicul in tigaie si o distribuim uniform.");
    clatite->addInstructiune(
        "dupa ce se rumeneste pe margini, o intoarcem pe cealalta parte si o mai lasam un minut.");
    clatite->addInstructiune("scoatem clatita pe o farfurie si procedam la fel pana terminam compozitia.");
    carte.adaugaReteta(std::move(clatite));

    Stoc::addIngredientFull("ou", 10, "buc", 20, 3, 2025, depozit);
    Stoc::addIngredientFull("lapte", 1000, "ml", 20, 1, 2025, depozit);
    Stoc::addIngredientFull("faina", 1000, "g", 17, 3, 2027, depozit);
    Stoc::addIngredientFull("apa minerala", 3000, "ml", 17, 10, 2029, depozit);
    Stoc::addIngredientFull("esenta de vanilie", 50, "ml", 13, 9, 2026, depozit);

    auto paste = std::make_unique<RetetaMancare>("paste");
    paste->addIngredient("spaghete", 500, "g", 3);
    paste->addIngredient("parmezan", 150, "g", 4);
    paste->addIngredient("usturoi", 50, "g", 2);
    paste->addIngredient("ardei iute", 1, "buc", 39);
    paste->addIngredient("ulei de masline", 75, "ml", 9);
    paste->addInstructiune("fierbem pastele conform instructiunilor de pe ambalaj.");
    paste->addInstructiune(
        "intr-o tigaie se adauga uleiul de masline, usturoiul taiat cubulete si ardeiul iute taiat rondele.");
    paste->addInstructiune("adaugam pastele in tigaie si le lasam 2 minute");
    paste->addInstructiune("punem in farfurii si adaugam parmezanul ras.");
    carte.adaugaReteta(std::move(paste));

    Stoc::addIngredientFull("spaghete", 750, "g", 16, 9, 2025, depozit);
    Stoc::addIngredientFull("parmezan", 500, "g", 9, 4, 2025, depozit);
    Stoc::addIngredientFull("usturoi", 40, "g", 7, 12, 2025, depozit);
    Stoc::addIngredientFull("ardei iute", 3, "buc", 8, 3, 2025, depozit);
    Stoc::addIngredientFull("ulei de masline", 750, "ml", 8, 4, 2026, depozit);

    auto chiftele = std::make_unique<RetetaMancare>("chiftele");
    chiftele->addIngredient("carne tocata", 600, "g", 3);
    chiftele->addIngredient("ou", 2, "buc", 1);
    chiftele->addIngredient("ceapa", 100, "g", 2);
    chiftele->addIngredient("usturoi", 75, "g", 2);
    chiftele->addIngredient("pesmet", 50, "g", 4);
    chiftele->addInstructiune(
        "tocam marunt ceapa si usturoiul, apoi amestecam toate ingredientele intr-un bol si framantam bine.");
    chiftele->addInstructiune("formam chiftelele rotunde si le prajim.");
    chiftele->addInstructiune("scoatem chiftelele pe un servetel de hartie pentru a absorbi uleiul in exces.");
    if (auto *retetaMancare = chiftele.get()) {
        retetaMancare->setPrajire(true);
    }
    carte.adaugaReteta(std::move(chiftele));

    Stoc::addIngredientFull("carne tocata", 1000, "g", 2, 2, 2025, depozit);
    Stoc::addIngredientFull("ceapa", 300, "g", 3, 2, 2025, depozit);
    Stoc::addIngredientFull("pesmet", 20, "g", 5, 2, 2025, depozit);

    auto salata = std::make_unique<RetetaMancare>("salata");
    salata->addIngredient("rosii", 500, "g", 1);
    salata->addIngredient("ceapa", 100, "g", 2);
    salata->addIngredient("ulei de masline", 20, "ml", 9);
    salata->addIngredient("sare", 5, "g", 0);
    salata->addInstructiune("se taie legumele si se pun intr-un bol.");
    salata->addInstructiune("se adauga uleiul si sarea.");
    salata->addInstructiune("se amesteca totul");
    if (auto *retetaMancare = salata.get()) {
        retetaMancare->setVegan(true);
    }
    carte.adaugaReteta(std::move(salata));

    Stoc::addIngredientFull("rosii", 1000, "g", 2, 3, 2025, depozit);
    Stoc::addIngredientFull("sare", 1000, "g", 5, 9, 2027, depozit);
}

void Meniu::addReteta() {
    std::string numeReteta, numeIngredient, unitateMasura, instructiune;
    int nrIngrediente, nrInstructiuni, cantitate, tip;
    std::cin.ignore();
    std::cout << "Tipuri retete\n1.Mancare\n2.Prajitura\nIntroduceti tipul retetei: ";
    std::cin >> tip;
    std::cin.ignore();
    if (tip != 1 and tip != 2) {
        throw eroare_intrare("Optiune invalida la tipul retetei");
    }
    std::cout << "Introduceti numele retetei: ";
    std::getline(std::cin, numeReteta);
    std::unique_ptr<Reteta> nouaReteta;
    if (tip == 1) {
        nouaReteta = std::make_unique<RetetaMancare>(numeReteta);
    } else {
        nouaReteta = std::make_unique<RetetaDesert>(numeReteta);
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
    bool opt;
    std::cin >> opt;
    if (auto *retetaMancare = dynamic_cast<RetetaMancare *>(nouaReteta.get())) {
        retetaMancare->setPrajire(opt);
    } else if (auto *retetaDesert = dynamic_cast<RetetaDesert *>(nouaReteta.get())) {
        retetaDesert->setCoacere(opt);
    }

    carte.adaugaReteta(std::move(nouaReteta));
}

void Meniu::modificaReteta() {
    std::cout << carte;
    std::string numeReteta;
    std::cout << "Introduceti numele retetei pe care doriti sa o modificati: ";
    std::cin.ignore();
    std::getline(std::cin, numeReteta);

    if (Reteta *reteta = carte.gasesteReteta(numeReteta); reteta == nullptr) {
        std::cout << "Reteta nu a fost gasita.\n";
    } else {
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
            int nr;
            std::cout << "Cate ingrediente doriti sa adaugati? ";
            std::cin >> nr;
            std::cin.ignore();

            for (int i = 0; i < nr; ++i) {
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
                reteta->addIngredient(ingredient, cantitate, unitateMasura, nrCalorii);
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

                reteta->addInstructiune(instructiune);
            }
        }
    }
}

void Meniu::afisRetete() {
    std::cout << "Exista " << Reteta::nr << ' ';
    std::cout << carte;
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

        if (Reteta *reteta = carte.gasesteReteta(nume); reteta == nullptr) {
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

void Meniu::afisStoc() {
    std::cout << "Produse expirate sau fara data de expirare:\n";
    for (Stoc &it: depozit) {
        int zi, luna, an;
        if (it.getAn() == 0) {
            std::cout << it << "\nProdusul are data expirarii neinitializata. Introduceti data expirarii.\nZiua: ";
            std::cin >> zi;
            std::cout << "\nLuna: ";
            std::cin >> luna;
            std::cout << "\nAnul: ";
            std::cin >> an;
            if (zi > 31 or an < 2025 or luna > 12)
                throw eroare_stoc("Data invalida");
            it.setExpirare(zi, luna, an);
            std::cout << "Data a fost modificata.\n";
        }
        if (it.expirat() == true) {
            std::cout << it << "\nProdusul a expirat. Introduceti noua data a expirarii.\nZiua: ";
            std::cin >> zi;
            std::cout << "\nLuna: ";
            std::cin >> luna;
            std::cout << "\nAnul: ";
            std::cin >> an;
            if (zi > 31 or an < 2025 or luna > 12)
                throw eroare_stoc("Data invalida");
            it.setExpirare(zi, luna, an);
            it.setCantitate(0);
            std::cout << "Data a fost modificata si produsele expirate sterse.\n";
        }
    }
    for (const Stoc &i: depozit)
        std::cout << i;
    std::cout << "Doriti sa modificati un produs?\n1. Da\n2. Nu\nIntroduceti o optiune: ";
    int optiune;
    std::cin >> optiune;
    if (optiune != 1 and optiune != 2) {
        throw eroare_intrare("Optiune invalida.");
    }
    std::cin.ignore();
    if (optiune == 1) {
        std::string produs;
        std::cout << "Ce produs doriti sa modificati?\n";
        std::getline(std::cin, produs);
        Stoc *ingr = Stoc::gasesteProdus(produs, depozit);
        while (ingr == nullptr) {
            throw eroare_stoc("Produsul nu a fost gasit");
        }
        int opt;
        std::cout << "Ce doriti sa modificati?\n1. Cantitatea\n2. Data expirarii\nIntroduceti optiunea: ";
        std::cin >> opt;
        if (opt != 1 and opt != 2) {
            throw eroare_intrare("Optiune invalida.");
        }
        if (opt == 1) {
            std::cout << "Introduceti noua cantitate pentru " << ingr->getNumeIngredient() << ':';
            int cantitate;
            std::cin >> cantitate;
            std::cin.ignore();
            ingr->setCantitate(cantitate);
        } else if (opt == 2) {
            int zi, luna, an;
            std::cout << "\nIntroduceti data expirarii.\nZiua: ";
            std::cin >> zi;
            std::cout << "\nLuna: ";
            std::cin >> luna;
            std::cout << "\nAnul: ";
            std::cin >> an;
            if (zi > 31 or an < 2025 or luna > 12)
                throw eroare_stoc("Data invalida");
            ingr->setExpirare(zi, luna, an);
            std::cout << "Data a fost modificata";
        }
    }
}

int Meniu::program() {
    int caz;
    exemple();
    while (true) {
        std::cout << "Sistem de management al retetelor\n\n";
        std::cout << "1. Adaugati o reteta.\n";
        std::cout << "2. Modificati o reteta.\n";
        std::cout << "3. Vedeti retetele.\n";
        std::cout << "4. Vedeti stocul.\n";
        std::cout << "5. Iesire.\n";
        std::cout << "\nIntroduceti optiunea:\n";
        std::cin >> caz;
        while (caz < 1 or caz > 5) {
            std::cout << "\nOptiune invalida. Introduceti o optiune:";
            std::cin >> caz;
            std::cin.ignore();
        }
        switch (caz) {
            case 1: {
                try {
                    addReteta();
                } catch (eroare &e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }

            case 2: {
                try {
                    modificaReteta();
                } catch (eroare &e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }

            case 3: {
                try {
                    afisRetete();
                } catch (eroare &e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }
            case 4: {
                try {
                    afisStoc();
                } catch (eroare &e) {
                    std::cout << e.what() << '\n';
                }
                break;
            }
            case 5: {
                return 0;
            }
            default: {
                std::cout << "Optiune invalida.\n";
                break;
            }
        }
    }
}
