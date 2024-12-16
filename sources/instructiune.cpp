#include "instructiune.h"

Instructiune::Instructiune() : pas{} {}

Instructiune::Instructiune(std::string& pas_) : pas{std::move(pas_)} {}

Instructiune::Instructiune(const Instructiune& other) : pas{other.pas} {}

Instructiune& Instructiune::operator=(const Instructiune& other) {
    if (this == &other) {
        return *this;
    }
    pas = other.pas;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Instructiune& instructiune) {
    os << instructiune.pas;
    return os;
}

Instructiune::~Instructiune() {}