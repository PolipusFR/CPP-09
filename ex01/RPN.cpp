#include "RPN.hpp"


RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

double RPN::processExpression(const std::string &expression)
{
    //verifyExpression(expression);
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] == ' ')
            continue;
        else if (std::isdigit(expression[i]))
            _stack.push(expression[i] - ASCII_SHIFT);
        else if (isOperator(expression[i]))
        {
            if (_stack.size() < 2)
                throw std::invalid_argument("Error: Invalid expression");
            double a = _stack.top();
            _stack.pop();
            double b = _stack.top();
            _stack.pop();
            double result = processOperation(a, b, expression[i]);
            _stack.push(result);  
        }
        else
            throw std::invalid_argument("Error: Invalid expression");
    }
    return _stack.top();
}

bool RPN::isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double RPN::processOperation(double a, double b, char op)
{
    if (op == '+')
        return a + b;
    else if (op == '-')
        return a - b;
    else if (op == '*')
        return a * b;
    else if (op == '/')
    {
        if (b == 0)
            throw std::invalid_argument("Error: Impossible division by zero");
        return a / b;
    }
    throw std::invalid_argument("Error: Invalid operator");
}