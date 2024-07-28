#pragma once

template<typename T>
struct TreeNode {
    T value;
    TreeNode* right;
    TreeNode* left;

    explicit TreeNode(T val):
        value(val),
        right(nullptr),
        left(nullptr) {};
};

// This is a basic BT, right?!
