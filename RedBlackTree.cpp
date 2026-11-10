#include "RedBlackTree.h"

// ================================================
// 1. INITIALISATION
// ================================================

void RedBlackTree::initializeNULLNode() {

    TNULL = new Node();

    TNULL->color = BLACK;

    TNULL->left = TNULL;
    TNULL->right = TNULL;
    TNULL->parent = TNULL;

    root = TNULL;
}

RedBlackTree::RedBlackTree() {
    initializeNULLNode();
}

RedBlackTree::~RedBlackTree() {
    destroyTree(root);
    delete TNULL;
}

// ================================================
// 2. ROTATION GAUCHE
// ================================================

void RedBlackTree::leftRotate(Node* x) {

    Node* y = x->right;

    x->right = y->left;

    if (y->left != TNULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == TNULL)
        root = y;

    else if (x == x->parent->left)
        x->parent->left = y;

    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// ================================================
// 3. ROTATION DROITE
// ================================================

void RedBlackTree::rightRotate(Node* x) {

    Node* y = x->left;

    x->left = y->right;

    if (y->right != TNULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == TNULL)
        root = y;

    else if (x == x->parent->right)
        x->parent->right = y;

    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

// ================================================
// 4. CORRECTION APRES INSERTION
// ================================================

void RedBlackTree::insertFix(Node* k) {

    Node* u;

    while (k->parent->color == RED) {

        if (k->parent == k->parent->parent->right) {

            u = k->parent->parent->left;

            // Cas 1 : oncle rouge
            if (u->color == RED) {

                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;

                k = k->parent->parent;
            }

            else {

                // Cas 2 : triangle
                if (k == k->parent->left) {

                    k = k->parent;
                    rightRotate(k);
                }

                // Cas 3 : ligne
                k->parent->color = BLACK;
                k->parent->parent->color = RED;

                leftRotate(k->parent->parent);
            }
        }

        else {

            u = k->parent->parent->right;

            // Cas 1 : oncle rouge
            if (u->color == RED) {

                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;

                k = k->parent->parent;
            }

            else {

                // Cas 2 : triangle
                if (k == k->parent->right) {

                    k = k->parent;
                    leftRotate(k);
                }

                // Cas 3 : ligne
                k->parent->color = BLACK;
                k->parent->parent->color = RED;

                rightRotate(k->parent->parent);
            }
        }

        if (k == root)
            break;
    }

    root->color = BLACK;
}

// ================================================
// 5. RECHERCHE INTERNE
// ================================================

Node* RedBlackTree::searchNode(Node* node, int key) const {

    if (node == TNULL || node->data == key)
        return node;

    if (key < node->data)
        return searchNode(node->left, key);

    return searchNode(node->right, key);
}

// ================================================
// 6. RECHERCHE PUBLIQUE
// ================================================

bool RedBlackTree::recherche(int key) const {

    return searchNode(root, key) != TNULL;
}

// ================================================
// 7. TROUVER LE MINIMUM
// ================================================

Node* RedBlackTree::minimum(Node* node) const {

    while (node->left != TNULL)
        node = node->left;

    return node;
}

// ================================================
// 8. REMPLACEMENT D'UN NOEUD
// ================================================

void RedBlackTree::transplant(Node* u, Node* v) {

    if (u->parent == TNULL)
        root = v;

    else if (u == u->parent->left)
        u->parent->left = v;

    else
        u->parent->right = v;

    v->parent = u->parent;
}

// ================================================
// 9. CORRECTION APRES SUPPRESSION
// ================================================

void RedBlackTree::deleteFix(Node* x) {

    Node* s;

    while (x != root && x->color == BLACK) {

        if (x == x->parent->left) {

            s = x->parent->right;

            if (s->color == RED) {

                s->color = BLACK;
                x->parent->color = RED;

                leftRotate(x->parent);

                s = x->parent->right;
            }

            if (s == TNULL) {
                x = x->parent;
                continue;
            }

            if (s->left->color == BLACK &&
                s->right->color == BLACK) {

                s->color = RED;
                x = x->parent;
            }

            else {

                if (s->right->color == BLACK) {

                    s->left->color = BLACK;
                    s->color = RED;

                    rightRotate(s);

                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;

                leftRotate(x->parent);

                x = root;
            }
        }

        else {

            s = x->parent->left;

            if (s->color == RED) {

                s->color = BLACK;
                x->parent->color = RED;

                rightRotate(x->parent);

                s = x->parent->left;
            }

            if (s == TNULL) {
                x = x->parent;
                continue;
            }

            if (s->right->color == BLACK &&
                s->left->color == BLACK) {

                s->color = RED;
                x = x->parent;
            }

            else {

                if (s->left->color == BLACK) {

                    s->right->color = BLACK;
                    s->color = RED;

                    leftRotate(s);

                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;

                rightRotate(x->parent);

                x = root;
            }
        }
    }

    x->color = BLACK;
}

// ================================================
// 10. INSERTION PUBLIQUE
// ================================================

void RedBlackTree::insertion(int key) {

    Node* node = new Node(key);

    node->parent = TNULL;
    node->left = TNULL;
    node->right = TNULL;

    Node* y = TNULL;
    Node* x = root;

    while (x != TNULL) {

        y = x;

        if (node->data < x->data)
            x = x->left;

        else if (node->data > x->data)
            x = x->right;

        else {

            // Eviter les doublons
            delete node;
            return;
        }
    }

    node->parent = y;

    if (y == TNULL)
        root = node;

    else if (node->data < y->data)
        y->left = node;

    else
        y->right = node;

    if (node->parent == TNULL) {

        node->color = BLACK;
        return;
    }

    if (node->parent->parent == TNULL)
        return;

    insertFix(node);
}

// ================================================
// 11. SUPPRESSION PUBLIQUE
// ================================================

bool RedBlackTree::suppression(int key) {

    Node* z = searchNode(root, key);

    if (z == TNULL)
        return false;

    Node* y = z;
    Node* x;

    Color originalColor = y->color;

    if (z->left == TNULL) {

        x = z->right;
        transplant(z, z->right);
    }

    else if (z->right == TNULL) {

        x = z->left;
        transplant(z, z->left);
    }

    else {

        y = minimum(z->right);

        originalColor = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;

        else {

            transplant(y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    delete z;

    if (originalColor == BLACK)
        deleteFix(x);

    return true;
}

// ================================================
// 12. LIBERATION DE LA MEMOIRE
// ================================================

void RedBlackTree::destroyTree(Node* node) {

    if (node == TNULL)
        return;

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}
