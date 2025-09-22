#pragma once
#include <string>
#include <vector>
#include <utility>

class StringCalculator {
public:
    int Add(const std::string& input);

private:
    // Core steps
    std::pair<std::string, std::vector<std::string>> preprocessInput(const std::string& input);
    void validateNegatives(const std::vector<int>& parsed);
    int sumNumbers(const std::vector<int>& parsed);

    // Delimiter parsing
    std::vector<std::string> parseDelimiters(const std::string& section);
    std::vector<std::string> parseMultiDelimiters(const std::string& section);
    std::vector<std::string> parseSingleDelimiter(const std::string& section);

    // Number parsing
    std::vector<int> splitAndParse(const std::string& numbers,
                                   const std::vector<std::string>& delimiters);
    std::string buildDelimiterRegex(const std::vector<std::string>& delimiters);

    // Helpers
    std::string escapeRegex(const std::string& s);
    std::vector<int> collectNegatives(const std::vector<int>& parsed);
    void throwIfNegatives(const std::vector<int>& negatives);
};
