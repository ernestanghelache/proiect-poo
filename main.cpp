#include <iostream>
#include <string>
#include <vector>

class Ingredient {
    std::string numeIngredient;
    std::string cantitate;
public:
    Ingredient() : numeIngredient{}, cantitate{} {}
    Ingredient(std::string& numeIngredient_, std::string& cantitate_) : numeIngredient{std::move(numeIngredient_)}, cantitate{std::move(cantitate_)}{}
    Ingredient(const Ingredient& other) : numeIngredient{other.numeIngredient}, cantitate{other.cantitate}{}
    Ingredient& operator=(const Ingredient& other) {
        if (this == &other) {
            return *this;
        }
        numeIngredient = other.numeIngredient;
        cantitate = other.cantitate;
        return *this;
    }
    [[nodiscard]] std::string getNumeIngredient() const {return numeIngredient;}
    [[nodiscard]] std::string getCantitate() const {return cantitate;}
    ~Ingredient() {}
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

    [[nodiscard]] std::string getPas() const {return pas;}
    ~Instructiune() {}
};
class Reteta {
    std::string numeReteta;
    std::vector<Ingredient> ingr;
    std::vector<Instructiune> instr;
public:
    Reteta() : numeReteta{}, ingr{}, instr{} {}
    explicit Reteta(std::string numeReteta_): numeReteta{std::move(numeReteta_)}{}
    Reteta(std::string& numeReteta_, const std::vector<Ingredient>&ingr_, const std::vector<Instructiune>& instr_) : numeReteta{std::move(numeReteta_)}, ingr{ingr_}, instr{instr_}{}

    Reteta(const Reteta& other) : numeReteta{other.numeReteta}, ingr{other.ingr}, instr{other.instr} {}

    Reteta& operator=(const Reteta& other) {
        if (this == &other) {
            return *this;
        }
        numeReteta = other.numeReteta;
        ingr= other.ingr;
        instr = other.instr;
        return *this;
    }

    void addIngredient(std::string num, std::string can) {
            ingr.emplace_back(num, can);
    }

    void addInstructiune(std::string instruct) {
        instr.emplace_back(instruct);
    }

    friend std::ostream& operator<<(std::ostream& os, const Reteta& r) {
        std::cout << "Nume reteta: " << r.numeReteta << '\n';
        std::cout << "Ingrediente:" << '\n';
        for (const auto & it : r.ingr)
            std::cout << it.getNumeIngredient() << ": " << it.getCantitate() << '\n';

        std::cout << "Instructiuni:\n";
        for (const auto & it : r.instr)
            std::cout << "- " << it.getPas() << '\n';

        return os;
    }
    [[nodiscard]] std::string getnumeReteta() const {return numeReteta;}
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
    friend std::ostream& operator<<(std::ostream& os, const CarteBucate& c) {
        std::cout << "Retete: \n";
        for(const Reteta& reteta : c.retete) {
            std::cout << "- " << reteta.getnumeReteta() << '\n';
        }
        return os;
    };
};

