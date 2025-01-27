#ifndef ABSTRACTINGREDIENT_H
#define ABSTRACTINGREDIENT_H

#include <iostream>
#include <string>

class AbstractIngredient {
public:
    virtual ~AbstractIngredient() = default;

    virtual void afisare() const = 0;
    [[nodiscard]] virtual AbstractIngredient* clone() const = 0;
    [[nodiscard]] virtual int getCantitate() const = 0;
    [[nodiscard]] virtual const std::string& getNumeIngredient() const = 0;
    [[nodiscard]] virtual const std::string& getUnitateMasura() const = 0;
    [[nodiscard]] virtual double getValoareNutritiva() const = 0;

    virtual void modificareCantitate(int cantitate_) = 0;
};

#endif

