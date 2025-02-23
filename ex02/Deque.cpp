#include "PmergeMe.hpp"

void PmergeMe::printDeq() {
    for (std::deque<int>::iterator it = _deq.begin(); it != _deq.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

std::deque<int> PmergeMe::fordJohnsonSortDeq(std::deque<int> deq) {
    if (deq.size() <= 1)
        return deq;
    bool is_odd = deq.size() % 2;
    size_t num_pairs = deq.size() / 2;
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < num_pairs; ++i) {
        int a = deq[2*i];
        int b = deq[2*i + 1];
        if (a < b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }
    std::sort(pairs.begin(), pairs.end(), std::greater<std::pair<int, int> >());
    std::deque<int> main_chain, sec_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        main_chain.push_back(pairs[i].first);
        sec_chain.push_back(pairs[i].second);
    }
    if (is_odd)
        sec_chain.push_back(deq.back());
    main_chain = fordJohnsonSortDeq(main_chain);
    std::deque<int> order = generateInsertionOrderDeq(sec_chain.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        int val = sec_chain[order[i]];
        std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), val);
        main_chain.insert(pos, val);
    }
    return main_chain;
}

std::deque<int> PmergeMe::generateInsertionOrderDeq(int sec_chain_size) {
    std::deque<int> order;
    if (sec_chain_size == 0)
        return order;
    std::deque<int> jacob = generateJacobsthalDeq(sec_chain_size);
    order.push_back(0);
    if (sec_chain_size >= 2)
        order.push_back(1);
    for (size_t k = 2; k < jacob.size(); ++k)
    {
        int start = jacob[k-1] + 1;
        int end = std::min(jacob[k], sec_chain_size - 1);
        for (int i = end; i >= start; --i)
        {
            order.push_back(i);
            if ((int)order.size() == sec_chain_size)
                break;
        }
        if ((int)order.size() == sec_chain_size)
            break;
    }
    return order;
}

std::deque<int> PmergeMe::generateJacobsthalDeq(int n)
{
    std::deque<int> jacob;
    if (n >= 0)
        jacob.push_back(0);
    if (n >= 1)
        jacob.push_back(1);
    int next = 0;
    while (next <= n)
    {
        next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

void PmergeMe::sortDeq(int begin, int end) {
    std::deque<int> sub(_deq.begin() + begin, _deq.begin() + end + 1);
    std::deque<int> sorted = fordJohnsonSortDeq(sub);
    for (size_t i = 0; i < sorted.size(); ++i)
        _deq[begin + i] = sorted[i];
}