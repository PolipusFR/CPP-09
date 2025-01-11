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

PmergeMe::PmergeMe(char **list) : _list(list)
{
    parse();
    sorting();
    return;
}

void PmergeMe::printVec() {
    for (long unsigned int i = 0; i < _vec.size(); i++) {
        std::cout << _vec[i].value << " ";
    }
    std::cout << std::endl;
}

// void PmergeMe::printDeq() {
//     for (std::deque<int>::iterator it = _deq.begin(); it != _deq.end(); it++) {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;
// }

void PmergeMe::printList() {
    int i = 1;
    while (_list[i]) {
        std::cout << _list[i] << " ";
        i++;
    }
    std::cout << std::endl;
}

NumberToSort PmergeMe::atonts(char *str) {
    NumberToSort nts;
    nts.x = 0;
    nts.y = 0;
    nts.value = atoi(str);
    return nts;
}
    

void PmergeMe::parse()
{
    int i,j;

    i = 1;
    while (_list[i])
    {
        j = 0;
        while (_list[i][j])
        {
            if (!isdigit(_list[i][j]))
            {
                std::cerr << "Error: Negative number or non digit detected." << std::endl;
                exit(1);
            }
            j++;
        }
        _vec.push_back(atonts(_list[i]));
        _deq.push_back(atonts(_list[i]));
        i++;
    }
}

void PmergeMe::sorting()
{
    clock_t start, end;
    double time_vec;

    std::cout << "Before: " << std::endl;
    printList(); 
    start = clock();
    sortVec();
    end = clock();
    time_vec = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "After; Vector: " << std::endl;
    printVec();

    // start = clock();
    // sortDeq(0, _deq.size() - 1);
    // end = clock();
    // time_deq = (double)(end - start) / CLOCKS_PER_SEC;
    // std::cout << "After; Deque: " << std::endl;
    // printDeq();

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector is: " << time_vec << " µs" << std::endl;
    // std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque is: " << time_deq << " µs" << std::endl;

    return;
}

void PmergeMe::mergeVec(int begin, int middle, int end)
{
    std::vector<NumberToSort> left(_vec.begin() + begin, _vec.begin() + middle + 1);
    std::vector<NumberToSort> right(_vec.begin() + middle + 1, _vec.begin() + end + 1);
    size_t left_i = 0;
    size_t right_i = 0;

    for (int i = begin; i <= end; i++)
    {
        if (right_i == right.size())
        {
            _vec[i] = left[left_i];
            left_i++;
        }
        else if (left_i == left.size())
        {
            _vec[i] = right[right_i];
            right_i++;
        }
        else if (left[left_i].value < right[right_i].value)
        {
            _vec[i] = left[left_i];
            left_i++;
        }
        else
        {
            _vec[i] = right[right_i];
            right_i++;
        }
    } 

}

// void PmergeMe::mergeDeq(int begin, int middle, int end)
// {
//     std::deque<int> left(_deq.begin() + begin, _deq.begin() + middle + 1);
//     std::deque<int> right(_deq.begin() + middle + 1, _deq.begin() + end + 1);
//     size_t left_i = 0;
//     size_t right_i = 0;

//     for (int i = begin; i <= end; i++)
//     {
//         if (right_i == right.size())
//         {
//             _deq[i] = left[left_i];
//             left_i++;
//         }
//         else if (left_i == left.size())
//         {
//             _deq[i] = right[right_i];
//             right_i++;
//         }
//         else if (left[left_i] < right[right_i])
//         {
//             _deq[i] = left[left_i];
//             left_i++;
//         }
//         else
//         {
//             _deq[i] = right[right_i];
//             right_i++;
//         }
//     }
// }

void PmergeMe::insertVec(int begin, int end)
{
    for (int i = begin; i < end; i++)
    {
        NumberToSort temp = _vec[i + 1];
        int j = i + 1;
        while (j > begin && _vec[j - 1].value > temp.value)
        {
            _vec[j] = _vec[j - 1];
            j--;
        }
        _vec[j] = temp;
    }
}

// void PmergeMe::insertDeq(int begin, int end)
// {
//     for (int i = begin; i < end; i++)
//     {
//         int temp = _deq[i + 1];
//         int j = i + 1;
//         while (j > begin && _deq[j - 1] > temp)
//         {
//             _deq[j] = _deq[j - 1];
//             j--;
//         }
//         _deq[j] = temp;
//     }
// }

void PmergeMe::sortVec()
{
    for (long unsigned int i = 0; i < _vec.size(); i += 2)
    {
        if (_vec[i].value > _vec[i + 1].value)
        {
            int temp = _vec[i].value;
            _vec[i] = _vec[i + 1];
            _vec[i + 1].value = temp;
        }
    }
    std::cout << "Step 1: Determine the min and max in pairs: " << std::endl;
    printVec();
}

// void PmergeMe::sortDeq(int begin, int end)
// {
//     if (end - begin > 5)
//     {
//         int middle = (begin + end) / 2;
//         sortDeq(begin, middle);
//         sortDeq(middle + 1, end);
//         mergeDeq(begin, middle, end);
//     }
//     else
//         insertDeq(begin, end);
// }
