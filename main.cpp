#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Ingredient{
    std::string nume;
    int cantitate;
    std::string unitateMasura;
public:
    Ingredient() : nume{}, cantitate{}, unitateMasura{} {}
    Ingredient(std::string& nume_, int cantitate_, std::string& unitateMasura_) : nume{std::move(nume_)}, cantitate{cantitate_}, unitateMasura{std::move(unitateMasura_)}{}
    Ingredient(const Ingredient& other) : nume{other.nume}, cantitate{other.cantitate}, unitateMasura{other.unitateMasura}{}
    Ingredient& operator=(const Ingredient& other) {
        if (this == &other) {
            return *this;
        }
        nume = other.nume;
        cantitate = other.cantitate;
        unitateMasura = other.unitateMasura;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ingredient& produs) {
        os << produs.nume << ": " << produs.cantitate << produs.unitateMasura;
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const std::vector<Ingredient>& stoc) {
        for (const Ingredient &it : stoc)
            os << it << '\n';

        return os;
    }

    void modificareCantitate(int cantitate_) {
        cantitate = cantitate + cantitate_;
    }
    virtual void inventar() {
        int cant;
        std::cout<<"buna ziua";
    }
    void setCantitate(int cantitate_){cantitate=cantitate_;}
    [[nodiscard]] int getCantitate() const{return cantitate;}
    [[nodiscard]] const std::string& getNume() const {return nume;}
    [[nodiscard]] const std::string& getUnitateMasura() const {return unitateMasura;}
    virtual ~Ingredient() {}
};

class Stoc : public Ingredient{
    public:
    virtual void inventar() {
        int cant;
        std::cin >> cant;
        modificareCantitate(cant);
    }
    static std::shared_ptr<Ingredient> gasesteProdus(const std::string &numeProdus, std::vector<Ingredient> &produse) {
        for (Ingredient& it : produse) {
            if (it.getNume()==numeProdus) {
                return std::shared_ptr<Ingredient>(&it);
            }
        }
        return nullptr;
    }

    static void addIngredient(std::string num, std::string um, std::vector<Ingredient>& produse) {
        produse.emplace_back(num,0,um);
    }

    static void addIngredientFull(std::string num, const int can, std::string um, std::vector<Ingredient>& produse) {
        produse.emplace_back(num,can,um);
    }
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
    friend std::ostream& operator<<(std::ostream& os, const std::vector<Reteta>& carte) {
        os << "Retete: \n";
        for(const Reteta& reteta : carte) {
            os << "- " << reteta.getnumeReteta() << '\n';
        }
        return os;
    };
    [[nodiscard]] const std::string& getnumeReteta() const {return numeReteta;}
    [[nodiscard]] const std::vector<Ingredient>& getIngrediente() const {return ingrediente;};
    ~Reteta() {}
};
class CarteBucate : public Reteta{
public:
    static void adaugaReteta(Reteta &reteta, std::vector<Reteta>& carte) {
        carte.emplace_back(reteta);
    }

    static std::shared_ptr<Reteta> gasesteReteta(const std::string& numeReteta,std::vector<Reteta> &carte) {
        for (Reteta& reteta : carte) {
            if (reteta.getnumeReteta() == numeReteta) {
                return std::shared_ptr<Reteta>(&reteta);
            }
        }
        return nullptr;
    }

};
void exemple(std::vector<Reteta> &carte, std::vector<Ingredient> &depozit) {
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
void addReteta(std::vector<Reteta> &carte, std::vector<Ingredient> &depozit) {
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
void modificaReteta(std::vector<Reteta> &carte, std::vector<Ingredient> &depozit) {
    std::cout << carte;
    std::string numeReteta;
    std::cout << "Introduceti numele retetei pe care doriti sa o modificati: ";
    std::cin.ignore();
    std::getline(std::cin, numeReteta);
    std::shared_ptr<Reteta> reteta = CarteBucate::gasesteReteta(numeReteta,carte);

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
            std::cout << "Optiune invalida.\n";
        }
    }
}
void afisRetete(std::vector<Reteta> &carte, std::vector<Ingredient> &depozit) {
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

        std::shared_ptr<Reteta> reteta = CarteBucate::gasesteReteta(nume,carte);

        if (reteta == nullptr) {
            std::cout << "Reteta nu a fost gasita.\n";
        } else {
            std::cout << reteta;

            bool realizabil = true;
            const std::vector<Ingredient> ingredients = reteta->getIngrediente();
            for (const Ingredient& ingredient : ingredients) {
                const std::shared_ptr<Ingredient> stoc = Stoc::gasesteProdus(ingredient.getNume(),depozit);
                if(stoc==nullptr) {
                    realizabil=false;
                }else if (stoc->getCantitate() < ingredient.getCantitate()) {
                    std::cout << "Mai aveti nevoie de " <<ingredient.getCantitate() - stoc->getCantitate() << ingredient.getUnitateMasura()<< ' '<<ingredient.getNume() << " pentru a gati reteta.\n";
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
                        Stoc::gasesteProdus(ingredient.getNume(),depozit)->modificareCantitate(-ingredient.getCantitate());
                    }
                    std::cout << "Cantitatile au fost actualizate.\n";
                }
            }
        }
    }
}

void afisStoc(std::vector<Ingredient> &depozit) {
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
        std::shared_ptr<Ingredient> ingr=Stoc::gasesteProdus(produs,depozit);
        while(ingr==nullptr) {
            std::cout<<"Optiune invalida.\n";
            std::cout<<"Ce produs doriti sa modificati?\n";
            std::getline(std::cin, produs);
            ingr=Stoc::gasesteProdus(produs,depozit);
        }
        std::cout<<"Introduceti noua cantitate pentru "<<ingr->getNume()<<':';
        int cantitate;
        std::cin>>cantitate;
        std::cin.ignore();
        ingr->setCantitate(cantitate);
    }

}
int sistem(std::vector<Reteta> &carte, std::vector<Ingredient> &depozit) {
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
                addReteta(carte,depozit);
                break;
            }

            case 2: {
                modificaReteta(carte,depozit);
                break;
            }


            case 3: {
                afisRetete(carte,depozit);
                break;
            }
            case 4: {
                afisStoc(depozit);
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
    std::vector<Reteta> retetar;
    std::vector<Ingredient> depozit;
    exemple(retetar,depozit);
    sistem(retetar,depozit);

    return 0;
}
