#pragma once
#include <string>
#include <vector>

class StringCalculator {
public:
    int Add(const std::string& input);

private:
    std::vector<std::string> parseDelimiters(const std::string& section);
    std::vector<int> splitAndParse(const std::string& numbers,
                                   const std::vector<std::string>& delimiters);
    std::string escapeRegex(const std::string& s);
};
