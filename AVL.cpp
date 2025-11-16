#include "AVL.h"
#include "TreeBase.h"
#include <iostream>
#include <algorithm>
#include <string>

AVLNode::AVLNode(const std::string &w) {
    this->word = w;
    this->left = nullptr;
    this->right = nullptr;
    this->probability = 0.0;
    this -> height = 1;
}

/**
 *
 * @param node
 * @return
 */
int getHeight(AVLNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return node -> height;
}

int getBalanceFactor(AVLNode* node) {
    if( node == nullptr ) return 0;
    return getHeight(static_cast<AVLNode *>(node -> left)) - getHeight(static_cast<AVLNode *>(node -> right));
}

void updateHeight(AVLNode* node) {
    if( node == nullptr ) return;
    node -> height = 1 + std::max(getHeight(static_cast<AVLNode *>(node -> left)), getHeight(static_cast<AVLNode *>(node -> right)));
}

AVLNode* rotateRight(AVLNode* r) {
    AVLNode* c = static_cast<AVLNode *>(r -> left);
    AVLNode* t2 = static_cast<AVLNode*>(c -> right);

    c -> right = r;
    r -> left = t2;

    updateHeight(r);
    updateHeight(c);

    return c;
}

AVLNode* rotateLeft(AVLNode* r){
    AVLNode* c = static_cast<AVLNode *>(r -> right);
    AVLNode* t2 = static_cast<AVLNode*>(c -> left);

    c -> left = r;
    r -> right = t2;

    updateHeight(r);
    updateHeight(c);

    return c;
}

AVLNode* balance(AVLNode* node) {
    updateHeight(node);
    int bf = getBalanceFactor(node);

    // Left heavy (LL nebo LR)
    if (bf > 1) {
        if (getBalanceFactor(static_cast<AVLNode *>(node -> left)) < 0){
            node -> left = rotateLeft(static_cast<AVLNode *>(node -> left));
        }
        return rotateRight(node);
    }

    // Right heavy (RR nebo RL)
    if (bf < -1) {
        if (getBalanceFactor(static_cast<AVLNode *>(node -> right)) > 0) {
            node -> right = rotateRight(static_cast<AVLNode *>(node -> right));
        }
        return rotateLeft(node);
    }

    return node;
}

AVL::AVL() : BinaryTreeBase<AVLNode>(){}

void AVL::insert(const std::string &word) {
    root = insertRecursive(root, word);
}

AVLNode *AVL::insertRecursive(AVLNode *node, const std::string &word) {
    if( node == nullptr ){
        return new AVLNode(word);
    }
    if(word < node->word){
        node->left = insertRecursive(static_cast<AVLNode *>(node -> left), word);
    } else if (word > node->word){
        node->right = insertRecursive(static_cast<AVLNode *>(node -> right), word);
    } else {
        return node;
    }

    return balance(node); // KONTROLA A BALANCOVÁNÍ po každém vložení

}









