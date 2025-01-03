#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _bitcoinRates(other._bitcoinRates) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _bitcoinRates = other._bitcoinRates;
    }
    return *this;
}

void BitcoinExchange::loadData(const std::string &filename)
{
    std::ifstream file(filename.c_str());

    if (!file)
        throw std::invalid_argument("Error: Could not open file " + filename);
    std::string line;
    std::string date;
    double rate;

    if (std::getline(file, line))
    {
        if (line != "date,exchange_rate")
        {
            std::istringstream iss(line);
            if (std::getline(iss, date, ',') && (iss >> rate))
                _bitcoinRates[date] = rate;
        }
    }
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (std::getline(iss, date, ',') && (iss >> rate))
            _bitcoinRates[date] = rate;
    }
}

void BitcoinExchange::processInput(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
        throw std::invalid_argument("Error: Could not open file " + filename);
    std::string line;
    std::string date;
    std::string inputValue;
    double value;
    double rate;
    while (std::getline(file, line))
    {
        if (line == "date | value")
            continue;
        std::stringstream ss(line);
        if (line[10] != ' ' || line[11] != '|' || line[12] != ' ')
        {
            if (line.empty())
                line = "empty";
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (std::getline(ss, date, ' '))
        {
            if (!std::getline(ss, inputValue))
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            inputValue.erase(0, 2);
            if (!isValidValue(inputValue))
            {
                if (inputValue[0] == '-')
                    std::cout << "Error: not a positive number." << std::endl;
                else if (inputValue > "1000")
                    std::cout << "Error: too large a number." << std::endl;
                continue;
            }
            if (!isValidDate(date))
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            value = strtod(inputValue.c_str(), NULL);
            rate = getBitcoinValue(date);
            value *= rate;
            std::cout << date << " => " << inputValue << " = " << value << std::endl;
        }
            
    }
}

double BitcoinExchange::getBitcoinValue(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = _bitcoinRates.lower_bound(date);
    if (it == _bitcoinRates.end() || it->first != date)
    {
        if (it == _bitcoinRates.begin())
            return 0;
        --it;
    }
    return it->second;
}

bool BitcoinExchange::isValidValue(const std::string &value) const
{
    double val;
    val = strtod(value.c_str(), NULL);
    if (val >= 0 && val <= MAX_VALUE)
        return true;
    return false;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.length() != DATE_LENGTH || date[DATE_FIRST_DELIM] != '-' || date[DATE_SECOND_DELIM] != '-')
        return false;
    for (int i = 0; i < DATE_LENGTH; i++)
    {
        if (i == DATE_FIRST_DELIM || i == DATE_SECOND_DELIM)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int year = atoi(date.substr(YEAR_POS, YEAR_CHARS).c_str());
    int month = atoi(date.substr(MONTH_POS, MONTH_CHARS).c_str());
    int day = atoi(date.substr(DAY_POS, DAY_CHARS).c_str());

    
    return true;
}
