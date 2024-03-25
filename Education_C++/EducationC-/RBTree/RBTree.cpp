// RBTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;
#define BLACK true
#define RED false
class RBNode;
RBNode* nil;
class RBNode
{
public:
    int key = 0;
    int value = 0;
    RBNode* left = nil;
    RBNode* right = nil;
    RBNode* parent = nil;
    bool color = BLACK;

    RBNode()
    {
        this->key = NULL;
        this->value = NULL;
        this->color = RED;
        this->left = nil;
        this->right = nil;
        this->parent = nil;
    };

    RBNode(int keyp, int valuep)
    {
        this->key = keyp;
        this->value = valuep;
        this->color = RED;
        this->left = nil;
        this->right = nil;
        this->parent = nil;
    }
    bool nodeExists() { return this != nil; };
};
RBNode* nil = new RBNode;

class RBTree
{
public:
    RBNode* root;

    RBNode* search(int keyp) {
        RBNode* currentNode = root;
        while (currentNode != nil) {
            if (keyp < currentNode->key)
                currentNode = currentNode->left;
            else if (keyp > currentNode->key)
                currentNode = currentNode->right;
            else
                return currentNode;
        }
        return nil;
    }
    void transplantNode(RBNode* from, RBNode* to)
    {
        if (to == root) root = from;
        else if (to == to->parent->left) to->parent->left = from;
        else to->parent->right = from;
        from->parent = to->parent;
    }
    void insert(int keyp, int valuep) {
        RBNode* newNode = new RBNode(keyp, valuep);
        RBNode* y = nil;
        RBNode* x = this->root;

        while (x != nil) {
            y = x;
            if (newNode->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        newNode->parent = y;
        if (y == nil) {
            this->root = newNode;
        }
        else if (newNode->key < y->key) {
            y->left = newNode;
        }
        else {
            y->right = newNode;
        }

        newNode->left = nil;
        newNode->right = nil;
        newNode->color = RED;

        balance(newNode);
    }
    void leftRotate(RBNode* node) {
        RBNode* y = node->right;
        node->right = y->left;
        if (y->left != nil) y->left->parent = node;
        y->parent = node->parent;
        if (node->parent == nil) root = y;
        else if (node == node->parent->left) node->parent->left = y;
        else node->parent->right = y;
        y->left = node;
        node->parent = y;
    }
    void rightRotate(RBNode* node) {
        RBNode* y = node->left;
        node->left = y->right;
        if (y->right != nil) y->right->parent = node;
        y->parent = node->parent;
        if (node->parent == nil) root = y;
        else if (node == node->parent->right) node->parent->right = y;
        else node->parent->left = y;
        y->right = node;
        node->parent = y;
    }
    void balance(RBNode* x) {
        while (x->parent->color == RED) {
            if (x->parent == x->parent->parent->left) {
                RBNode* y = x->parent->parent->right;
                if (y->color == RED) {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else {
                    if (x == x->parent->right) {
                        x = x->parent;
                        leftRotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rightRotate(x->parent->parent);
                }
            }
            else {
                RBNode* y = x->parent->parent->left;
                if (y->color == RED) {
                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        rightRotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    leftRotate(x->parent->parent);
                }
            }
        }
        this->root->color = BLACK;
    }
    void remove(int key) {
        RBNode* nodeToDelete = search(key);
        if (nodeToDelete == nil) {
            cout << "Узел с предоставленным ключом не найден." << endl;
            return;
        }
        RBNode* y = nodeToDelete;
        RBNode* x;
        bool yOriginalColor = y->color;

        if (nodeToDelete->left == nil) {
            x = nodeToDelete->right;
            transplantNode(nodeToDelete, nodeToDelete->right);
        }
        else if (nodeToDelete->right == nil) {
            x = nodeToDelete->left;
            transplantNode(nodeToDelete, nodeToDelete->left);
        }
        else {
            y = nodeToDelete->right;
            while (y->left != nil) y = y->left;
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == nodeToDelete) x->parent = y;
            else {
                transplantNode(y, y->right);
                y->right = nodeToDelete->right;
                y->right->parent = y;
            }
            transplantNode(nodeToDelete, y);
            y->left = nodeToDelete->left;
            y->left->parent = y;
            y->color = nodeToDelete->color;
        }

        delete nodeToDelete;
        if (yOriginalColor == BLACK) fixedRules(x);
    }
    int getChildrenCount(RBNode* node)
    {
        int count = 0;
        if (node->left->nodeExists()) count += 1;
        if (node->right->nodeExists()) count += 1;
        return count;
    };

    void fixedRules(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                RBNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
};
int main() {
    // Создание нового Красно-Чёрного дерева
    RBTree* tree = new RBTree();

    // Вставка узлов в дерево
    tree->insert(10, 100);
    tree->insert(20, 200);
    tree->insert(30, 300);
    tree->insert(40, 400);
    tree->insert(50, 500);

    // Поиск узла по ключу
    RBNode* node = tree->search(30);
    if (node->nodeExists()) {
        cout << "Найден узел с ключом 30 и значением " << node->value << endl;
    }
    else {
        cout << "Узел с ключом 30 не найден" << endl;
    }

    // Удаление узла из дерева
    tree->remove(20);

    // Проверка, что узел был удален
    node = tree->search(20);
    if (!node->nodeExists()) {
        cout << "Узел с ключом 20 успешно удален" << endl;
    }

    // Получение количества детей узла
    node = tree->search(30);
    if (node->nodeExists()) {
        cout << "Узел с ключом 30 имеет " << tree->getChildrenCount(node) << " детей" << endl;
    }

    // Удаление дерева
    delete tree;

    return 0;
}
