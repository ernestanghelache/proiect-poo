#include "sources/CarteBucate.h"
#include "sources/Stoc.h"
#include "sources/Ingredient.h"
#include <iostream>

void afisareMeniu() {
    std::cout << "\n=== Sistem de Management al Retetelor ===\n";
    std::cout << "1. Adauga reteta\n";
    std::cout << "2. Afiseaza retete\n";
    std::cout << "3. Verifica stoc pentru o reteta\n";
    std::cout << "4. Afiseaza stoc\n";
    std::cout << "5. Modifica stoc\n";
    std::cout << "6. Gateste reteta (actualizeaza stocul)\n";
    std::cout << "7. Calculeaza valoarea nutritiva\n"; // Adăugăm această linie
    std::cout << "8. Iesire\n";
    std::cout << "Alege o optiune: ";
}


void sistem(CarteBucate& carte, Stoc& stoc) {
    int optiune = 0;
    while (optiune != 7) {
        afisareMeniu();
        std::cin >> optiune;
        std::cin.ignore();

        switch (optiune) {
            case 1: {
                try {
                    std::string numeReteta;
                    std::cout << "Introduceti numele retetei: ";
                    std::getline(std::cin, numeReteta);

                    Reteta reteta(numeReteta);
                    int nrIngrediente;
                    std::cout << "Cate ingrediente are reteta? ";
                    std::cin >> nrIngrediente;
                    std::cin.ignore();for (int i = 0; i < nrIngrediente; ++i) {
                        std::string nume;
                        int cantitate;
                        std::string unitate;
                        double valoareNutritiva;

                        std::cout << "Nume ingredient: ";
                        std::getline(std::cin, nume);

                        if (const auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(nume))) {
                            unitate = produs->getUnitateMasura();
                            valoareNutritiva = produs->getValoareNutritiva();
                            std::cout << "Ingredientul \"" << nume << "\" există deja în stoc cu următoarele detalii:\n";
                            std::cout << "- Unitatea de masura: " << unitate << "\n";
                            std::cout << "- Valoarea nutritiva: " << valoareNutritiva << "\n";
                        } else {
                            int optiuneUnitate;
                            std::cout << "Selectati unitatea de masura:\n";
                            std::cout << "1. buc\n2. g\n3. ml\n";
                            std::cin >> optiuneUnitate;
                            std::cin.ignore();

                            switch (optiuneUnitate) {
                                case 1: unitate = "buc"; break;
                                case 2: unitate = "g"; break;
                                case 3: unitate = "ml"; break;
                                default: unitate = ""; break;
                            }

                            std::cout << "Valoare nutritiva (per unitate): ";
                            std::cin >> valoareNutritiva;
                            std::cin.ignore();

                            if (valoareNutritiva < 0) {
                                throw IngredientException("Valoarea nutritiva nu poate fi negativa.");
                            }

                            stoc.adaugaIngredient(Ingredient(nume, 0, unitate, valoareNutritiva));
                        }

                        std::cout << "Cantitate: ";
                        std::cin >> cantitate;
                        std::cin.ignore();

                        if (cantitate < 0) {
                            throw IngredientException("Cantitatea nu poate fi negativa.");
                        }

                        reteta.addIngredient(Ingredient(nume, cantitate, unitate, valoareNutritiva));
                    }

                    int nrInstructiuni;
                    std::cout << "Cate instructiuni are reteta? ";
                    std::cin >> nrInstructiuni;
                    std::cin.ignore();

                    for (int i = 0; i < nrInstructiuni; ++i) {
                        std::string instructiune;
                        std::cout << "Instructiunea " << i + 1 << ": ";
                        std::getline(std::cin, instructiune);
                        reteta.addInstructiune(instructiune);
                    }

                    carte.adaugaReteta(reteta);
                    std::cout << "Reteta a fost adaugata cu succes!\n";
                } catch (const IngredientException& e) {
                    std::cerr << "Eroare legata de ingrediente: " << e.what() << "\n";
                } catch (const RetetaException& e) {
                    std::cerr << "Eroare legata de retete: " << e.what() << "\n";
                } catch (const std::exception& e) {
                    std::cerr << "Eroare generala: " << e.what() << "\n";
                }
                break;
            }

            case 2: {
                try {
                    std::cout << "Retete disponibile:\n";
                    std::cout << carte;
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la afisarea retetelor: " << e.what() << "\n";
                }
                break;
            }
            case 3: {
                try {
                    std::string nume;
                    std::cout << "Introduceti numele retetei: ";
                    std::getline(std::cin, nume);

                    const Reteta* reteta = carte.gasesteReteta(nume);
                    if (!reteta) {
                        std::cout << "Reteta nu a fost gasita!\n";
                    } else {
                        bool realizabil = true;
                        std::cout << "Verificare stoc pentru reteta \"" << nume << "\":\n";
                        for (const auto& ingredient : reteta->getIngrediente()) {
                            const auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(ingredient->getNumeIngredient()));
                            if (!produs) {
                                std::cout << "- Lipseste: " << ingredient->getNumeIngredient() << " (" << ingredient->getCantitate() << " " << ingredient->getUnitateMasura() << ")\n";
                                realizabil = false;
                            } else if (produs->getCantitate() < ingredient->getCantitate()) {
                                std::cout << "- Mai aveti nevoie de: " << ingredient->getCantitate() - produs->getCantitate()
                                          << " " << ingredient->getUnitateMasura() << " de " << ingredient->getNumeIngredient() << "\n";
                                realizabil = false;
                            }
                        }

                        if (realizabil) {
                            std::cout << "Toate ingredientele sunt disponibile pentru reteta.\n";
                        }
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la verificarea stocului: " << e.what() << "\n";
                }
                break;
            }
            case 4: {
                try {
                    std::cout << "Stocul disponibil:\n";
                    std::cout << stoc;
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la afisarea stocului: " << e.what() << "\n";
                }
                break;
            }
            case 5: {
                try {
                    std::string nume;
                    std::cout << "Introduceti numele produsului de modificat: ";
                    std::getline(std::cin, nume);
                    auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(nume));
                    if (!produs) {
                        std::cout << "Produsul nu a fost gasit!\n";
                    } else {
                        int cantitateNoua;
                        std::cout << "Introduceti noua cantitate: ";
                        std::cin >> cantitateNoua;
                        std::cin.ignore();
                        produs->setCantitate(cantitateNoua);
                        std::cout << "Cantitatea a fost actualizata.\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la modificarea stocului: " << e.what() << "\n";
                }
                break;
            }
            case 6: {
                try {
                    std::string nume;
                    std::cout << "Introduceti numele retetei: ";
                    std::getline(std::cin, nume);

                    const Reteta* reteta = carte.gasesteReteta(nume);
                    if (!reteta) {
                        std::cout << "Reteta nu a fost gasita!\n";
                    } else {
                        bool realizabil = true;
                        for (const auto& ingredient : reteta->getIngrediente()) {
                            const auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(ingredient->getNumeIngredient()));
                            if (!produs || produs->getCantitate() < ingredient->getCantitate()) {
                                realizabil = false;
                                break;
                            }
                        }

                        if (realizabil) {
                            for (const auto& ingredient : reteta->getIngrediente()) {
                                auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(ingredient->getNumeIngredient()));
                                produs->modificareCantitate(-ingredient->getCantitate());
                            }
                            std::cout << "Reteta \"" << nume << "\" a fost gatita, iar stocul a fost actualizat.\n";
                        } else {
                            std::cout << "Nu aveti suficiente ingrediente pentru a gati aceasta reteta.\n";
                        }
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la gatirea retetei: " << e.what() << "\n";
                }
                break;
            }
            case 7: { // Calcul valoare nutritiva
                try {
                    std::string nume;
                    std::cout << "Introduceti numele retetei: ";
                    std::getline(std::cin, nume);

                    const Reteta* reteta = carte.gasesteReteta(nume);
                    if (!reteta) {
                            std::cout << "Reteta nu a fost gasita!\n";
                    } else {
                        double valoare = reteta->calculValoareNutritiva();
                        std::cout << "Valoarea nutritiva pentru reteta \"" << reteta->getNumeReteta() << "\": " << valoare << " calorii.\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Eroare la calculul valorii nutritive: " << e.what() << "\n";
                }
                break;
            }

            case 8: {
                std::cout << "La revedere!\n";
                break;
            }
            default: {
                std::cout << "Optiune invalida! Incercati din nou.\n";
            }
        }
    }
}



