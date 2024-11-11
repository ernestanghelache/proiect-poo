#include <iostream>
#include <string>
#include <vector>

class Ingredient {
    std::string numeIngredient;
    int cantitate;
    std::string unitateMasura;
public:
    Ingredient() : numeIngredient{}, cantitate{}, unitateMasura{} {}
    Ingredient(std::string& numeIngredient_, int cantitate_, std::string& unitateMasura_) : numeIngredient{std::move(numeIngredient_)}, cantitate{cantitate_}, unitateMasura{std::move(unitateMasura_)}{}
    Ingredient(const Ingredient& other) : numeIngredient{other.numeIngredient}, cantitate{other.cantitate}, unitateMasura{other.unitateMasura}{}
    Ingredient& operator=(const Ingredient& other) {
        if (this == &other) {
            return *this;
        }
        numeIngredient = other.numeIngredient;
        cantitate = other.cantitate;
        unitateMasura = other.unitateMasura;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ingredient& ingredient) {
        os << ingredient.numeIngredient << ": " << ingredient.cantitate << ingredient.unitateMasura;

        return os;
    }
    void modificareCantitate(int cantitate_) {
        cantitate = cantitate + cantitate_;
    }
    [[nodiscard]] int getCantitate() const{
        return cantitate;
    }
    void setCantitate(int cantitate_){cantitate=cantitate_;}
    [[nodiscard]] const std::string& getNumeIngredient() const {return numeIngredient;}
    [[nodiscard]] const std::string& getUnitateMasura() const {return unitateMasura;}
    ~Ingredient() {}
};
class Stoc {
    std::vector<Ingredient> produse;
    public:
    Stoc() : produse{} {}
    explicit Stoc(const Ingredient &produse_) : produse{produse_} {}
    Stoc(const Stoc& other) : produse{other.produse} {}
    Stoc& operator=(const Stoc& other) {
        if (this == &other) {
            return *this;
        }
        produse = other.produse;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stoc& stoc) {
        for (const auto & it : stoc.produse)
            os << it << '\n';

        return os;
    }
    Ingredient* gasesteProdus(const std::string& numeProdus) {
        for (auto& it : produse) {
            if (it.getNumeIngredient()==numeProdus) {
                return &it;
            }
        }
        return nullptr;
    }
    void addIngredient(std::string num, std::string um) {
        produse.emplace_back(num, 0, um);
    }
    void addIngredientFull(std::string num, int can, std::string um) {
        produse.emplace_back(num,can,um);
    }
    ~Stoc() {}
};
class Instructiune {
    std::string pas;
public:
    Instructiune() : pas{} {}
    explicit Instructiune(std::string& pas_) : pas{std::move(pas_)}{}
    Instructiune(const Instructiune& other) : pas{other.pas}{}
    Instructiune& operator=(const Instructiune& other) {
        if (this == &other) {
            return *this;
        }
        pas = other.pas;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Instructiune& instructiune) {
        os << instructiune.pas;
        return os;
    }
    ~Instructiune() {}
};
class Reteta {
    std::string numeReteta;
    std::vector<Ingredient> ingrediente;
    std::vector<Instructiune> instructiuni;
public:
    Reteta() : numeReteta{}, ingrediente{}, instructiuni{} {}
    explicit Reteta(std::string numeReteta_): numeReteta{std::move(numeReteta_)}{}
    Reteta(std::string& numeReteta_, const std::vector<Ingredient>&ingrediente_, const std::vector<Instructiune>& instructiuni_) : numeReteta{std::move(numeReteta_)}, ingrediente{ingrediente_}, instructiuni{instructiuni_}{}

    Reteta(const Reteta& other) : numeReteta{other.numeReteta}, ingrediente{other.ingrediente}, instructiuni{other.instructiuni} {}

    Reteta& operator=(const Reteta& other) {
        if (this == &other) {
            return *this;
        }
        numeReteta = other.numeReteta;
        ingrediente= other.ingrediente;
        instructiuni = other.instructiuni;
        return *this;
    }

    void addIngredient(std::string num, int can, std::string um) {
            ingrediente.emplace_back(num, can, um);
    }

    void addInstructiune(std::string instruct) {
        instructiuni.emplace_back(instruct);
    }

