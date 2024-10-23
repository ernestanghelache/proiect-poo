#include <iostream>

class Ingredient {
    std::string numeIngredient;
    std::string cantitate;
public:
    Ingredient() : numeIngredient{}, cantitate{} {}
    Ingredient(std::string& numeIngredient_, std::string& cantitate_) : numeIngredient{std::move(numeIngredient_)}, cantitate{move(cantitate_)}{}
    Ingredient(Ingredient& other) : numeIngredient{std::move(other.numeIngredient)}, cantitate{std::move(other.cantitate)}{}
    Ingredient& operator=(const Ingredient& other) {
        if (this == &other) {
            return *this;
        }
        numeIngredient = other.numeIngredient;
        cantitate = other.cantitate;
        return *this;
    }
    std::string getNumeIngredient() {return numeIngredient;}
    std::string getCantitate() {return cantitate;}
    ~Ingredient() {}
};
class Instructiune {
    std::string pas;
public:
    Instructiune() : pas{} {}
    explicit Instructiune(std::string& pas_) : pas{std::move(pas_)}{}
    Instructiune(Instructiune& other) : pas{std::move(other.pas)}{}
    Instructiune& operator=(const Instructiune& other) {
        if (this == &other) {
            return *this;
        }
        pas = other.pas;
        return *this;
    }

    std::string getPas() {return pas;}
    ~Instructiune() {}
};
class Reteta {
    std::string numeReteta;
    int nrIng = 0;
    int nrIns = 0;
    Ingredient ingr[10];
    Instructiune instr[10];
public:
    Reteta() : numeReteta{}, nrIng{}, nrIns{}, ingr{}, instr{} {}
    explicit Reteta(std::string numeReteta_): numeReteta{std::move(numeReteta_)}{}
    Reteta(std::string& numeReteta_, int nrIng_, int nrIns_,
           Ingredient ingr_[], Instructiune instr_[])
        : numeReteta{std::move(numeReteta_)}, nrIng{nrIng_}, nrIns{nrIns_} {
        for (int i = 0; i < nrIng_ && i < 10; i++) {
            ingr[i] = ingr_[i];
        }
        for (int i = 0; i < nrIns_ && i < 10; i++) {
            instr[i] = instr_[i];
        }
    }
    Reteta(const Reteta& other) {
        numeReteta = other.numeReteta;
        nrIng = other.nrIng;
        nrIns = other.nrIns;
        for (int i = 0; i < other.nrIng; i++) {
            ingr[i] = other.ingr[i];
        }
        for (int i = 0; i < other.nrIns; i++) {
            instr[i] = other.instr[i];
        }
    }
    Reteta& operator=(const Reteta& other) {
        if (this == &other) {
            return *this;
        }
        numeReteta = other.numeReteta;
        nrIng = other.nrIng;
        nrIns = other.nrIns;
        for (int i = 0; i < other.nrIng; i++) {
            ingr[i] = other.ingr[i];
        }
        for (int i = 0; i < other.nrIns; i++) {
            instr[i] = other.instr[i];
        }
        return *this;
    }

    void addIngredient(std::string num, std::string can) {
        if (nrIng < 10) {
            ingr[nrIng]=Ingredient{num, can};
            nrIng++;
            std::cout << "Ingredient adaugat.\n";
        } else {
            std::cout << "Nu se mai pot adauga ingrediente la aceasta reteta.\n";
        }
    }

    void addInstructiune(std::string instruct) {
        if (nrIns < 10) {
            instr[nrIns]=Instructiune{instruct};
            nrIns++;
            std::cout << "Instructiune adaugata.\n";
        } else {
            std::cout << "Nu se mai pot adauga instructiuni la aceasta reteta.\n";
        }
    }
    void afisReteta()
    {
        std::cout << "Nume reteta: " << numeReteta << '\n';
        std::cout << "Ingrediente:" << '\n';
        for (int i = 0; i < nrIng; i++) {
            std::cout << "- " << ingr[i].getCantitate() << ": " << ingr[i].getNumeIngredient() << '\n';
        }
        std::cout << "Instructiuni:\n";
        for (int i = 0; i < nrIns; i++) {
            std::cout << instr[i].getPas() << '\n';
        }
    }
    ~Reteta() {}
};

int main() {
    Reteta clati("clatite");
    clati.addIngredient("Faina","500g");
    clati.addInstructiune("lzlz");

    return 0;
}

