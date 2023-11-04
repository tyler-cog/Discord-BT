/**
 * Project 2 - Binary Trees
 * DiscriminatorTree.h
 * An interface for the DTree class.
 */

#pragma once

#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

#define DEFAULT_USERNAME ""
#define INVALID_DISC -1
#define MIN_DISC 0000
#define MAX_DISC 9999
#define DEFAULT_BADGE ""
#define DEFAULT_STATUS ""

#define DEFAULT_SIZE 1
#define DEFAULT_NUM_VACANT 0

class Grader;   /* For grading purposes */
class Tester;   /* Forward declaration for testing class */

class Account {
public:
    friend class Grader;
    friend class Tester;
    friend class DNode;
    friend class DTree;
    Account() {
        _username = DEFAULT_USERNAME;
        _disc = INVALID_DISC;
        _nitro = false;
        _badge = DEFAULT_BADGE;
        _status = DEFAULT_STATUS;
    }

    Account(string username, int disc, bool nitro, string badge, string status) {
        if(disc < MIN_DISC || disc > MAX_DISC) {
            throw std::out_of_range("Discriminator out of valid range (" + std::to_string(MIN_DISC) 
                                    + "-" + std::to_string(MAX_DISC) + ")");
        }
        _username = username;
        _disc = disc;
        _nitro = nitro;
        _badge = badge;
        _status = status;
    }

    /* Getters */
    string getUsername() const {return _username;}
    int getDiscriminator() const {return _disc;}
    bool hasNitro() const {return _nitro;}
    string getBadge() const {return _badge;}
    string getStatus() const {return _status;}

private:
    string _username;
    int _disc;
    bool _nitro;
    string _badge;
    string _status;
};

/* Overloaded << operator to print Accounts */
ostream& operator<<(ostream& sout, const Account& acct);

class DNode {
    friend class Grader;
    friend class Tester;
    friend class DTree;

public:
    DNode() {
        _size = DEFAULT_SIZE;
        _numVacant = DEFAULT_NUM_VACANT;
        _vacant = false;
        _left = nullptr;
        _right = nullptr;
    }

    DNode(Account account) {
        _account = account;
        _size = DEFAULT_SIZE;
        _numVacant = DEFAULT_NUM_VACANT;
        _vacant = false;
        _left = nullptr;
        _right = nullptr;
    }

    /* Getters */
    Account getAccount() const {return _account;}
    int getSize() const {return _size;}
    int getNumVacant() const {return _numVacant;}
    bool isVacant() const {return _vacant;}
    string getUsername() const {return _account.getUsername();}
    int getDiscriminator() const {return _account.getDiscriminator();}

private:
    Account _account;
    int _size;
    int _numVacant;
    bool _vacant;
    DNode* _left;
    DNode* _right;
    /* IMPLEMENT (optional): any other helper functions */
};

class DTree {
    friend class Grader;
    friend class Tester;

public:
    DTree(): _root(nullptr) {}

    /* IMPLEMENT: destructor and assignment operator*/
    ~DTree();
    DTree& operator=(const DTree& rhs);

    /* IMPLEMENT: Basic operations */
    bool insert(Account newAcct);
    bool remove(int disc, DNode*& removed);
    DNode* retrieve(int disc);
    void clear();
    void printAccounts() const;
    void dump() const {dump(_root);}
    void dump(DNode* node) const;

    /* IMPLEMENT: "Helper" functions */

    

    int getNumUsers() const;
    string getUsername() const {return _root->getUsername();}
    void updateSize(DNode* node);
    void updateNumVacant(DNode* node);
    bool checkImbalance(DNode* node);
    //----------------
    void rebalance(DNode*& node);
    // -- OR --
    //DNode* rebalance(DNode* node);
    //----------------

private:
    DNode* _root;
    int Counter = 0;
    int notVacant = 0;
    int vacCount = 0;
    DNode** nodeArray;
    DNode* temp;
    int nodeCount = 0;
    int arraySize = 0;
    /* IMPLEMENT (optional): any additional helper functions here */
int updateSizeHelper(DNode* node) 
    {
        // once the end is reached returns the size
        if (node == nullptr)
        {
            return Counter;
        }
        else
        {
            // increment count of node isn't nullptr
            Counter += 1;
            
            // recursive?
            updateSizeHelper(node->_left);
            updateSizeHelper(node->_right);
        }

        return Counter;
    }

    // helper to reset count to 0
    void setCount()
    {
        Counter = 0;
    }

    int updateNumVacantHelper(DNode* node)
    {
        
        //cout << "DISC IS " << node->getDiscriminator() << " VACANT IS " << node->_vacant << endl;
        // once the end is reached returns the number of vacant nodes
        if (node == nullptr)
        {
            return vacCount;
        }
        if (node->_vacant == true)
        {
             // increment count of node isn't nullptr
            vacCount += 1;
            // recursive?
            updateNumVacantHelper(node->_left);
            updateNumVacantHelper(node->_right);
        }
        // if node isnt vacant, continue
        else
        {
            // recursive?
            updateNumVacantHelper(node->_left);
            updateNumVacantHelper(node->_right);
        }

        return vacCount;
    }
    // helper to reset count to 0
    void set_vacCount()
    {
        vacCount = 0;
    }