    friend std::ostream& operator<<(std::ostream& os, const Reteta& reteta) {
        os << "Nume reteta: " << reteta.numeReteta << '\n';
        os << "Ingrediente:" << '\n';
        for (const auto & it : reteta.ingrediente)
            os << it << '\n';

        os << "Instructiuni:\n";
        for (const auto & it : reteta.instructiuni)
            os << "- " << it << '\n';

        return os;
    }
    [[nodiscard]] const std::string& getnumeReteta() const {return numeReteta;}
    [[nodiscard]] const std::vector<Ingredient>& getIngrediente() const {return ingrediente;};
    ~Reteta() {}
};
class CarteBucate {
    std::vector<Reteta> retete;
public:
    void adaugaReteta(const Reteta& reteta) {
        retete.push_back(reteta);
    }
    Reteta* gasesteReteta(const std::string& numeReteta) {
        for (auto& reteta : retete) {
            if (reteta.getnumeReteta() == numeReteta) {
                return &reteta;
            }
        }
        return nullptr;
    }
    friend std::ostream& operator<<(std::ostream& os, const CarteBucate& carte) {
        os << "Retete: \n";
        for(const Reteta& reteta : carte.retete) {
            os << "- " << reteta.getnumeReteta() << '\n';
        }
        return os;
    };
};
void exemple(CarteBucate &carte, Stoc &depozit) {
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
    carte.adaugaReteta(clatite);

    depozit.addIngredientFull("Ou",10,"buc");
    depozit.addIngredientFull("Lapte",1000,"ml");
    depozit.addIngredientFull("Faina",1000,"g");
    depozit.addIngredientFull("Apa minerala",3000,"ml");
    depozit.addIngredientFull("Esenta de vanilie",50,"ml");


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
    carte.adaugaReteta(paste);

    depozit.addIngredientFull("Spaghete",750,"g");
    depozit.addIngredientFull("Parmezan",500,"g");
    depozit.addIngredientFull("Usturoi",40,"g");
    depozit.addIngredientFull("Ardei iute",3,"buc");
    depozit.addIngredientFull("Ulei de masline",750,"ml");

    Reteta chiftele("Chiftele");
    chiftele.addIngredient("Carne tocata",600,"g");
    chiftele.addIngredient("Ou",2,"buc");
    chiftele.addIngredient("Ceapa",100,"g");
    chiftele.addIngredient("Usturoi",75,"g");
    chiftele.addIngredient("Pesmet",50,"g");
    chiftele.addInstructiune("Tocam marunt ceapa si usturoiul, apoi amestecam toate ingredientele intr-un bol si framantam bine.");
    chiftele.addInstructiune("Formam chiftelele rotunde si le prajim.");
    chiftele.addInstructiune("Scoatem chiftelele pe un servetel de hartie pentru a absorbi uleiul in exces.");
    carte.adaugaReteta(chiftele);

    depozit.addIngredientFull("Carne tocata",1000,"g");
    depozit.addIngredientFull("Ceapa",300,"g");
    depozit.addIngredientFull("Pesmet",20,"g");

}
void case1(CarteBucate &carte, Stoc &depozit) {
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
        while(optiune < 1 or optiune > 3) {
            std::cout<<"Optiune invalida.\n Introduceti o optiune:\n";
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
            default: {
                unitateMasura="";
                break;
            }
        }

        nouaReteta.addIngredient(numeIngredient, cantitate, unitateMasura);
        if(depozit.gasesteProdus(numeIngredient)==nullptr)
            depozit.addIngredient(numeIngredient, unitateMasura);

    }

    std::cout << "Cate instructiuni are reteta? ";
    std::cin >> nrInstructiuni;
    std::cin.ignore();

    for (int i = 0; i < nrInstructiuni; ++i) {
        std::cout << "Introduceti instructiunea " << i + 1 << ": ";
        std::getline(std::cin, instructiune);
        nouaReteta.addInstructiune(instructiune);
    }

    carte.adaugaReteta(nouaReteta);
    std::cout << "Reteta a fost adaugata cu succes!\n";
}
void case2(CarteBucate &carte, Stoc &depozit) {
    std::cout << carte;
    std::string numeReteta;
    std::cout << "Introduceti numele retetei pe care doriti sa o modificati: ";
    std::cin.ignore();
    std::getline(std::cin, numeReteta);
    Reteta* reteta = carte.gasesteReteta(numeReteta);

    if (reteta == nullptr) {
        std::cout << "Reteta nu a fost gasita.\n";
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
                if(depozit.gasesteProdus(ingredient)==nullptr)
                    depozit.addIngredient(ingredient,unitateMasura);
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
            std::cout << "Optiune invalida.\n";
        }
    }
}
void case3(CarteBucate &carte, Stoc &depozit) {
    std::cout << carte;
    std::cout << "\nDoriti sa vedeti o reteta?\n";
    std::cout << "1. Da\n";
    std::cout << "2. Nu\n";
    int caz;
    std::cin >> caz;
    std::cin.ignore();


    while (caz < 1 || caz > 2) {
        std::cout << "Optiune invalida. Introduceti o valoare:";
        std::cin >> caz;
        std::cin.ignore();
    }

    if (caz == 1) {
        std::string nume;
        std::cout << "Ce reteta doriti sa vedeti?\n";
        std::getline(std::cin, nume);

        const Reteta* reteta = carte.gasesteReteta(nume);

        if (reteta == nullptr) {
            std::cout << "Reteta nu a fost gasita.\n";
        } else {
            std::cout << *reteta;

            bool realizabil = true;
            const std::vector<Ingredient> ingredients = reteta->getIngrediente();
            for (const Ingredient& ingredient : ingredients) {
                const Ingredient* stoc = depozit.gasesteProdus(ingredient.getNumeIngredient());
                if(stoc==nullptr) {
                    realizabil=false;
                }else if (stoc->getCantitate() < ingredient.getCantitate()) {
                    std::cout << "Mai aveti nevoie de " <<ingredient.getCantitate() - stoc->getCantitate() << ingredient.getUnitateMasura()<< ' '<<ingredient.getNumeIngredient() << " pentru a gati reteta.\n";
                    realizabil = false;
                }
            }

            if (realizabil) {
                std::cout << "\nAti gatit reteta?\n1. Da\n2. Nu\n";
                int optiune;
                std::cin >> optiune;

                while (optiune < 1 or optiune > 2) {
                    std::cout << "Optiune invalida. Introduceti o valoare:";
                    std::cin >> optiune;
                    std::cin.ignore();
                }

                if (optiune == 1) {
                    for (const auto& ingredient : ingredients) {
                        depozit.gasesteProdus(ingredient.getNumeIngredient())->modificareCantitate(-ingredient.getCantitate());
                    }
                    std::cout << "Cantitatile au fost actualizate.\n";
                }
            }
        }
    }
}

