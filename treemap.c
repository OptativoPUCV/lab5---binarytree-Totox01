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
  TreeMap *map = (TreeMap *) malloc(sizeof(TreeMap));
  if (map == NULL){
    printf("Error al reservar memoria para el nuevo mapa");
    return NULL;
  }
  map->root = NULL;
  map->current = NULL;
  map->lower_than = lower_than;
  //new->lower_than = lower_than;
  return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  tree->current = tree->root;

  while(tree->current != NULL){
    if(is_equal(tree,tree->current->pair->key, key) == 1){
      return;
    } else if(tree->lower_than(tree->current->pair->key, key) == 0){
      tree->current = tree->current->left;
    } else{
      tree->current = tree->current->right;
    }
  }
  
  TreeNode *newNode = createTreeNode(key,value);
  if(tree->root == NULL){
    tree->root = newNode;
  } else {
    TreeNode *parent = NULL;
    tree->current = tree->root;
    
    while (tree->current != NULL){
      parent = tree->current;
      if (tree->lower_than(tree->current->pair->key, key) == 0){
        tree->current = tree->current->left;
      } else {
        tree->current = tree->current->right;
      }
    }
    
    newNode->parent = parent;
    if (tree->lower_than(parent->pair->key, key) == 0){
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
  }
  tree->current = newNode;
}

TreeNode * minimum(TreeNode * x){
  while (x->left != NULL){
    x = x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
 if(node == NULL){
   return;
 }
  //caso 0 hijos
  if(node->left == NULL && node->right == NULL){
    if(tree->lower_than(node->pair->key, node->parent->pair->key) == 0){
    node->parent->right = NULL;
  } else {
    node->parent->left = NULL;
  }
    free(node);
    return;
  } else if(node->left == NULL || node->right == NULL){
    //caso 1 hijo
    TreeNode* hijo = node->left ? node->left : node->right;
    if (node->parent->left == node){
      node->parent->left = hijo;
    } else {
      node->parent->right = hijo;
    }
    hijo->parent = node->parent;
    free(node);
    return;
  } else {
    //caso 2 hijos
    TreeNode *min = minimum(node->right);
    node->pair->key = min->pair->key;
    node->pair->value = min->pair->value;
    removeNode(tree, min);
  }
  return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;
  
  while(tree->current != NULL){
    if(is_equal(tree,tree->current->pair->key,key) == 1){
      return tree->current->pair;
    }else if(tree->lower_than(tree->current->pair->key,key) == 0){
      tree->current = tree->current->left;
    }else{
      tree->current = tree->current->right;
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
