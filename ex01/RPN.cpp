#include "RPN.hpp"

RPN::RPN() : stack(){}

RPN::RPN(const RPN &copy) : stack(copy.stack){}

RPN &RPN::operator=(const RPN &copy){
    if (this != &copy)
        stack = copy.stack;
    return *this;
}

RPN::~RPN(){}

static long apply(std::list<long> &stack, char op){
    if (stack.size() < 2)
        throw RPN::InvalidExpression();
    long rhs = stack.back();
    stack.pop_back();
    long lhs = stack.back();
    stack.pop_back();
    switch (op){
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/':
            if (rhs == 0)
                throw RPN::DivisionByZero();
            return lhs / rhs;
    }
    throw RPN::InvalidExpression();
}

long RPN::evaluate(const std::string &expr){
    stack.clear();
    std::istringstream in(expr);
    std::string token;
    while (in >> token){
        if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
            stack.push_back(token[0] - '0');
        else if (token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos)
            stack.push_back(apply(stack, token[0]));
        else
            throw InvalidExpression();
    }
    if (stack.size() != 1)
        throw InvalidExpression();
    return stack.back();
}

const char *RPN::InvalidExpression::what() const throw(){
    return "Error";
}

const char *RPN::DivisionByZero::what() const throw(){
    return "Error";
}
