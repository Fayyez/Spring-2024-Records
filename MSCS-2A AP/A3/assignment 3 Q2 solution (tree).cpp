class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode *root;

    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->val) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->val) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    bool isSumRecursive(TreeNode* node) {
        if (node == nullptr) return true;
        if (node->left == nullptr && node->right == nullptr) return true;
        int leftSum = node->left ? node->left->val : 0;
        int rightSum = node->right ? node->right->val : 0;
        return (node->val == leftSum + rightSum) &&
               isSumRecursive(node->left) &&
               isSumRecursive(node->right);
    }

    TreeNode* findLCARecursive(TreeNode* node, TreeNode* x, TreeNode* y) {
        if (node == nullptr) return nullptr;
        if (node == x || node == y) return node;

        TreeNode* leftLCA = findLCARecursive(node->left, x, y);
        TreeNode* rightLCA = findLCARecursive(node->right, x, y);

        if (leftLCA && rightLCA) return node;
        return leftLCA ? leftLCA : rightLCA;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    bool isSum() {
        return isSumRecursive(root);
    }

    TreeNode* findLCA(TreeNode* x, TreeNode* y) {
        return findLCARecursive(root, x, y);
    }
};