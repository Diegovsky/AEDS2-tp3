#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
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

// Splits a string by spaces
char** strsplit(const char* txt, char* sep) {
    const char* cursor = txt;
    int count = 0;
    unsigned long blocklen = strlen(txt)+1;
    char* buf = malloc(blocklen);
    buf[0] = '\0';
    char* cursor2 = buf;
    while(cursor[0] != '\0') {
        // Skip multiple separators
        int len = strcspn(cursor, sep);
        if(len == 0) {
            cursor++;
            continue;
        }
        assert((unsigned long)(cursor2-buf + len) <= blocklen);
        memcpy(cursor2, cursor, len);
        cursor += len;
        cursor2[len] = '\0';
        cursor2 += len+1;
        count++;
    }
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

// Remove trailing \n
void strim(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

void convert_from_morse(Tree* t, const char* code) {
    char** strs = strsplit(code, " ");
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
}

void convert_from_ascii(Tree* t, const char* code) {
    for(int word = 0; code[word] != '\0'; word++) {
        char* c;
        if (code[word] == ' ') {
            c = "/";
        } else {
            c = tree_search_aplha(t, code[word]);
            if(c == NULL) {
                c = "?";
            }
        }
        printf("%s ", c);
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    Tree* t = tree_new();
    // Insert morse code table
    fill_morse(t);
    // tree_print(t);
    char* filename;
    if(argc == 1) {
        filename = "msg.txt";
    } else {
        filename = argv[1];
    }
    FILE* f = fopen(filename, "r");
    if(f == NULL) {
        fprintf(stderr, "Arquivo '%s' não encontrado!\n", filename);
        return 1;
    }
    char* buf = malloc(1024);
    int read = fread(buf, 1, 1024, f);
    buf[read] = '\0';
    char** lines = strsplit(buf, "\n");
    for(char** phrase = lines; *phrase != NULL; phrase++) {
#ifdef DECOD_MORSE
    convert_from_morse(t, *phrase);
#else
    convert_from_ascii(t, *phrase);
#endif
    }
    tree_destroy(t);
    fclose(f);
    freestrs(lines);
    free(buf);
}
