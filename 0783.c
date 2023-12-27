/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


void inorder_travel(struct TreeNode* root, int *ex_val, int *res)
{
    if (!root)
    {
        return;
    }
    inorder_travel(root->left, ex_val, res);
    if (*ex_val >= 0)
    {
        *res = fmin(abs(*ex_val - root->val), *res);
    }
    *ex_val = root->val;
    inorder_travel(root->right, ex_val, res);
}

int minDiffInBST(struct TreeNode* root) {
    int res = 999999;
    int ex_val = -1;
    inorder_travel(root, &ex_val, &res);
    return res;
}