    bool checkImbalanceHelper(DNode* node)
    {
        // cout << "LEFT SIZE IS " << node->_left->_size << endl;
        // cout << "Right SIZE IS " << node->_right->getSize() << endl;

        // if the left node is null, the right node is looked at
        if (node->_left == nullptr)
        {
            if (node->_right == nullptr)
            {
                return false;
            }
            else if (node->_right->getSize() < 4)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        // if the right node is null, the left node is looked at
        else if (node->_right == nullptr)
        {
            if (node->_left== nullptr)
            {
                return false;
            }
            else if (node->_left->getSize() < 4)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        // if both children's sizes are less than 4, return false
        else if (node->_left->getSize() < 4 && node->_right->getSize() < 4)
        {
            return false;
        }
        // if the right child is 50% bigger than left, return true
        else if (node->_left->getSize() * 1.5 < node->_right->getSize())
        {
            return true;
        }
        // if the left child is 50% bigger than right, return true
        else if  (node->_left->getSize() > node->_right->getSize() * 1.5)
        {
            return true;
        }

        // return false if not imbalanced 
        return false;
    }

    int getNumUsersHelper(DNode* node) const
    {
        // should take the current node's size and subtract it's current numVacant
        // issue is that size / numVacant doesn't update automatically?? (const)
        int notVacant = node->getSize() - node->getNumVacant();
        return notVacant;
    }
    // int set_notVacant()
    // {
    //     notVacant = 0;
    //     return notVacant;
    // }


    DNode* copyHelper(DNode* node) 
    {
        // if null is null, return nullptr
        if (node == nullptr)
        {
            return nullptr;
        }

        //DNode* TEST = new node;
    }

    void clearHelper(DNode* &node)
    {
        // base case
        if (node == nullptr)
        {
            return;
        }
        // delete current node 
        //delete node;
        

        // delete left and right subtree first (Postorder)
        clearHelper(node->_left);
        clearHelper(node->_right);
        cout << "Cleared: " << node->getDiscriminator() << endl;
        delete node;
        
    }

    void printHelper(DNode* node) const
    {
        
        if (node == nullptr)
        {
            return;
        }
        // post order traversal
        printHelper(node->_left);
        // cout << "Username is " << node->getUsername() << endl;
        cout << "Disc is " << node->getDiscriminator() << endl;
        // cout << "Nitro is " << node->_account.hasNitro() << endl;
        // cout << "Badge is " << node->_account.getBadge() << endl;
        // cout << "Status is " << node->_account.getStatus() << endl;
        printHelper(node->_right);
    
    }

    void createArray(DNode* node)
    {
        if (node == nullptr)
        {
            return;
        }
        else if (node->_vacant == false)
        {

            arraySize += 1;
            //cout << "SIZE " << arraySize << endl;
            //cout << "DISC " << node->getDiscriminator() << endl;
            createArray(node->_left);
            createArray(node->_right);
        }
        else
        {
            createArray(node->_left);
            createArray(node->_right);
        }
       
        cout << "SIZE " << arraySize << endl;
        nodeArray = new DNode* [arraySize];
    }
    void updateArray(DNode* node)
    {
        //should take a node, put everything into an array except vacants, sort array, insert back into tree
        //nodeCount = 0;
        if (node == nullptr)
        {
            return;
        }

        else if (node->_vacant == false)
        {

            nodeArray[nodeCount] = node;
            nodeCount += 1;
            updateArray(node->_left);
            updateArray(node->_right);
        }
        else if (node->_vacant == true)
        {
            delete node;
            updateArray(node->_left);
            updateArray(node->_right);
        }
        cout << "nodeCount: " << nodeCount << endl;
        for (int i = 0; i < nodeCount; i++)
        {
            for (int j = i + 1; j < nodeCount; j++)
            {
                if (nodeArray[i]->getDiscriminator() > nodeArray[j]->getDiscriminator())
                    {
                        temp = nodeArray[i];
                        nodeArray[i] = nodeArray[j];
                        nodeArray[j] = temp;
                    }
            }
        }
        nodeCount = 0;
        while (nodeCount != node->getSize())
        {
            insert(nodeArray[nodeCount]->getAccount());
            nodeCount ++;
        }

        //return node;
    }

    void operatorHelper(DNode* _root, const DTree rhs)
    {
        if (rhs._root == nullptr)
        {
            return;
        }
        // new node is created to store values from rhs
        _root = new DNode;//(*rhs._root);

        // post order traversal
        _root->_account = rhs._root->_account;
        _root->_size = rhs._root->_size;
        _root->_vacant = rhs._root->_vacant;
        _root->_numVacant = rhs._root->_numVacant;
        operatorHelper(_root->_left, rhs);
        operatorHelper(_root->_right, rhs);
    }
};