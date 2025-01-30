#ifndef RETETA_BAUTURA_H
#define RETETA_BAUTURA_H

#include "Reteta.h"
#include <string>

class RetetaBautura final : public Reteta {
    bool alcoolic;

public:
    RetetaBautura();

    explicit RetetaBautura(std::string numeReteta_);

    void setAlcoolic(bool alcoolic_);

    unsigned long long estimaretimp() override;

    ~RetetaBautura() override = default;
};

#endif
