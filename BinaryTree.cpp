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
