#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <stdexcept>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        ~PmergeMe();
        PmergeMe &operator=(const PmergeMe &other);
        PmergeMe (char **list);

        void parse(char **list);

        std::vector<int> fordJohnsonSortVec(std::vector<int> vec);
        std::deque<int> fordJohnsonSortDeq(std::deque<int> deq);
        std::vector<int> generateInsertionOrder(int pend_size);
        std::deque<int> generateInsertionOrderDeq(int pend_size);
        std::vector<int> generateJacobsthal(int n);
        std::deque<int> generateJacobsthalDeq(int n);
        
        void sortVec(int begin, int end);
        void sortDeq(int begin, int end);

        void printVec();
        void printDeq();
        void printList(char **list);

    private:
        std::vector<int> _vec;
        std::deque<int> _deq;
};

#endif