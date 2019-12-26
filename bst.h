//Zane Choudhry
//bst.h
//zchoudhry
#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include<vector>
using namespace std;

class BST
{
public:
    //public member function most call the memebr functions in the private
    BST();
    ~BST();
    bool insert(string data);
    bool find(string data);
    string breadth();
    string print();
    int size();
    double distance();
    bool isBalanced();
    void rebalance();
private:
    
    struct Node // equivalent of doing a class Node
    {
        string data;
        Node *left;
        Node *right;
        Node(string data)
        {
            this->data = data;
            left = NULL;
            right = NULL;
        }
    };
    
    Node *root;
    int numEntries;
    // all private function most are called through the public member function
    Node *insert(Node *current, string &data, bool &result);
    void sumDistances(Node *current, int currentDistance, int &totalDistance);
    void print(Node *current, stringstream &ss);
    bool find(Node *current, string &data);
    void destroy(Node *current);
    bool checkBalance(Node *current);
    bool isBalanced(Node *current);
    int height(Node *current);
    void arrangeNodesInOrder(Node *current, vector<Node *> &nodes);
    Node *rebalance(vector<Node *> &nodes, int start, int end);
};

#endif
