#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

void PmergeMe::printVec() {
    for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

// Merge two sorted groups of pairs (sorted by their `a` values)
void PmergeMe::merge_vec(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right) {
    std::vector<std::pair<int, int> > temp;
    int i = left;
    int j = mid;
    while (i < mid && j < right)
    {
        if (pairs[i].second <= pairs[j].second)
            temp.push_back(pairs[i++]);
        else
            temp.push_back(pairs[j++]);
    }
    while (i < mid)
        temp.push_back(pairs[i++]);
    while (j < right)
        temp.push_back(pairs[j++]);
    for (int k = 0; k < static_cast<int>(temp.size()); ++k)
        pairs[left + k] = temp[k];
}

// Recursively sort pairs by `a` values
void PmergeMe::sort_pairs_vec(std::vector<std::pair<int, int> >& pairs, int group_size) {
    if (group_size >= static_cast<int>(pairs.size()))
        return;
    for (int i = 0; i < static_cast<int>(pairs.size()); i += 2 * group_size)
    {
        int left = i;
        int mid = std::min(left + group_size, static_cast<int>(pairs.size()));
        int right = std::min(left + 2 * group_size, static_cast<int>(pairs.size()));
        merge_vec(pairs, left, mid, right);
    }
    sort_pairs_vec(pairs, group_size * 2);
}

// Generate Jacobsthal numbers up to `n`
std::vector<int> PmergeMe::generate_jacobsthal_vec(int n) {
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() <= n)
    {
        int next = jacob[jacob.size()-1] + 2 * jacob[jacob.size()-2];
        jacob.push_back(next);
    }
    return jacob;
}

// Binary search to find insertion point in `main`
int PmergeMe::binary_search_vec(const std::vector<int>& main, int value) {
    int low = 0;
    int high = main.size();
    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (main[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

void PmergeMe::ford_johnson_vec(std::vector<int>& v) {
    if (v.size() <= 1) return;

    // Handle odd element
    bool has_odd = v.size() % 2 != 0;
    int odd_element = has_odd ? v.back() : -1;
    if (has_odd)
        v.pop_back();

    // Step 1: Form pairs and sort them by `a` values
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < v.size(); i += 2)
    {
        int a = v[i];
        int b = v[i + 1];
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    // Sort pairs by `a` values
    sort_pairs_vec(pairs, 1);

    // Step 2: Extract `main` and `pend`
    std::vector<int> main, pend;
    if (!pairs.empty())
    {
        main.push_back(pairs[0].first); // b1
        for (size_t i = 0; i < pairs.size(); ++i)
        {
            main.push_back(pairs[i].second);    // a's
            if (i > 0) // Skip b1 for pend
                pend.push_back(pairs[i].first);
        }
    }

    // Step 3: Insert `pend` elements using Jacobsthal sequence
    std::vector<int> jacob = generate_jacobsthal_vec(pend.size());
    std::vector<bool> inserted(pend.size(), false);

    // Insert in Jacobsthal order (reverse iteration)
    for (int k = static_cast<int>(jacob.size()) - 1; k >= 0; --k)
    {
        int j = jacob[k];
        if (j == 0 || j > static_cast<int>(pend.size())) 
            continue;
        for (int i = j - 1; i >= 0; --i) 
        {
            if (i < static_cast<int>(pend.size()) && !inserted[i])
            {
                int pos = binary_search_vec(main, pend[i]);
                main.insert(main.begin() + pos, pend[i]);
                inserted[i] = true;
            }
        }
    }

    // Insert remaining elements in `pend`
    for (size_t i = 0; i < pend.size(); ++i)
    {
        if (!inserted[i])
        {
            int pos = binary_search_vec(main, pend[i]);
            main.insert(main.begin() + pos, pend[i]);
        }
    }

    // Final loop to insert odd element if present
    if (has_odd)
    {
        int pos = binary_search_vec(main, odd_element);
        main.insert(main.begin() + pos, odd_element);
    }

    v = main;
}