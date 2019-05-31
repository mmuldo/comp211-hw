/*
 * COMP 211, Spring 2019
 * Homework #8
 *
 * Driver code to work with queue data structure.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "hw8.h"

struct menu_opt {
    char* desc;
    void (*act)(void);
};


queue q;

void do_exit() { exit(0); }
void do_create() { q = create(); }
void do_dequeue() { dequeue(&q); }
void do_print() {  print(&q); }

void do_enqueue() {
    char c;
    printf("Enter character: ");
    scanf(" %1c", &c);
    enqueue(&q, c);
}

int main(int argc, char **argv) {

    struct menu_opt menu[] = {
        {"Exit", do_exit},
        {"Create queue", do_create},
        {"Enqueue character", do_enqueue},
        {"Dequeue character", do_dequeue},
        {"Print queue", do_print}
    };

    // WARNING:  this method for computing the size of an array only works when
    // the array is declared on the stack.  In particular, it is not valid when
    // the array is allocated using malloc, calloc, etc.
    int n_menu = sizeof(menu)/sizeof(struct menu_opt);
    int choice;

    while (true) {

        for (int i=0; i<n_menu; ++i) {
            printf("(%d) %s\n", i, menu[i].desc);
        }

        printf("Enter choice: ");
        scanf("%u", &choice);

        if (choice >= 0 && choice < n_menu) {
            menu[choice].act();
            printf("Queue contents:\n");
            do_print();
        }
    }
    return 0;
}
