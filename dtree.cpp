/**
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */

#include "dtree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
DTree::~DTree() {
    clear();
}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */
DTree& DTree::operator=(const DTree& rhs) {
    // using from circularLL
    // need to traverse the tree
    //TODO:
    // deallocates memory
    //clear();
    //DNode* rhs2;
    if (this != &rhs)
    {
        clear();
        operatorHelper(_root, rhs);
    
    }

    return *this;
}

/**
 * Dynamically allocates a new DNode in the tree. 
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */
bool DTree::insert(Account newAcct) {
    // update size and numvacant
    // check for imbalance (rebalance if needed?)
    DNode* toInsert = new DNode(newAcct);
    DNode* Parent; 

    if (_root == nullptr) 
    {
        // //If root is null, tree is empty 
        _root = toInsert;
        Parent = _root;
       // cout << "INTIAL CHECK " << endl;
        return true;
    }

    Parent = _root;
    updateSize(Parent);
    while (Parent != nullptr)
    {
        //cout << "BEGINNING OF WHILE LOOP " << endl;
        updateSize(Parent);
        if (Parent->_left != nullptr)
        {
            updateSize(Parent->_left);
        }
        else if (Parent->_right != nullptr)
        {
            updateSize(Parent->_right);
        }
        // checks for repeated discriminator
        if (Parent->getDiscriminator() == toInsert->getDiscriminator())
        {
            return false;
        }
        // cout << "PARENT " << Parent->getDiscriminator() << endl;
        // cout << "TOINSERT " << toInsert->getDiscriminator() << endl;

        // compares the disc of the parent and newly inserted node
        if (toInsert->getDiscriminator() > Parent->getDiscriminator())
        {
            //cout << "Insert > parent" << endl;
            // check for if the current parent is set to vacant
            if (Parent->_vacant == true)
            {
                //cout << "vacParent DISC IS " << Parent->getDiscriminator() << endl;
                // checks if BST order is maintained
                if (Parent->_left == nullptr && Parent->_right == nullptr)
                {
                    //cout << "PARENT: " << Parent->getDiscriminator() << " TO REPLACE: " << toInsert->getDiscriminator() << endl;
                    Parent->_account = newAcct;
                    Parent->_vacant = false;
                    updateNumVacant(Parent);
                    return true;
                }
                // else if (Parent->_left == nullptr && toInsert->getDiscriminator() < Parent->_right->getDiscriminator())
                // {
                //     Parent->_account = newAcct;
                //     return true;
                // }
                else if (((Parent->_right == nullptr) && (toInsert->getDiscriminator() > Parent->_left->getDiscriminator())) || ((Parent->_left == nullptr) && (toInsert->getDiscriminator() < Parent->_right->getDiscriminator())))
                {
                    //cout << "PARENT: " << Parent->getDiscriminator() << " TO REPLACE: " << toInsert->getDiscriminator() << endl;
                    Parent->_account = newAcct;
                    Parent->_vacant = false;
                    updateNumVacant(Parent);
                    return true;
                }
                else if ((toInsert->getDiscriminator() > Parent->_left->getDiscriminator()) && (toInsert->getDiscriminator() < Parent->_right->getDiscriminator()))
                {
                    // if vacant replace current spot
                        Parent->_account = newAcct;
                        Parent->_vacant = false;
                        updateNumVacant(Parent);
                        return true;
                    }
            }

            // if the child of the parent is empty, set child to newly inserted node
            else if (Parent->_right == nullptr)
            {
               // _root->_right == toInsert;
                Parent->_right = toInsert;
                updateSize(Parent);
                updateSize(Parent->_right);
                // updateSize(Parent);
                updateNumVacant(Parent->_right);
                updateNumVacant(Parent);
                // if (checkImbalance(Parent) == true)
                // {
                //     cout << "YO IMBALANCED " << endl;
                // }
                // else
                // {
                //     cout << "YO NOT IMBALANCED " << endl;
                // }
                // DO I NEED TO CALL IMBALANCE AND REBALANCE?
                // cout << "Parent->_right after insert " << toInsert->getDiscriminator() << endl;
                // cout << "RIGHT " << endl;
                return true;
            }
            // set parent to right child to traverse further down tree.
            Parent = Parent->_right;
            
        }
        // compares the disc of the parent and newly inserted node
        else if (toInsert->getDiscriminator() < Parent->getDiscriminator())
        {
           // cout << "Parent > Insert" << endl;

            // check for if the current parent is set to vacant
            if (Parent->_vacant == true)
            {
                //cout << "vacParent DISC IS " << Parent->getDiscriminator() << endl;

                // checks if BST order is maintained, if so update parent with newly inserted node
                if (Parent->_left == nullptr && Parent->_right == nullptr)
                {
                    //cout << "PARENT: " << Parent->getDiscriminator() << " TO REPLACE: " << toInsert->getDiscriminator() << endl;
                    Parent->_account = newAcct;
                    Parent->_vacant = false;
                    updateNumVacant(Parent);
                    return true;
                }
                // else if (Parent->_left == nullptr && toInsert->getDiscriminator() < Parent->_right->getDiscriminator())
                // {
                //     Parent->_account = newAcct;
                //     return true;
                // }
                // checks if BST order is maintained, if so update parent with newly inserted node
                else if (((Parent->_right == nullptr) && (toInsert->getDiscriminator() > Parent->_left->getDiscriminator())) || ((Parent->_left == nullptr) && (toInsert->getDiscriminator() < Parent->_right->getDiscriminator())))
                {
                    //cout << "PARENT: " << Parent->getDiscriminator() << " TO REPLACE: " << toInsert->getDiscriminator() << endl;
                    Parent->_account = newAcct;
                    Parent->_vacant = false;
                    updateNumVacant(Parent);
                    return true;
                }
                // checks if BST order is maintained, if so update parent with newly inserted node
                else if ((toInsert->getDiscriminator() > Parent->_left->getDiscriminator()) && (toInsert->getDiscriminator() < Parent->_right->getDiscriminator()))
                {
                    // if vacant replace current spot
                        Parent->_account = newAcct;
                        Parent->_vacant = false;
                        updateNumVacant(Parent);
                        return true;
                    }
                }
            // if the child of the parent is empty, set child to newly inserted node
            else if (Parent->_left == nullptr)
            {
                //cout << "Parent->_left " << Parent->_left->getDiscriminator() << endl;
               // _root->_left == toInsert;
                Parent->_left = toInsert;

                // update size 
                updateSize(Parent);
                updateSize(Parent->_left);
                // updateSize(Parent);
                updateNumVacant(Parent->_left);
                updateNumVacant(Parent);
                // if (checkImbalance(Parent) == true)
                // {
                //     cout << "YO IMBALANCED " << endl;
                // }
                // else
                // {
                //     cout << "YO NOT IMBALANCED " << endl;
                // }
                // update size and numvacant
                // DO I NEED TO CALL IMBALANCE AND REBALANCE?
                // cout << "Parent->_left after insert " << toInsert->getDiscriminator() << endl;
                // cout << "LEFT " << endl;
                return true;
            }

            // set parent to left child to traverse further down tree.
            Parent = Parent->_left;
        }
        
    }

    return false; 
}

