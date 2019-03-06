/* COMP 211, Spring 2019, Wesleyan University
 * Homework #5, Problem 2
 *
 * Recursion.
 */

/* unimodal_search_r(A, a, b) = j, where A[j] = max{A[a],...,A[b]}.
 *
 * Pre-conditions:
 * - A has size n.
 * - There is j such that
 *     A[0] < A[1] < ... < A[j-1] < A[j] > A[j+1] > ... A[n-1].
 *   It is possible that j=0 or j=n-1.
 */
int unimodal_search_r(int[], int, int);
