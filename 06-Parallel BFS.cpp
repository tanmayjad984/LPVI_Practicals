#include<iostream>
#include <queue>
#include <vector>
#include <omp.h>
#define MAX_NODES 1000
using namespace std;

int visited[MAX_NODES];
int n_threads;

struct TreeNode {
    int value;
    vector<TreeNode*> children;
};

void bfs(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    visited[root->value] = 1;
    while (!q.empty()) {
        int size = q.size(); // Store the initial size
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            for (auto child : node->children) {
                if (!visited[child->value]) {
                    visited[child->value] = 1;
                    q.push(child);
                }
            }
        }
    }
}

int main() {
    // Construct a tree
    TreeNode* root = new TreeNode{0};
    for (int i = 1; i < 10; i++) {
        TreeNode* child = new TreeNode{i};
        root->children.push_back(child);
        for (int j = 0; j < i; j++) {
            TreeNode* grandchild = new TreeNode{j};
            child->children.push_back(grandchild); // Corrected syntax
        }
    }
    // Initialize OpenMP
    n_threads = omp_get_max_threads();
    // Run BFS
    bfs(root);
    // Print visited nodes
    for (int i = 0; i < 10; i++) {
        if (visited[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
