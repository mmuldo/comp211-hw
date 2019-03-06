/* COMP 211, Spring 2019, Wesleyan University
 * Homework 4 driver program
 *
 * This is a simple program that reads in N integers from the terminal (N can
 * be set below) and stores them in an array, then calls a search function on
 * that array and reports the return value.
 */

#include <stdio.h>

#include "hw4.h"

const int M = 7;
const int N = 4;

int main() {

    int A[20] = {-100, -71, -47, -19, 8, 28, 77, 78, 104, 128, 153, 190, 203, 244, 252, 288, 305, 279, 255, 231};
    int B[M];
    int C[M+N];
    int x;

    printf("%d", unimodal_search(A, 20));

    return 0;

    /*
     * Test binary search
     */
    printf("--------------------------------\n");
    printf("Testing binary search\n");
    for (int i = 0; i < N; ++i) {
        printf("Enter A[%d]: ", i);
        scanf(" %d", &A[i]);
    }
    printf("Enter x: ");
    scanf(" %d", &x);
    printf("bin_search(A, %d, %d) == %d\n", N, x, bin_search(A, N, x));

    /*
     * Test unimodal search
     */
    printf("--------------------------------\n");
    printf("Testing unimodal search\n");
    for (int i = 0; i < N; ++i) {
        printf("Enter A[%d]: ", i);
        scanf(" %d", &A[i]);
    }
    printf("unimodal_search(A, %d) == %d\n", N, unimodal_search(A, N));

    /*
     * Test merge
     */
    printf("--------------------------------\n");
    printf("Testing merge\n");
    for (int i = 0; i < N; ++i) {
        printf("Enter A[%d]: ", i);
        scanf(" %d", &A[i]);
    }
    for (int i = 0; i < M; ++i) {
        printf("Enter B[%d]: ", i);
        scanf(" %d", &B[i]);
    }
    merge(A, N, B, M, C);
    printf("C = [");
    for (int i=0; i<M+N; ++i) {
        printf("%d, ", C[i]);
    }
    printf("]\n");

    return 0;
}
