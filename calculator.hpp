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


#endif // __CALCULATOR_HPP

