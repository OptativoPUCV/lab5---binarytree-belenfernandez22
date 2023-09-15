#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *new = (TreeMap *) malloc(sizeof(TreeMap));
    if (new == NULL) {
        return NULL;  // no se pudo asignar memoria
    }

    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;

    return new;
}



void insertTreeMap(TreeMap* tree, void* key, void* value) {
    if (tree == NULL) {
        return;  // El árbol está vacío
    }

    // Buscar la clave en el árbol
    Pair* pair = searchTreeMap(tree, key);
    if (pair != NULL) {
        return;  // La clave ya existe en el árbol
    }

    // Crear un nuevo nodo
    TreeNode* newNode = createTreeNode(key, value);
    if (newNode == NULL) {
        return;  // No se pudo asignar memoria para el nuevo nodo
    }

    // Insertar el nuevo nodo en el árbol
    TreeNode* aux = tree->root;
    TreeNode* parent = NULL;
    while (aux != NULL) {
        parent = aux;
        if (tree->lower_than(key, aux->pair->key)) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;

    // Hacer que current apunte al nuevo nodo
    tree->current = newNode;
}

TreeNode * minimum(TreeNode * x) {
    if (x->left == NULL) {
        return x;
    } else {
        return minimum(x->left);
    }
}
// Estructura de un nodo del árbol
typedef struct TreeNode {
    void* key;
    void* value;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

// Estructura del árbol
typedef struct TreeMap {
    TreeNode* root;
    // Otros campos del árbol
} TreeMap;

// Función para encontrar el nodo mínimo en un subárbol
TreeNode* minimum(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Función para eliminar un nodo del árbol
void removeNode(TreeMap* tree, TreeNode* node) {
    if (node == NULL) {
        return;
    }

    // Caso 1: Nodo sin hijos
    if (node->left == NULL && node->right == NULL) {
        if (node->parent == NULL) {
            // Este era el nodo raíz
            tree->root = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        free(node);
    }
    // Caso 2: Nodo con un hijo
    else if (node->left == NULL || node->right == NULL) {
        TreeNode* child = (node->left != NULL) ? node->left : node->right;
        if (node->parent == NULL) {
            // Este era el nodo raíz
            tree->root = child;
            child->parent = NULL;
        } else {
            if (node == node->parent->left) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
            child->parent = node->parent;
        }
        free(node);
    }
    // Caso 3: Nodo con dos hijos
    else {
        TreeNode* successor = minimum(node->right);
        // Copia los datos del sucesor al nodo que se va a eliminar
        node->key = successor->key;
        node->value = successor->value;
        // Luego, elimina el sucesor (que tiene uno o ningún hijo, debido al caso 1 o 2)
        removeNode(tree, successor);
    }
  {{{}}}



      


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}



Pair* searchTreeMap(TreeMap* tree, void* key) {
    TreeNode* aux = tree->root;

    while (aux != NULL) {
        if (is_equal(tree, key, aux->pair->key)) {
            tree->current = aux;
            return aux->pair;
        } else if (tree->lower_than(key, aux->pair->key)) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    return NULL;
}



Pair* upperBound(TreeMap* tree, void* key) {
    TreeNode* node = tree->root;
    TreeNode* ub_node = NULL;

    while (node != NULL) {
        if (tree->lower_than(key, node->pair->key)) {
            ub_node = node;
            node = node->left;
        } else if (tree->lower_than(node->pair->key, key)) {
            node = node->right;
        } else {
            return node->pair;  // La clave es igual a la clave del nodo
        }
    }

    return (ub_node != NULL) ? ub_node->pair : NULL;
   }

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;  // El árbol está vacío
    }

    TreeNode* node = tree->root;
    while (node->left != NULL) {
        node = node->left;
    }

    tree->current = node;
    return node->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->current == NULL) {
        return NULL;  // El árbol está vacío o current es NULL
    }

    TreeNode* node = tree->current;
    if (node->right != NULL) {
        node = node->right;
        while (node->left != NULL) {
            node = node->left;
        }
    } else {
        while (node->parent != NULL && node == node->parent->right) {
            node = node->parent;
        }
        node = node->parent;
    }

    tree->current = node;
    return (node != NULL) ? node->pair : NULL;
}
