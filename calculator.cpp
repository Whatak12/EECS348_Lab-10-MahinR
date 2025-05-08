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
