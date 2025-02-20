#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::PmergeMe(char **list) {
    parse(list);

    clock_t start, end;
    double time_vec, time_deq;

    std::cout << "Before: " << std::endl;
    printList(list); 
    start = clock();
    sortVec(0, _vec.size() - 1);
    end = clock();
    time_vec = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "After; Vector: " << std::endl;
    printVec();

    start = clock();
    sortDeq(0, _deq.size() - 1);
    end = clock();
    time_deq = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "After; Deque: " << std::endl;
    printDeq();

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector is: " << time_vec << " µs" << std::endl;
    std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque is: " << time_deq << " µs" << std::endl;
}

void PmergeMe::printList(char **list) {
    int i = 1;
    while (list[i]) {
        std::cout << list[i] << " ";
        i++;
    }
    std::cout << std::endl;
}	

void PmergeMe::parse(char **list)
{
    int i,j;

    i = 1;
    while (list[i])
    {
        j = 0;
        while (list[i][j])
        {
            if (!isdigit(list[i][j]))
            {
                std::cerr << "Error: Negative number or non digit detected." << std::endl;
                exit(1);
            }
            j++;
        }
        _vec.push_back(atoi(list[i]));
        _deq.push_back(atoi(list[i]));
        i++;
    }
}
