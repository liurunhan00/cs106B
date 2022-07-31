#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;
const int NONE = -1; // used as sentinel index

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
PQHeap::PQHeap() {
    /* TODO: Implement this function. */
    _numAllocated = INITIAL_CAPACITY;
    _elements = new DataPoint[_numAllocated]();
    _numFilled = 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
PQHeap::~PQHeap() {
    /* TODO: Implement this function. */
    delete []_elements;
}

void PQHeap::swap(int index1, int index2) {
    auto tmp = _elements[index1];
    _elements[index1] = _elements[index2];
    _elements[index2] = tmp;
}

/*
 * enqueue process
 */
void PQHeap::shiftUp(int index) {
    while (index > 0 &&
           _elements[getParentIndex(index)].priority > _elements[index].priority) {
        swap(index, getParentIndex(index));
        index = getParentIndex(index);
    }
}

/*
 * dequeue process
 */
void PQHeap::shiftDown(int index) {
    while (getLeftChildIndex(index) != -1) {
        int swapIndex = getLeftChildIndex(index);
        if (-1 != getRightChildIndex(index)&&
            _elements[getRightChildIndex(index)].priority < _elements[getLeftChildIndex(index)].priority) {
            swapIndex = getRightChildIndex(index);
        }
        if (_elements[swapIndex].priority < _elements[index].priority) {
            swap(swapIndex, index);
            index = swapIndex;
        } else {
            return ;
        }
    }
}

/*
 * double size Heap when _numFilled >= _numAllocated / 2
 */
void PQHeap::resizeHeap() {
    _numAllocated *= 2;
    auto tmp = new DataPoint[_numAllocated]();
    for (int i = 0; i < _numFilled; i++) {
        tmp[i] = _elements[i];
    }

    delete []_elements;
    _elements = tmp;
    tmp = nullptr;
}


/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::enqueue(DataPoint elem) {
    /* TODO: Implement this function. */
    // resize process
    if (_numFilled >= _numAllocated / 2) {
        resizeHeap();
    }
    _elements[_numFilled++] = elem;
    shiftUp(_numFilled - 1);
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
DataPoint PQHeap::peek() const {
    /* TODO: Implement this function. */
    if (isEmpty()) {
        error("PQHeap is empty!");
    }

    return _elements[0];
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
DataPoint PQHeap::dequeue() {
    /* TODO: Implement this function. */
    if (isEmpty()) {
        error("PQHeap is empty!");
    }

    auto front = _elements[0];
    swap(0, --_numFilled);
    shiftDown(0);
    return front;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
bool PQHeap::isEmpty() const {
    /* TODO: Implement this function. */
    return _numFilled == 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
int PQHeap::size() const {
    /* TODO: Implement this function. */
    return _numFilled;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::clear() {
    /* TODO: Implement this function. */
    _numFilled = 0;
}

/*
 * TODO: Replace this comment with a descriptive function
 * comment about your implementation of the function.
 */
void PQHeap::printDebugInfo(string msg) const {
    cout << msg << endl;
    /* TODO: Implement this function. */
}

/*
 * We strongly recommend implementing this helper function, which
 * should traverse the heap array and ensure that the heap property
 * holds for all elements in the array. If elements are found that
 * violate the heap property, an error should be thrown.
 */
void PQHeap::validateInternalState() const {
    /* TODO: Implement this function. */
    if (isEmpty()) {
        return;
    }

    for (int i = 0; i < _numFilled / 2; i++) {
        if ((getLeftChildIndex(i) != -1 && _elements[i].priority > _elements[getLeftChildIndex(i)].priority) ||
            (getRightChildIndex(i) != -1 && _elements[i].priority > _elements[getRightChildIndex(i)].priority) ) {
            const string msg = "Heap parent node index " + to_string(i) + "error in priority";
            error(msg);
        }
    }

    return;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the parent of the
 * specified child index. If this child has no parent, return
 * the sentinel value NONE.
 */
int PQHeap::getParentIndex(int child) const {
    /* TODO: Implement this function. */

    return (child - 1) / 2;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the left child of the
 * specified parent index. If this parent has no left child, return
 * the sentinel value NONE.
 */
int PQHeap::getLeftChildIndex(int parent) const {
    /* TODO: Implement this function. */

    if (parent * 2 + 1 >= _numFilled) return -1;
    return parent * 2 + 1;
}

/*
 * We strongly recommend implementing this helper function, which
 * calculates the index of the element that is the right child of the
 * specified parent index. If this parent has no right child, return
 * the sentinel value NONE.
 */
int PQHeap::getRightChildIndex(int parent) const {
    /* TODO: Implement this function. */

    if (parent * 2 + 2 >= _numFilled) return -1;
    return parent * 2 + 2;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */




/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("PQHeap example from writeup, validate each step") {
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 } };

    pq.validateInternalState();
    for (DataPoint dp : input) {
        pq.enqueue(dp);
        pq.validateInternalState();
    }
    while (!pq.isEmpty()) {
        pq.dequeue();
        pq.validateInternalState();
    }
}
