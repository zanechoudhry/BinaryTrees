//Zane Choudhry
//bst.cpp
//zchoudhry
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>
#include <sstream>
#include <cmath>
#include"bst.h"
using namespace std;

//setting the root to null and num of entries (nodes) to 0
BST::BST(){
    root = NULL;
    numEntries = 0;
}
// destructor which called function destroy and resets root and numEntries
BST::~BST(){
    destroy(root);
    numEntries = 0;
    root = NULL;
}
//public insert function which calls the private insert function
bool BST::insert(string data){
    bool result;
    root = insert(root, data, result); // calling private insert function
    
    return result;
}
//find function calling private find function
bool BST::find(string data){
    return find(root, data);
}
string BST::breadth(){
    if (numEntries == 0) // if there is nothing in the tree then just output the open and closed brackets
        return "{}";
    
    stringstream ss;
    ss << "{";
    
    queue<Node *> q; // queue of Node pointers
    q.push(root); // pushing value onto the queue
    ss << root->data << ", ";
    
    while (!q.empty()){ //using breadth first traversal to print everything in the tree
        Node *next = q.front();
        q.pop();
        
        if (next->left != NULL){
            q.push(next->left);
            ss << next->left->data << ", ";
        }
        
        if (next->right != NULL){
            q.push(next->right);
            ss << next->right->data << ", ";
        }
    }
    
    string result = ss.str();
    result = result.substr(0, result.size() - 2);
    result += "}";
    
    return result;
}
string BST::print(){
    if (numEntries == 0) // if there isnt anything in the tree then just output the open and closed brackets
        return "{}";
    
    stringstream ss;
    print(root, ss);
    
    string result = ss.str();
    result = result.substr(0, result.size() - 2);
    result = "{" + result + "}";
    return result;
}
int BST:: size(){
    return numEntries;
}
double BST::distance(){
    if (numEntries == 0) //if there arent any entries just return 0
        return 0;
    
    int totalDistance = 0;
    sumDistances(root, 0, totalDistance); //calling sumDistances function to get all the distances
    return (double) totalDistance / numEntries; //returning average distance
}
bool BST::isBalanced(){
    return checkBalance(root); //callling checkbalance
}
void BST::rebalance(){
    if (numEntries == 0)
        return;
    vector<Node *> inOrderNodes; //creating a vector of node pointers
    arrangeNodesInOrder(root, inOrderNodes);
    
    for (unsigned i = 0; i < inOrderNodes.size(); i++){
        inOrderNodes[i]->left = NULL;
        inOrderNodes[i]->right = NULL;
    }

    root = rebalance(inOrderNodes, 0, inOrderNodes.size() - 1);
}
BST::Node* BST::insert(Node *current, string &data, bool &result){
    if (current == NULL){
        numEntries++; //incrementing number of entried or nodes
        result = true;
        return new Node(data);
    }
    
    if (data < current->data){ //if the data is less than the current data then go down the left side
        current->left = insert(current->left, data, result);
    }
    if (data > current->data){//if the data is greater than the current data then go down the right side
        current->right = insert(current->right, data, result);
    }
    
    return current;
}
void BST::sumDistances(Node *current, int currentDistance, int &totalDistance){
    if (current == NULL)
        return;
    
    totalDistance += currentDistance; // keeps adding the current distance to the total distance by recursion
    
    sumDistances(current->left, currentDistance + 1, totalDistance);
    sumDistances(current->right, currentDistance + 1, totalDistance);
}
void BST::print(Node *current, stringstream &ss){
    if (current == NULL)
        return;
    //recursion function to print everything in Depth First Traversal
    print(current->left, ss);
    ss << current->data << ", ";
    print(current->right, ss);
}
bool BST::find(Node *current, string &data){
    if (current == NULL)
        return false;
    
    if (data < current->data) // checks if the data is less that the current data so that way it doesnt have to go through each and every node instead can just go down the left side and ignore the right
        return find(current->left, data);
    
    if (data > current->data)//checks if the data is greater that the current data so that way it doesnt have to go through each and every node instead can just go down the right side ignore the left
        return find(current->right, data);
    
    return true;
}
void BST::destroy(Node *current){
    if (current == NULL)
        return;
    //dealllocating which is called throught the destructor
    destroy(current->left);
    destroy(current->right);
    delete current;
}
bool BST::checkBalance(Node *current){
    if (current == NULL)
        return true;
    //simply an if statement that makes sure not the tree is balanced whatsoever
    if (!isBalanced(current) ||
        !checkBalance(current->left) ||
        !checkBalance(current->right))
        return false;
    
    return true;
}
bool BST::isBalanced(Node *current){
    if (current == NULL)
        return true;
    //checks if the tree is balanced by seeing if the absolute value of the height of the left and right arent greater than or equal to 2
    int leftHeight = height(current->left);
    int rightHeight = height(current->right);
    
    if (abs(leftHeight - rightHeight) >= 2)
        return false;
    
    return true;
}
int BST::height(Node *current){
    if (current == NULL)
        return 0;
    
    int leftHeight = height(current->left); // recursive funtion to keep doing the left side and see how many nodes are on the left side
    int rightHeight = height(current->right); // recursive funtion to keep doing the right side and see how many nodes are on the right side
    
    if (leftHeight > rightHeight){ // if the left side is greater than the right side then add 1 to the left height
        return 1 + leftHeight;
    }
    return 1 + rightHeight;
}
void BST::arrangeNodesInOrder(Node *current, vector<Node *> &nodes){
    if (current == NULL)
        return;
    //in order is where the order is left, *, and then the right
    arrangeNodesInOrder(current->left, nodes);
    nodes.push_back(current);
    arrangeNodesInOrder(current->right, nodes);
}
BST::Node* BST::rebalance(vector<Node *> &nodes, int start, int end){
    if (start > end)
        return NULL;
    
    int mid = (start + end) / 2; //assigning the middle to the variable mid
    Node *root = nodes[mid]; // assigning the middle value to the root
    root->left = rebalance(nodes, start, mid - 1);
    root->right = rebalance(nodes, mid + 1, end);
    return root;
}
