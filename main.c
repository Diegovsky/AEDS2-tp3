#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void fill_morse(Tree* t) {
    tree_insert(t, ".-", 'a');
    tree_insert(t, "-...", 'b');
    tree_insert(t, "-.-.", 'c');
    tree_insert(t, "-..", 'd');
    tree_insert(t, ".", 'e');
    tree_insert(t, "..-.", 'f');
    tree_insert(t, "--.", 'g');
    tree_insert(t, "....", 'h');
    tree_insert(t, "..", 'i');
    tree_insert(t, ".---", 'j');
    tree_insert(t, "-.-", 'k');
    tree_insert(t, ".-..", 'l');
    tree_insert(t, "--", 'm');
    tree_insert(t, "-.", 'n');
    tree_insert(t, "---", 'o');
    tree_insert(t, ".--.", 'p');
    tree_insert(t, "--.-", 'q');
    tree_insert(t, ".-.", 'r');
    tree_insert(t, "...", 's');
    tree_insert(t, "-", 't');
    tree_insert(t, "..-", 'u');
    tree_insert(t, "...-", 'v');
    tree_insert(t, ".--", 'w');
    tree_insert(t, "-..-", 'x');
    tree_insert(t, "-.--", 'y');
    tree_insert(t, "--..", 'z');
    tree_insert(t, "-----", '0');
    tree_insert(t, ".----", '1');
    tree_insert(t, "..---", '2');
    tree_insert(t, "...--", '3');
    tree_insert(t, "....-", '4');
    tree_insert(t, ".....", '5');
    tree_insert(t, "-....", '6');
    tree_insert(t, "--...", '7');
    tree_insert(t, "---..", '8');
    tree_insert(t, "----.", '9');
}

char** strsspc(const char* txt) {
    const char* cursor = txt;
    int count = 0;
    char* buf = malloc(strlen(txt)+1);
    char* cursor2 = buf;
    while(1) {
        // Skip multiple spaces
        while(cursor[0] == ' ') cursor++;
        int len = strcspn(cursor, " ");
        memcpy(cursor2, cursor, len);
        cursor2[len] = '\0';
        cursor += len;
        cursor2 += len+1;
        count++;
        if(cursor[0] == '\0') break;
        cursor++;
    }
    int blocklen = (cursor - txt)+1;
    buf = realloc(buf, blocklen + (count+1)*sizeof(char*));
    char** strs = (char**)(buf + blocklen);
    cursor2 = buf;
    strs[0] = cursor2;
    for(int i = 1; i < count; i++) {
        strs[i] = strs[i-1] + strlen(strs[i-1]) + 1;
    }
    strs[count] = NULL;
    return strs;
}

void freestrs(char** strs) {
    free(strs[0]);
}

void strim(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

int main(int argc, char **argv) {
    Tree* t = tree_new();
    fill_morse(t);
    // Insert morse code table
    tree_print(t);
    char code[200];
    fgets(code, 200, stdin);
    strim(code);
    char** strs = strsspc(code);
    for(int word = 0; strs[word] != NULL; word++) {
        char c;
        if (*strs[word] == '/') {
            c = ' ';
        } else {
            c = tree_get(t, strs[word]);
            if(c == 0) {
                c = '?';
            }
        }
        putchar(c);
    }
    putchar('\n');
    freestrs(strs);

    tree_destroy(t);
}
