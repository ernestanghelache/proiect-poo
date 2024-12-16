#ifndef INSTRUCTIUNE_H
#define INSTRUCTIUNE_H

#include <iostream>
#include <string>

class Instructiune {
    std::string pas;

public:
    Instructiune();
    explicit Instructiune(std::string& pas_);
    Instructiune(const Instructiune& other);
    Instructiune& operator=(const Instructiune& other);

    friend std::ostream& operator<<(std::ostream& os, const Instructiune& instructiune);

    ~Instructiune();
};

#endif