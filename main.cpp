#include <iostream>
#include <fstream>
#include <string>
#include "calculator.hpp" 

int main() {
    //get file name from user
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    //attempt to open file
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "error: could not open file.\n";
        return 1;
    }

    //read in file and check if each line is a valid double
    std::string line;
    int caseNum = 1;
    while (std::getline(infile, line)) {
        std::cout << "case#" << caseNum << ": " << line << "\n";

        //trim whitespace
        size_t first = line.find_first_not_of(" \t\r\n");
        size_t last = line.find_last_not_of(" \t\r\n");

        //if all whitespace or empty, skip
        if (first == std::string::npos || last == std::string::npos) {
            std::cout << "  invalid number format.\n\n";
            caseNum++;
            continue;
        }

        //slice trimmed string
        std::string trimmed = line.substr(first, last - first + 1);

        if (!isValidDouble(trimmed)) {
            std::cout << "  invalid number format.\n\n";
        } else {
            std::cout << "  valid number format.\n";
            double parsed = parse_number(trimmed);
            std::cout << "  parsed value: " << parsed << "\n";
        
            std::string result = add_validated_strings(trimmed, "-123.456");
            std::cout << "  + (-123.456): " << result << "\n\n";
        }

        caseNum++;
    }

    //close file
    infile.close();
    return 0;
}
