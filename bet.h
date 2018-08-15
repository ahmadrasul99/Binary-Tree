#ifndef _BET_H
#define _BET_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class BET
{
  struct BinaryNode
  {
    // Constructors

    BinaryNode(const string & token, BinaryNode * temp1, BinaryNode * temp2)
    : element{token}, left{temp1}, right{temp2} { }
    BinaryNode(string && token, BinaryNode * temp1, BinaryNode * temp2)
    : element{std::move(token)}, left{temp1}, right{temp2} { }

    // Data varibales

    string element;
    BinaryNode * left;
    BinaryNode * right;
  };
  
  public:
    BET();                                                      // Defualt constructor
    BET(const string & postfix);                                // Single parameter constructor
    BET(const BET & temp);                                      // Copy constructor
    ~BET();                                                     // Destructor
    const BET & operator= (const BET & temp);                   // Assignment Operator
    bool buildFromPostfix(const string & postfix);              // Building tree from parameter
    void printInfixExpression() const;                          // Print infix expression
    void printPostfixExpression() const;                        // Print postfix expression
    size_t size() const;                                        // Return number of nodes
    size_t leaf_nodes() const;                                  // Return number of leaf nodes
    bool empty() const;                                         // Checks if tree is empty

  private:
    void printInfixExpression(BinaryNode * n) const;            // Print infix expression to stdout
    void printPostfixExpression(BinaryNode * n) const;          // Print outfix expression to stdout
    void makeEmpty(BinaryNode *& t);                            // Deletes all nodes in T
    size_t size(BinaryNode * t) const;                          // Return number of nodes
    size_t leaf_nodes(BinaryNode * t) const;                    // Return number of leaf nodes

    BinaryNode * clone(BinaryNode * t);                         // Clone all nodes in T
    BinaryNode * current;                                       // Data variable
};

bool Operators(char sign);                                      // Stand-alone function


#include "bet.cpp"
#endif
