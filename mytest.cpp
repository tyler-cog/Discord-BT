#include "dtree.h"
#include "dtree.cpp"
#include <random>

#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);
    bool testBasicDTreeRemove(DTree& dtree);
    int testBasicDTreeBalance(DTree& dtree);
    bool testBasicDTreeUnbalanced(DTree& dtree);
};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}


bool Tester::testBasicDTreeRemove(DTree& dtree) {
    bool allRemoved = true;
    int numDiscriminators = 3;
    int discriminators[] = {8735, 3516, 1271};
    DNode* removed = nullptr;
    for(int i = 0; i < numDiscriminators; i++) {
            Account newAcct = Account("", discriminators[i], 0, "", "");
            dtree.insert(newAcct);
    }
    for(int j = 0; j < numDiscriminators; j++) {
        if(!dtree.remove(discriminators[j], removed)) {
            cout << "Deletion on node " << discriminators[j] << " did not return true" << endl;
        }
    }

    cout << "Dumping the tree after 3 deletions time" << endl;
    dtree.dump();
    cout << endl;

    cout << "Inserting 1 element to cause an imbalance and to clear vacant nodes" << endl;
    Account bigAcct = Account("", 9999, 0, "", "");
    dtree.insert(bigAcct);
    return allRemoved;
}

int Tester::testBasicDTreeBalance(DTree& dtree) {
    bool allInserted = true;
    int _head = 0;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if (i = 0) 
        {
            _head = disc;
        }
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            //allInserted = false;
        }
    }
    dtree.printAccounts();
    return _head;
}

bool Tester::testBasicDTreeUnbalanced(DTree& dtree) {
    Account acnt("Giuseppe", 25, false, "Subbed", "Chillin");
    dtree.insert(acnt);
    Account acnt2("Crobnob", 27, true, "not subbed", "being dumb");
    dtree.insert(acnt2);
    Account acnt3("Rock", 13, false, "proj2", "playing music");
    dtree.insert(acnt3);
    Account acnt4("Shane", 15, false, "proj3", "playing abc");
    dtree.insert(acnt4);
    Account acnt5("Shane", 26, false, "proj3", "playing abc");
    dtree.insert(acnt5);
    Account acnt6("Shane", 12, false, "proj3", "playing abc");
    dtree.insert(acnt6);
    Account acnt7("Shane", 19, false, "proj3", "playing abc");
    dtree.insert(acnt7);
    Account acnt8("Shane", 21, false, "proj3", "playing abc");
    dtree.insert(acnt8);
    Account acnt9("Shane", 22, false, "proj3", "playing abc");
    dtree.insert(acnt9);
    
    return true;
}

int main() {
    Tester tester;

    /* Basic dtree tests */
    DTree dtree;

    cout << "Testing DTree insertion...";
    if(tester.testBasicDTreeInsert(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    dtree.dump();
    dtree.clear();
    cout << endl;


    Tester tester2;
    /* Basic dtree tests */
    DTree dtree2;
    cout << "\n\nTesting DTree deletion..." << endl;
    if(tester2.testBasicDTreeRemove(dtree2)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree2:" << endl;
    dtree2.dump();
    dtree2.clear();
    cout << endl;


    // Tester tester3;
    // /* Basic dtree tests */
    // DTree dtree3;
    // cout << "\n\nTesting DTree balance..." << endl;
    // // if(tester3.testBasicDTreeBalance(dtree3)) {
    // //     cout << "test passed" << endl;
    // // } else {
    // //     cout << "test failed" << endl;
    // // }
    // cout << " Is it imbalanced? " << endl;
    // // DNode* TEST = dtree.retrieve(2987);
    // // dtree.printAccounts();
    // if (dtree3.checkImbalance(dtree3.retrieve(.testBasicDTreeBalance(dtree3))) == true)
    // {
    //     cout << "Tree is imbalanced " << endl;
    //     //dtree.rebalance(TEST);
    // }
    // else
    // {
    //     cout << "Tree is not imbalanced " << endl;
    // }
    // cout << "Resulting DTree2:" << endl;
    // dtree3.dump();
    // dtree3.clear();
    // cout << endl;
    
    Tester tester4;
    /* Basic dtree tests */
    DTree dtree4;
    cout << "\n\nTesting DTree balance..." << endl;
    if(tester4.testBasicDTreeUnbalanced(dtree4)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }
    cout << " Is it imbalanced? " << endl;
    //DNode* TEST = dtree.retrieve(2987);
    if (dtree4.checkImbalance(dtree4.retrieve(25)) == true)
    {
        cout << "Tree is imbalanced " << endl;
        //dtree.rebalance(TEST);
    }
    else
    {
        cout << "Tree is not imbalanced " << endl;
    }
    cout << "Resulting DTree2:" << endl;
    dtree4.dump();
    //dtree4.clear();
    cout << endl;
    return 0;
}
