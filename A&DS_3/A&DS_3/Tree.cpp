// Implementation.cpp
#include "Header.h"

namespace my {
    template <typename _T>
    TreeNode<_T>::TreeNode(int _key, _T _value)
        : key(_key), value(_value), ptr_left(nullptr), ptr_right(nullptr) {}

    template <typename _T>
    TreeNode<_T>::~TreeNode() {
        delete ptr_left;
        delete ptr_right;
    }

    template <typename _T>
    void TreeNode<_T>::insert(int _key, _T _value) {
        if (_key < key) {
            if (!ptr_left)
                ptr_left = new TreeNode(_key, _value);
            else
                ptr_left->insert(_key, _value);
        }
        else if (_key > key) {
            if (!ptr_right)
                ptr_right = new TreeNode(_key, _value);
            else
                ptr_right->insert(_key, _value);
        }
    }

    template <typename _T>
    TreeNode<_T>* TreeNode<_T>::remove(int _key, TreeNode* root) {
        if (!root) return nullptr;

        if (_key < root->key) {
            root->ptr_left = remove(_key, root->ptr_left);
        }
        else if (_key > root->key) {
            root->ptr_right = remove(_key, root->ptr_right);
        }
        else {
            if (!root->ptr_left) {
                TreeNode* rightChild = root->ptr_right;
                delete root;
                return rightChild;
            }
            if (!root->ptr_right) {
                TreeNode* leftChild = root->ptr_left;
                delete root;
                return leftChild;
            }

            TreeNode* minLargerNode = min(root->ptr_right);
            root->key = minLargerNode->key;
            root->value = minLargerNode->value;
            root->ptr_right = remove(minLargerNode->key, root->ptr_right);
        }
        return root;
    }

    template <typename _T>
    TreeNode<_T>* TreeNode<_T>::max(TreeNode* node) {
        while (node && node->ptr_right)
            node = node->ptr_right;
        return node;
    }

    template <typename _T>
    TreeNode<_T>* TreeNode<_T>::min(TreeNode* node) {
        while (node && node->ptr_left)
            node = node->ptr_left;
        return node;
    }

    template <typename _T>
    AVL_node<_T>::AVL_node(int _key, _T _value)
        : TreeNode<_T>(_key, _value), height(1) {}

    template <typename _T>
    AVL_node<_T>::~AVL_node() {}

    template <typename _T>
    int AVL_node<_T>::getHeight(AVL_node* node) {
        return node ? node->height : 0;
    }

    template <typename _T>
    void AVL_node<_T>::updateHeight(AVL_node* node) {
        if (node)
            node->height = 1 + std::max(getHeight(dynamic_cast<AVL_node*>(node->ptr_left)),
                getHeight(dynamic_cast<AVL_node*>(node->ptr_right)));
    }

    template <typename _T>
    int AVL_node<_T>::getDifference(AVL_node* node) {
        return getHeight(dynamic_cast<AVL_node*>(node->ptr_right)) -
            getHeight(dynamic_cast<AVL_node*>(node->ptr_left));
    }

    template <typename _T>
    void AVL_node<_T>::rightRotate(AVL_node*& root) {
        AVL_node* leftChild = dynamic_cast<AVL_node*>(root->ptr_left);
        root->ptr_left = leftChild->ptr_right;
        leftChild->ptr_right = root;
        updateHeight(root);
        updateHeight(leftChild);
        root = leftChild;
    }

    template <typename _T>
    void AVL_node<_T>::leftRotate(AVL_node*& root) {
        AVL_node* rightChild = dynamic_cast<AVL_node*>(root->ptr_right);
        root->ptr_right = rightChild->ptr_left;
        rightChild->ptr_left = root;
        updateHeight(root);
        updateHeight(rightChild);
        root = rightChild;
    }

    template <typename _T>
    void AVL_node<_T>::balance(AVL_node*& root) {
        updateHeight(root);
        int balanceFactor = getDifference(root);

        if (balanceFactor > 1) {
            if (getDifference(dynamic_cast<AVL_node*>(root->ptr_right)) < 0)
                rightRotate(dynamic_cast<AVL_node*&>(root->ptr_right));
            leftRotate(root);
        }
        else if (balanceFactor < -1) {
            if (getDifference(dynamic_cast<AVL_node*>(root->ptr_left)) > 0)
                leftRotate(dynamic_cast<AVL_node*&>(root->ptr_left));
            rightRotate(root);
        }
    }

    template <typename _T>
    void AVL_node<_T>::insert(AVL_node*& root, int _key, _T _value) {
        if (!root) {
            root = new AVL_node(_key, _value);
            return;
        }

        if (_key < root->key)
            insert(dynamic_cast<AVL_node*&>(root->ptr_left), _key, _value);
        else
            insert(dynamic_cast<AVL_node*&>(root->ptr_right), _key, _value);

        balance(root);
    }





    template <typename _T>
    void TreeNode<_T>::preorderTraversal(TreeNode* node, const std::function<void(int, _T)>& visit) {
        if (!node) return;
        visit(node->key, node->value);
        preorderTraversal(node->ptr_left, visit);
        preorderTraversal(node->ptr_right, visit);
    }

    template <typename _T>
    void TreeNode<_T>::inorderTraversal(TreeNode* node, const std::function<void(int, _T)>& visit) {
        if (!node) return;
        inorderTraversal(node->ptr_left, visit);
        visit(node->key, node->value);
        inorderTraversal(node->ptr_right, visit);
    }

    template <typename _T>
    void TreeNode<_T>::postorderTraversal(TreeNode* node, const std::function<void(int, _T)>& visit) {
        if (!node) return;
        postorderTraversal(node->ptr_left, visit);
        postorderTraversal(node->ptr_right, visit);
        visit(node->key, node->value);
    }

    template <typename _T>
    void AVL_node<_T>::levelOrderTraversal(AVL_node* root, const std::function<void(int, _T)>& visit) {
        if (!root) return;
        std::queue<AVL_node*> q;
        q.push(root);

        while (!q.empty()) {
            AVL_node* current = q.front();
            q.pop();

            visit(current->key, current->value);

            if (current->ptr_left)
                q.push(dynamic_cast<AVL_node*>(current->ptr_left));
            if (current->ptr_right)
                q.push(dynamic_cast<AVL_node*>(current->ptr_right));
        }
    }
}
