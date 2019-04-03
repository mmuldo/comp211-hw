/* COMP 211 Midterm Programming Project: palindromes and bubble sort
 * Spring 2019
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hw6.h"

static int MAX_STR_LEN = 256;

int main() {

    // Palindrome code check

    char palindrome[MAX_STR_LEN];

    printf("Please enter a string: ");
    fgets(palindrome, MAX_STR_LEN, stdin);
    palindrome[strlen(palindrome) - 1] = '\0';

    if (is_palindrome(palindrome)) {
        printf("%s is a palindrome\n", palindrome);
    }
    else {
        printf("%s is not a palindrome\n", palindrome);
    }

    // Merge and insertion sort code check

    //int A[] = {14, 23, 3, 5, 7, 13, 1, 5, 2};
    //int n = 9;

    //int A[] = {56, 2, 135, 14, -3, 23, -75, 3, 5, 7, 13, 1, 5, 2};
    //int n = 14;

    int A[] = {23, 7, 8, 26, 0, -4, 46, 4, 33, 13, 1, 0, 3535, -3, 7};
    int n = 15;

    int i;

    insertion_sort(A, n);
    //merge_sort3(A, 0, n);


    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0 ;
}
