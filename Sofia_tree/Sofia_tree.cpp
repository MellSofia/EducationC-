﻿// Sofia_tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;

class Node {
public:
    int key;
    int value;
    Node* left;
    Node* right;
    int height;

    Node(int key, int value) : key(key), value(value), left(nullptr), right(nullptr), height(0) {}

    int getMax() {
        if (this->right == nullptr) {
            return this->key;
        }
        else {
            return this->right->getMax();
        }
    }

    int getMin() {
        if (this->left == nullptr) {
            return this->key;
        }
        else {
            return this->left->getMin();
        }
    }

    Node* find(int key_f) {
        if (this == nullptr || this->key == key_f) {
            return this;
        }
        else if (key_f < this->key) {
            return this->left->find(key_f);
        }
        else {
            return this->right->find(key_f);
        }
    }

    void printTree() {
        if (this != nullptr) {
            this->left->printTree();
            cout << this->key << " ";
            this->right->printTree();
        }
    }

    void deleteTree() {
        if (this != nullptr) {
            this->left->deleteTree();
            delete this->left;
            this->right->deleteTree();
            delete this->right;
        }
    }

    Node* copyTree() {
        Node* copy = new Node(this->key, this->value);
        if (this->left != nullptr) {
            copy->left = this->left->copyTree();
        }
        if (this->right != nullptr) {
            copy->right = this->right->copyTree();
        }
        return copy;
    }

    void updateHeight() {
        height = max(getHeight(left), getHeight(right)) + 1;
    }

    int getHeight(Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance() {
        return getHeight(right) - getHeight(left);
    }

    void swap(Node* a, Node* b) {
        int a_key = a->key;
        a->key = b->key;
        b->key = a_key;
        int  value = a->value;
        a->value = b->value;
        b->value = value;
    }

    Node* rightRotate() {
        swap(this, left);
        Node* buffer = right;
        right = left;
        left = right->left;
        right->left = right->right;
        right->right = buffer;
        right->updateHeight();
        updateHeight();
        return this;
    }

    Node* leftRotate() {
        swap(this, right);
        Node* buffer = left;
        left = right;
        right = left -> right;
        left -> right = left->left;
        left->left = buffer;
        left->updateHeight();
        updateHeight();
        return this;
    }

    Node* balance() {
        updateHeight();
        if (getBalance() == -2) {
            if (left->getBalance() > 0) left->leftRotate();
            rightRotate();
        }
        else if (getBalance() == 2) {
            if (right->getBalance() < 0) right->rightRotate();
            leftRotate();
        }
        return this;
    }

    Node* insert(int key_n, int value_n) {
        if (key_n < key) {
            if (left == nullptr) {
                left = new Node(key_n, value_n);
            } else {
                left = left->insert(key_n, value_n);
            }
        } else if (key_n > key) {
            if (right == nullptr) {
                right = new Node(key_n, value_n);
            } else {
                right = right->insert(key_n, value_n);
            }
        } else {
            return this;
        }

        balance();
    }

    Node* deleteNode(int key_d) {
        if (key_d < key) {
            if (left != nullptr) {
                left = left->deleteNode(key_d);
            }
        }
        else if (key_d > key) {
            if (right != nullptr) {
                right = right->deleteNode(key_d);
            }
        }
        else {
            if (left != nullptr && right != nullptr) {
                int minKey = right->getMin();
                key = minKey;
                right = right->deleteNode(minKey);
            }
            else if (left != nullptr) {
                Node* temp = left;
                delete this;
                return temp;
            }
            else if (right != nullptr) {
                Node* temp = right;
                delete this;
                return temp;
            }
            else {
                delete this;
                return nullptr;
            }
        }
        balance();
    }

};

int main() {
    setlocale(LC_ALL, "ru");

    // Создание корневого узла и дополнительных узлов
    Node* root = new Node(10, 0);
    root = root->insert(5, 0);
    root = root->insert(15, 0);
    root = root->insert(3, 0);
    root = root->insert(7, 0);
    root = root->insert(12, 0);
    root = root->insert(17, 0);

    // Вывод исходного дерева
    cout << "Исходное AVL-дерево: \n";
    root->printTree();
    cout << "\n";

    // Пример работы функции swapValues
    cout << "Обмен значений корня и его левого потомка...\n";
    root->swap(root, root->left);
    cout << "AVL-дерево после обмена значений: \n";
    root->printTree();
    cout << "\n";

    // Восстановление исходного порядка
    root->swap(root, root->left);

    // Пример работы функции rightRotate
    cout << "Выполнение правого поворота относительно корня...\n";
    root = root->rightRotate();
    cout << "AVL-дерево после правого поворота: \n";
    root->printTree();
    cout << "\n";

    cout << "Выполнение левого поворота относительно корня...\n";
    root = root->leftRotate();
    cout << "AVL-дерево после левого поворота: \n";
    root->printTree();
    cout << "\n";

    // Пример работы функции balance
    cout << "Вставка элементов для создания несбалансированного дерева...\n";
    root = root->insert(18, 0);
    root = root->insert(19, 0); // Это должно сделать дерево правым
    cout << "AVL-дерево до балансировки: \n";
    root->printTree();
    cout << "\n";

    cout << "Балансировка дерева...\n";
    root = root->balance();
    cout << "AVL-дерево после балансировки: \n";
    root->printTree();
    cout << "\n";

    // Удаление дерева
    root->deleteTree();
    delete root; // Удаляем корень дерева

    return 0;
}   

//int main() {
//    Node* root = new Node(10, 0);
//
//    // Вставка новых узлов
//    root = root->insert(5, 0);
//    root = root->insert(15, 0);
//    root = root->insert(3, 0);
//    root = root->insert(7, 0);
//    root = root->insert(12, 0);
//    root = root->insert(17, 0);
//
//    // Вывод максимального и минимального значений
//    cout << "Max: " << root->getMax() << endl;
//    cout << "Min: " << root->getMin() << endl;
//
//    // Поиск узла
//    Node* found = root->find(7);
//    if (found != nullptr) {
//        cout << "Found: " << found->key << endl;
//    }
//    else {
//        cout << "Not found" << endl;
//    }
//
//    // Вывод дерева
//    cout << "Tree: ";
//    root->printTree();
//    cout << endl;
//
//    // Копирование дерева
//    Node* copiedTree = root->copyTree();
//
//    // Вывод скопированного дерева
//    cout << "Copied Tree: ";
//    copiedTree->printTree();
//    cout << endl;
//
//    // Удаление узла с ключом 7
//    copiedTree = copiedTree->deleteNode(7);
//
//    // Вывод изменённого скопированного дерева
//    cout << "Modified Copied Tree: ";
//    copiedTree->printTree();
//    cout << endl;
//
//    // Удаление скопированного дерева
//    copiedTree->deleteTree();
//    delete copiedTree; // Удаляем корень скопированного дерева
//
//    // Удаление дерева
//    root->deleteTree();
//    delete root; // Удаляем корень исходного дерева
//
//    return 0;
//}