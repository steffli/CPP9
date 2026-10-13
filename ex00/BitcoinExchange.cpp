#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : t(){};

BitcoinExchange::BitcoinExchange (const BitcoinExchange &copy) : t(copy.t){};

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy){
    if (this != &copy)
        this->t = copy.t;
    return (*this);
}
BitcoinExchange::~BitcoinExchange(){};

void BitcoinExchange::load_data(std::string file){
    std::ifstream in(file.c_str());
    if (!in)
        throw CouldNotOpen();
    std::string line;
    std::getline(in, line);
    while(std::getline(in, line)){
        size_t comma = line.find(",");
        if (comma == std::string::npos)
            throw InvalidFile();
        
        std::string date = line.substr(0, comma);
        std::string rate = line.substr(comma + 1);
        if (!valid_date(date))
            throw InvalidDate();
        if (!valid_rate(rate))
            throw InvalidRate();
        t[date] = rate;
    }
}


int validate_date(std::string line){
 
}

const char* BitcoinExchange::CouldNotOpen::what() const throw(){
    std::cout << "File could not be opened." << std::endl;
}

const char* BitcoinExchange::InvalidFile::what() const throw(){
    std::cout << "Invalid Formatting of the file." << std::endl;
}

const char* BitcoinExchange::InvalidDate::what() const throw(){
    std::cout << "Invalid Date." << std::endl;
}

const char* BitcoinExchange::InvalidRate::what() const throw(){
    std::cout << "Invalid Rate" << std::endl;
}