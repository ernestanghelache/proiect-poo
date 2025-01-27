#ifndef RETETA_H
#define RETETA_H

#include <string>
#include <vector>
#include <iostream>
#include "Ingredient.h"
#include "Instructiune.h"

class Reteta {
protected:
    std::string numeReteta;
    std::vector<Ingredient> ingrediente;
    std::vector<Instructiune> instructiuni;
    bool vegan;

public:
    static int nr;

    Reteta();

    explicit Reteta(std::string numeReteta_);

    Reteta(std::string &numeReteta_, const std::vector<Ingredient> &ingrediente_,
           const std::vector<Instructiune> &instructiuni_, bool vegan_);

    Reteta(const Reteta &other) = default;

    Reteta &operator=(const Reteta &other);

    void addIngredient(const std::string &num, int can, const std::string &um, int cal);

    void addInstructiune(std::string instruct);

    friend std::ostream &operator<<(std::ostream &os, const Reteta &reteta);

    void setVegan(bool vegan_);

    [[nodiscard]] const std::string &getnumeReteta() const;

    [[nodiscard]] const std::vector<Ingredient> &getIngrediente() const;

    virtual unsigned long long int estimaretimp() = 0;

    virtual ~Reteta() = default;
};

#endif
