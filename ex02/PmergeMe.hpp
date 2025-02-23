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

        void ford_johnson_vec(std::vector<int>& v);
        void merge_vec(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right);
        void sort_pairs_vec(std::vector<std::pair<int, int> >& pairs, int group_size);
        std::vector<int> generate_jacobsthal_vec(int n);
        int binary_search_vec(const std::vector<int>& main, int value);

        void ford_johnson_deq(std::deque<int>& v);
        void merge_deq(std::deque<std::pair<int, int> >& pairs, int left, int mid, int right);
        void sort_pairs_deq(std::deque<std::pair<int, int> >& pairs, int group_size);
        std::deque<int> generate_jacobsthal_deq(int n);
        int binary_search_deq(const std::deque<int>& main, int value);

        void printDeq();
        void printVec();
        void printList(char **list);

    private:
        std::vector<int> _vec;
        std::deque<int> _deq;
};

#endif