#include <iostream>
#include <fstream>
#include <string>

int main() {
    //get file name from user
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    //attempt to open file 
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }
    //read in file and print out for testing
    std::string line;
    int caseNum = 1;
    while (std::getline(infile, line)) {
        std::cout << "Case #" << caseNum << ": " << line << "\n";
        caseNum++;
    }

    infile.close();
    return 0;
}
