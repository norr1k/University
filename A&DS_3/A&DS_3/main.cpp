#include "defines.cpp"
#include "Header.h"
#include <iostream>



int main() {
    using namespace my;

    TreeNode<int>* root = new TreeNode<int>(10, 100);
    root->insert(5, 50);
    root->insert(15, 150);
    root->insert(3, 30);
    root->insert(7, 70);

    std::cout << "Pre-order Traversal:" << std::endl;
    root->preorderTraversal(root);

    std::cout << "In-order Traversal:" << std::endl;
    root->inorderTraversal(root);

    std::cout << "Post-order Traversal:" << std::endl;
    root->postorderTraversal(root);

    AVL_node<int>* avlRoot = new AVL_node<int>(10, 100);
    avlRoot->insert(avlRoot, 5, 50);
    avlRoot->insert(avlRoot, 15, 150);
    avlRoot->insert(avlRoot, 3, 30);
    avlRoot->insert(avlRoot, 7, 70);

    std::cout << "Level-order Traversal (AVL):" << std::endl;
    avlRoot->levelOrderTraversal(avlRoot);

    delete root;
    delete avlRoot;

    return 0;
}
