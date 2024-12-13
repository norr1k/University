#pragma once

#include <queue>
#include <iostream>

namespace my {
    template <typename _T>
    class TreeNode {
    public:
        TreeNode(int key, _T value) : key(key), value(value), ptr_left(nullptr), ptr_right(nullptr) {}

        ~TreeNode() {
            delete ptr_left;
            delete ptr_right;
        }

        void insert(int key, _T value) {
            if (key < this->key) {
                if (ptr_left == nullptr)
                    ptr_left = new TreeNode(key, value);
                else
                    ptr_left->insert(key, value);
            }
            else {
                if (ptr_right == nullptr)
                    ptr_right = new TreeNode(key, value);
                else
                    ptr_right->insert(key, value);
            }
        }

        void preorderTraversal(TreeNode* node) {
            if (!node) return;
            std::cout << "Key: " << node->key << ", Value: " << node->value << std::endl;
            preorderTraversal(node->ptr_left);
            preorderTraversal(node->ptr_right);
        }

        void inorderTraversal(TreeNode* node) {
            if (!node) return;
            inorderTraversal(node->ptr_left);
            std::cout << "Key: " << node->key << ", Value: " << node->value << std::endl;
            inorderTraversal(node->ptr_right);
        }

        void postorderTraversal(TreeNode* node) {
            if (!node) return;
            postorderTraversal(node->ptr_left);
            postorderTraversal(node->ptr_right);
            std::cout << "Key: " << node->key << ", Value: " << node->value << std::endl;
        }

    protected:
        int key;
        _T value;
        TreeNode* ptr_left;
        TreeNode* ptr_right;
    };

    template <typename _T>
    class AVL_node : protected TreeNode<_T> {
    public:
        AVL_node(int key, _T value) : TreeNode<_T>(key, value), height(1) {}

        ~AVL_node() {}

        void insert(AVL_node*& root, int key, _T value) {
            if (!root) {
                root = new AVL_node(key, value);
                return;
            }

            if (key < root->key) {
                insert(reinterpret_cast<AVL_node*&>(root->ptr_left), key, value);
            }
            else {
                insert(reinterpret_cast<AVL_node*&>(root->ptr_right), key, value);
            }

            balance(root);
        }

        void levelOrderTraversal(AVL_node* root) {
            if (!root) return;
            std::queue<AVL_node*> q;
            q.push(root);

            while (!q.empty()) {
                AVL_node* current = q.front();
                q.pop();

                std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;

                if (current->ptr_left)
                    q.push(reinterpret_cast<AVL_node*>(current->ptr_left));
                if (current->ptr_right)
                    q.push(reinterpret_cast<AVL_node*>(current->ptr_right));
            }
        }

        void balance(AVL_node*& root) {
            updateHeight(root);
            int balanceFactor = getDifference(root);

            if (balanceFactor > 1) {
                if (getDifference(reinterpret_cast<AVL_node*>(root->ptr_right)) < 0)
                    rightRotate(reinterpret_cast<AVL_node*&>(root->ptr_right));
                leftRotate(root);
            }

            if (balanceFactor < -1) {
                if (getDifference(reinterpret_cast<AVL_node*>(root->ptr_left)) > 0)
                    leftRotate(reinterpret_cast<AVL_node*&>(root->ptr_left));
                rightRotate(root);
            }
        }

        int getHeight(AVL_node* node) {
            return node ? node->height : 0;
        }

        void updateHeight(AVL_node* node) {
            node->height = 1 + std::max(getHeight(reinterpret_cast<AVL_node*>(node->ptr_left)),
                getHeight(reinterpret_cast<AVL_node*>(node->ptr_right)));
        }

        int getDifference(AVL_node* node) {
            return getHeight(reinterpret_cast<AVL_node*>(node->ptr_right)) -
                getHeight(reinterpret_cast<AVL_node*>(node->ptr_left));
        }

        void rightRotate(AVL_node*& root) {
            AVL_node* newRoot = reinterpret_cast<AVL_node*>(root->ptr_left);
            root->ptr_left = newRoot->ptr_right;
            newRoot->ptr_right = root;
            updateHeight(root);
            updateHeight(newRoot);
            root = newRoot;
        }

        void leftRotate(AVL_node*& root) {
            AVL_node* newRoot = reinterpret_cast<AVL_node*>(root->ptr_right);
            root->ptr_right = newRoot->ptr_left;
            newRoot->ptr_left = root;
            updateHeight(root);
            updateHeight(newRoot);
            root = newRoot;
        }

    protected:
        int height;
    };
}
