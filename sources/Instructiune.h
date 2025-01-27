#ifndef INSTRUCTIUNE_H
#define INSTRUCTIUNE_H

#include <string>
#include <iostream>

class Instructiune {
    std::string pas;

public:
    Instructiune() = default;

    explicit Instructiune(std::string &pas_);

    Instructiune(const Instructiune &other) = default;

    Instructiune &operator=(const Instructiune &other);

    friend std::ostream &operator<<(std::ostream &os, const Instructiune &instructiune);

    ~Instructiune() = default;
};

#endif
