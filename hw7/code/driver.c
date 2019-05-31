/* COMP 211, Spring 2019, Wesleyan University
 * Homework #7
 *
 * More arrays
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hw7.h"

typedef struct menu_opt {
    char* desc;
    void (*act)(void);
} menu_opt;

buffer buf;
char cs[BUF_LEN];

void do_exit() { exit(0); }
void do_make_empty() { buf = empty(); };
void do_delete_left() { delete_left(&buf); };
void do_delete_right() { delete_right(&buf); };
void do_move_left() { move_left(&buf); };
void do_move_right() { move_right(&buf); };
void do_print() { print_buffer(&buf); }

void do_insert() {
    char c;
    printf("Enter character: ");
    scanf(" %1c", &c);
    insert(&buf, c);
}
void do_set() {
    int n;
    printf("Enter position: ");
    scanf("%d", &n);
    set(&buf, n);
}

int main(int argc, char **argv) {

    menu_opt menu[] = {
        {"Exit", do_exit},
        {"Create empty buffer", do_make_empty},
        {"Insert character", do_insert},
        {"Delete left", do_delete_left},
        {"Delete right", do_delete_right},
        {"Move insert mark left", do_move_left},
        {"Move insert mark right", do_move_right},
        {"Set insert mark position", do_set},
        {"Print buffer", do_print}
    };

    // WARNING:  this method for computing the size of an array only works when
    // the array is declared on the stack.  In particular, it is not valid when
    // the array is allocated using malloc, calloc, etc.
    int n_menu = sizeof(menu)/sizeof(menu_opt);

    while (true) {

        for (int i=0; i<n_menu; ++i) {
            printf("(%d) %s\n", i, menu[i].desc);
        }

        int choice;
        printf("Enter choice: ");
        scanf("%u", &choice);
        menu[choice].act();

        printf("Buffer contents:\n");
        char left[BUF_LEN], right[BUF_LEN];
        contents(&buf, left, right);
        printf("%s|%s\n", left, right);
    }

    return 0;
}
