#include "BitcoinExchange.hpp"

int main(int ac, char **av){
    if (ac != 2)
        return(std::cout << "Invalid number of arguments.\nUsage: ./btc [file-name]." << std::endl, 1);

    std::ifstream file(av[1]);
    std::string line;
    if (file.is_open()){
        while(std::getline(file, line)){
            std::cout << line << std::endl;
        }
        file.close();
    }
    return 0;
}