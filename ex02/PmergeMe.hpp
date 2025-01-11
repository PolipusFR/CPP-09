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

        void parse();
        void sorting();
        void sortVec(int begin, int end);
        void sortDeq(int begin, int end);

        void mergeVec(int begin, int middle, int end);
        void mergeDeq(int begin, int middle, int end);
        void insertVec(int begin, int end);
        void insertDeq(int begin, int end);

        void printVec();
        void printDeq();
        void printList();

    private:
        char **_list;
        std::vector<int> _vec;
        std::deque<int> _deq;
};

#endif