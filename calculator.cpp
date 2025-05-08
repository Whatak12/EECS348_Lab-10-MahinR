#include "calculator.hpp"
#include <cctype> //for isdigit

//check if a string is a valid double format
bool isValidDouble(const std::string &s) {
    int i = 0;
    int n = s.size();
    if (n == 0) return false;

    //check optional + or - at beginning
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    bool hasDigitsBeforeDot = false;

    //consume digits before dot
    while (i < n && isdigit(s[i])) {
        hasDigitsBeforeDot = true;
        i++;
    }

    bool hasDigitsAfterDot = false;

    //if dot exists, consume digits after dot
    if (i < n && s[i] == '.') {
        i++;
        while (i < n && isdigit(s[i])) {
            hasDigitsAfterDot = true;
            i++;
        }
    }

    //must end at end of string and have at least one digit
    return (hasDigitsBeforeDot || hasDigitsAfterDot) && (i == n);
}

double parse_number(const std::string &s) {
    double result = 0.0;
    //use size_t to match s.size()
    size_t i = 0; 
    int sign = 1;

    //handle optional sign
    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') sign = -1;
        i++;
    }

    //parse integer part
    while (i < s.size() && isdigit(s[i])) {
        result = result * 10 + (s[i] - '0');
        i++;
    }

    //parse fractional part
    if (i < s.size() && s[i] == '.') {
        i++;
        double divisor = 10.0;
        while (i < s.size() && isdigit(s[i])) {
            result += (s[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }

    return result * sign;
}

void split_parts(const std::string &s, std::string &sign, std::string &intPart, std::string &fracPart) {
    size_t i = 0;
    sign = "+";
    intPart = "";
    fracPart = "";

    //check sign
    if (s[i] == '+' || s[i] == '-') {
        sign = s.substr(i, 1);
        i++;
    }

    //read integer part
    while (i < s.size() && isdigit(s[i])) {
        intPart += s[i];
        i++;
    }

    //read fractional part
    if (i < s.size() && s[i] == '.') {
        i++;
        while (i < s.size() && isdigit(s[i])) {
            fracPart += s[i];
            i++;
        }
    }

    //if int or frac is empty, default to "0"
    if (intPart.empty()) intPart = "0";
    if (fracPart.empty()) fracPart = "0";
}
