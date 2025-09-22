#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <regex>

int StringCalculator::Add(const std::string& input) {
    if (input.empty()) return 0;

    auto [numbers, delimiters] = preprocessInput(input);
    auto parsed = splitAndParse(numbers, delimiters);

    validateNegatives(parsed);

    return sumNumbers(parsed);
}

// ----------------- Helpers -----------------

std::pair<std::string, std::vector<std::string>>
StringCalculator::preprocessInput(const std::string& input) {
    std::string numbers = input;
    std::vector<std::string> delimiters = {",", "\n"};

    if (numbers.rfind("//", 0) == 0) {
        size_t newlinePos = numbers.find('\n');
        if (newlinePos == std::string::npos)
            throw std::invalid_argument("Invalid delimiter format");

        std::string delimiterSection = numbers.substr(2, newlinePos - 2);
        numbers = numbers.substr(newlinePos + 1);

        delimiters = parseDelimiters(delimiterSection);
    }
    return {numbers, delimiters};
}

void StringCalculator::validateNegatives(const std::vector<int>& parsed) {
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
}

int StringCalculator::sumNumbers(const std::vector<int>& parsed) {
    int sum = 0;
    for (int n : parsed) {
        if (n <= 1000) sum += n;
    }
    return sum;
}

std::vector<std::string> StringCalculator::parseDelimiters(const std::string& section) {
    std::vector<std::string> result;

    if (section.size() >= 2 && section.front() == '[' && section.back() == ']') {
        std::regex re(R"(\[([^\]]+)\])");
        std::smatch match;
        std::string s = section;
        while (std::regex_search(s, match, re)) {
            result.push_back(match[1]);
            s = match.suffix();
        }
    } else {
        result.push_back(section);
    }

    return result;
}

std::vector<int> StringCalculator::splitAndParse(
    const std::string& numbers,
    const std::vector<std::string>& delimiters) {

    std::vector<int> result;

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
