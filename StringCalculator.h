#ifndef STRINGCALCULATOR_H_
#define STRINGCALCULATOR_H_

#include <string>
#include <vector>
#include <utility>

class StringCalculator {  // must have a space
 public:
  int Add(const std::string& input);

 private:
  std::pair<std::string, std::vector<std::string>> preprocessInput(
      const std::string& input);
  std::vector<int> splitAndParse(
      const std::string& numbers, const std::vector<std::string>& delimiters);
  std::vector<std::string> parseDelimiters(const std::string& input);
  std::vector<std::string> parseMultiDelimiters(const std::string& input);
  std::vector<std::string> parseSingleDelimiter(const std::string& input);
  std::vector<int> collectNegatives(const std::vector<int>& numbers);
  void throwIfNegatives(const std::vector<int>& negatives);
  int sumNumbers(const std::vector<int>& numbers);
  std::string buildDelimiterRegex(const std::vector<std::string>& delimiters);
  std::string escapeRegex(const std::string& delimiter);
};

#endif  // STRINGCALCULATOR_H_
