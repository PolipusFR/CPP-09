#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void merge(vector<int>& v, int left, int mid, int right) {
    vector<int> temp;
    int i = left;
    int j = mid;
    while (i < mid && j < right) {
        if (v[i] <= v[j]) {
            temp.push_back(v[i++]);
        } else {
            temp.push_back(v[j++]);
        }
    }
    while (i < mid) {
        temp.push_back(v[i++]);
    }
    while (j < right) {
        temp.push_back(v[j++]);
    }
    for (int k = 0; k < (int)temp.size(); ++k) {
        v[left + k] = temp[k];
    }
}

void recursive_pair_sort(vector<int>& v, int block_size) {
    if (block_size >= (int)v.size()) {
        return;
    }
    for (int i = 0; i < (int)v.size(); i += 2 * block_size) {
        int left = i;
        int mid = min(i + block_size, (int)v.size());
        int right = min(i + 2 * block_size, (int)v.size());
        merge(v, left, mid, right);
    }
    recursive_pair_sort(v, block_size * 2);
}

void sort_vector(vector<int>& v) {
    recursive_pair_sort(v, 1);
}

int main() {
    // Initialize a vector with some integers
    vector<int> v = {11, 2, 17, 0, 16, 8, 6, 15, 10, 3, 21, 1, 18, 9, 14, 19, 12, 5, 4, 20, 13, 7};

    // Print the original vector
    cout << "Original vector: ";
    for (int num : v) {
        cout << num << " ";
    }
    cout << endl;

    // Sort the vector
    sort_vector(v);

    // Print the sorted vector
    cout << "Sorted vector: ";
    for (int num : v) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}