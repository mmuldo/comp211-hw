/* COMP 211, Spring 2019, Wesleyan University
 * Homework #4 testing program
 */

#include <stdbool.h>
#include <stdlib.h>

#include "comp211.h"
#include "hw4.h"

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

void do_bin_search_test(int A[], int n, int x, int exp) {
    dotestmsg(bin_search(A, n, x) == exp,
            "bin_search(%s, %d, %d)", array_to_string(A, n), n, x);
    return;
}

void do_unimodal_search_test(int A[], int n, int exp) {
    dotestmsg(unimodal_search(A, n) == exp,
            "unimodal_search(%s, %d)", array_to_string(A, n), exp);
    return;
}

int lin_search(int A[], int n, int x) {
    for (int i=0; i<n; ++i) {
        if (A[i] == x) {
            return i;
        }
    }
    return -1;
}

void test_range(int A[], int n, int q) {
    printf("\n");
    for (int i=0; i<q; ++i) {
        do_bin_search_test(A, n, i, lin_search(A, n, i));
    }
    printf("\n");
}

void sel_sort(int A[], int n) {
    int min_idx;
    int x;
    for (int i = 0; i < n - 1; ++i) {
        min_idx = i;
        for (int j = i + 1; j<n; ++j) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        x = A[min_idx];
        A[min_idx] = A[i];
        A[i] = x;
    }
}

void test_bin_search() {
    printf("*****\nBinary search tests\n*****\n");

    printf("*** Base cases\n");
    {
        int A[] = {};
        test_range(A, 0, 1);
    }
    {
        int A[] = {1};
        test_range(A, 1, 3);
    }
    {
        int A[] = {1, 3};
        test_range(A, 2, 5);
    }
    {
        int A[] = {1, 1};
        test_range(A, 2, 3);
    }

    {
        int A[] = {1, 1, 3};
        test_range(A, 3, 5);
    }

    {
        int A[] = {1, 3, 3};
        test_range(A, 3, 5);
    }

    {
        int A[] = {1, 1, 3, 5};
        test_range(A, 4, 7);
    }

    {
        int A[] = {1, 1, 3, 3};
        test_range(A, 4, 5);
    }

    {
        int A[] = {1, 3, 3, 3};
        test_range(A, 4, 5);
    }

    {
        int A[] = {1, 3, 5, 5};
        test_range(A, 4, 7);
    }

    {
        int A[] = {1, 3, 3, 5};
        test_range(A, 4, 7);
    }

    {
        int A[] = {1, 1, 1, 1};
        test_range(A, 4, 2);
    }


    /*  Perform a bunch of randomly-generated tests.  Randomly generate
     *  num_tests arrays with sizes between min_size and max_size, inclusive.
     *  Then fill the arrays with the numbers 1, 3, 5 at random.  Sort the
     *  arrays and then test bin_search on keB 0, 1,...,6.
     */
    {
        int num_tests = 20;
        int min_size = 5;
        int max_size = 16;
        int size_range = max_size-min_size;

        for (int i=0; i<num_tests; ++i) {
            int size = min_size + rand()%size_range;
            int A[size];
            for (int j=0; j<size; ++j) A[j] = 2*(rand()%3) + 1;
            sel_sort(A, size);
            test_range(A, size, 7);
        }
    }


       int A[] = {1, 2, 3, 4, 5};

       dotest(bin_search(A, 5, 1) == 0);
       dotest(bin_search(A, 5, 2) == 1);
       dotest(bin_search(A, 5, 3) == 2);
       dotest(bin_search(A, 5, 4) == 3);
       dotest(bin_search(A, 5, 5) == 4);
       dotest(bin_search(A, 5, 6) == -1);

       int B[10] = {1, 3, 3, 3, 5, 5, 7, 7, 7, 9};

       dotest(bin_search(B, 10, 0) == -1);
       dotest(bin_search(B, 10, 1) == 0);
       dotest(bin_search(B, 10, 2) == -1);
       dotest(bin_search(B, 10, 3) == 1);
       dotest(bin_search(B, 10, 4) == -1);
       dotest(bin_search(B, 10, 5) == 4);
       dotest(bin_search(B, 10, 6) == -1);
       dotest(bin_search(B, 10, 7) == 6);
       dotest(bin_search(B, 10, 8) == -1);
       dotest(bin_search(B, 10, 9) == 9);
       dotest(bin_search(B, 10, 12) == -1);
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
        printf("check these tests\n");

        int A[UNI_N];
        for (int i=0; i<UNI_N; ++i) {
            for (int j=i; j>=0; --j) {
                if (j == 0) {
                    A[j] = -100;
                } else {
                    A[j] = A[j-1] + rand() % 10 + 51;
                }
            }
            for (int j=i+1; j<UNI_N; ++j) {
                A[j] = A[j-1] - rand()%10 - 51;
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

    return;
}

const int n_A = 7;
const int n_B = 10;

bool array_eq(int A[], int B[], int n) {
    for (int i=0; i<n; ++i) {
        if (A[i] != B[i]) return false;
    }
    return true;
}

void test_merge() {
    printf("*****\nMerge tests\n*****\n");

    // We put these tests in blocks so that we can repeatedly declare
    // arrays with the same names (because execution of a block statement
    // adds a binding table onto the stack, which is popped when the
    // block finishes).

    {
        // A, B disjoint but overlapping.
        int evens[] = {0, 2, 4, 6, 8, 10, 12};
        int odds[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        int evensodds[] =
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 17, 19};
        int C[n_A+n_B];

        merge(evens, n_A, odds, n_B, C);
        dotest(array_eq(C, evensodds, n_A+n_B));

        merge(odds, n_B, evens, n_A, C);
        dotest(array_eq(C, evensodds, n_A+n_B));
    }

    {
        int A[] = {0, 2, 4, 6, 8, 10, 12};
        int B[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
        int exp[] = {0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 16, 18};
        int C[n_A+n_B];

        merge(A, n_A, B, n_B, C);
        dotest(array_eq(C, exp, n_A+n_B));

        merge(B, n_B, A, n_A, C);
        dotest(array_eq(C, exp, n_A+n_B));
    }

    return;
}

int main() {

    test_bin_search();
    test_unimodal_search();
    test_merge();

    return 0;
}
