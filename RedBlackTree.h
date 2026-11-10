#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Node.h"

class RedBlackTree {

private:

    Node* root;
    Node* TNULL;

    // Initialisation du noeud sentinelle
    void initializeNULLNode();

    // Rotations
    void leftRotate(Node* x);
    void rightRotate(Node* x);

    // Correction apres insertion
    void insertFix(Node* k);

    // Correction apres suppression
    void deleteFix(Node* x);

    // Recherche interne
    Node* searchNode(Node* node, int key) const;

    // Trouver le minimum
    Node* minimum(Node* node) const;

    // Remplacement d'un noeud
    void transplant(Node* u, Node* v);

    // Liberation de la memoire
    void destroyTree(Node* node);

public:

    // Constructeur et destructeur
    RedBlackTree();
    ~RedBlackTree();

    // Les trois operations principales
    void insertion(int key);

    bool recherche(int key) const;

    bool suppression(int key);
};

#endif
