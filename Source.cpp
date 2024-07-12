#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

typedef struct CustomerAccount{
    double primaryKey;
    double customerKey;
    string name;
    double bal;
}CustomerAccount;

typedef struct BTreeNode {
    CustomerAccount* data;
    int m;
    int dataNum;
    struct BTreeNode** pointers;
    int height;
    bool leaf;
} BTreeNode;

typedef struct BTree {
    BTreeNode* root;
    int m;
} BTree;

BTreeNode* createNode(int m, bool leaf) {
    BTreeNode* node = new BTreeNode;
    node->m = m;
    node->leaf = leaf;
    node->data = new CustomerAccount[m - 1];
    node->pointers = new BTreeNode * [m];
    node->height = 0;
    node->dataNum = 0;
    for (int i = 0; i <= m; i++) {
        node->pointers[i] = nullptr;
    }
    return node;
}

/*void traverse(BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (root->leaf == false) {
            traverse(root->C[i]);
        }
        cout << " " << root->keys[i];
    }
    if (root->leaf == false) {
        traverse(root->C[i]);
    }
}



void insertData(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf == true) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        x->keys[i + 1] = k;
        x->n = x->n + 1;
    }
    else {
        while (i >= 0 && x->keys[i] > k) {
            i--;
        }

        if (x->C[i + 1]->n == 2 * x->t - 1) {
            splitChild(x, i + 1, x->C[i + 1]);

            if (x->keys[i + 1] < k) {
                i++;
            }
        }
        insertNonFull(x->C[i + 1], k);
    }
}

void printNode(BTreeNode* node, int indent = 0) {
    if (node == nullptr) {
        return;
    }

    if (node->leaf) {
        for (int i = node->n - 1; i >= 0; i--) {
            cout << string(indent, ' ') << node->keys[i] << "\n";
        }
    }
    else {
        for (int i = node->n; i >= 0; i--) {
            if (i < node->n) {
                cout << string(indent, ' ') << node->keys[i] << "\n";
            }
            printNode(node->C[i], indent + 4);
        }
    }
}

void initializeBTree(BTree* tree, int t) {
    tree->root = nullptr;
    tree->t = t;
}

void insert(BTree* tree, int k) {
    if (tree->root == nullptr) {
        tree->root = createNode(tree->t, true);
        tree->root->keys[0] = k;
        tree->root->n = 1;
    }
    else {
        if (tree->root->n == 2 * tree->t - 1) {
            BTreeNode* s = createNode(tree->t, false);
            s->C[0] = tree->root;

            splitChild(s, 0, tree->root);
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            insertNonFull(s->C[i], k);
            tree->root = s;
        }
        else {
            insertNonFull(tree->root, k);
        }
    }
}

void printBTree(BTree* tree) {
    printNode(tree->root);
}

void readFileAndInsertToBTree(BTree* tree, const string& fileName) {
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cerr << "Unable to open file\n";
        return;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        string part;
        getline(iss, part, '|');
        int key = stoi(part);
        insert(tree, key);
    }

    file.close();
}*/

/*void splitNode(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->t, y->leaf);
    z->n = y->t - 1;

    for (int j = 0; j < y->t - 1; j++) {
        z->keys[j] = y->keys[j + y->t];
    }

    if (y->leaf == false) {
        for (int j = 0; j < y->t; j++) {
            z->C[j] = y->C[j + y->t];
        }
    }

    y->n = y->t - 1;

    for (int j = x->n; j >= i + 1; j--) {
        x->C[j + 1] = x->C[j];
    }

    x->C[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    x->keys[i] = y->keys[y->t - 1];
    x->n = x->n + 1;
}



void insert(BTree* tree, CustomerAccount ca) {
    if (tree->root == nullptr) {
        tree->root = createNode(tree->t, true);
        tree->root->keys[0] = k;
        tree->root->n = 1;
    }
    else {
        if (tree->root->n == 2 * tree->t - 1) {
            BTreeNode* s = createNode(tree->t, false);
            s->C[0] = tree->root;

            splitChild(s, 0, tree->root);
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            insertNonFull(s->C[i], k);
            tree->root = s;
        }
        else {
            insertNonFull(tree->root, k);
        }
    }
}*/

void splitNode(BTreeNode* x, int i, BTreeNode* y) {
    BTreeNode* tmp = createNode(y->m, y->leaf);
    int minKeys = (y->m % 2 == 0) ? (y->m / 2) : ((y->m + 1) / 2);
    tmp->dataNum = minKeys - 1;

    for (int j = 0; j < minKeys - 1; j++) {
        tmp->data[j] = y->data[j + minKeys - 1];
    }

    if (y->leaf == false) {
        for (int j = 0; j < minKeys; j++) {
            tmp->pointers[j] = y->pointers[j + minKeys - 1];
        }
    }

    y->dataNum = minKeys - 1;

    for (int j = x->dataNum; j >= i + 1; j--) {
        x->pointers[j + 1] = x->pointers[j];
    }

    x->pointers[i + 1] = tmp;

    for (int j = x->dataNum - 1; j >= i; j--) {
        x->data[j + 1] = x->data[j];
    }

    x->data[i] = y->data[minKeys - 1];
    x->dataNum = x->dataNum + 1;
}

