#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }
    BitcoinExchange exchange;
    // std::string line;
    // while (std::getline(file, line)) {
    //     std::cout << line << std::endl;
    // }
    exchange.loadData("data.csv");
    exchange.processInput(argv[1]);
    file.close();
    return 0;
}