#pragma once
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>

class RPN{
    private:
        std::list<long> stack;

    public:
        RPN();
        RPN(const RPN &copy);
        RPN &operator=(const RPN &copy);
        ~RPN();

        long evaluate(const std::string &expr);

        class InvalidExpression : public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class DivisionByZero : public std::exception{
            public:
                virtual const char *what() const throw();
        };
};
