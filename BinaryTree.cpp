#pragma once

template<typename T>
struct TreeNode {
    T value;
    TreeNode *right, *left;

    explicit TreeNode(T val):
        value(val),
        right(nullptr),
        left(nullptr) {};
};

// This is a basic BT, right?!

// void test() {
//     auto* root = new TreeNode<int>(5);
//     root->left = new TreeNode<int>(3);
//     root->right = new TreeNode<int>(9);
//     root->left->left = new TreeNode<int>(0);
// } // basic test - alloc leakage for some reason too 🤔
