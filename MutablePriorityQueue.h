/*
 * MutablePriorityQueue.h
 * A simple implementation of mutable priority queues, required by Dijkstra algorithm.
 *
 * Created on: 17/03/2018
 *      Author: João Pascoal Faria
 */

#ifndef DA_TP_CLASSES_MUTABLEPRIORITYQUEUE
#define DA_TP_CLASSES_MUTABLEPRIORITYQUEUE

#include <vector>
using namespace std;

/**
 * class M must have: (i) accessible field int queueIndex; (ii) operator< defined.
 */

template <class M>
class MutablePriorityQueue {
    std::vector<M *> H;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, M * x);
    void printQueue();
public:
    MutablePriorityQueue();
    void insert(M * x);
    M * extractMin();
    void decreaseKey(M * x);
    bool empty();
};

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

template <class M>
MutablePriorityQueue<M>::MutablePriorityQueue() {
    H.push_back(nullptr);
    // indices will be used starting in 1
    // to facilitate parent/child calculations
}

template <class M>
bool MutablePriorityQueue<M>::empty() {
    return H.size() == 1;
}

template <class M>
M* MutablePriorityQueue<M>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

template <class M>
void MutablePriorityQueue<M>::insert(M *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

template <class M>
void MutablePriorityQueue<M>::decreaseKey(M *x) {
    printQueue();
    heapifyUp(x->queueIndex);
    printQueue();
}

template <class M>
void MutablePriorityQueue<M>::printQueue() {
    cout << "Priority Queue Contents: ";
    for (unsigned i = 1; i < H.size(); ++i) {
        cout << H[i]->getInfo() << " ";
    }
    cout << endl;
}

template <class M>
void MutablePriorityQueue<M>::heapifyUp(unsigned i) {
    auto x = H[i];
    cout << "heapifyUp: Starting at position " << i << " with element: " << x->getInfo() << endl;
    while (i > 1 && *x < *H[parent(i)]) {
        cout << "heapifyUp: Swapping with parent at position " << parent(i) << endl;
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
    cout << "heapifyUp: Finished at position " << i << " with element: " << x->getInfo() << endl;
}

template <class M>
void MutablePriorityQueue<M>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

template <class M>
void MutablePriorityQueue<M>::set(unsigned i, M * x) {
    cout << "Setting position " << i << " with element: " << x->getInfo() << endl;
    cout << "Element queueIndex before setting: " << x->queueIndex << endl;
    H[i] = x;
    x->queueIndex = i;
    // Debugging output for queueIndex after setting
    cout << "Element queueIndex after setting: " << x->queueIndex << endl;
}

#endif /* DA_TP_CLASSES_MUTABLEPRIORITYQUEUE */