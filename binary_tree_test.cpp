#include <gtest/gtest.h>

#include "BinaryTree.cpp"

TEST(BinaryTree, BasicTest) {
    auto* root = new TreeNode<int>(0);

    ASSERT_EQ(root->value, 0);

    auto* node1 = new TreeNode<int>(-4);
    root->left = node1;
    node1->left = new TreeNode<int>(-6);

    ASSERT_EQ(root->left->left->value, -6);
}