void exemple(CarteBucate& carte, Stoc& stoc) {

    stoc.adaugaIngredient(Ingredient("ou", 10, "buc", 72));
    stoc.adaugaIngredient(Ingredient("faina", 1000, "g", 3));
    stoc.adaugaIngredient(Ingredient("lapte", 500, "ml", 2));
    stoc.adaugaIngredient(Ingredient("zahar", 200, "g", 5));
    stoc.adaugaIngredient(Ingredient("apa minerala", 2000, "ml", 0));

    Reteta clatite("clatite");
    clatite.addIngredient(Ingredient("ou", 2, "buc", 72));
    clatite.addIngredient(Ingredient("faina", 250, "g", 3));
    clatite.addIngredient(Ingredient("lapte", 200, "ml", 2));
    clatite.addIngredient(Ingredient("apa minerala", 300, "ml", 0));
    clatite.addIngredient(Ingredient("zahar", 50, "g", 5));
    clatite.addInstructiune("Punem ingredientele intr-un bol si amestecam.");
    clatite.addInstructiune("Punem compozitia cu polonicul in tigaie si o distribuim uniform.");
    clatite.addInstructiune("Dupa ce se rumeneste pe margini, o intoarcem pe cealalta parte si o mai lasam un minut.");
    clatite.addInstructiune("Scoatem clatita pe o farfurie si procedam la fel pana terminam compozitia.");
    carte.adaugaReteta(clatite);

    stoc.adaugaIngredient(Ingredient("spaghete", 750, "g", 3));
    stoc.adaugaIngredient(Ingredient("parmezan", 500, "g", 4));
    stoc.adaugaIngredient(Ingredient("usturoi", 40, "g", 3));
    stoc.adaugaIngredient(Ingredient("ardei iute", 3, "buc", 30));
    stoc.adaugaIngredient(Ingredient("ulei de masline", 750, "ml", 2));

    Reteta paste("paste");
    paste.addIngredient(Ingredient("spaghete",500,"g",3));
    paste.addIngredient(Ingredient("parmezan",150,"g",4));
    paste.addIngredient(Ingredient("usturoi",50,"g",3));
    paste.addIngredient(Ingredient("ardei iute",1,"buc",30));
    paste.addIngredient(Ingredient("ulei de masline",75,"ml",2));
    paste.addInstructiune("Fierbem pastele conform instructiunilor de pe ambalaj.");
    paste.addInstructiune("Intr-o tigaie se adauga uleiul de masline, usturoiul taiat cubulete si ardeiul iute taiat rondele.");
    paste.addInstructiune("Adaugam pastele in tigaie si le lasam 2 minute");
    paste.addInstructiune("Punem in farfurii si adaugam parmezanul ras.");
    carte.adaugaReteta(paste);

    stoc.adaugaIngredient(Ingredient("carne tocata", 750, "g", 6));
    stoc.adaugaIngredient(Ingredient("ceapa", 500, "g", 4));
    stoc.adaugaIngredient(Ingredient("pesmet", 40, "g", 2));

    Reteta chiftele("chiftele");
    chiftele.addIngredient(Ingredient("carne tocata",600,"g",6));
    chiftele.addIngredient(Ingredient("ou",2,"buc",72));
    chiftele.addIngredient(Ingredient("ceapa",100,"g",4));
    chiftele.addIngredient(Ingredient("usturoi",75,"g",3));
    chiftele.addIngredient(Ingredient("pesmet",50,"g",2));
    chiftele.addInstructiune("Tocam marunt ceapa si usturoiul, apoi amestecam toate ingredientele intr-un bol si framantam bine.");
    chiftele.addInstructiune("Formam chiftelele rotunde si le prajim.");
    chiftele.addInstructiune("Scoatem chiftelele pe un servetel de hartie pentru a absorbi uleiul in exces.");
    carte.adaugaReteta(chiftele);
}
int main() {
    CarteBucate carte;
    Stoc stoc;

    exemple(carte, stoc);
    sistem(carte, stoc);

    std::cout << "Retetele din carte:\n" << carte;
    std::cout << "\nStocul disponibil:\n" << stoc;

    std::cout << "\nNumarul total de retete: " << Reteta::getContorRetete() << "\n";
    return 0;
}
