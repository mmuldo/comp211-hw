/* CO MP 211, Spring 2019, Wesleyan University
 * Homework 5 driver program
 *
 * This is a simple program that reads in N integers from the terminal (N can
 * be set below) and stores them in an array, then calls a search function on
 * that array and reports the return value.
 */

#include <stdio.h>

#include "hw5a.h"

const int N = 1;

int main() {

    int A[N];

    for (int i = 0; i < N; ++i) {
        printf("Enter A[%d]: ", i);
        scanf(" %d", &A[i]);
    }
    printf("unimodal_search_r(A, 0, %d) == %d\n", N-1, unimodal_search_r(A, 0, N-1));

    return 0;
}
