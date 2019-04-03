/* COMP 211, Spring 2019, Wesleyan University
 * Homework #6
 *
 * Palindromes and sorting.
 */

#include <stdbool.h>

/* is_palindrome(s) =
 *   true, if s is a palindrome (s[i] == s[n-1-i] for all 0 <= i < n-1-i,
 *         n = strlen(s))
 *   false, otherwise.
 */
bool is_palindrome(char[]);

/* Insertion sort
 */
void insertion_sort(int[], int);

/* Mergesort
 */
int min3(int, int, int);
void merge3(int[], int, int, int, int);
void merge_sort3(int[], int, int);
