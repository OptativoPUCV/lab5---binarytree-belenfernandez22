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
    //new->lower_than = lower_than;
    return NULL;
}
    new->lower_than = lower_than;
    new->root = NULL;
    new->current = NULL;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode* node = tree->root;
  TreeNode* parent = NULL;
   while (node != NULL) {
        parent = node;
        if (tree->lower_than(key, node->pair->key)) {
            node = node->left;
        } else if (tree->lower_than(node->pair->key, key)) {
            node = node->right;
        } else {
            return;
        }
    }

    TreeNode* newNode = createTreeNode(key, value);
    newNode->parent = parent;

    if (parent == NULL) {
        tree->root = newNode;
    } else if (tree->lower_than(key, parent->pair->key)) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    tree->current = newNode;
}


TreeNode * minimum(TreeNode * x) {
    if (x == NULL) {
        return NULL;  // El árbol está vacío
    }

    while (x->left != NULL) {
        x = x->left;
    }

    return x;


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


Pair* searchTreeMap(TreeMap* tree, void* key) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;  
    }

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



Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
