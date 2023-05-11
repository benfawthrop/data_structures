#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
    std::vector<T> m_heap;

public:
    priority_queue() {}

    priority_queue( std::vector<T> const& values )
    {
        for (int i = 0; i < values.size(); i++) {
            push(values[i]);
        }
    }

    const T& top() const
    {
        assert( !m_heap.empty() );
        return m_heap[0];
    }

    void push( const T& entry )
    {
        m_heap.push_back(entry);
        int i = m_heap.size() - 1;
        while (i > 0 && m_heap[i] < m_heap[(i-1) / 2]) {
            T temp = m_heap[i];
            m_heap[i] = m_heap[(i-1) / 2];
            m_heap[(i-1) / 2] = temp;
            i = (i-1) / 2;
        }
    }

    void pop()
    {
        assert( !m_heap.empty() );
        m_heap[0] = m_heap[m_heap.size() - 1];
        m_heap.pop_back();
        int i = 0;
        while (2*i + 1 < m_heap.size()) {
            int child = 2*i + 1;
            if (child + 1 < m_heap.size() && m_heap[child + 1] < m_heap[child]) {
                child++;
            }
            if (m_heap[i] > m_heap[child]) {
                std::swap(m_heap[i], m_heap[child]);
                i = child;
            } else {
                break;
            }
        }
    }

    int size() { return m_heap.size(); }
    bool empty() { return m_heap.empty(); }


    //  The following three functions are used for debugging.

    //  Check to see that internally the heap property is realized.
    bool check_heap( )
    {
        return this->check_heap( this->m_heap );
    }

    //  Check an external vector to see that the heap property is realized.
    bool check_heap( const std::vector<T>& heap )
    {
        for (int i = 0; i < heap.size(); i++) {
            if ((i * 2) + 1 < heap.size()) {
                if (heap[i] < heap[(i * 2) + 1]) {
                    return false;
                }
            } if ((i * 2) + 2 < heap.size()) {
                if (heap[i] < heap[(i * 2) + 2]) {
                    return false;
                }
            }
        }
        return true;
    }

    //  A utility to print the contents of the heap.  Use it for debugging.
    void print_heap( std::ostream & ostr )
    {
        for ( unsigned int i=0; i<m_heap.size(); ++i )
            ostr << i << ": " << m_heap[i] << std::endl;
    }

};

template <class T>
void heapify(std::vector<T> &vec, int n, int i) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && vec[left] > vec[largest])
        largest = left;

    if (right < n && vec[right] > vec[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        std::swap(vec[i], vec[largest]);
        heapify(vec, n, largest);
    }
}

template <class T>
void heap_sort( std::vector<T> &v )
{
    int n = v.size();
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
        std::swap(v[0], v[i]);

        // Heapify root element to get highest element at root again
        heapify(v, i, 0);
    }
}



#endif