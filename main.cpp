#include <iostream>
#include <string>
#include <vector>
#include "sources/ingredient.h"
#include "sources/reteta.h"
#include "sources/cartebucate.h"
#include "sources/stoc.h"
#include "sources/check.h"

void exemple(std::vector<Reteta> &carte, std::vector<Stoc> &depozit) {
    Reteta clatite("Clatite");
    clatite.addIngredient("Ou",3,"buc");
    clatite.addIngredient("Lapte",250,"ml");
    clatite.addIngredient("Faina",250,"g");
    clatite.addIngredient("Apa minerala",300,"ml");
    clatite.addIngredient("Esenta de vanilie",2,"ml");
    clatite.addInstructiune("Punem ingredientele intr-un bol si amestecam.");
    clatite.addInstructiune("Punem compozitia cu polonicul in tigaie si o distribuim uniform.");
    clatite.addInstructiune("Dupa ce se rumeneste pe margini, o intoarcem pe cealalta parte si o mai lasam un minut.");
    clatite.addInstructiune("Scoatem clatita pe o farfurie si procedam la fel pana terminam compozitia.");
    CarteBucate::adaugaReteta(clatite,carte);

    Stoc::addIngredientFull("Ou",10,"buc",depozit);
    Stoc::addIngredientFull("Lapte",1000,"ml",depozit);
    Stoc::addIngredientFull("Faina",1000,"g",depozit);
    Stoc::addIngredientFull("Apa minerala",3000,"ml",depozit);
    Stoc::addIngredientFull("Esenta de vanilie",50,"ml",depozit);


    Reteta paste("Paste");
    paste.addIngredient("Spaghete",500,"g");
    paste.addIngredient("Parmezan",150,"g");
    paste.addIngredient("Usturoi",50,"g");
    paste.addIngredient("Ardei iute",1,"buc");
    paste.addIngredient("Ulei de masline",75,"ml");
    paste.addInstructiune("Fierbem pastele conform instructiunilor de pe ambalaj.");
    paste.addInstructiune("Intr-o tigaie se adauga uleiul de masline, usturoiul taiat cubulete si ardeiul iute taiat rondele.");
    paste.addInstructiune("Adaugam pastele in tigaie si le lasam 2 minute");
    paste.addInstructiune("Punem in farfurii si adaugam parmezanul ras.");
    CarteBucate::adaugaReteta(paste,carte);

    Stoc::addIngredientFull("Spaghete",750,"g",depozit);
    Stoc::addIngredientFull("Parmezan",500,"g",depozit);
    Stoc::addIngredientFull("Usturoi",40,"g",depozit);
    Stoc::addIngredientFull("Ardei iute",3,"buc",depozit);
    Stoc::addIngredientFull("Ulei de masline",750,"ml",depozit);

    Reteta chiftele("Chiftele");
    chiftele.addIngredient("Carne tocata",600,"g");
    chiftele.addIngredient("Ou",2,"buc");
    chiftele.addIngredient("Ceapa",100,"g");
    chiftele.addIngredient("Usturoi",75,"g");
    chiftele.addIngredient("Pesmet",50,"g");
    chiftele.addInstructiune("Tocam marunt ceapa si usturoiul, apoi amestecam toate ingredientele intr-un bol si framantam bine.");
    chiftele.addInstructiune("Formam chiftelele rotunde si le prajim.");
    chiftele.addInstructiune("Scoatem chiftelele pe un servetel de hartie pentru a absorbi uleiul in exces.");
    CarteBucate::adaugaReteta(chiftele,carte);

    Stoc::addIngredientFull("Carne tocata",1000,"g",depozit);
    Stoc::addIngredientFull("Ceapa",300,"g",depozit);
    Stoc::addIngredientFull("Pesmet",20,"g",depozit);

}
void addReteta(std::vector<Reteta> &carte, std::vector<Stoc> &depozit) {
    std::string numeReteta, numeIngredient, unitateMasura, instructiune;
    int nrIngrediente, nrInstructiuni, cantitate;
    std::cin.ignore();
    std::cout << "Introduceti numele retetei: ";
    std::getline(std::cin, numeReteta);

    Reteta nouaReteta(numeReteta);

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
        std::cout<<"2. ml\n";
        std::cout<<"3. buc\n";
        std::cin >> optiune;
        std::cin.ignore();
        if(optiune < 1 or optiune > 3) {
            throw eroare_intrare("optiune invalida");
        }
        switch (optiune) {
            case 1:{
                unitateMasura="g";
                break;
            }
            case 2: {
                unitateMasura="ml";
                break;
            }
            case 3: {
                unitateMasura="buc";
                break;
            }
            default: {
                unitateMasura="";
                break;
            }
        }

        nouaReteta.addIngredient(numeIngredient, cantitate, unitateMasura);
        if(Stoc::gasesteProdus(numeIngredient,depozit)==nullptr)
            Stoc::addIngredient(numeIngredient, unitateMasura,depozit);

    }

    std::cout << "Cate instructiuni are reteta? ";
    std::cin >> nrInstructiuni;
    std::cin.ignore();

    for (int i = 0; i < nrInstructiuni; ++i) {
        std::cout << "Introduceti instructiunea " << i + 1 << ": ";
        std::getline(std::cin, instructiune);
        nouaReteta.addInstructiune(instructiune);
    }

    CarteBucate::adaugaReteta(nouaReteta,carte);
    std::cout << "Reteta a fost adaugata cu succes!\n";
}
void modificaReteta(std::vector<Reteta> &carte, std::vector<Stoc> &depozit) {
    std::cout << carte;
    std::string numeReteta;
    std::cout << "Introduceti numele retetei pe care doriti sa o modificati: ";
    std::cin.ignore();
    std::getline(std::cin, numeReteta);
    Reteta* reteta = CarteBucate::gasesteReteta(numeReteta,carte);

    if (reteta == nullptr) {
        throw eroare_intrare("reteta invalida");
    } else {
        int c;
        std::cout << "Ce doriti sa modificati?\n";
        std::cout << "1. Adaugati ingrediente.\n";
        std::cout << "2. Adaugati instructiuni.\n";
        std::cin >> c;
        std::cin.ignore();

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
                while(optiune < 1 or optiune > 3) {
                    std::cout<<"Optiune invalida.\n Introduceti o optiune: ";
                    std::cin >> optiune;
                    std::cin.ignore();
                }
                switch (optiune) {
                    case 1:{
                        unitateMasura="g";
                        break;
                    }
                    case 2: {
                        unitateMasura="ml";
                        break;
                    }
                    case 3: {
                        unitateMasura="buc";
                        break;
                    }
                    default:{
                        unitateMasura="";
                        break;
                    }
                }
                reteta->addIngredient(ingredient, cantitate, unitateMasura);
                if(Stoc::gasesteProdus(ingredient,depozit)==nullptr)
                    Stoc::addIngredient(ingredient,unitateMasura,depozit);
                std::cout<<"Ingredientul a fost adaugat cu succes!\n";
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
                std::cin.ignore();

                reteta->addInstructiune(instructiune);
            }
        } else {
            throw eroare_intrare("optiune invalida");;
        }
    }
}
void afisRetete(std::vector<Reteta> &carte, std::vector<Stoc> &depozit) {
    std::cout << carte;
    std::cout << "\nDoriti sa vedeti o reteta?\n";
    std::cout << "1. Da\n";
    std::cout << "2. Nu\n";
    int caz;
    std::cin >> caz;
    std::cin.ignore();


    if (caz < 1 or caz > 2) {
        throw eroare_intrare("optiune invalida");
    }

    if (caz == 1) {
        std::string nume;
        std::cout << "Ce reteta doriti sa vedeti?\n";
        std::getline(std::cin, nume);

        const Reteta* reteta = CarteBucate::gasesteReteta(nume,carte);

        if (reteta == nullptr) {
            throw eroare_intrare("nume reteta invalid");
        } else {
            std::cout << *reteta;

            bool realizabil = true;
            const std::vector<Ingredient> ingredients = reteta->getIngrediente();
            for (const Ingredient& ingredient : ingredients) {
                const Stoc* stoc = Stoc::gasesteProdus(ingredient.getNume(),depozit);
                if(stoc==nullptr) {
                    realizabil=false;
                }else if (stoc->getCantitate() < ingredient.getCantitate()) {
                    std::cout << "Mai aveti nevoie de " << (ingredient.getCantitate() - stoc->getCantitate()) << stoc->getUnitateMasura() << ' '  << ingredient.getNume() << " pentru a gati reteta.\n";
                    realizabil = false;
                }
            }

            if (realizabil) {
                std::cout << "\nAti gatit reteta?\n1. Da\n2. Nu\n";
                int optiune;
                std::cin >> optiune;

                if (optiune < 1 or optiune > 2) {
                    throw eroare_intrare("optiune invalida");
                }

                if (optiune == 1) {
                    for (const Ingredient& ingredient : ingredients) {
                        Stoc::gasesteProdus(ingredient.getNume(),depozit)->modificareCantitate(-ingredient.getCantitate());
                    }
                    std::cout << "Cantitatile au fost actualizate.\n";
                }
            }
        }
    }
}