/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */ // sudo apt install gdb 
bool DTree::remove(int disc, DNode*& removed) {
    // set _vacant to true, will be removed during rebalance.
    // increase _numVacant by 1
    
    // set toFind to root of tree
    DNode* toFind = _root;

    // traverses tree to find node with disc
    while (disc != toFind->getDiscriminator())
    {
        if (disc > toFind->getDiscriminator())
        {
            toFind = toFind->_right;
        }
        else if (disc < toFind->getDiscriminator())
        {
            toFind = toFind->_left;
        }
    }
    // once out of the while loop check again, and change values
    
    if (disc == toFind->getDiscriminator())
    {
        toFind->_vacant = true;
        //cout << "DISC IS " << toFind->getDiscriminator() << " VACANT IS " << toFind->_vacant << endl;
        // how does this compare with getNumVacant????????????
        updateNumVacant(toFind);
        //toFind->_numVacant += 1;

        return true;
    }

   // value not found
    return false; 
}

/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::retrieve(int disc) {
    DNode* Search = _root;
    // need to check the Dnode and make sure vacant is false

    // initial check
    if (disc == NULL) 
    {
        return nullptr;
    }

    //traverse through tree to find node with disc
    while (disc != Search->getDiscriminator())
    {
        if (disc > Search->getDiscriminator())
        {
            Search = Search->_right;
        }
        else if (disc < Search->getDiscriminator())
        {
            Search = Search->_left;
        }
    }

    // if disc if found return the node
    if (disc == Search->getDiscriminator() && Search->_vacant != true)
    {
        //cout << "Retrieved: " << disc << endl;
        return Search;
    }

    // return nullptr if not found
    return nullptr;
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::clear() {

    //TODO: Check if correct?
    // causes seg fault 
    clearHelper(_root);
}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const {
    // This function prints out account details using in-order traversal of discriminator values. 
    // It should use the overloaded insertion operator (<<) for the Account class. 
    // The implementation of insertion operator is provided. 
    // Vacant nodes should not be printed. 
    // (Hint: if you want to implement the functionality recursively, 
    //  facilitate a recursive implementation you can introduce a helper function.)
    // how do i set initial node w/o being nullprt? (because of root)
    DNode* Parent = _root;
    printHelper(Parent);
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {
    // use recursion to count if node's are not vacant
    DNode* Parent = _root;
    //updateSize(Parent);
    //cout << "NUM USERS IS " << getNumUsersHelper(Parent) << endl;
    return getNumUsersHelper(Parent);
}

/**
 * Updates the size of a node based on the imediate children's sizes
 * @param node DNode object in which the size will be updated
 */
void DTree::updateSize(DNode* node) {

   if (node->_left == nullptr && node->_right == nullptr)
   {
       //cout << "Size for " << node->getDiscriminator() << " is " << node->getSize() << endl;
       node->_size = 1;
   }
   else if (node->_left == nullptr)
   {
        node->_size = updateSizeHelper(node);
        //cout << "Size for " << node->getDiscriminator() << " is " << node->getSize() << endl;
        setCount();
   }
   else if (node->_right == nullptr)
   {

        node->_size = updateSizeHelper(node);
        //cout << "Size for " << node->getDiscriminator() << " is " << node->getSize() << endl;
        setCount();
   }
   else
   {
        node->_size = updateSizeHelper(node);
        //cout << "Size for " << node->getDiscriminator() << " is " << node->getSize() << endl;
        setCount();
   }

}


/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node) {

    // node->_vacant = true;
    // node->_left->_vacant = true;
    // testing with node->_left->_left gives me seg fault
    node->_numVacant = updateNumVacantHelper(node);
    //cout << "NUM VACANT FOR " << node->getDiscriminator() << " is " << node->getNumVacant() << endl;
    set_vacCount();

}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
bool DTree::checkImbalance(DNode* node) {

    return checkImbalanceHelper(node);

}

//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */ // in order traversal/ post order delete?
void DTree::rebalance(DNode*& node) {
    updateSize(node);
    createArray(node);
    updateArray(node);
}
// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
//DNode* DTree::rebalance(DNode*& node) {
    
//}
//----------------

/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
 */
ostream& operator<<(ostream& sout, const Account& acct) {
    sout << "Account name: " << acct.getUsername() << 
            "\n\tDiscriminator: " << acct.getDiscriminator() <<
            "\n\tNitro: " << acct.hasNitro() << 
            "\n\tBadge: " << acct.getBadge() << 
            "\n\tStatus: " << acct.getStatus();
    return sout;
}