#pragma once
#include <stddef.h>

typedef struct node {
    char morse[6];
    char alpha;
    struct node* left;
    struct node* right;
} Node;

typedef Node Tree;

Tree* tree_new(void);
void tree_insert(Tree* t, char* morse, char alpha);
char tree_get(Tree* t, char* morse);
void tree_print(Tree* t);
void tree_destroy(Tree* t);
