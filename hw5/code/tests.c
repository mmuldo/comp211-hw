/* COMP 211, Spring 2019, Wesleyan University
 * Homework #5 testing program
 */

#include <stdbool.h>
#include <stdlib.h>

#include "comp211.h"
#include "hw5a.h"

#define MAX_LEN 4096
char _array_str[MAX_LEN];

/*  array_to_string(A, n) fills _array_str with a string representation of of
 *  A.
 *
 *  Pre-condition:  A has size n and the string representation requires at
 *  most MAX_LEN characters (including the terminating NULL character).
 */
char* array_to_string(int A[], int n) {
    if (n == 0) {
        snprintf(_array_str, MAX_LEN, "[]");
    } else if (n == 1) {
        snprintf(_array_str, MAX_LEN, "[%d]", A[0]);
    } else {
        _array_str[0] = '[';
        int p = 1;
        int q = 0;
        for (int i=0; i<n-1; ++i) {
            snprintf(&_array_str[p], MAX_LEN-p, "%d, %n", A[i], &q);
            p += q;
        }
        snprintf(&_array_str[p], MAX_LEN-p, "%d]", A[n-1]);
    }
    return _array_str;
}

void do_unimodal_search_test(int A[], int n, int exp) {
    dotestmsg(unimodal_search_r(A, 0, n-1) == exp,
            "unimodal_search_r(%s, %d)", array_to_string(A, n), exp);
}

const int UNI_N = 20;
const int UNI_N_ODD = 21;

void test_unimodal_search() {
    printf("****\nUnimodal search tests\n*****\n");
    // unimodal_search(A, UNI_N) should return i.

    {
        int A[] = {-1};
        do_unimodal_search_test(A, 1, 0);
    }
    {
        int A[] = {-1, 0};
        do_unimodal_search_test(A, 2, 1);
    }
    {
        int A[] = {0, -1};
        do_unimodal_search_test(A, 2, 0);
    }
    {
        int A[] = {-1, 0, -5};
        do_unimodal_search_test(A, 3, 1);
    }
    {
        int A[] = {1, 2, 3};
        do_unimodal_search_test(A, 3, 2);
    }
    {
        int A[] = {3, 2, -1};
        do_unimodal_search_test(A, 3, 0);
    }
    {
        int A[] = {0, 5, 10, -1};
        do_unimodal_search_test(A, 4, 2);
    }
    {
        int A[] = {5, 10, -1, -5};
        do_unimodal_search_test(A, 4, 1);
    }
    {
        int A[] = {10, -1, -15, -20};
        do_unimodal_search_test(A, 4, 0);
    }
    {
        int A[] = {-10, -1, 5, 20};
        do_unimodal_search_test(A, 4, 3);
    }
    {
        int A[UNI_N];
        for (int i=0; i<UNI_N; ++i) {
            // Set A[0],...,A[i] to {...,-2, -1, 0}
            for (int j=i; j>=0; --j) {
                A[j] = j-i;
            }
            // Set A[i+1],...,A[n-1] to {-1, -2, -3,...}
            for (int j=i+1; j<UNI_N; ++j) {
                A[j] = i-j;
            }
            do_unimodal_search_test(A, UNI_N, i);
        }
    }
    /*
    {
        int A[UNI_N];
        for (int i=0; i<UNI_N; ++i) {
            for (int j=i; j>=0; --j) {
                if (j == 0) {
                    A[j] = -100;
                } else {
                    A[j] = A[j-1] + rand() % 10 + 21;
                }
            }
            for (int j=i+1; j<UNI_N; ++j) {
                A[j] = A[j-1] - rand()%10 - 21;
            }
            do_unimodal_search_test(A, UNI_N, i);
        }
    }*/
    {
        int A[UNI_N_ODD];
        for (int i=0; i<UNI_N_ODD; ++i) {
            // Set A[0],...,A[i] to {...,-2, -1, 0}
            for (int j=i; j>=0; --j) {
                A[j] = j-i;
            }
            // Set A[i+1],...,A[n-1] to {-1, -2, -3,...}
            for (int j=i+1; j<UNI_N_ODD; ++j) {
                A[j] = i-j;
            }
            do_unimodal_search_test(A, UNI_N_ODD, i);
        }
    }
    {
        int A[UNI_N_ODD];
        for (int i=0; i<UNI_N_ODD; ++i) {
            // Set A[0],...,A[i] to {...,-2, -1, 0}
            for (int j=i; j>=0; --j) {
                A[j] = j*10-i*10;
            }
            // Set A[i+1],...,A[n-1] to {-1, -2, -3,...}
            for (int j=i+1; j<UNI_N_ODD; ++j) {
                A[j] = i*10-j*10;
            }
            do_unimodal_search_test(A, UNI_N_ODD, i);
        }
    }
}

int main() {

    test_unimodal_search();

    return 0;
}