int main() {
    CarteBucate retetar;

    Reteta clatite("clatite");
    clatite.addIngredient("Oua","3");
    clatite.addIngredient("Lapte","250ml");
    clatite.addIngredient("Faina","250g");
    clatite.addIngredient("Apa minerala","300ml");
    clatite.addIngredient("Esenta de vanilie","o fiola");
    clatite.addInstructiune("Punem ingredientele intr-un bol si amestecam.");
    clatite.addInstructiune("Punem compozitia cu polonicul in tigaie si o distribuim uniform.");
    clatite.addInstructiune("Dupa ce se rumeneste pe margini, o intoarcem pe cealalta parte si o mai lasam un minut.");
    clatite.addInstructiune("Scoatem clatita pe o farfurie si procedam la fel pana terminam compozitia.");
    retetar.adaugaReteta(clatite);

    Reteta paste("paste");
    paste.addIngredient("Spaghete","500g");
    paste.addIngredient("Parmezan","150g");
    paste.addIngredient("Usturoi","4 catei");
    paste.addIngredient("Ardei iute","1");
    paste.addIngredient("Ulei de masline","75g");
    paste.addInstructiune("Fierbem pastele conform instructiunilor de pe ambalaj.");
    paste.addInstructiune("Intr-o tigaie se adauga uleiul de masline, usturoiul taiat cubulete si ardeiul iute taiat rondele.");
    paste.addInstructiune("Adaugam pastele in tigaie si le lasam 2 minute");
    paste.addInstructiune("Punem in farfurii si adaugam parmezanul ras.");
    retetar.adaugaReteta(paste);

    Reteta chiftele("chiftele");
    chiftele.addIngredient("Carne tocata","600g");
    chiftele.addIngredient("Ou","1");
    chiftele.addIngredient("Ceapa","1");
    chiftele.addIngredient("Usturoi","1");
    chiftele.addIngredient("Pesmet","3 linguri");
    chiftele.addInstructiune("Tocam marunt ceapa si usturoiul, apoi amestecam toate ingredientele intr-un bol si framantam bine.");
    chiftele.addInstructiune("Formam chiftelele rotunde si le prajim.");
    chiftele.addInstructiune("Scoatem chiftelele pe un servetel de hartie pentru a absorbi uleiul in exces.");
    retetar.adaugaReteta(chiftele);

    int caz;
    while(true) {
        std::cout<<"Sistem de management al retetelor\n\n";
        std::cout<<"1. Adaugati o reteta.\n";
        std::cout<<"2. Modificati o reteta.\n";
        std::cout<<"3. Vedeti retetele.\n";
        std::cout<<"4. Iesire.\n";
        std::cout<<"\nIntroduceti optiunea:\n";
        std::cin>>caz;
        std::cin.ignore();
        switch(caz) {
            case 1: {
                std::string numeReteta, numeIngredient, cantitate, instructiune;
                int nrIngrediente, nrInstructiuni;

                std::cout << "Introduceti numele retetei: ";
                std::cin>> numeReteta;
                std::cin.ignore();

                Reteta nouaReteta(numeReteta);

                std::cout << "Cate ingrediente are reteta? ";
                std::cin >> nrIngrediente;
                std::cin.ignore();

                for (int i = 0; i < nrIngrediente; ++i) {
                    std::cout << "Introduceti numele ingredientului " << i + 1 << ": ";
                    std::cin>>numeIngredient;
                    std::cin.ignore();
                    std::cout << "Introduceti cantitatea pentru " << numeIngredient << ": ";
                    std::cin>>cantitate;
                    std::cin.ignore();
                    nouaReteta.addIngredient(numeIngredient, cantitate);
                }

                std::cout << "Cate instructiuni are reteta? ";
                std::cin >> nrInstructiuni;
                std::cin.ignore();

                for (int i = 0; i < nrInstructiuni; ++i) {
                    std::cout << "Introduceti instructiunea " << i + 1 << ": ";
                    std::cin>> instructiune;
                    std::cin.ignore();
                    nouaReteta.addInstructiune(instructiune);
                }

                retetar.adaugaReteta(nouaReteta);
                std::cout << "Reteta a fost adaugata cu succes!\n";
                break;
            }

            case 2: {
                std::cout << retetar;
                std::string num;
                std::cout << "Introduceti numele retetei pe care doriti sa o modificati: ";
                std::getline(std::cin, num);  // Citește întregul nume

                Reteta* ret = retetar.gasesteReteta(num);

                if (ret == nullptr) {
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
                            std::string in, can;
                            std::cout << "Introduceti numele ingredientului " << i + 1 << ": ";
                            std::getline(std::cin, in);
                            std::cout << "Introduceti cantitatea pentru " << in << ": ";
                            std::getline(std::cin, can);

                            ret->addIngredient(in, can);
                        }

                    } else if (c == 2) {
                        int nrIn;
                        std::cout << "Cate instructiuni doriti sa adaugati? ";
                        std::cin >> nrIn;
                        std::cin.ignore();

                        for (int i = 0; i < nrIn; ++i) {
                            std::string instructiune;
                            std::cout << "Introduceti instructiunea " << i + 1 << ": ";
                            std::getline(std::cin, instructiune);

                            ret->addInstructiune(instructiune);
                        }
                    } else {
                        std::cout << "Optiune invalida.\n";
                    }
                }
                break;
            }


            case 3: {
                std::cout<<retetar;
                std::cout<<"Doriti sa vedeti o reteta?\n1. Da.\n2. Nu.\n";
                int c;
                std::cin>>c;
                if(c==1){
                        std::string nume;
                        std::cout<<"Ce reteta doriti sa vedeti?\n";
                        std::cin>>nume;
                        std::cin.ignore();
                        const Reteta* ret = retetar.gasesteReteta(nume);

                        if (ret == nullptr) {
                            std::cout << "Rețeta nu a fost găsită.\n";
                        } else {
                            std::cout<<*ret;
                        }
                    }
                else if(c==2) {
                    break;
                }else {
                        std::cout<<"Optiune invalida.\n";
                    }
                }
                break;

            case 4: {
                return 0;
            }
            default: {

                std::cout<<"Optiune invalida.\n";
                break;
            }
        }
    }
}
