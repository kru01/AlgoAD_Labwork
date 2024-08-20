/* CSC14111 - 21KHMT - Lab 5: Dynamic Programming
 * 21127135 - Diep Huu Phuc
 *
 * Q7. The optimal binary search trees.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

const std::string inPath = "inputs/";

struct Node {
    int idx;
    Node* left, *right;
    Node(int idx): idx(idx), left(nullptr), right(nullptr) {}
};

Node* buildTree
(int* keys, std::vector<std::vector<int>>& roots, int i, int j) {
    if (i > j) return nullptr;

    int t = roots[i][j];
    if (t == 0) return nullptr;

    Node* p = new Node(t - 1);
    p->left = buildTree(keys, roots, i, t - 1);
    p->right = buildTree(keys, roots, t + 1, j);

    return p;
}

float buildOptBST(int keyNum, int* keys, float* probs, Node*& root) {
    std::vector<std::vector<float>>
        costs(keyNum + 2, std::vector<float>(keyNum + 1, 0));

    std::vector<std::vector<int>>
        roots(keyNum + 2, std::vector<int>(keyNum + 1, 0));

    for (int i = 1; i <= keyNum; i++) {
        costs[i][i] = probs[i - 1];
        roots[i][i] = i;
    }

    for (int diag = 1; diag < keyNum; diag++)
        for (int i = 1; i <= keyNum - diag; i++) {
            int j = i + diag;

            costs[i][j] = std::numeric_limits<float>::max();
            float sumProb = 0.0;

            for (int t = i; t <= j; t++) {
                sumProb += probs[t - 1];

                float val = costs[i][t - 1] + costs[t + 1][j];

                if (val < costs[i][j]) {
                    costs[i][j] = val; roots[i][j] = t;
                }
            }

            costs[i][j] += sumProb;
        }

    root = buildTree(keys, roots, 1, keyNum);
    return costs[1][keyNum];
}

void printTree(Node* root, int* keys, float* probs) {
    if (root == nullptr) return;
    printTree(root->left, keys, probs);
    std::cout << keys[root->idx] << " " << probs[root->idx] << "\n";
    printTree(root->right, keys, probs);
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    std::ifstream inFile(inPath + "7.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int keyNum; inFile >> keyNum;

    int* keys = new int[keyNum];
    float* probs = new float[keyNum];

    for (int i = 0; i < keyNum; i++) inFile >> keys[i];
    for (int i = 0; i < keyNum; i++) inFile >> probs[i];
    inFile.close();

    Node* root = nullptr;
    float minCost = buildOptBST(keyNum, keys, probs, root);

    printTree(root, keys, probs);
    std::cout << minCost << std::endl;

    deleteTree(root);
    delete[] keys; delete[] probs;
    return 0;
}