/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BPlusTree {
        public:
            // constructors
            // default constructor
            BPlusTree(int b) : num_keys(b - 1), num_pointers(b) {};
            ~BPlusTree() { clear(); }; // destructor
            BPlusTree(BPlusTree &other); // copy constructor

            // setters

            // inserts element into the B+ tree at the proper position
            void insert(const T& to_insert);

            // getters

            // returns a pointer to the node where to_find is found
            // (or where it would be found if it doesn't already)
            BPlusTreeNode<T>* find(const T& to_find);

            //outputs

            void print_sideways(std::ofstream &outfile);
            void print_BFS(std::ofstream &outfile);
            void print_BFS_pretty(std::ofstream &outfile);


        private:
            int num_keys; // number of keys a node can hold (b - 1)
            int num_pointers; // number of daughter pointers that a node can hold (b)
            BPlusTreeNode<T>* head; // head node of the tree
            BPlusTreeNode<T>* find_helper(const T& to_find, BPlusTreeNode<T>* node);
            void clear(); // helper for the destructor
            void clearHelper(BPlusTreeNode<T>* &node); // recursive helper for clear fxn
            // recursive helper for copy constructor
            BPlusTreeNode<T>* copyHelper(BPlusTreeNode<T>* &node);
            void insertHelper(BPlusTreeNode<T>* &node, const T& val);

        };

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copyHelper(BPlusTreeNode<T>* &node) {
    if (!node) { return nullptr; } // base case
    // allocates space in memory for the new copied node
    BPlusTreeNode<T>* temp = new BPlusTreeNode<T>();
    temp->keys = node->keys; // copies keys
    for (unsigned long int i = 0; i < node->children.size(); i++) {
        // loops through all children nodes and recursively copies them
        temp->children.push_back(nullptr);
        temp->children[i] = copyHelper(node->children[i]);
        temp->children[i]->parent = temp;
    }
    return temp;
}

template <class T>
BPlusTree<T>::BPlusTree(BPlusTree<T> &other) {
    // copies basic variables and uses recursive helper to copy nodes
    num_keys = other.num_keys;
    num_pointers = other.num_pointers;
    head = copyHelper(other.head);
}

template <class T>
void BPlusTree<T>::clear() {
    // calls the recursive clear function for the destructor
    clearHelper(head);
}

template <class T>
void BPlusTree<T>::clearHelper(BPlusTreeNode<T>* &node) {
    if (!node) { return; } // base case
    for (int i = 0; i < node->children.size(); i++) {
        // recurses and deletes all children nodes
        clearHelper(node->children[i]);
    }
    // deletes itself
    delete node;
}

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& to_find) {
    BPlusTreeNode<T>* node = head;

    while (!node->is_leaf()) {
        // loops through all leaf nodes until it finds the leaf node that could store
        // the to_find key
        typename std::vector<T>::iterator it =
                std::lower_bound(node->keys.begin(), node->keys.end(), to_find);
        node = node->children[it - node->keys.begin()];
    }

    // returns the node that it can be stored at
    return node;
}

template <class T>
void BPlusTree<T>::insert(const T& to_insert) {
    if (!head) { // tree is empty
        head = new BPlusTreeNode<T>();
        head->keys.push_back(to_insert);
        return;
    }
    BPlusTreeNode<T>* node = find(to_insert); // find the node where to insert
    insertHelper(node, to_insert); // insert the element
}

template <class T>
void BPlusTree<T>::insertHelper(BPlusTreeNode<T>* &node, const T& val) {
    // get the iterator to the position to insert
    typename std::vector<T>::iterator it = std::lower_bound(
            node->keys.begin(), node->keys.end(), val);
    node->keys.insert(it, val); // insert the value
    if (node->keys.size() >= num_pointers) { // if the node is full
        int mid = node->keys.size() / 2; // get the middle index
        // create a new node for the right half
        BPlusTreeNode<T>* right = new BPlusTreeNode<T>();

        // copy the right half of the keys to the new node
        right->keys.assign(node->keys.begin() + mid, node->keys.end());

        // erase the right half of the keys from the old node
        node->keys.erase(node->keys.begin() + mid, node->keys.end());

        if (!node->parent) { // if the node is the root
            node->parent = new BPlusTreeNode<T>(); // create a new root
            head = node->parent;
        }
        right->parent = node->parent; // set the parent of the new node

        // find the iterator to the old node
        typename std::vector<BPlusTreeNode<T>*>::iterator it2 = std::find(
                node->parent->children.begin(), node->parent->children.end(), node);

        // insert the new node to the parent
        node->parent->children.insert(it2 + 1, right);
        if (node->is_leaf()) { // if the node is a leaf
            // copy the last child pointer to the new node
            right->children.push_back(node->children.back());
            // erase the last child pointer from the old node
            node->children.pop_back();
        }
        else { // if the node is an internal node
            // copy the right half of the child pointers to the new node
            right->children.assign(node->children.begin() + mid, node->children.end());
            for (typename std::vector<BPlusTreeNode<T>*>::iterator it3 =
                    right->children.begin(); it3 != right->children.end(); ++it3) {
                (*it3)->parent = right; // set the parent of the child pointers
            }
            // erase the right half of the child pointers from the old node
            node->children.erase(node->children.begin() + mid, node->children.end());
        }
        // insert the first key of the new node to the parent
        insertHelper(node->parent, right->keys.front());
    }
}


//template <class T>
//void BPlusTree<T>::insert(const T& to_insert) {
//    // Find the leaf node where the key should be inserted
//    BPlusTreeNode<T>* node = find(to_insert);
//
//    // check to see if the key can be added or if we need to split
//    if (node->keys.size() <= num_keys) {
//        node->keys.push_back(to_insert);
//        std::sort(node->keys.begin(), node->keys.end());
//        return;
//    }
//
//    // splits bucket into two half vectors
//    int length_of_og_keys = ceil((node->keys.size() + 1) / 2);
//    std::vector<T> upper_half(node->keys.end() - length_of_og_keys, node->keys.end());
//    std::vector<T> lower_half(node->keys.begin(), node->keys.begin() + length_of_og_keys);
//
//    // adds the key to the parent node for splitting
//    node->parent->keys.push_back(upper_half[0]);
//    std::sort(node->parent.begin(), node->parent.end());
//}

#endif
