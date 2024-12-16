#ifndef RETETA_H
#define RETETA_H

#include <iostream>
#include <string>
#include <vector>
#include "ingredient.h"
#include "instructiune.h"

class Reteta {
    std::string numeReteta;
    std::vector<Ingredient> ingrediente;
    std::vector<Instructiune> instructiuni;

public:
    Reteta();
    explicit Reteta(std::string numeReteta_);
    Reteta(std::string& numeReteta_, const std::vector<Ingredient>& ingrediente_, const std::vector<Instructiune>& instructiuni_);
    Reteta(const Reteta& other);
    Reteta& operator=(const Reteta& other);

    void addIngredient(std::string num, int can, std::string um);
    void addInstructiune(std::string instruct);

    friend std::ostream& operator<<(std::ostream& os, const Reteta& reteta);
    friend std::ostream& operator<<(std::ostream& os, const std::vector<Reteta>& carte);

    [[nodiscard]] const std::string& getnumeReteta() const;
    [[nodiscard]] const std::vector<Ingredient>& getIngrediente() const;

    ~Reteta();
};

#endif