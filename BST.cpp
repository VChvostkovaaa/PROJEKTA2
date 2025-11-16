#include "BST.h"
#include "TreeBase.h"
#include <iostream>
#include <string>

/**
 * @brief - konstructor pro uzel BST
 * @param w - slova, ktere se ma do uzlu ulozit
 */
BSTNode::BSTNode(const std::string& w) {
    this->word = w;
    this->left = nullptr;
    this->right = nullptr;
    this->probability = 0.0;
}

/**
 * @brief - zakladni konstructor pro cely BST strom
 * vola konstructor BinaryTreeBase
 */
BST::BST() : BinaryTreeBase<BSTNode>() {
}

/**
 * @brief - verejna metoda pro vlozeni slova do BST
 * @param word - slovo, ktere se nam ma ulozit
 */
void BST::insert(const std::string& word) {
    root = insertRecursive(root, word);
}

/**
 * @brief - funkce pro vlozzeni uzlu do BST
 * zjisti zakladni logiku BST: mensi -> doleva, vetsi -> doprava
 * @param node - aktualni uzel, ve kterem jsem
 * @param word - slovo, ktere vkladame
 * @return BSTNode* - ukazatel na kpren podtromu
 */
BSTNode* BST::insertRecursive(BSTNode* node, const std::string& word) {
    if (node == nullptr) {
        return new BSTNode(word);   // nasli jsme prazdne misto -> vytvorime novy uzel a vratime ho
    }

    // porovnavani
    if (word < node -> word) {
        // rekurze doleva
        node -> left = insertRecursive(static_cast<BSTNode*>(node -> left), word);
    } else if (word > node -> word) {
        // rekurze doprava
        node -> right = insertRecursive(static_cast<BSTNode*>(node -> right), word);
    }

    // duplikat -> vracime stavajici uzel
    return node;
}
