#ifndef RETETA_BAUTURA_H
#define RETETA_BAUTURA_H

#include "Reteta.h"
#include <string>

class RetetaBautura final : public Reteta {
    bool fierbere;

public:
    RetetaBautura();

    explicit RetetaBautura(std::string numeReteta_);

    void setFierbere(bool fierbere_);

    unsigned long long estimaretimp() override;

    ~RetetaBautura() override = default;
};

#endif
