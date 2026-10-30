#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac != 2){
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    try {
        btc.load_data("data.csv");
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
        return 1;
    }
    btc.convert(av[1]);
    return 0;
}
