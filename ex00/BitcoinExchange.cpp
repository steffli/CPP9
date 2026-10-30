#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() : t(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : t(copy.t){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy){
    if (this != &copy)
        t = copy.t;
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

static std::string trim(const std::string &s){
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

static bool is_digits(const std::string &s){
    return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

// date format: YYYY-MM-DD
static bool validate_date(std::string date){
    std::stringstream s(date);
    std::string year, month, day, extra;
    if (!std::getline(s, year, '-') || !std::getline(s, month, '-') || !std::getline(s, day, '-'))
        return false;
    if (std::getline(s, extra, '-'))
        return false;
    if (!is_digits(year) || !is_digits(month) || !is_digits(day))
        return false;
    int m = std::atoi(month.c_str());
    int d = std::atoi(day.c_str());
    return m >= 1 && m <= 12 && d >= 1 && d <= 31;
}

static bool parse_number(const std::string &s, double &value){
    if (s.empty())
        return false;
    char *end = NULL;
    value = std::strtod(s.c_str(), &end);
    // value == value is false for NaN, which strtod accepts from "nan"
    return *end == '\0' && value == value;
}

static bool validate_rate(std::string rate, double &value){
    return parse_number(rate, value) && value >= 0;
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

void BitcoinExchange::convert(const std::string &file) const{
    std::ifstream in(file.c_str());
    if (!in){
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)){
        size_t bar = line.find('|');
        if (bar == std::string::npos){
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, bar));
        std::string str = trim(line.substr(bar + 1));
        double value;
        if (!validate_date(date))
            std::cout << "Error: bad input => " << date << std::endl;
        else if (!parse_number(str, value))
            std::cout << "Error: bad input => " << line << std::endl;
        else if (value < 0)
            std::cout << "Error: not a positive number." << std::endl;
        else if (value > 1000)
            std::cout << "Error: too large a number." << std::endl;
        else {
            // closest date on or before the requested one
            std::map<std::string, double>::const_iterator it = t.upper_bound(date);
            if (it == t.begin())
                std::cout << "Error: bad input => " << date << std::endl;
            else {
                --it;
                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
            }
        }
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
