#pragma once
#include <iostream>
#include<chrono>
#include<vector>

using namespace std;

namespace my_namespace{

class BinarySearchTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroyTree(Node* leaf) {
        if (leaf != nullptr) {
            destroyTree(leaf->left);
            destroyTree(leaf->right);
            delete leaf;
        }
    }

    bool insert(int key, Node*& leaf) {
        if (leaf == nullptr) {
            leaf = new Node(key);
            return true;
        }

        if (key == leaf->key) {
            return false; // элемент уже существует
        }
        else if (key < leaf->key) {
            return insert(key, leaf->left);
        }
        else {
            return insert(key, leaf->right);
        }
    }

    bool contains(int key, Node* leaf) const {
        if (leaf == nullptr) {
            return false;
        }

        if (key == leaf->key) {
            return true;
        }
        else if (key < leaf->key) {
            return contains(key, leaf->left);
        }
        else {
            return contains(key, leaf->right);
        }
    }

    bool erase(int key, Node*& leaf) {
        if (leaf == nullptr) {
            return false;
        }

        if (key == leaf->key) {
            return removeNode(leaf);
        }
        else if (key < leaf->key) {
            return erase(key, leaf->left);
        }
        else {
            return erase(key, leaf->right);
        }
    }

    bool removeNode(Node*& node) {
        if (node == nullptr) {
            return false;
        }

        Node* temp;
        if (node->left == nullptr) {
            temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            temp = node;
            node = node->left;
            delete temp;
        }
        else {
            temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->key = temp->key;
            erase(temp->key, node->right);
        }

        return true;
    }

    void print(Node* leaf) {
        if (leaf != nullptr) {
            print(leaf->left);
            std::cout << leaf->key << " ";
            print(leaf->right);
        }
    }

    void treeToVector(Node* node, std::vector<int>& vec) const {
        if (node) {
            treeToVector(node->left, vec);
            vec.push_back(node->key);
            treeToVector(node->right, vec);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() { destroyTree(root); }

    BinarySearchTree(const BinarySearchTree& other) {
        root = clone(other.root);
    }

    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            destroyTree(root);
            root = clone(other.root);
        }
        return *this;
    }

    void print() { print(root); std::cout << std::endl; }

    bool insert(int key) { return insert(key, root); }

    bool contains(int key) { return contains(key, root); }

    bool erase(int key) { return erase(key, root); }

    bool find(int key) const {
        return contains(key, root); 
    }

    std::vector<int> toVector() const {
        vector<int> result;
        treeToVector(root, result);
        return result;
    }
private:
    Node* clone(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            Node* newNode = new Node(node->key);
            newNode->left = clone(node->left);
            newNode->right = clone(node->right);
            return newNode;
        }
    }

};

//для заданного std::vector<int> верните новый std::vector<int>, 
//содержащий все повторяющиеся элементы 
//(для вектора {3 2 2 4} результат должен быть {2})

std::vector<int> findDuplicates(const std::vector<int>& vec) {
    my_namespace::BinarySearchTree seen;
    my_namespace::BinarySearchTree duplicates;

    for (int num : vec) {
        if (seen.find(num)) {
            duplicates.insert(num); //2 
        }
        else {
            seen.insert(num); // 3 2 4
        }
    }

    return duplicates.toVector();
}

size_t  random_number() { // or use Linear Congruential Generator
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

BinarySearchTree generateRandomBinarySearchTree(size_t size) {
    BinarySearchTree bst;
    for (size_t i = 0; i < size; ++i)
        bst.insert(random_number());
    return bst;
}

std::vector<size_t> generateRandomVector(size_t size) {
    std::vector<size_t> vec;
    for (size_t i = 0; i < size; ++i)
        vec.push_back(random_number());
    return vec;
}

template<typename T>
double averageFillingTime(T generate_func, size_t size) {
    double totalTime = 0.0;
    const size_t numTrials = 100; // number of trials

    for (size_t i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();

        generate_func(size);

        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration<double>(end - start).count();
    }

    return totalTime / numTrials;
}

double averageFindTimeBinarySearchTree(const BinarySearchTree& bst, size_t value) {
    double totalTime = 0.0;
    const size_t numTrials = 1000;
    for (size_t i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();
        bst.find(value);
        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration<double>(end - start).count();
    }

    return totalTime / numTrials;
}

double averageFindTimeVector(const vector<size_t>& vec, size_t value) {
    double totalTime = 0.0;
    const size_t numTrials = 1000;

    for (size_t i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();
        std::find(vec.begin(), vec.end(), value);
        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration<double>(end - start).count();
    }
    return totalTime / numTrials; 
}


double averageInsertTimeBinarySearchTree(BinarySearchTree& bst, size_t value) {
    double totalTime = 0.0;
    const size_t numTrials = 1000;

    for (int i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();
        bst.insert(value);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> duration = end - start;
        totalTime += duration.count();
    }

    return totalTime / numTrials;
}

double averageInsertTimeVector(std::vector<size_t>& vec, size_t index, size_t value) {
    double totalTime = 0.0;
    const size_t numTrials = 1000;

    for (size_t i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();
        vec.insert(vec.begin() + index, value);
        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration<double>(end - start).count();
    }

    return totalTime / numTrials;
}

double averageEraseTimeBinarySearchTree(BinarySearchTree& bst, size_t value) {
    double totalTime = 0.0;
    const size_t numTrials = 1000;

    for (size_t i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();
        bst.erase(value);
        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration<double> (end - start).count();
    }

    return totalTime / numTrials;
}

double averageEraseTimeVector(std::vector<size_t>& vec, size_t index) {
    double totalTime = 0.0;
    const size_t numTrials = 1000;

    for (size_t i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();
        vec.erase(vec.begin() + index);
        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration<double>(end - start).count();
    }

    return totalTime / numTrials;
}
}