#include <iostream>
#include "mymath/mymath.h"
#include "factorial/factorial.h"

int main() {
    std::cout << "Я умею суммировать! Зацени 10+32=";
    std::cout << mymath::sum(10, 32) << std::endl;

    std::cout << "И вычислять факториал! Факториал 10=";
    std::cout << factorial::fact(10) << std::endl;

    return 0;
}
