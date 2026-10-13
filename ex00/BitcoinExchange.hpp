#pragma once
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

class BitcoinExchange{
    private:
        std::map<std::string, double> t;

    public:
        BitcoinExchange();
        BitcoinExchange (const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &copy);    
        ~BitcoinExchange();

        class CouldnotOpen : public std::exception{
            public:
                virtual const char *what() const throw();
        };
};