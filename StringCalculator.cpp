#include "StringCalculator.h"

#include <numeric>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <utility>

int StringCalculator::Add(const std::string& input) {
  if (input.empty()) return 0;

  auto [numbersPart, delimiters] = preprocessInput(input);
  auto numbers = splitAndParse(numbersPart, delimiters);

  auto negatives = collectNegatives(numbers);
  throwIfNegatives(negatives);

  return sumNumbers(numbers);
}

// ----------------- Preprocessing -----------------
std::pair<std::string, std::vector<std::string>> StringCalculator::preprocessInput(
    const std::string& input) {
  if (input.rfind("//", 0) == 0) {
    size_t newlinePos = input.find('\n');
    return {input.substr(newlinePos + 1), parseDelimiters(input)};
  }
  return {input, {",", "\n"}};  // default delimiters
}

// ----------------- Negative numbers -----------------
std::vector<int> StringCalculator::collectNegatives(const std::vector<int>& numbers) {
  std::vector<int> negatives;
  std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(negatives),
               [](int n) { return n < 0; });
  return negatives;
}

void StringCalculator::throwIfNegatives(const std::vector<int>& negatives) {
  if (!negatives.empty()) {
    std::ostringstream oss;
    oss << "negatives not allowed:";
    for (size_t i = 0; i < negatives.size(); ++i) {
      oss << " " << negatives[i];
    }
    throw std::invalid_argument(oss.str());
  }
}

// ----------------- Sum numbers -----------------
int StringCalculator::sumNumbers(const std::vector<int>& numbers) {
  return std::accumulate(
      numbers.begin(), numbers.end(), 0,
      [](int acc, int n) { return n <= 1000 ? acc + n : acc; });
}

// ----------------- Delimiters -----------------
std::vector<std::string> StringCalculator::parseDelimiters(const std::string& input) {
  if (input.rfind("//[", 0) == 0) return parseMultiDelimiters(input);
  if (input.rfind("//", 0) == 0) return parseSingleDelimiter(input);
  return {",", "\n"};  // default
}

std::vector<std::string> StringCalculator::parseMultiDelimiters(const std::string& input) {
  std::vector<std::string> delimiters;
  size_t pos = 2;  // skip "//"
  while ((pos = input.find('[', pos)) != std::string::npos) {
    size_t end = input.find(']', pos);
    delimiters.push_back(input.substr(pos + 1, end - pos - 1));
    pos = end + 1;
  }
  return delimiters;
}

std::vector<std::string> StringCalculator::parseSingleDelimiter(const std::string& input) {
  return {std::string(1, input[2])};
}

// ----------------- Split and parse -----------------
std::vector<int> StringCalculator::splitAndParse(
    const std::string& numbers, const std::vector<std::string>& delimiters) {
  std::vector<int> result;
  std::regex re(buildDelimiterRegex(delimiters));
  std::sregex_token_iterator it(numbers.begin(), numbers.end(), re, -1);
  std::sregex_token_iterator end;

  for (; it != end; ++it) {
    if (!it->str().empty()) result.push_back(std::stoi(it->str()));
  }
  return result;
}

std::string StringCalculator::buildDelimiterRegex(const std::vector<std::string>& delimiters) {
  std::ostringstream oss;
  for (size_t i = 0; i < delimiters.size(); ++i) {
    if (i > 0) oss << "|";
    oss << escapeRegex(delimiters[i]);
  }
  return oss.str();
}

std::string StringCalculator::escapeRegex(const std::string& delimiter) {
  static const std::regex special(R"([-[\]{}()*+?.,\^$|#\s])");
  return std::regex_replace(delimiter, special, R"(\$&)");
}
