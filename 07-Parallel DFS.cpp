#include <iostream>
#include <vector>
#include <omp.h>


#define MAX_NODES 1000


using namespace std;


int result[MAX_NODES];
int n_threads;


struct TreeNode {
    int value;
    vector<TreeNode*> children;
};


void dfs(TreeNode* node, int depth) {
    // Base case: leaf node
    if (node->children.empty()) {
        #pragma omp critical
        {
            result[depth] += node->value;
        }
    } else {
        // Recursive case: internal node
        #pragma omp parallel num_threads(n_threads)
        {
            #pragma omp single nowait
            {
                for (auto child : node->children) {
                    #pragma omp task
                    {
                        dfs(child, depth + 1);
                    }
                }
            }
        }
    }
}


int main() {
    // Construct a tree
    TreeNode* root = new TreeNode{1};
    TreeNode* child1 = new TreeNode{2};
    TreeNode* child2 = new TreeNode{3};
    root->children.push_back(child1);
    root->children.push_back(child2);
    TreeNode* grandchild1 = new TreeNode{4};
    TreeNode* grandchild2 = new TreeNode{5};
    TreeNode* grandchild3 = new TreeNode{6};
    child1->children.push_back(grandchild1);
    child2->children.push_back(grandchild2);
    child2->children.push_back(grandchild3);


    // Initialize OpenMP
    n_threads = omp_get_max_threads();


    // Run DFS
    dfs(root, 0);


    // Print results
    for (int i = 0; i < MAX_NODES; i++) {
        if (result[i] > 0) {
            cout << "Depth " << i << ": " << result[i] << endl;
        }
    }


    return 0;
}
