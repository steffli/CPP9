#pragma once
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <exception>

class BitcoinExchange{
    private:
        std::map<std::string, double> t;

    public:
        BitcoinExchange();
        BitcoinExchange (const BitcoinExchange &copy);
        BitcoinExchange &operator=(const BitcoinExchange &copy);
        ~BitcoinExchange();

        void load_data(std::string file);
        void convert(const std::string &file) const;

        class CouldNotOpen : public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class InvalidFile : public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class InvalidDate : public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class InvalidRate : public std::exception{
            public:
                virtual const char *what() const throw();
        };
};


