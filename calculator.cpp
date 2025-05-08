#include "calculator.hpp"
#include <cctype> //for isdigit
#include <algorithm> //for reverse

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

//compare magnitude of a.int + a.frac vs b.int + b.frac
int compare_parts(const std::string &int1, const std::string &frac1,
                  const std::string &int2, const std::string &frac2) {
    if (int1.length() != int2.length())
        return int1.length() > int2.length() ? 1 : -1;
    if (int1 != int2)
        return int1 > int2 ? 1 : -1;
    if (frac1 != frac2)
        return frac1 > frac2 ? 1 : -1;
    return 0;
}

//subtract equal-length strings with borrow
std::string subtract_parts(const std::string &a, const std::string &b, int &borrow) {
    std::string result = "";
    for (int i = a.length() - 1; i >= 0; --i) {
        int d1 = a[i] - '0';
        int d2 = b[i] - '0';
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result += (diff + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}



//add two validated double strings with same or different signs
std::string add_validated_strings(const std::string &a, const std::string &b) {
    std::string sign1, int1, frac1;
    std::string sign2, int2, frac2;

    //split both strings into parts
    split_parts(a, sign1, int1, frac1);
    split_parts(b, sign2, int2, frac2);

    //handle different signs by turning into subtraction
    if (sign1 != sign2) {
        int cmp = compare_parts(int1, frac1, int2, frac2);
        std::string larger_int, larger_frac, smaller_int, smaller_frac, result_sign;

        if (cmp == 0) return "0";

        if (cmp > 0) {
            result_sign = sign1;
            larger_int = int1;
            larger_frac = frac1;
            smaller_int = int2;
            smaller_frac = frac2;
        } else {
            result_sign = sign2;
            larger_int = int2;
            larger_frac = frac2;
            smaller_int = int1;
            smaller_frac = frac1;
        }

        //pad fractional parts
        while (larger_frac.length() < smaller_frac.length()) larger_frac += '0';
        while (smaller_frac.length() < larger_frac.length()) smaller_frac += '0';

        //subtract fractional
        int borrow = 0;
        std::string frac_diff = subtract_parts(larger_frac, smaller_frac, borrow);

        //pad integer parts
        while (larger_int.length() < smaller_int.length()) larger_int = '0' + larger_int;
        while (smaller_int.length() < larger_int.length()) smaller_int = '0' + smaller_int;

        //subtract integer
        std::string int_diff = subtract_parts(larger_int, smaller_int, borrow);

        //remove leading/trailing zeros
        while (int_diff.length() > 1 && int_diff[0] == '0') int_diff.erase(0, 1);
        while (frac_diff.length() > 1 && frac_diff.back() == '0') frac_diff.pop_back();

        std::string result = int_diff;
        if (frac_diff != "0") result += "." + frac_diff;
        if (result_sign == "-") result = "-" + result;
        return result;
    }

    //pad fractional parts
    while (frac1.length() < frac2.length()) frac1 += '0';
    while (frac2.length() < frac1.length()) frac2 += '0';

    //add fractional part
    std::string frac_sum = "";
    int carry = 0;
    for (int i = frac1.length() - 1; i >= 0; --i) {
        int digit = (frac1[i] - '0') + (frac2[i] - '0') + carry;
        carry = digit / 10;
        frac_sum += (digit % 10) + '0';
    }
    std::reverse(frac_sum.begin(), frac_sum.end());

    //pad integer parts
    while (int1.length() < int2.length()) int1 = '0' + int1;
    while (int2.length() < int1.length()) int2 = '0' + int2;

    //add integer part
    std::string int_sum = "";
    for (int i = int1.length() - 1; i >= 0; --i) {
        int digit = (int1[i] - '0') + (int2[i] - '0') + carry;
        carry = digit / 10;
        int_sum += (digit % 10) + '0';
    }
    if (carry) int_sum += '1';
    std::reverse(int_sum.begin(), int_sum.end());

    //remove trailing zeros in fractional part
    while (frac_sum.length() > 1 && frac_sum.back() == '0') {
        frac_sum.pop_back();
    }

    //remove leading zeros in integer part
    while (int_sum.length() > 1 && int_sum[0] == '0') {
        int_sum.erase(0, 1);
    }

    std::string result = int_sum;
    if (frac_sum != "0") result += "." + frac_sum;
    if (sign1 == "-") result = "-" + result;

    return result;
}