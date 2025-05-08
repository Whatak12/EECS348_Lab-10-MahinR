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

