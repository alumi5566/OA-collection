//
//  main.cpp
//  05_SubtreeMaximumAverageNode
//
//  Created by alumi5566 on 2019/2/19.
//  Copyright © 2019 alumi5566. All rights reserved.
//

// Description Given a binary tree, find the subtree with maximum average. Return the root of the
// subtree.
// Example Given a binary tree:
//      1
//    /  \
//   -5   11
//  / \  /  \
// 1  2 4   -2
// return the node 11.

/**
 * Definition of TreeNode:
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left, right;
 *     public TreeNode(int val) {
 *         this.val = val;
 *         this.left = this.right = null;
 *     }
 * }
 */
// lintcode #597
// https://yeqiuquan.blogspot.com/2017/03/lintcode-597-subtree-with-maximum.html
// https://blog.csdn.net/roufoo/article/details/86240887
// https://www.jiuzhang.com/qa/6908/

#include "../amazonOA/Header.h"
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};

// use this to store result, avg = sum/cnt
struct ResultType {
    TreeNode * node; // one of the node in tree
    int sum;    // sum (include this node)
    int count;  // count (include this node)
    ResultType(TreeNode * t = NULL, int s = 0, int c = 0):
        node(t), sum(s), count(c) {}
};

ResultType maxResult;

ResultType helper(TreeNode * root) {
    if (!root) return ResultType();
    ResultType left = helper(root->left);
    ResultType right = helper(root->right);
    
    int sum = left.sum + right.sum + root->val;
    int count = left.count + right.count + 1;
    
    // left child + right child + self => summary and compare
    ResultType newResult = ResultType(root, sum, count);
    
    if ((maxResult.count == 0) ||
        ((double)maxResult.sum / maxResult.count < (double)newResult.sum / newResult.count)) {
        maxResult = newResult;
    }
    return newResult;
}

TreeNode * findSubtree2(TreeNode * root) {
    if (!root) return NULL;
    
    // initial as a NULL node
    maxResult = ResultType(NULL, 0, 0);
    helper(root);
    return maxResult.node;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "05_Hello, World!\n";
    return 0;
}
