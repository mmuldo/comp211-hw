/* COMP 211, Fall 2017, Wesleyan University
 * Homework #6
 *
 * Sorting.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "comp211.h"
#include "hw6.h"

#define N_PALINDROMES 10
#define MAX_LEN 1024

void test_is_palindrome() {
    fprintf(stderr, "*****\nPalindrome tests\n*****\n");
    char palindromes[N_PALINDROMES][MAX_LEN] = {
        "",
        "a",
        "c",
        "aa",
        "aaa",
        "aba",
        "abba",
        "abcba",
        "abccba",
        "racecar",
    };
    for (int i=0; i<N_PALINDROMES; ++i) {
        dotestmsg(is_palindrome(palindromes[i]),
                "is_palindrome(%s)", palindromes[i]);
    }
}

void test_is_not_palindrome() {
    fprintf(stderr, "*****\nNot palindrome tests\n*****\n");
    char ws[N_PALINDROMES][MAX_LEN] = {
        "ab",
        "aab",
        "aaba",
        "aabb",
        "aabbcdbbaa",
        "abcdefcba",
        ""
    };
    for (int i=0; i<N_PALINDROMES && strcmp(ws[i], ""); ++i) {
        dotestmsg(!is_palindrome(ws[i]), "!is_palindrome(%s)", ws[i]);
    }
}

char rand_char() {
    return 65 + rand()%26;
}

void test_palindrome_rnd() {
    fprintf(stderr, "*****\nPalindrome (random) tests\n*****\n");

    // Creata a palindrome by randomly choosing a base length n, then
    // choosing at random whether the word has length 2n or 2n+1, then
    // filling the characters at random.
    for (int i=0; i<10; ++i) {
        // n = number of mirrored letters.
        int n = 7 + rand()%7;

        // Word has odd length if is_odd == 1.
        bool is_odd = rand()%2;

        // Length of the string.
        int len = 2*n + is_odd;

        // The string itself.
        char s[len+1];

        // Fill the first half of the string at random, then fill the second
        // half to make it a palindrome.
        for (int j=0; j<n; ++j) s[j] = rand_char();
        if (is_odd) s[n] = rand_char();
        for (int j=0; j<n; ++j) s[n+is_odd+j] = s[n-j-1];
        s[len] = '\0';

        dotestmsg(is_palindrome(s), "is_palindrome(%s)", s);
    }
}

void test_is_not_palindrome_rnd() {
    fprintf(stderr, "*****\nNot palindrome (random) tests\n*****\n");

    // Creata a non-palindrome by randomly choosing a base length n, then
    // choosing at random whether the word has length 2n or 2n+1, then
    // filling the characters at random, then making sure one pair of
    // symmetric characters is different.
    for (int i=0; i<10; ++i) {
        // n = number of mirrored letters.
        int n = 7 + rand()%7;

        // Word has odd length if is_odd == 1.
        bool is_odd = rand()%2;

        // Length of the string.
        int len = 2*n + is_odd;

        // The string itself.
        char s[len+1];

        // Fill the first half of the string at random, then fill the second
        // half to make it a palindrome.
        for (int j=0; j<n; ++j) s[j] = rand_char();
        if (is_odd) s[n] = rand_char();
        for (int j=0; j<n; ++j) s[n+is_odd+j] = s[n-j-1];
        s[len] = '\0';

        // Choose an index in the first half at random and make sure the
        // corresponding characters are different.
        int k = rand()%n;
        s[n+is_odd+k] = 65 + (s[n-k-1] - 65 + 1)%65;

        dotestmsg(!is_palindrome(s), "!is_palindrome(%s)", s);
    }
}

bool array_eq(int A[], int m, int B[], int n) {

    if (m != n) return false;

    for (int i = 0; i < n; i++) {
        if (A[i] != B[i]) {
            return false;
        }
    }
    return true;
}

#define MAX_ARRAY_STR_LEN 4096
char _array_str[MAX_ARRAY_STR_LEN];

/*  array_to_string(A, n) fills _array_str with a string representation of of
 *  A.
 *
 *  Pre-condition:  A has size n and the string representation requires at
 *  most MAX_ARRAY_STR_LEN characters (including the terminating NULL character).
 */
char* array_to_string(int A[], int n) {
    if (n == 0) {
        snprintf(_array_str, MAX_ARRAY_STR_LEN, "[]");
    } else if (n == 1) {
        snprintf(_array_str, MAX_ARRAY_STR_LEN, "[%d]", A[0]);
    } else {
        _array_str[0] = '[';
        int p = 1;
        int q = 0;
        for (int i=0; i<n-1; ++i) {
            snprintf(&_array_str[p], MAX_ARRAY_STR_LEN-p, "%d, %n", A[i], &q);
            p += q;
        }
        snprintf(&_array_str[p], MAX_ARRAY_STR_LEN-p, "%d]", A[n-1]);
    }
    return _array_str;
}

