#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

#define MAX_VALUE 1000
#define DATE_LENGTH 10
#define DATE_FIRST_DELIM 4
#define DATE_SECOND_DELIM 7
#define YEAR_CHARS 4
#define MONTH_CHARS 2
#define DAY_CHARS 2
#define YEAR_POS 0
#define MONTH_POS 5
#define DAY_POS 8
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_DAY 1
#define MAX_DAY 31
#define MAX_DAY_SHORT 30
#define FEBRUARY 2
#define APRIL 4
#define JUNE 6
#define SEPTEMBER 9
#define NOVEMBER 11


class BitcoinExchange
{
    private:
        std::map<std::string, double> _bitcoinRates;
        bool isValidValue(const std::string &value) const;
        bool isValidDate(const std::string &date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        ~BitcoinExchange();
        BitcoinExchange &operator=(const BitcoinExchange &other);

        void loadData(const std::string &filename);
        void processInput(const std::string &filename);
        double getBitcoinValue(const std::string &date) const;
};

#endif