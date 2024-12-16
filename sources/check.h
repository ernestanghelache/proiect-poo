#ifndef EROARE_H
#define EROARE_H

#include <stdexcept>
#include <string>

class eroare : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class eroare_intrare : public eroare {
public:
    explicit eroare_intrare(const std::string& mesaj);
};

#endif