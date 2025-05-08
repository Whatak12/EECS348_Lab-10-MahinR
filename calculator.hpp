#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

//check if string is a valid double format
bool isValidDouble(const std::string &s); 

//convert valid double string into a double manually
double parse_number(const std::string &s); 

//split string into parts
void split_parts(const std::string &s, std::string &sign, std::string &intPart, std::string &fracPart); 

//add two validated double strings
std::string add_validated_strings(const std::string &a, const std::string &b); 

//helper: subtract b from a (assuming a > b), same length
std::string subtract_parts(const std::string &a, const std::string &b, int &borrow);

//helper: compare magnitude of two numbers
int compare_parts(const std::string &int1, const std::string &frac1, const std::string &int2, const std::string &frac2);


#endif // __CALCULATOR_HPP

