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


void PmergeMe::printVec() {
    for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printDeq() {
    for (std::deque<int>::iterator it = _deq.begin(); it != _deq.end(); it++) {
        std::cout << *it << " ";
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
// Tri Ford-Johnson pour std::vector
std::vector<int> PmergeMe::fordJohnsonSortVec(std::vector<int> vec) {
    if (vec.size() <= 1)
        return vec;
    bool is_odd = vec.size() % 2;
    size_t num_pairs = vec.size() / 2;
    // 1) Regrouper les éléments de vec en vec.size()/2 paires
    // Si vec a un nombre d elements impair, laisser 1 elem de cote
    
    // 2) Trier les paires avec le plus grand élément en premier
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < num_pairs; ++i)
    {
        int a = vec[2*i];
        int b = vec[2*i + 1];
        if (a < b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }
    std::sort(pairs.begin(), pairs.end(), std::less<std::pair<int, int> >()); // Tri ascendant
    std::vector<int> main_chain, sec_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        main_chain.push_back(pairs[i].first);
        sec_chain.push_back(pairs[i].second);
    }
    if (is_odd)
        sec_chain.push_back(vec.back());
    // Trier récursivement la chaîne principale
    main_chain = fordJohnsonSortVec(main_chain);
    std::vector<int> order = generateInsertionOrder(sec_chain.size());
    for (size_t i = 0; i < order.size(); ++i) {
        int val = sec_chain[order[i]];
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), val);
        main_chain.insert(pos, val);
    }
    return main_chain;
}

// Tri Ford-Johnson pour std::deque (similaire)
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

// Générer l'ordre d'insertion Jacobsthal
std::vector<int> PmergeMe::generateInsertionOrder(int sec_chain_size) {
    std::vector<int> order;
    if (sec_chain_size == 0)
        return order;

    std::vector<int> jacob = generateJacobsthal(sec_chain_size);
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

// Générer la séquence de Jacobsthal
std::vector<int> PmergeMe::generateJacobsthal(int n)
{
    std::vector<int> jacob;
    if (n >= 0)
        jacob.push_back(0);
    if (n >= 1)
        jacob.push_back(1);
    int next;
    while (next <= n)
    {
        next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

std::deque<int> PmergeMe::generateJacobsthalDeq(int n)
{
    std::deque<int> jacob;
    if (n >= 0)
        jacob.push_back(0);
    if (n >= 1)
        jacob.push_back(1);
    int next;
    while (next <= n)
    {
        next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

// Tri du vecteur
void PmergeMe::sortVec(int begin, int end) {
    std::vector<int> sub(_vec.begin() + begin, _vec.begin() + end + 1);
    std::vector<int> sorted = fordJohnsonSortVec(sub);
    for (size_t i = 0; i < sorted.size(); ++i)
        _vec[begin + i] = sorted[i];
}

// Tri de la deque
void PmergeMe::sortDeq(int begin, int end) {
    std::deque<int> sub(_deq.begin() + begin, _deq.begin() + end + 1);
    std::deque<int> sorted = fordJohnsonSortDeq(sub);
    for (size_t i = 0; i < sorted.size(); ++i)
        _deq[begin + i] = sorted[i];
}