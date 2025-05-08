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

    const std::string constant = "-123.456";

    //read file and process each line
    std::string line;
    int caseNum = 1;
    while (std::getline(infile, line)) {
        std::cout << "case #" << caseNum << ": " << line << "\n";

        //trim whitespace
        size_t first = line.find_first_not_of(" \t\r\n");
        size_t last = line.find_last_not_of(" \t\r\n");

        //skip blank lines
        if (first == std::string::npos || last == std::string::npos) {
            std::cout << "  invalid number format.\n\n";
            caseNum++;
            continue;
        }

        std::string trimmed = line.substr(first, last - first + 1);

        //validate and process
        if (!isValidDouble(trimmed)) {
            std::cout << "  invalid number format.\n\n";
        } else {
            std::string result = add_validated_strings(trimmed, constant);
            std::cout << "  + (-123.456): " << result << "\n\n";
        }

        caseNum++;
    }

    //close file
    infile.close();
    return 0;
}
