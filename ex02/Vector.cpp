#include "PmergeMe.hpp"

void PmergeMe::printVec() {
    for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
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
    // 3) Trier récursivement les vec.size()/2 plus grands éléments de chaque paire
    main_chain = fordJohnsonSortVec(main_chain);
    // 4) Inserer dans main chain le reste des elements de sec chain
    std::vector<int> order = generateInsertionOrder(sec_chain.size());
    for (size_t i = 0; i < order.size(); ++i) {
        int val = sec_chain[order[i]];
        std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), val);
        main_chain.insert(pos, val);
    }
    return main_chain;
}

// Générer l'ordre d'insertion grace a la sequence de Jacobsthal
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

// Générer la séquence de Jacobsthal
std::vector<int> PmergeMe::generateJacobsthal(int n)
{
    std::vector<int> jacob;
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

// Fonction actionnant le tri du vecteur
void PmergeMe::sortVec(int begin, int end) {
    std::vector<int> sub(_vec.begin() + begin, _vec.begin() + end + 1);
    std::vector<int> sorted = fordJohnsonSortVec(sub);
    for (size_t i = 0; i < sorted.size(); ++i)
        _vec[begin + i] = sorted[i];
}
