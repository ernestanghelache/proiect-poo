#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>

class eroare : public std::exception {
protected:
    std::string mesaj;

public:
    [[nodiscard]] const char *what() const noexcept override;

    eroare();

    explicit eroare(std::string mesaj);

    ~eroare() override = default;
};

class eroare_reteta final : public eroare {
public:
    explicit eroare_reteta(const std::string &mesaj);

    ~eroare_reteta() override = default;
};

class eroare_stoc final : public eroare {
public:
    explicit eroare_stoc(const std::string &mesaj);

    ~eroare_stoc() override = default;
};

class eroare_intrare final : public eroare {
public:
    explicit eroare_intrare(const std::string &mesaj);
};

#endif
