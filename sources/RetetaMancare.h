#ifndef RETETA_MANCARE_H
#define RETETA_MANCARE_H

#include "Reteta.h"
#include <string>

class RetetaMancare final : public Reteta {
    bool prajire;

public:
    RetetaMancare();

    explicit RetetaMancare(std::string numeReteta_);

    void setPrajire(bool prajire_);

    unsigned long long estimaretimp() override;

    ~RetetaMancare() override = default;
};

#endif
