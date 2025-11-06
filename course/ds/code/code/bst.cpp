struct TreeNode {
    int key;
    TreeNode *left;
    TreeNode *right;
    // 维护其他信息，如高度，节点数量等
    int size;  // 当前节点为根的子树大小
    int count; // 当前节点的重复数量

    TreeNode(int value)
        : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
};

TreeNode *findMinNode(TreeNode *root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

bool search(TreeNode *root, int target) {
    if (root == nullptr) {
        return false;
    }
    if (root->key == target) {
        return true;
    } else if (target < root->key) {
        return search(root->left, target);
    } else {
        return search(root->right, target);
    }
}

TreeNode *insert(TreeNode *root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->key) {
        root->left = insert(root->left, value);
    } else if (value > root->key) {
        root->right = insert(root->right, value);
    } else {
        root->count++; // 节点值相等，增加重复数量
    }
    root->size = root->count + (root->left ? root->left->size : 0) +
                 (root->right ? root->right->size : 0); // 更新节点的子树大小
    return root;
}

// 此处返回值为删除 value 后的新 root
TreeNode *remove(TreeNode *root, int value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->key) {
        root->left = remove(root->left, value);
    } else if (value > root->key) {
        root->right = remove(root->right, value);
    } else {
        if (root->count > 1) {
            root->count--; // 节点重复数量大于1，减少重复数量
        } else {
            if (root->left == nullptr) {
                TreeNode *temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                TreeNode *temp = root->left;
                delete root;
                return temp;
            } else {
                TreeNode *successor = findMinNode(root->right);
                root->key = successor->key;
                root->count = successor->count; // 更新重复数量
                // 当 successor->count > 1时，也应该删除该节点，否则
                // 后续的删除只会减少重复数量
                successor->count = 1;
                root->right = remove(root->right, successor->key);
            }
        }
    }
    // 继续维护size，不写成 --root->size;
    // 是因为value可能不在树中，从而可能未发生删除
    root->size = root->count + (root->left ? root->left->size : 0) +
                 (root->right ? root->right->size : 0);
    return root;
}
