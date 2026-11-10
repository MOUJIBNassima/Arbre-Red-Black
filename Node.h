#ifndef NODE_H
#define NODE_H

// Les deux couleurs possibles
enum Color {
    RED,
    BLACK
};

// Structure d'un noeud
struct Node {
    int data;
    Color color;

    Node* left;
    Node* right;
    Node* parent;

    // Constructeur
    Node(int value = 0) {
        data = value;
        color = RED;

        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

#endif
