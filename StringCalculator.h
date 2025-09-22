#pragma once
#include <string>
#include <vector>
#include <utility>

class StringCalculator {
public:
    int Add(const std::string& input);

private:
    std::pair<std::string, std::vector<std::string>> preprocessInput(const std::string& input);
    void validateNegatives(const std::vector<int>& parsed);
    int sumNumbers(const std::vector<int>& parsed);

    std::vector<std::string> parseDelimiters(const std::string& section);
    std::vector<int> splitAndParse(const std::string& numbers,
                                   const std::vector<std::string>& delimiters);
    std::string escapeRegex(const std::string& s);
};
