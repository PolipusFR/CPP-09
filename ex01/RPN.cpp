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
    verifyExpression(expression);
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
        return b + a;
    else if (op == '-')
        return b - a;
    else if (op == '*')
        return b * a;
    else if (op == '/')
    {
        if (b == 0)
            throw std::invalid_argument("Error: Impossible division by zero");
        return b / a;
    }
    throw std::invalid_argument("Error: Invalid operator");
}

void RPN::verifyExpression(const std::string &expression)
{
    if (expression.empty())
        throw std::invalid_argument("Error: Empty expression");
    if (expression[0] == ' ' || expression[expression.size() - 1] == ' ')
        throw std::invalid_argument("Error: Invalid expression");
    int operators = 0;
    int operands = 0;
    int space = 0;
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] == ' ')
            space++;
        else if (std::isdigit(expression[i]))
            operands++;
        else if (isOperator(expression[i]))
            operators++;
        else
            throw std::invalid_argument("Error: Invalid expression");
    }
    if (space != operators + operands - 1)
        throw std::invalid_argument("Error: Invalid expression");
    if (operands != operators + 1 || operators == 0)
        throw std::invalid_argument("Error: Invalid expression");
}
