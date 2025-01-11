#ifndef RETETA_H
#define RETETA_H

#include "Ingredient.h"
#include <vector>
#include <memory>
#include <string>

class Reteta {
    std::string numeReteta;
    std::vector<std::unique_ptr<AbstractIngredient>> ingrediente;
    std::vector<std::string> instructiuni;

    static int contorRetete;

public:
    Reteta();
    explicit Reteta(const std::string& numeReteta_);
    Reteta(const Reteta& other);
    Reteta& operator=(const Reteta& other);

    void addIngredient(const AbstractIngredient& ingredient);
    void addInstructiune(const std::string& instructiune);

    [[nodiscard]] bool validareIngrediente(const std::vector<std::unique_ptr<AbstractIngredient>>& stoc) const;
    [[nodiscard]] double calculValoareNutritiva() const;

    [[nodiscard]] const std::string& getNumeReteta() const;

    static int getContorRetete();
    [[nodiscard]] const std::vector<std::unique_ptr<AbstractIngredient>>& getIngrediente() const;
    friend std::ostream& operator<<(std::ostream& os, const Reteta& reteta);
    ~Reteta();
};

#endif

