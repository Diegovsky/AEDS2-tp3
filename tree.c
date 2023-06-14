#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "tree.h"

#define alloc(ty) calloc(sizeof(ty), 1)

Tree* tree_new(void) {
    Tree* t = alloc(Tree);
    return t;
}

static Node* new_node(char* morse, char alpha) {
    Node* node = alloc(Node);
    // Segurança nunca é demais
    const size_t morse_max_size = sizeof(node->morse);
    strncpy(node->morse, morse, morse_max_size);
    node->morse[morse_max_size-1] = '\0';

    node->alpha = alpha;
    return node;
}

static void node_swap(Node** a, Node** b) {
    (*a)->left =  (*b)->left;
    (*a)->right = (*b)->right;
    (*b)->left = NULL;
    (*b)->right= NULL;
    Node* aux = *b;
    *b = *a;
    *a = aux;
}

static void node_insert(Node* t, Node* new, int8_t level) {
    Node** next;
    if(new->morse[level] == '.') {
        next = &t->left;
    } else {
        next = &t->right;
    }
    if(*next == NULL) {
        *next = new;
    } else {
        // If new node is smaller than current node,
        // swap with current node and continue insertion
        if(strlen((*next)->morse) > strlen(new->morse)) {
            node_swap(&new, next);
        }
        node_insert(*next, new, level+1);
    }
}

void tree_insert(Tree* t, char* code, char alpha) {
    node_insert(t, new_node(code, alpha), 0);
}

static void print_alpha(Node* n, int depth, int8_t lanes, bool last) {
    int spacing = 4;
    for(int i = 0; i < (depth-1)*spacing; i++) {
        if(i % spacing == 0 && (lanes>>(i/spacing))&1)
            printf("│");
        else
            putchar(' ');
    }
    if(!last) {
        printf("├");
    } else {
        printf("└");
    }
    for(int i = 0; i < spacing-1; i++) {
        printf("─");
    }
    printf("(%s): '%c' \n", n->morse, n->alpha);
}

static void print_node(Node* n, int depth, int8_t lanes, bool last) {
    if(n == NULL) return;
    // Root is special cased
    if(depth > 0)
        print_alpha(n, depth, lanes, last);
    else
        printf(".\n");
    depth += 1;
    print_node(n->left, depth, lanes, n->right == NULL);
    print_node(n->right, depth, lanes &~(1<<(depth-1)), true);
}

void tree_print(Tree* t) {
    print_node(t, 0, ~0, false);
}

static char node_get(Node* n, char* code, int l) {
    if(n == NULL || l >= 5) {
        return '\0';
    } 
    if (strcmp(code, n->morse) == 0){
        return n->alpha;
    }
    Node* next;
    if(code[l] == '.') {
        next = n->left;
    } else {
        next = n->right;
    }

    return node_get(next, code, l+1);
}

char tree_get(Tree* t, char* code) {
    return node_get(t, code, 0);
}

void tree_destroy(Tree* t) {
    if(t == NULL) return;
    tree_destroy(t->left);
    tree_destroy(t->right);
    free(t);
}
