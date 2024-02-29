#include<../include/search_tree.h>

using namespace my_namespace;

int main() {
    /*size_t data_size = 100000;
    size_t value = my_namespace::random_number();

    BinarySearchTree bst = generateRandomBinarySearchTree(data_size);
    std::vector<size_t> vec = generateRandomVector(data_size);

    double bstTime = averageFillingTime(generateRandomBinarySearchTree, data_size);
    std::cout << "Average Filling Time (BinarySearchTree): " << bstTime << " seconds" << std::endl;
    double vectorTime = averageFillingTime(generateRandomVector, data_size);
    std::cout << "Average Filling Time (Vector): " << vectorTime << " seconds" << std::endl;
    cout << "bstTime - vectorTime = " << bstTime - vectorTime << endl;
    cout << endl;


    double avgInsertTimeBST = averageInsertTimeBinarySearchTree(bst, value);
    std::cout << "Average Insert Time (BinarySearchTree): " << avgInsertTimeBST << " seconds" << std::endl;
    double avgInsertTimeVec = averageInsertTimeVector(vec, data_size / 2, value);
    std::cout << "Average Insert Time (Vector): " << avgInsertTimeVec << " seconds" << std::endl;
    cout << "avgInsertTimeBST - avgInsertTimeVec = " << avgInsertTimeBST - avgInsertTimeVec << endl;
    cout << endl;


    double avgFindTimeBST = averageFindTimeBinarySearchTree(bst, value);
    std::cout << "Average Find Time (BinarySearchTree): " << avgFindTimeBST << " seconds" << std::endl;
    double avgFindTimeVec = averageFindTimeVector(vec, value);
    std::cout << "Average Find Time (Vector): " << avgFindTimeVec << " seconds" << std::endl;
    cout << "avgFindTimeBST - avgFindTimeVec = " << avgFindTimeBST - avgFindTimeVec << endl;
    cout << endl;



    double avgEraseTimeBST = averageEraseTimeBinarySearchTree(bst, value);
    std::cout << "Average Erase Time (BinarySearchTree): " << avgEraseTimeBST << " seconds" << std::endl;
    double avgEraseTimeVec = averageEraseTimeVector(vec, data_size / 2);
    std::cout << "Average Erase Time (Vector): " << avgEraseTimeVec << " seconds" << std::endl;
    cout << "avgEraseTimeBST - avgEraseTimeVec = " << avgEraseTimeBST - avgEraseTimeVec << endl;
    cout << endl;*/

    vector<int> vec = { 3,2,2,4 };
    vector<int> result = findDuplicates(vec);
    for (auto i : result) {
        std::cout << i << " ";
    }
    return 0;
}
