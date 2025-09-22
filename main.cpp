#include "StringCalculator.h"
#include <iostream>

int main() {
    StringCalculator calc;

    std::cout << calc.Add("") << "\n";                  // 0
    std::cout << calc.Add("1") << "\n";                 // 1
    std::cout << calc.Add("1,2") << "\n";               // 3
    std::cout << calc.Add("1\n2,3") << "\n";            // 6
    std::cout << calc.Add("//;\n1;2") << "\n";          // 3
    std::cout << calc.Add("//[***]\n1***2***3") << "\n"; // 6
    std::cout << calc.Add("2,1001") << "\n";            // 2

    try {
        std::cout << calc.Add("1,-2,3,-4") << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n"; // negatives not allowed: -2 -4
    }

    return 0;
}
