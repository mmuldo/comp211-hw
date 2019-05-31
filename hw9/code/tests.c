/* COMP 211, Spring 2019
 * Homework 9
 *
 * Linked lists and an editor buffer
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "comp211.h"

#include "hw9.h"

struct string_int {
    char* s;
    int n;
};

struct string_int* rand_string_int(int n) {
    struct string_int* si = malloc(sizeof(struct string_int));

    si->s = calloc(n+1, sizeof(char));
    for (int i=0; i<n; ++i) si->s[i] = (char)(65 + (rand()%26));

    si->n = rand()%(n+1);

    return si;
}

struct buffer *_from_string(char* s) {
    struct buffer* b = empty();
    for (char* c = s; *c != '\0'; ++c) insert(b, *c);
    return b;

}

bool test_insert(char* s, char* left, char* right) {
    struct buffer* b = _from_string(s);
    struct buffer_contents* c = contents(b);
    return strncmp(c->left, left, strlen(left)) == 0 &&
        strncmp(c->right, right, strlen(right)) == 0;
}

bool test_setpos(char* s, int pos, char* left, char* right) {
    struct buffer* b = _from_string(s);
    set(b, pos);
    struct buffer_contents* c = contents(b);
    return strncmp(c->left, left, strlen(left)) == 0 &&
        strncmp(c->right, right, strlen(right)) == 0;

}

int main() {
    struct string_int* si;

    dotest(test_insert("", "", ""));
    dotest(test_insert("A", "A", ""));
    dotest(test_insert("AB", "AB", ""));

    si = rand_string_int(15);
    dotestmsg(test_insert(si->s, si->s, ""), "s = %s", si->s);

    dotest(test_setpos("", 0, "", ""));
    dotest(test_setpos("A", 0, "", "A"));
    dotest(test_setpos("A", 1, "A", ""));
    dotest(test_setpos("AB", 0, "", "AB"));
    dotest(test_setpos("AB", 1, "A", "B"));
    dotest(test_setpos("AB", 2, "AB", ""));

    return 0;

}
