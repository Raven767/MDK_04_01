#include <iostream>
#include "PriorityQueue.cpp"
using namespace N;
//от большего к меньшему
template<typename T> struct hcmp {
    bool operator () (const T& a, const T& b) const {
        return (a > b);
    }
};

//от меньшему к большему
template<typename T> struct lcmp {
    bool operator () (const T& a, const T& b) const {
        return (a < b);
    }
};
int main(void) {

    int a[] = { 3, 4, 9, 7, 8, 2, 0, 1, 6 };
    PriorityQueue<int, hcmp<int>> pq1;

    for (int i : a)
        pq1.push1(i);

    while (!pq1.empty()) {
        std::cout << pq1.top() << ' ';
        pq1.pop();
    }
    std::cout << std::endl;

    PriorityQueue<int, lcmp<int> > pq2(std::cbegin(a), std::cend(a));

    while (!pq2.empty()) {
        std::cout << pq2.top() << ' ';
        pq2.pop();
    }
    std::cout << std::endl;
    std::cin.get();
    return 0;
};