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


#endif // __CALCULATOR_HPP

