#include "BSTree.h"

#include <iostream>
#include <queue>

using namespace std;

///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement 


// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
    tree.print_level_by_level(out);
    return out;
}

ostream& operator<<(ostream& out, Node& node)
{
    return out << node.value << "[" << node.search_time << "]";
}

istream& operator>>(istream& in, BSTree& tree)
{
    /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
    int next;
    while(in >> next) {
        tree.insert(next);
    }
    return in;
}

// Example recursive function
// If you try to use it without care, you will get a memory leak.
void BSTree::copy_helper(Node*& newNode, const Node* sourceNode) {
    //Don't copy if the node is nullptr
    if(sourceNode == nullptr)
        return;

    //Change the new node to a copy of sourceNode
    newNode = new Node(sourceNode->value);
    //Copy over the search cost
    newNode->search_time = sourceNode->search_time;

    //Copy left subtree
    if (sourceNode->left != nullptr)
        copy_helper(newNode->left, sourceNode->left);
    //Copy right subtree
    if(sourceNode->right != nullptr)
        copy_helper(newNode->right, sourceNode->right);
}

// recursive function
int BSTree::get_total_search_time(Node* node)
{
  if (node != nullptr) {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}


///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

// copy constructor
BSTree::BSTree(const BSTree& other)
{
    size = other.size;
    root = nullptr;
    copy_helper(root, other.root);
}

// move constructor
BSTree::BSTree(BSTree&& other)
{
    size = other.size;
    root = other.root;
    other.size = 0;
    other.root = nullptr;
    
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
    if ( this != &other ) {
        root_helper(root);
        size = other.size;
        root = nullptr;
        copy_helper(root, other.root);
    }
    return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other)
{
    if ( this != &other ) {
        root_helper(root);
        size = other.size;
        root = other.root;
        other.size = 0;
        other.root = nullptr;
    }
    return *this;
}

// destructor
BSTree::~BSTree()
{
    // Make sure to call delete on every node of the tree
    // You can use a recursive helper function to do this
    root_helper(root);
    size = 0;
    root = nullptr;
}

Node* BSTree::insert(int obj)
{
    /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */
    Node* newNode = new Node( obj );
    
    if ( root == nullptr ) {
        size++;
        root = newNode;
        root->search_time = 1;
        return root;
    } else {
        newNode->search_time = 2;
        newNode = insert_helper(root, newNode);
    }
    return newNode;
}

Node* BSTree::search(int obj)
{
    /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */
    if ( root == nullptr ) return nullptr;
    if ( root->value == obj ) return root;
    return search_helper(root, obj);
}

void BSTree::update_search_times()
{
    /* do a BFS or DFS of your tree and update the search times of all nodes at once
      The root has a search time of 1, and each child is 1 more than its parent */
    
    search_time_helper(root, 1);
}

void BSTree::inorder(ostream& out)
{
    /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */
    
    inorder_helper( root, out );
}

void BSTree::print_level_by_level(ostream& out)
{
    /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */
    print_level_helper(*this, out);
}

void BSTree::root_helper( Node* tRoot )
{
    if ( tRoot == nullptr ) return;
    root_helper(tRoot->left);
    root_helper(tRoot->right);
    delete tRoot;
}

Node* BSTree::insert_helper(Node* tRoot, Node* nNode)
{
    if ( nNode->value > tRoot->value ) {
        if ( tRoot->right != nullptr ) {
            nNode->search_time++;
            insert_helper(tRoot->right, nNode);
        } else {
            tRoot->right = nNode;
            size++;
        }
    } else {
        if ( tRoot->left != nullptr ) {
            nNode->search_time++;
            insert_helper(tRoot->left, nNode);
        } else {
            tRoot->left = nNode;
            size++;
        }
    }
    return nNode;
}

Node* BSTree::search_helper(Node* tRoot, int obj)
{
    if ( tRoot == nullptr ) return tRoot;
    if ( tRoot->value == obj ) return tRoot;
    
    if ( tRoot->value > obj ) return search_helper(tRoot->left, obj);
    else return search_helper(tRoot->right, obj);
}

void BSTree::search_time_helper(Node* tRoot, int source_cost)
{
    if ( tRoot == nullptr ) return;
    tRoot->search_time = source_cost;
    if ( tRoot->left != nullptr ) search_time_helper(tRoot->left, source_cost + 1);
    if ( tRoot->right != nullptr ) search_time_helper(tRoot->right, source_cost + 1);
    
}

void BSTree::inorder_helper(Node* tRoot, std::ostream& os)
{
    if ( tRoot == nullptr ) return;
    inorder_helper(tRoot->left, os);
    os << tRoot->value << "[" << tRoot->search_time << "] ";
    inorder_helper(tRoot->right, os);
}

void BSTree::print_level_helper(BSTree tree, std::ostream& os)
{
    if ( root == nullptr ) return;
    
    queue<Node*> q;
    q.push(tree.root);
    int elementsInLevel = 1;
    bool nonNullChild = false;
    while ( elementsInLevel > 0 ) {
        Node* newNode = q.front();
        q.pop();
        elementsInLevel--;
        if ( newNode != nullptr ) {
            os << newNode->value << "[" << newNode->search_time << "] ";
            
            if ( newNode->left != nullptr ) {
                nonNullChild = true;
                q.push( newNode->left );
            } else {
                q.push( nullptr );
            }
            if ( newNode->right != nullptr ) {
                nonNullChild = true;
                q.push( newNode->right );
            } else {
                q.push( nullptr );
            }
        } else {
            os << "X ";
            q.push( nullptr );
            q.push( nullptr );
        }
        
        if ( elementsInLevel == 0 ) {
            os << std::endl;
            if ( nonNullChild ) {
                nonNullChild = false;
                elementsInLevel = q.size();
            }
        }
    }
}
