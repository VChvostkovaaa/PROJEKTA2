#ifndef BST_H
#define BST_H

#include "TreeBase.h"

/**
 * @brief - uzel pro Binarni Vyhledavaci Strom
 * dedi se z BaseNode
 */
struct BSTNode : public BaseNode {
  // nepotrebuje zadne spocificke pole, protoze vzecho je definovane v BaseNode

  /**
   * @brief - konstructor pro uzel BST
   * @param w - slovo ulozene v uzlu
   */
  BSTNode(const std::string& w);
};

/**
 * @brief - implementace BST
 * dedi veskeroui analytickou strukturu u BinaryTreeBase
 */
class BST : public BinaryTreeBase<BSTNode> {
private:
 BSTNode* insertRecursive(BSTNode* node, const std::string& word);

public:
 /**
  * @brief - konstructor stromu
  */
 BST();

 // implementace vizualnich metod z BinaryTreeBAse
 /**
  * @brief - vlozi nove slovo do BST
  * BST vkladani - jetli je nemsi -> doleva / vetsi -> doprava
  * @param word - slovo k vlozeni
  */
 void insert(const std::string& word) override;

};
#endif //BST_H
