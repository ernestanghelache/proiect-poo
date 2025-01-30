#include "Meniu.h"
#include "Reteta.h"
#include "RetetaMancare.h"
#include "RetetaDesert.h"
#include "RetetaBautura.h"
#include "Exceptii.h"


Meniu::Meniu() = default;

Meniu &Meniu::getInstance() {
    static Meniu instance;
    return instance;
}

void Meniu::exemple() {
    auto milkshake = std::make_unique<RetetaBautura>("milkshake");
    milkshake->addIngredient("lapte", 250, "ml", 4);
    milkshake->addIngredient("inghetata de vanilie", 100, "g", 3);
    milkshake->addIngredient("miere", 10, "g", 3);
    milkshake->addInstructiune("Pune toate ingredientele intr-un blender.");
    milkshake->addInstructiune("Mixeaza pana devine cremos");
    carte.adaugaReteta(std::move(milkshake));


    Stoc::addIngredientFull("lapte", 1000, "ml", 20, 1, 2025, depozit);
    Stoc::addIngredientFull("inghetata de vanilie", 1000, "g", 25, 7, 2026, depozit);
    Stoc::addIngredientFull("miere", 750, "g", 29, 7, 2028, depozit);

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

void Meniu::modificaReteta() {
    std::cout << carte;
    std::string numeReteta;
    std::cout << "Introduceti numele retetei pe care doriti sa o modificati: ";
    std::cin.ignore();
    std::getline(std::cin, numeReteta);

    if (Reteta *reteta = carte.gasesteReteta(numeReteta); reteta == nullptr) {
        std::cout << "Reteta nu a fost gasita.\n";
    } else {
        reteta->modificare(depozit);
    }
}


void Meniu::afisStoc() {
    std::cout << "Produse expirate sau fara data de expirare:\n";
    for (Stoc &it: depozit) {
        it.verificareData();
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
        if (ingr == nullptr) {
            throw eroare_stoc("Produsul nu a fost gasit");
        }
        ingr->modificare();
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
                    carte.addReteta(depozit);
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
                    carte.afisRetete(depozit);
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
