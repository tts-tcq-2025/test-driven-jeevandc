#include <sstream>

int StringCalculator::Add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    int sum = 0;
    std::stringstream ss(numbers);
    std::string token;

    while (std::getline(ss, token, ',')) {
        sum += std::stoi(token);
    }

    return sum;
}