void afisStoc(std::vector<Stoc> &depozit) {
    std::cout<<depozit;
    std::cout<<"Doriti sa modificati un produs?\n1. Da\n2. Nu\n";
    int optiune;
    std::cin >> optiune;
    if (optiune < 1 or optiune > 2) {
        throw eroare_intrare("optiune invalida");
    }
    std::cin.ignore();
    if(optiune==1) {
        std::string produs;
        std::cout<<"Ce produs doriti sa modificati?\n";
        std::getline(std::cin, produs);
        Ingredient* ingr=Stoc::gasesteProdus(produs,depozit);
        while(ingr==nullptr) {
            throw eroare_intrare("produs inexistent");
        }
        std::cout<<"Introduceti noua cantitate pentru "<<ingr->getNume()<<':';
        int cantitate;
        std::cin>>cantitate;
        std::cin.ignore();
        auto* co = dynamic_cast<Stoc*>(ingr);
        co->modificareCantitate(cantitate);
    }

}
int sistem(std::vector<Reteta> &carte, std::vector<Stoc> &depozit) {
    int caz;
    while(true) {
        std::cout<<"Sistem de management al retetelor\n\n";
        std::cout<<"1. Adaugati o reteta.\n";
        std::cout<<"2. Modificati o reteta.\n";
        std::cout<<"3. Vedeti retetele.\n";
        std::cout<<"4. Vedeti stocul.\n";
        std::cout<<"5. Inventar\n";
        std::cout<<"6. Iesire.\n";
        std::cout<<"\nIntroduceti optiunea:\n";
        std::cin>>caz;
        while(caz < 1 or caz > 6) {
            std::cout<<"\nOptiune invalida. Introduceti o optiune:";
            std::cin>>caz;
            std::cin.ignore();
        }
        switch(caz) {
            case 1: {
                try {
                    addReteta(carte,depozit);
                }
                catch (eroare_intrare &err) {
                    std::cout<<err.what();
                }
                break;
            }

            case 2: {
                try {
                    modificaReteta(carte,depozit);
                }
                catch (eroare_intrare &err){
                    std::cout<<err.what();
                }
                break;
            }


            case 3: {
                try {
                    afisRetete(carte,depozit);
                }
                catch(eroare_intrare &err){
                    std::cout<<err.what()<<'\n';
                }

                break;
            }
            case 4: {
                try {
                    afisStoc(depozit);
                }
                catch(eroare_intrare &err) {
                    std::cout<<err.what()<<'\n';
                }
                break;
            }
            case 5: {
                try {
                    Stoc::inventar(depozit);
                }
                catch(eroare_intrare &err) {
                    std::cout<<err.what()<<'\n';
                }
                break;
            }
            case 6: {
                return 0;
            }
            default: {
                std::cout<<"Optiune invalida.\n";
                break;
            }
        }
    }
}

int main() {
    std::vector<Reteta> retetar;
    std::vector<Stoc> depozit;
    exemple(retetar,depozit);
    sistem(retetar,depozit);
    return 0;
}
