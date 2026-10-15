#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() : t(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : t(copy.t){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy){
    if (this != &copy)
        t = copy.t;
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

// date format: YYYY-MM-DD
static bool validate_date(std::string date){
    std::stringstream s(date);
    std::string year, month, day;
    if (!std::getline(s, year, '-') || !std::getline(s, month, '-') || !std::getline(s, day, '-'))
        return false;
    int m = std::atoi(month.c_str());
    int d = std::atoi(day.c_str());
    return m >= 1 && m <= 12 && d >= 1 && d <= 31;
}

static bool validate_rate(std::string rate, double &value){
    if (rate.empty())
        return false;
    char *end = NULL;
    value = std::strtod(rate.c_str(), &end);
    return *end == '\0' && value >= 0;
}

void BitcoinExchange::load_data(std::string file){
    std::ifstream in(file.c_str());
    if (!in)
        throw CouldNotOpen();

    std::string line;
    std::getline(in, line);
    double value;

    while (std::getline(in, line)){
        size_t comma = line.find(',');
        if (comma == std::string::npos)
            throw InvalidFile();

        std::string date = line.substr(0, comma);
        std::string rate = line.substr(comma + 1);
        if (!validate_date(date))
            throw InvalidDate();
        if (!validate_rate(rate, value))
            throw InvalidRate();
        t[date] = value;
    }
}

const char *BitcoinExchange::CouldNotOpen::what() const throw(){
    return "File could not be opened.";
}

const char *BitcoinExchange::InvalidFile::what() const throw(){
    return "Invalid formatting of the file.";
}

const char *BitcoinExchange::InvalidDate::what() const throw(){
    return "Invalid date.";
}

const char *BitcoinExchange::InvalidRate::what() const throw(){
    return "Invalid rate.";
}
