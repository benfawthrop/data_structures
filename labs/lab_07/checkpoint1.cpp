//
// Created by Benjamin Fawthrop on 2/22/23.
//
#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 10.
template <class T>
class Node {
public:
    T value;
    Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
    std::cout << label;
    Node<T> *tmp = data;
    while (tmp != NULL) {
        std::cout << " " << tmp->value;
        tmp = tmp->ptr;
    }
    std::cout << std::endl;
}


/*
 * Pseudo Code:
 * Previous is a pointer to null
 * current is a pointer to the first node
 * next is a pointer to null
 *
 * while our current doesn't point to null:
 *      next is now pointing to the node after our current
 *      the pointer at our current node is po   inting to the previous node
 *      the previous pointer is now pointing to our current node
 *      our current pointer is now pointing to the following node
 * after the loop, our head then points to the old last node
 * */

template <class T>
void reverse(Node<T>* &input) {
    // FILL IN THIS FUNCTION
    Node<T>* prev = nullptr;
    Node<T>* curr = input;
    Node<T>* next = nullptr;
    while (curr != nullptr) {
        next = curr->ptr;  // save next node before reversing pointers
        curr->ptr = prev;  // reverse the pointer to the previous node
        prev = curr;       // move previous to current node
        curr = next;       // move current to next node
    }
    input = prev;        // update head of the list
}




int main() {

    // manually create a linked list of notes with 4 elements
    Node<int>* my_list = new Node<int>;
    my_list->value = 1;
    my_list->ptr = new Node<int>;
    my_list->ptr->value = 2;
    my_list->ptr->ptr = new Node<int>;
    my_list->ptr->ptr->value = 3;
    my_list->ptr->ptr->ptr = new Node<int>;
    my_list->ptr->ptr->ptr->value = 4;
    my_list->ptr->ptr->ptr->ptr = NULL;


    print(my_list,"my_list before");
    reverse(my_list);
    print(my_list,"my_list after ");


    // extra test cases
    Node<int>* my_list2 = new Node<int>;
    print (my_list2, "my_list of length 0 before");
    reverse(my_list2);
    print (my_list2, "my_list of length 0 after");

    // Note: We are not deleting any of the Nodes we created...  so this
    // program has memory leaks!  More on this in Checkpoint 2!

}

// ===========================================================================