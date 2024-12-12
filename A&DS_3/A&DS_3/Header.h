// Header.h
#pragma once

#include <functional>
#include <queue>

namespace my {
    template <typename _T>
    class TreeNode {
    public:
        TreeNode(int key, _T value);
        ~TreeNode();

        void insert(int key, _T value);
        TreeNode* remove(int key, TreeNode* root);
        TreeNode* max(TreeNode* node);
        TreeNode* min(TreeNode* node);

        void preorderTraversal(TreeNode* node, const std::function<void(int, _T)>& visit);
        void inorderTraversal(TreeNode* node, const std::function<void(int, _T)>& visit);
        void postorderTraversal(TreeNode* node, const std::function<void(int, _T)>& visit);

    protected:
        int key;
        _T value;
        TreeNode* ptr_left;
        TreeNode* ptr_right;
    };

    template <typename _T>
    class AVL_node : protected TreeNode<_T> {
    public:
        AVL_node(int key, _T value);
        ~AVL_node();

        int getHeight(AVL_node* node);
        void updateHeight(AVL_node* node);
        int getDifference(AVL_node* node);

        void rightRotate(AVL_node*& root);
        void leftRotate(AVL_node*& root);
        void balance(AVL_node*& root);

        void insert(AVL_node*& root, int key, _T value);
        void levelOrderTraversal(AVL_node* root, const std::function<void(int, _T)>& visit);

    protected:
        int height;
    };
}
