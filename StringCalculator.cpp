#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <regex>

int StringCalculator::Add(const std::string& input) {
    if (input.empty()) return 0;

    std::string numbers = input;
    std::vector<std::string> delimiters = {",", "\n"};

    // Check for custom delimiter prefix
    if (numbers.rfind("//", 0) == 0) {
        size_t newlinePos = numbers.find('\n');
        if (newlinePos == std::string::npos)
            throw std::invalid_argument("Invalid delimiter format");

        std::string delimiterSection = numbers.substr(2, newlinePos - 2);
        numbers = numbers.substr(newlinePos + 1);

        delimiters = parseDelimiters(delimiterSection);
    }

    std::vector<int> parsed = splitAndParse(numbers, delimiters);

    // Validate negatives
    std::vector<int> negatives;
    for (int n : parsed) {
        if (n < 0) negatives.push_back(n);
    }
    if (!negatives.empty()) {
        std::ostringstream err;
        err << "negatives not allowed:";
        for (int n : negatives) err << " " << n;
        throw std::runtime_error(err.str());
    }

    // Sum valid numbers
    int sum = 0;
    for (int n : parsed) {
        if (n <= 1000) sum += n;
    }
    return sum;
}

std::vector<std::string> StringCalculator::parseDelimiters(const std::string& section) {
    std::vector<std::string> result;

    if (section.size() >= 2 && section.front() == '[' && section.back() == ']') {
        // Multi-char delimiter(s)
        std::regex re(R"(\[([^\]]+)\])");
        std::smatch match;
        std::string s = section;
        while (std::regex_search(s, match, re)) {
            result.push_back(match[1]);
            s = match.suffix();
        }
    } else {
        // Single-char delimiter
        result.push_back(section);
    }

    return result;
}

std::vector<int> StringCalculator::splitAndParse(
    const std::string& numbers,
    const std::vector<std::string>& delimiters) {

    std::vector<int> result;

    // Build regex for all delimiters
    std::string regexPattern;
    for (size_t i = 0; i < delimiters.size(); ++i) {
        if (i > 0) regexPattern += "|";
        regexPattern += escapeRegex(delimiters[i]);
    }
    std::regex re(regexPattern);

    std::sregex_token_iterator iter(numbers.begin(), numbers.end(), re, -1);
    std::sregex_token_iterator end;
    for (; iter != end; ++iter) {
        if (!iter->str().empty()) {
            result.push_back(std::stoi(iter->str()));
        }
    }

    return result;
}

std::string StringCalculator::escapeRegex(const std::string& s) {
    static const std::regex special(R"([-[\]{}()*+?.,\^$|#\s])");
    return std::regex_replace(s, special, R"(\$&)");
}
