#ifndef RETETA_DESERT_H
#define RETETA_DESERT_H

#include "Reteta.h"
#include <string>

class RetetaDesert final : public Reteta {
    bool coacere;

public:
    RetetaDesert();

    explicit RetetaDesert(std::string numeReteta_);

    void setCoacere(bool coacere_);

    unsigned long long estimaretimp() override;

    ~RetetaDesert() override = default;
};

#endif
