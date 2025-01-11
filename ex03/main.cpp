#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./ex02 [num1] [num2] ... [numN]" << std::endl;
        return 1;
    }
    PmergeMe pmm(argv);
}