/*void insertData(BTreeNode* x, CustomerAccount ca) {
    int i = x->dataNum - 1;
  

    if (x->leaf == true) {
        while (i >= 0 && x->data[i].primaryKey > ca.primaryKey) {
            x->data[i + 1] = x->data[i];
            i--;
        }

        x->data[i + 1] = ca;
        x->dataNum = x->dataNum + 1;
    }
    else {
        while (i >= 0 && x->data[i].primaryKey > ca.primaryKey) {
            i--;
        }

        if (x->pointers[i + 1]->dataNum == x->m - 1) {
            splitNode(x, i + 1, x->pointers[i + 1]);

            if (x->data[i + 1].primaryKey < ca.primaryKey) {
                i++;
            }
        }
        insertData(x->pointers[i + 1], ca);
    }
}*/
void insertData(BTreeNode* x, CustomerAccount ca) {
    int i = x->dataNum - 1;
    if (x->leaf == true) {
        while (i >= 0 && x->data[i].primaryKey > ca.primaryKey) {
            x->data[i + 1] = x->data[i];
            i--;
        }
        x->data[i + 1] = ca;
        x->dataNum = x->dataNum + 1;
    }
    else {
        while (i >= 0 && x->data[i].primaryKey > ca.primaryKey) {
            i--;
        }
        if (x->pointers[i + 1]->dataNum == x->m - 1) {
            splitNode(x, i + 1, x->pointers[i + 1]);
            if (x->data[i + 1].primaryKey < ca.primaryKey) {
                i++;
            }
        }
        insertData(x->pointers[i + 1], ca);
    }
}

void initializeBTree(BTree* tree) {
    int m;
    cout << "Unesi red stabla" << endl;
    cin >> m;

    tree->root = nullptr;
    tree->m = m;
}

void insertNode(BTree* tree, CustomerAccount ca) {
    if (tree->root == nullptr) {
        tree->root = createNode(tree->m, true);
        tree->root->data[0] = ca;
        tree->root->dataNum = 1;
    }
    else {
        if (tree->root->dataNum == tree->m - 1) {
            BTreeNode* tmp = createNode(tree->m, false);
            tmp->pointers[0] = tree->root;

            splitNode(tmp, 0, tree->root);
            int i = 0;
            if (tmp->data[0].primaryKey < ca.primaryKey) {
                i++;
            }
            insertData(tmp->pointers[i], ca);
            tree->root = tmp;
        }
        else {
            insertData(tree->root, ca);
        }
    }
}

void readFileAndInsertToBTree(BTree* tree, const string& fileName) {

    ifstream file(fileName);
    string line;
    char separator = '|';

    double CA_ID;
    double CA_B_ID; 
    double CA_C_ID;
    string CA_NAME;
    int CA_TAX_ST;
    double CA_BAL;

    if (!file.is_open()) {
        cerr << "Unable to open file\n";
        return;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        CustomerAccount ca;

        getline(iss, token, separator);
        CA_ID = stod(token);
        ca.primaryKey = CA_ID;
        
        getline(iss, token, separator);
        CA_B_ID = stod(token);

        
        getline(iss, token, separator);
        CA_C_ID = stod(token);
        ca.customerKey = CA_C_ID;
        
        getline(iss, token, separator);
        ca.name = token;

        
        getline(iss, token, separator);
        CA_TAX_ST = stoi(token);

      
        getline(iss, token, separator);
        ca.bal = stod(token);

        insertNode(tree, ca);
    }

    file.close();
}

void traverseLevelOrder(BTreeNode* root) {
    if (root == nullptr) return;

    queue<BTreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size(); // Number of nodes at the current level

        for (int i = 0; i < levelSize; ++i) {
            BTreeNode* node = q.front();
            q.pop();

            // Process the node here
            for (int j = 0; j < node->dataNum; ++j) {
                cout << node->data[j].primaryKey << " ";
            }
            cout << "| "; // Separator for nodes at the same level

            // Enqueue child nodes
            if (!node->leaf) {
                for (int j = 0; j <= node->dataNum; ++j) {
                    if (node->pointers[j] != nullptr) {
                        q.push(node->pointers[j]);
                    }
                }
            }
        }
        cout << endl; // New line after each level
    }
}


int main() {
    BTree t;
    initializeBTree(&t);
    readFileAndInsertToBTree(&t, "CustomerAccount20.txt");
    traverseLevelOrder(t.root);
    
    return 0;
}