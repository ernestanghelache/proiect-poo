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
    std::cout << "7. Iesire\n";
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
                // Adaugare reteta
                std::string numeReteta;
                std::cout << "Introduceti numele retetei: ";
                std::getline(std::cin, numeReteta);

                Reteta reteta(numeReteta);
                int nrIngrediente;
                std::cout << "Cate ingrediente are reteta? ";
                std::cin >> nrIngrediente;
                std::cin.ignore();

                for (int i = 0; i < nrIngrediente; ++i) {
                    std::string nume;
                    int cantitate;
                    std::string unitate;
                    double valoareNutritiva;

                    std::cout << "Nume ingredient: ";
                    std::getline(std::cin, nume);

                    std::cout << "Cantitate: ";
                    std::cin >> cantitate;

                    // Selectarea unitatii de masura
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

                    Ingredient ingredient(nume, cantitate, unitate, valoareNutritiva);
                    reteta.addIngredient(ingredient);

                    // Adaugam ingredientul in stoc daca nu exista (cu cantitate 0)
                    if (!stoc.gasesteProdus(nume)) {
                        stoc.adaugaIngredient(Ingredient(nume, 0, unitate, valoareNutritiva));
                    }
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
                break;
            }
            case 2: {
                std::cout << "Retetele disponibile:\n";
                std::cout << carte;
                break;
            }
            case 3: {
                std::string nume;
                std::cout << "Introduceti numele retetei: ";
                std::getline(std::cin, nume);

                Reteta* reteta = carte.gasesteReteta(nume);
                if (!reteta) {
                    std::cout << "Reteta nu a fost gasita!\n";
                } else {
                    bool realizabil = true;
                    std::cout << "Verificare stoc pentru reteta \"" << nume << "\":\n";
                    for (const auto& ingredient : reteta->getIngrediente()) {
                        auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(ingredient->getNumeIngredient()));
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
                break;
            }
            case 4: {
                std::cout << "Stocul disponibil:\n";
                std::cout << stoc;
                break;
            }
            case 5: {
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
                break;
            }
            case 6: {
                std::string nume;
                std::cout << "Introduceti numele retetei: ";
                std::getline(std::cin, nume);

                Reteta* reteta = carte.gasesteReteta(nume);
                if (!reteta) {
                    std::cout << "Reteta nu a fost gasita!\n";
                } else {
                    bool realizabil = true;
                    for (const auto& ingredient : reteta->getIngrediente()) {
                        auto* produs = dynamic_cast<Ingredient*>(stoc.gasesteProdus(ingredient->getNumeIngredient()));
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
                break;
            }
            case 7: {
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
    stoc.adaugaIngredient(Ingredient("Ou", 10, "buc", 72));
    stoc.adaugaIngredient(Ingredient("Faina", 1000, "g", 364));
    stoc.adaugaIngredient(Ingredient("Lapte", 500, "ml", 50));
    stoc.adaugaIngredient(Ingredient("Zahar", 200, "g", 387));
    stoc.adaugaIngredient(Ingredient("Apa minerala", 2000, "ml", 0));

    Reteta clatite("Clatite");
    clatite.addIngredient(Ingredient("Ou", 2, "buc", 72));
    clatite.addIngredient(Ingredient("Faina", 250, "g", 364));
    clatite.addIngredient(Ingredient("Lapte", 200, "ml", 50));
    clatite.addIngredient(Ingredient("Apa minerala", 300, "ml", 0));
    clatite.addIngredient(Ingredient("Zahar", 50, "g", 387));
    clatite.addInstructiune("Amestecati ingredientele.");
    clatite.addInstructiune("Coaceti compozitia in tigaie.");
    carte.adaugaReteta(clatite);

    Reteta gogosi("Gogosi");
    gogosi.addIngredient(Ingredient("Faina", 500, "g", 364));
    gogosi.addIngredient(Ingredient("Zahar", 100, "g", 387));
    gogosi.addIngredient(Ingredient("Ou", 3, "buc", 72));
    gogosi.addIngredient(Ingredient("Apa minerala", 150, "ml", 0));
    gogosi.addInstructiune("Amestecati toate ingredientele.");
    gogosi.addInstructiune("Formati gogosi si prajiti-le.");
    carte.adaugaReteta(gogosi);

    Reteta omleta("Omleta");
    omleta.addIngredient(Ingredient("Ou", 4, "buc", 72));
    omleta.addIngredient(Ingredient("Lapte", 50, "ml", 50));
    omleta.addInstructiune("Bateti ouale cu laptele.");
    omleta.addInstructiune("Prajiti compozitia intr-o tigaie.");
    carte.adaugaReteta(omleta);
}
int main() {
    try {
        CarteBucate carte;
        Stoc stoc;

        exemple(carte, stoc);
        sistem(carte, stoc);

        std::cout << "Retetele din carte:\n" << carte;
        std::cout << "\nStocul disponibil:\n" << stoc;

        std::cout << "\nNumarul total de retete: " << Reteta::getContorRetete() << "\n";

    } catch (const RetetaException& e) {
        std::cerr << "Eroare legata de retete: " << e.what() << "\n";
    } catch (const IngredientException& e) {
        std::cerr << "Eroare legata de ingrediente: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Eroare generala: " << e.what() << "\n";
    }

    return 0;
}
