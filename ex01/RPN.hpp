#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <exception>
#include <cctype>

#define ASCII_SHIFT 48

class RPN
{
    private:
        std::stack<double> _stack;
    
    public:
        RPN();
        RPN(const RPN &other);
        ~RPN();
        RPN &operator=(const RPN &other);

        double processExpression(const std::string &expression);
        bool isOperator(char c);
        double processOperation(double a, double b, char op);
        void verifyExpression(const std::string &expression);
};

#endif