#include "StringCalculator.h"
#include <iostream>

int main() {
  StringCalculator calc;

  try {
    std::cout << "Empty string: " << calc.Add("") << std::endl;  // should print 0
    std::cout << "\"1\": " << calc.Add("1") << std::endl;  // should print 1
    std::cout << "\"1,2\": " << calc.Add("1,2") << std::endl;  // should print 3
    std::cout << "\"1\\n2,3\": " << calc.Add("1\n2,3") << std::endl;  // should print 6
    std::cout << "\"//;\\n1;2\": " << calc.Add("//;\n1;2") << std::endl;  // should print 3
    std::cout << "\"2,1001\": " << calc.Add("2,1001") << std::endl;  // should print 2
    std::cout << "\"//[***]\\n1***2***3\": " << calc.Add("//[***]\n1***2***3") << std::endl;  // 6
  } catch (const std::invalid_argument& ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
  }
  return 0;
}
