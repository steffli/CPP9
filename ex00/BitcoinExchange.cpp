#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : t(){};

BitcoinExchange::BitcoinExchange (const BitcoinExchange &copy) : t(copy.t){};

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy){
    if (this != &copy)
        this->t = copy.t;
    return (*this);
}
BitcoinExchange::~BitcoinExchange(){};