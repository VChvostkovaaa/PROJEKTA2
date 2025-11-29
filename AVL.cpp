#include "AVL.h"
#include "TreeBase.h"
#include <iostream>
#include <algorithm>
#include <string>


// inspirace téhle části kodu je z: https://github.com/Korf-tms/Algoritmy-II/blob/main/Week%203/main.cpp
/**
 * @brief Konstruktor pro uzel AVL stromu.
 * @param word Slovo, které se má do uzlu uložit.
 */
AVLNode::AVLNode(const std::string &word) {
    this -> word = word;
    this -> left = nullptr;
    this -> right = nullptr;
    this -> probability = 0.0;
    this -> height = 1;  // nově vytvořený uzel má vždy výšku 1
}

/**
 * @brief - vrací aktuální výšku uzlu
 * @param node - uzel, od kterého nás výška zajímá
 * @return - výška uzlu, nebo 0, pokud je uzel nullptr
 */
int getHeight(AVLNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return node -> height;
}

/**
 * @brief - vypočet faktoru vyvážení
 * faktor je rozdíl výšky levého a pravého podstromu
 * @param node - uzel, pro který se faktor počítá
 * @return Hodnota faktoru vyvážení. Kladná = levý podstrom je vyšší, Záporná = pravý je vyšší
 */
int getBalanceFactor(AVLNode* node) {
    if( node == nullptr ) return 0;
    return getHeight(static_cast<AVLNode *>(node -> left)) - getHeight(static_cast<AVLNode *>(node -> right));
}

/**
 * @brief - aktualizuje výšku uzlu na základě výšek jeho potomků
 * výška = 1 + max(výška levého, výška pravého)
 * @param node uzel, jehož výška se má aktualizovat
 */
void updateHeight(AVLNode* node) {
    if( node == nullptr ) return;
    node -> height = 1 + std::max(getHeight(static_cast<AVLNode *>(node -> left)), getHeight(static_cast<AVLNode *>(node -> right)));
}

/**
 * @brief - udělá pravou rotaci kolem uzlu
 * Používá se pro vyvážení v případech LL
 * @param x - uzel, který je kořenem nevyváženého podstromu
 * @return - nový kořen podstromu po rotaci
 */
AVLNode* rotateRight(AVLNode* x) {
    // c se stane novým kořenem
    AVLNode* c = static_cast<AVLNode *>(x -> left);
    // t2 je pravý potomek c, který se přesune
    AVLNode* t2 = static_cast<AVLNode*>(c -> right);

    // provedení rotace
    c -> right = x;
    x -> left = t2;

    // aktualizace výšek
    updateHeight(x);
    updateHeight(c);

    // vrátíme nový kořen podstromu
    return c;
}

/**
 * @brief - provede levou rotaci kolem uzlu
 * Používá se pro vyvážení v případech RR
 * @param x - uzel, který je kořenem nevyváženého podstromu
 * @return - nový kořen podstromu po rotaci
 */
AVLNode* rotateLeft(AVLNode* x){
    // c se stane novým kořenem
    AVLNode* c = static_cast<AVLNode *>(x -> right);
    // t2 je levý potomek c, který se přesune
    AVLNode* t2 = static_cast<AVLNode*>(c -> left);

    // provedení rotace
    c -> left = x;
    x -> right = t2;

    // aktualizace výšek
    updateHeight(x);
    updateHeight(c);

    // vrátíme nový kořen podstromu
    return c;
}

/**
 * @brief - zkontroluje a vyváží uzel, pokud je nevyvážený
 * @param node - uzel, který se má zkontrolovat a případně vyvážit
 * @return - ukazatel na kořen vyváženého podstromu
 */
AVLNode* balance(AVLNode* node) {
    updateHeight(node);
    int bf = getBalanceFactor(node);

    // levý podstrom je vyššá
    if (bf > 1) {
        // LR
        if (getBalanceFactor(static_cast<AVLNode *>(node -> left)) < 0){
            // ano -> levá rotace na levém potomkovi
            node -> left = rotateLeft(static_cast<AVLNode *>(node -> left));
        }
        // potom pravá rotace
        return rotateRight(node);
    }

    // pravý podstrom je vyšší
    if (bf < -1) {
        // RL
        if (getBalanceFactor(static_cast<AVLNode *>(node -> right)) > 0) {
            // ano -> pravá rotace na pravém potomkovi
            node -> right = rotateRight(static_cast<AVLNode *>(node -> right));
        }
        // potom levá rotace
        return rotateLeft(node);
    }

    // strom je vyvážený
    return node;
}

/**
 * @brief - konstruktor pro vytvoření prázdného AVL
 */
AVL::AVL() : BinaryTreeBase(){}

/**
  * @brief - metoda pro vložení nového slova do stromu
  * @param word - slovo, které se má vložit
  */
void AVL::insert(const std::string &word) {
    root = insertRecursive(static_cast<AVLNode*>(root), word);
}

/**
 * @brief - rekurzivní funkce pro vložení uzlu a následné vyvážení
 * @param node - aktuální uzel, ve kterém se nacházíme
 * @param word - slovo, které vkládáme
 * @return - kořen podstromu po vložení a vyvážení
 */
AVLNode *AVL::insertRecursive(AVLNode *node, const std::string &word) {
    if( node == nullptr ){
        return new AVLNode(word);
    }

    if(word < node->word){
        node -> left = insertRecursive(static_cast<AVLNode *>(node -> left), word);
    } else if (word > node->word){
        node -> right = insertRecursive(static_cast<AVLNode *>(node -> right), word);
    }

    // vyvážení uzlu po vložení
    return balance(node);
}