void case4(Stoc &depozit) {
    std::cout<<depozit;
    std::cout<<"Doriti sa modificati un produs?\n1. Da\n2. Nu\n";
    int optiune;
    std::cin >> optiune;
    while (optiune < 1 or optiune > 2) {
        std::cout<<"\nOptiune invalida. Introduceti o optiune:";
        std::cin.ignore();
        std::cin >> optiune;
    }
    std::cin.ignore();
    if(optiune==1) {
        std::string produs;
        std::cout<<"Ce produs doriti sa modificati?\n";
        std::getline(std::cin, produs);
        Ingredient* ingr=depozit.gasesteProdus(produs);
        while(ingr==nullptr) {
            std::cout<<"Optiune invalida.\n";
            std::cout<<"Ce produs doriti sa modificati?\n";
            std::getline(std::cin, produs);
            ingr=depozit.gasesteProdus(produs);
        }
        std::cout<<"Introduceti noua cantitate pentru "<<ingr->getNumeIngredient()<<':';
        int cantitate;
        std::cin>>cantitate;
        std::cin.ignore();
        ingr->setCantitate(cantitate);
    }

}
int sistem(CarteBucate &carte, Stoc &depozit) {
    int caz;
    while(true) {
        std::cout<<"Sistem de management al retetelor\n\n";
        std::cout<<"1. Adaugati o reteta.\n";
        std::cout<<"2. Modificati o reteta.\n";
        std::cout<<"3. Vedeti retetele.\n";
        std::cout<<"4. Vedeti stocul.\n";
        std::cout<<"5. Iesire.\n";
        std::cout<<"\nIntroduceti optiunea:\n";
        std::cin>>caz;
        while(caz < 1 or caz > 5) {
            std::cout<<"\nOptiune invalida. Introduceti o optiune:";
            std::cin>>caz;
            std::cin.ignore();
        }
        switch(caz) {
            case 1: {
                case1(carte,depozit);
                break;
            }

            case 2: {
                case2(carte,depozit);
                break;
            }


            case 3: {
                case3(carte,depozit);
                break;
            }
            case 4: {
                case4(depozit);
                break;
            }
            case 5: {
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
    CarteBucate retetar;
    Stoc depozit;
    exemple(retetar,depozit);
    sistem(retetar,depozit);

    return 0;
}