void sel_sort(int A[], int n) {
    for (int i=0; i<n-1; ++i) {
        int min_idx = i;
        for (int j=i+1; j<n; ++j) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        int x = A[min_idx];
        A[min_idx] = A[i];
        A[i] = x;
    }
}

void test_insertion_sort() {
    fprintf(stderr, "****\nInsertion sort tests (small)\n*****\n");
    {
        int A[] = {};
        int B[] = {};
        int C[] = {};
        insertion_sort(B, 0);
        dotestmsg(array_eq(B, 0, C, 0),
                "insertion_sort(%s)", array_to_string(A, 0));
    }
    {
        int A[] = {0};
        int B[] = {0};
        int C[] = {0};
        insertion_sort(B, 1);
        dotestmsg(array_eq(B, 1, C, 1),
                "insertion_sort(%s)", array_to_string(A, 1));
    }
    {
        int A[] = {0, 1};
        int B[] = {0, 1};
        int C[] = {0, 1};
        insertion_sort(B, 2);
        dotestmsg(array_eq(B, 2, C, 2),
                "insertion_sort(%s)", array_to_string(A, 2));
    }
    {
        int A[] = {1, 0};
        int B[] = {1, 0};
        int C[] = {0, 1};
        insertion_sort(B, 2);
        dotestmsg(array_eq(B, 2, C, 2),
                "insertion_sort(%s)", array_to_string(A, 2));
    }
    {
        int A[] = {0, 0};
        int B[] = {0, 0};
        int C[] = {0, 0};
        insertion_sort(B, 2);
        dotestmsg(array_eq(B, 2, C, 2),
                "insertion_sort(%s)", array_to_string(A, 2));
    }
    {
        int A[] = {0, 1, 2};
        int B[] = {0, 1, 2};
        int C[] = {0, 1, 2};
        insertion_sort(B, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "insertion_sort(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {2, 1, 0};
        int B[] = {2, 1, 0};
        int C[] = {0, 1, 2};
        insertion_sort(B, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "insertion_sort(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {0, 1, 0};
        int B[] = {0, 1, 0};
        int C[] = {0, 0, 1};
        insertion_sort(B, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "insertion_sort(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {1, 1, 0};
        int B[] = {1, 1, 0};
        int C[] = {0, 1, 1};
        insertion_sort(B, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "insertion_sort(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        int B[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        int C[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        insertion_sort(B, 8);
        dotestmsg(array_eq(B, 8, C, 8),
                "insertion_sort(%s)", array_to_string(A, 8));
    }
    {
        int A[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        int B[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        int C[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        insertion_sort(B, 8);
        dotestmsg(array_eq(B, 8, C, 8),
                "insertion_sort(%s)", array_to_string(A, 8));
    }
}

#define N_TESTS 15
#define ARRAY_MIN_SIZE 7
#define ARRAY_MAX_SIZE 17

void test_insertion_sort_rnd_no_dups() {
    fprintf(stderr, "****\nInsertion sort tests (no dups, random)\n*****\n");

    for (int nt=0; nt<N_TESTS; ++nt) {
        int n = 7 + rand()%(ARRAY_MAX_SIZE-ARRAY_MIN_SIZE+1);
        int A[n];
        int B[n];
        int C[n];

        for (int i=0; i<n; ++i) {

            bool try_again = false;
            do {
                try_again = false;
                int val = rand()%100;
                for (int j=0; j<i; ++j) {
                    if (A[j] == val) {
                        try_again = true;
                        break;
                    }
                }
                A[i] = val;
            } while (try_again);
            C[i] = B[i] = A[i];
        }

        insertion_sort(B, n);
        sel_sort(C, n);

        dotestmsg(array_eq(B, n, C, n),
                "insertion_sort(%s)", array_to_string(A, n));
    }
}

void test_insertion_sort_rnd_dups() {
    fprintf(stderr, "****\nInsertion sort tests (dups, random)\n*****\n");

    for (int nt=0; nt<N_TESTS; ++nt) {
        int n = 7 + rand()%(ARRAY_MAX_SIZE-ARRAY_MIN_SIZE+1);
        int A[n];
        int B[n];
        int C[n];

        for (int i=0; i<n; ++i)
            A[i] = B[i] = C[i] = rand()%((ARRAY_MAX_SIZE-ARRAY_MIN_SIZE)/3);

        insertion_sort(B, n);
        sel_sort(C, n);

        dotestmsg(array_eq(B, n, C, n),
                "insertion_sort(%s)", array_to_string(A, n));

    }
}


void test_merge_sort3() {
    fprintf(stderr, "****\nMerge sort tests (small)\n*****\n");
    {
        int A[] = {};
        int B[] = {};
        int C[] = {};
        merge_sort3(B, 0, 0);
        dotestmsg(array_eq(B, 0, C, 0),
                "merge_sort3(%s)", array_to_string(A, 0));
    }
    {
        int A[] = {0};
        int B[] = {0};
        int C[] = {0};
        merge_sort3(B, 0, 1);
        dotestmsg(array_eq(B, 1, C, 1),
                "merge_sort3(%s)", array_to_string(A, 1));
    }
    {
        int A[] = {0, 1};
        int B[] = {0, 1};
        int C[] = {0, 1};
        merge_sort3(B, 0, 2);
        dotestmsg(array_eq(B, 2, C, 2),
                "merge_sort3(%s)", array_to_string(A, 2));
    }
    {
        int A[] = {1, 0};
        int B[] = {1, 0};
        int C[] = {0, 1};
        merge_sort3(B, 0, 2);
        dotestmsg(array_eq(B, 2, C, 2),
                "merge_sort3(%s)", array_to_string(A, 2));
    }
    {
        int A[] = {0, 0};
        int B[] = {0, 0};
        int C[] = {0, 0};
        merge_sort3(B, 0, 2);
        dotestmsg(array_eq(B, 2, C, 2),
                "merge_sort3(%s)", array_to_string(A, 2));
    }
    {
        int A[] = {0, 1, 2};
        int B[] = {0, 1, 2};
        int C[] = {0, 1, 2};
        merge_sort3(B, 0, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "merge_sort3(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {2, 1, 0};
        int B[] = {2, 1, 0};
        int C[] = {0, 1, 2};
        merge_sort3(B, 0, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "merge_sort3(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {0, 1, 0};
        int B[] = {0, 1, 0};
        int C[] = {0, 0, 1};
        merge_sort3(B, 0, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "merge_sort3(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {1, 1, 0};
        int B[] = {1, 1, 0};
        int C[] = {0, 1, 1};
        merge_sort3(B, 0, 3);
        dotestmsg(array_eq(B, 3, C, 3),
                "merge_sort3(%s)", array_to_string(A, 3));
    }
    {
        int A[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        int B[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        int C[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        merge_sort3(B, 0, 8);
        dotestmsg(array_eq(B, 8, C, 8),
                "merge_sort3(%s)", array_to_string(A, 8));
    }
    {
        int A[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        int B[] = {-1, -2, -3, -4, -5, -6, -7, -8};
        int C[] = {-8, -7, -6, -5, -4, -3, -2, -1};
        merge_sort3(B, 0, 8);
        dotestmsg(array_eq(B, 8, C, 8),
                "merge_sort3(%s)", array_to_string(A, 8));
    }
}

void test_merge_sort3_rnd_no_dups() {
    fprintf(stderr, "****\nMerge sort tests (no dups, random)\n*****\n");

    for (int nt=0; nt<N_TESTS; ++nt) {
        int n = 7 + rand()%(ARRAY_MAX_SIZE-ARRAY_MIN_SIZE+1);
        int A[n];
        int B[n];
        int C[n];

        for (int i=0; i<n; ++i) {

            bool try_again = false;
            do {
                try_again = false;
                int val = rand()%100;
                for (int j=0; j<i; ++j) {
                    if (A[j] == val) {
                        try_again = true;
                        break;
                    }
                }
                A[i] = val;
            } while (try_again);
            C[i] = B[i] = A[i];
        }

        merge_sort3(B, 0, n);
        sel_sort(C, n);

        dotestmsg(array_eq(B, n, C, n),
                "merge_sort3(%s)", array_to_string(A, n));
    }
}

void test_merge_sort3_rnd_dups() {
    fprintf(stderr, "****\nMerge sort tests (dups, random)\n*****\n");

    for (int nt=0; nt<N_TESTS; ++nt) {
        int n = 7 + rand()%(ARRAY_MAX_SIZE-ARRAY_MIN_SIZE+1);
        int A[n];
        int B[n];
        int C[n];

        for (int i=0; i<n; ++i)
            A[i] = B[i] = C[i] = rand()%((ARRAY_MAX_SIZE-ARRAY_MIN_SIZE)/3);

        merge_sort3(B, 0, n);
        sel_sort(C, n);

        dotestmsg(array_eq(B, n, C, n),
                "merge_sort3(%s)", array_to_string(A, n));

    }
}

int main() {

    test_is_palindrome();
    test_is_not_palindrome();
    test_palindrome_rnd();
    test_is_not_palindrome_rnd();

    test_merge_sort3();
    test_merge_sort3_rnd_no_dups();
    test_merge_sort3_rnd_dups();

    test_insertion_sort();
    test_insertion_sort_rnd_no_dups();
    test_insertion_sort_rnd_dups();


    return 0;
}
