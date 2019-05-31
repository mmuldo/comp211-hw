/* COMP 211, Spring 2019
 * Homework 9
 *
 * Linked lists and an editor buffer
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hw9.h"

struct menu_opt {
    char* desc;
    void (*act)(void);
};

struct buffer *buf = NULL;

void do_exit() {
    exit(0);
}

void do_make_empty() {
    buf = empty();
};

void do_insert() {
    char c;
    printf("Enter character: ");
    scanf(" %1c", &c);
    insert(buf, c);
}

void do_delete_left() {
    delete_left(buf);
};

void do_delete_right() {
    delete_right(buf);
};

void do_move_left() {
    move_left(buf);
};

void do_move_right() {
    move_right(buf);
};

void do_set() {
    int n;
    printf("Enter position: ");
    scanf("%d", &n);
    set(buf, n);
}

int main(int argc, char **argv) {

    struct menu_opt menu[] = {
        {"Exit", do_exit},
        {"Create empty buffer", do_make_empty},
        {"Insert character", do_insert},
        {"Delete left", do_delete_left},
        {"Delete right", do_delete_right},
        {"Move insert mark left", do_move_left},
        {"Move insert mark right", do_move_right},
        {"Set insert mark position", do_set}
    };

    // WARNING:  this method for computing the size of an array only works when
    // the array is declared on the stack.  In particular, it is not valid when
    // the array is allocated using malloc, calloc, etc.
    int n_menu = sizeof(menu)/sizeof(struct menu_opt);

    int choice;
    struct buffer_contents *cnt;

    while (true) {
        for (int i=0; i<n_menu; ++i) {
            printf("(%d) %s\n", i, menu[i].desc);
        }
        printf("Enter choice: ");
        scanf("%u", &choice);
        menu[choice].act();

        printf("Buffer contents:\n");
        cnt = contents(buf);
        printf("%s|%s\n", cnt->left, cnt->right);
    }

    return 0;
}
