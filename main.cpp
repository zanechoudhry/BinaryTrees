//Zane Choudhry
//main.cpp
//zchoudhry
#include <iostream>
#include <sstream>
#include <string>
#include "bst.h"

using namespace std;

int main()
{
    BST bst; // declaring class object
    
    while (true)
    {
        string line;
        if (!getline(cin, line)){ //stop the loop if there arent any more inputs to read gets out of the infinite loop
            break;
        }
        stringstream ss(line);
        string command;
        ss >> command; //reading in command
        
        if (command == "echo"){ // if command is equal to echo which is just practially notes or summary
            getline(ss, line); // grab the whole line and store it in line
            line.erase(0, 1); //removing extra space before start of line
            cout << line << endl; // output line to standard output
        }
        else if (command == "size"){
            cout << bst.size() << endl; // call size function to get the correct size
        }
        else if (command == "find"){ // if command is equal to find
            string entry;
            getline(ss, entry); // assign the line to entry
            entry.erase(0, 1); // removing extra space before start of line
            
            if (bst.find(entry))
                cout << "<" << entry << "> is in tree." << endl;
            else
                cout << "<" << entry << "> is not in tree." << endl;
        }
        else if (command == "insert"){
            string entry;
            getline(ss, entry); // reading in as entry
            entry.erase(0, 1); // removing extra space before start of line
            
            if (!bst.insert(entry))
                cerr << "insert <" << entry << "> failed. String already in tree." << endl;
        }
        else if (command == "breadth"){
            cout <<  bst.breadth() << endl; // calling the breadth function to output the correct order
        }
        else if (command == "print"){
            cout << bst.print() << endl; // calling the print function to display whatever is inserted into the tree
        }
        else if (command == "distance"){
            cout << "Average distance of nodes to root = " << bst.distance() << endl; //calling the distance function
        }
        else if (command == "balanced"){
            if (bst.isBalanced()) //calling is balanced function
                cout << "Tree is balanced." << endl; // output this if the tree is balanced
            else
                cout << "Tree is not balanced." << endl; // else output this
        }
        else if (command == "rebalance"){
            bst.rebalance(); //calling rebalance funtction
        }
        else{
            cerr << "Illegal command <" << command << ">." << endl; // if not a familiar command print error to standard error
        }
    }
    
    return 0;
}
