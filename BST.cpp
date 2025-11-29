#include "BST.h"
#include "TreeBase.h"
#include <iostream>
#include <string>

// inspirace téhle části kodu je z: https://github.com/Korf-tms/Algoritmy-I/blob/main/Week%209-11/binary_search_tree.cpp
/**
 * @brief - konstruktor pro BST
 * @param word - slovo, které se má uložit
 */
BSTNode::BSTNode(const std::string& word) {
    this -> word = word;
    this -> left = nullptr;
    this -> right = nullptr;
    this -> probability = 0.0;
    // výška se pro BST nepoužívá
}

/**
 * @brief - konstuctor pro vytvoření prázdného BST
 */
BST::BST() : BinaryTreeBase() {
}

/**
  * @brief - metoda pro vložení nového slova do stromu
  * @param word - slovo, které se má vložit
  */
void BST::insert(const std::string& word) {
    // nový kořen se uloží do 'root'
    root = insertRecursive(static_cast<BSTNode*>(root), word);
}

/**
  * @brief - rekurzivní funkce pro vložení uzlu do BST
  * logika BST: menší -> doleva, větší -> doprava
  * @param node - aktuální uzel, ve kterém se nacházíme
  * @param word - slovo, které vkládáme
  * @return - kořen podstromu po vložení
  */
BSTNode* BST::insertRecursive(BSTNode* node, const std::string& word) {
    if (node == nullptr) {
        // vytvoříme nový uzel a vrátíme na něj ukazatel.
        return new BSTNode(word);
    }

    // porovnáváme vkládané slovo se slovem v aktuálním uzlu
    if (word < node -> word) {
        node -> left = insertRecursive(static_cast<BSTNode*>(node -> left), word);
    } else if (word > node -> word) {
        node -> right = insertRecursive(static_cast<BSTNode*>(node -> right), word);
    }

    // vrátíme ukazatel na aktuální uzel
    return node;
}
