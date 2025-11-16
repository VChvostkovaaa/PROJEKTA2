#ifndef TREEBASE_H
#define TREEBASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // For std::max
#include <utility>   // For std::pair

// Forward-declaration is sufficient. No need for full include.
struct InputDataExtracted;

/**
 * @brief Base struct for a node.
 */
struct BaseNode {
    std::string word;
    BaseNode *left = nullptr;
    BaseNode *right = nullptr;
    double probability = 0.0;
    int height = 1; // Used by AVL tree
    virtual ~BaseNode() = default; // Virtual destructor for polymorphism
};

// --- Forward declarations for recursive helper functions ---

template<typename TNode>
int calculateHeightRecursive(TNode* node);

template<typename TNode>
void setProbabilitiesRecursive(TNode* node, const std::unordered_map<std::string, double>& probMap);


template<typename TNode>
double calculateAverageRecursive(TNode* node, int depth);


/**
 * @brief Base class for all binary search trees (BST, AVL, OPT).
 * Contains common logic for analysis (height, average comparisons).
 * TNode is the specific node type (BSTNode, AVLNode, OPTNode).
*/
template<typename TNode>
class BinaryTreeBase {
protected:
    TNode* root;

public:
    BinaryTreeBase() : root(nullptr) {}

    // --- Public Interface ---

    int getHeight() {
        return calculateHeightRecursive(root);
    }

    void setProbabilities(const std::unordered_map<std::string, double>& probMap) {
        setProbabilitiesRecursive(root, probMap);
    }

    double calculateAverageComparisons() { // Fixed name to be plural
        return calculateAverageRecursive(root, 0);
    }

    virtual ~BinaryTreeBase() = default;

    // --- Virtual methods to be implemented by derived classes ---

    // Used by BST/AVL for sequential insertion. OPT provides a dummy implementation.
    virtual void insert(const std::string& word) = 0;

    // Used by OPT to build the tree at once. BST/AVL can have a dummy implementation.
    // The signature now matches the implementation in OPT and the call in main.cpp.
    virtual void build(const std::vector<std::pair<std::string, double>>& data) {
        // Default implementation is empty. OPT will override this.
        (void)data;
    }
};

// --- Implementations of recursive helper functions ---

template<typename TNode>
int calculateHeightRecursive(TNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(calculateHeightRecursive(static_cast<TNode*>(node->left)),
                        calculateHeightRecursive(static_cast<TNode*>(node->right)));
}

template<typename TNode>
void setProbabilitiesRecursive(TNode* node, const std::unordered_map<std::string, double>& probMap) {
    if (node == nullptr) {
        return;
    }
    auto it = probMap.find(node->word);
    if (it != probMap.end()) {
        node->probability = it->second;
    }
    setProbabilitiesRecursive(static_cast<TNode*>(node->left), probMap);
    setProbabilitiesRecursive(static_cast<TNode*>(node->right), probMap);
}

template<typename TNode>
double calculateAverageRecursive(TNode* node, int depth) {
    if (node == nullptr) {
        return 0.0;
    }
    double c_i = (double)depth + 1.0;
    double currentContribution = c_i * node->probability;

    return currentContribution
           + calculateAverageRecursive(static_cast<TNode*>(node->left), depth + 1)
           + calculateAverageRecursive(static_cast<TNode*>(node->right), depth + 1);
}

#endif //TREEBASE_H