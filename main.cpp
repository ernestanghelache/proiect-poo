#include "sources/Meniu.h"

int Reteta::nr = 0;

int main() {
    Meniu &meniu = Meniu::getInstance();
    meniu.program();
    return 0;
}
