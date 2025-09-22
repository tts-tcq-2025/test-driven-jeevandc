#include "StringCalculator.h"
#include <sstream>
#include <stdexcept>
#include <regex>

// ----------------- Public -----------------
int StringCalculator::Add(const std::string& input) {
    if (input.empty()) return 0;

    auto [numbers, delimiters] = preprocessInput(input);
    auto parsed = splitAndParse(numbers, delimiters);

    validateNegatives(parsed);

    return sumNumbers(parsed);
}

// ----------------- Preprocessing -----------------
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

// ----------------- Validation -----------------
void StringCalculator::validateNegatives(const std::vector<int>& parsed) {
    auto negatives = collectNegatives(parsed);
    throwIfNegatives(negatives);
}

std::vector<int> StringCalculator::collectNegatives(const std::vector<int>& parsed) {
    std::vector<int> negatives;
    for (int n : parsed) {
        if (n < 0) negatives.push_back(n);
    }
    return negatives;
}

void StringCalculator::throwIfNegatives(const std::vector<int>& negatives) {
    if (!negatives.empty()) {
        std::ostringstream err;
        err << "negatives not allowed:";
        for (int n : negatives) err << " " << n;
        throw std::runtime_error(err.str());
    }
}

// ----------------- Summing -----------------
int StringCalculator::sumNumbers(const std::vector<int>& parsed) {
    int sum = 0;
    for (int n : parsed) {
        if (n <= 1000) sum += n;
    }
    return sum;
}

// ----------------- Delimiters -----------------
std::vector<std::string> StringCalculator::parseDelimiters(const std::string& input) {
    if (input.rfind("//[", 0) == 0) {
        return parseMultiDelimiters(input);
    }
    if (input.rfind("//", 0) == 0) {
        return parseSingleDelimiter(input);
    }
    return {",", "\n"}; // default delimiters
}


std::vector<std::string> StringCalculator::parseMultiDelimiters(const std::string& section) {
    std::vector<std::string> result;
    std::regex re(R"(\[([^\]]+)\])");
    std::smatch match;
    std::string s = section;
    while (std::regex_search(s, match, re)) {
        result.push_back(match[1]);
        s = match.suffix();
    }
    return result;
}

std::vector<std::string> StringCalculator::parseSingleDelimiter(const std::string& section) {
    return {section};
}

// ----------------- Splitting -----------------
std::vector<int> StringCalculator::splitAndParse(
    const std::string& numbers,
    const std::vector<std::string>& delimiters) {

    std::vector<int> result;
    std::regex re(buildDelimiterRegex(delimiters));

    std::sregex_token_iterator iter(numbers.begin(), numbers.end(), re, -1);
    std::sregex_token_iterator end;
    for (; iter != end; ++iter) {
        if (!iter->str().empty()) {
            result.push_back(std::stoi(iter->str()));
        }
    }
    return result;
}

std::string StringCalculator::buildDelimiterRegex(const std::vector<std::string>& delimiters) {
    std::string regexPattern;
    for (size_t i = 0; i < delimiters.size(); ++i) {
        if (i > 0) regexPattern += "|";
        regexPattern += escapeRegex(delimiters[i]);
    }
    return regexPattern;
}

// ----------------- Helpers -----------------
std::string StringCalculator::escapeRegex(const std::string& s) {
    static const std::regex special(R"([-[\]{}()*+?.,\^$|#\s])");
    return std::regex_replace(s, special, R"(\$&)");
}
