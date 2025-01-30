#ifndef PRODUS_H
#define PRODUS_H

#include <string>

class Produs {
protected:
    std::string numeIngredient;
    int cantitate;
    std::string unitateMasura;

public:
    Produs();

    Produs(std::string numeIngredient_, int cantitate_, std::string unitateMasura_);

    [[nodiscard]] virtual bool recomandat() const = 0;

    void modificareCantitate(int cantitate_);

    [[nodiscard]] int getCantitate() const;

    [[nodiscard]] const std::string &getNumeIngredient() const;

    [[nodiscard]] const std::string &getUnitateMasura() const;

    virtual ~Produs() = default;
};

#endif
