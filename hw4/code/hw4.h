/* COMP 211, Spring 2019, Wesleyan University
 * Homework #4, Problems 2-4
 *
 * Arrays and searching.
 */

/* bin_search(A, n, x) =
 *   i,   where A[i] == x and A[j] != x for j<i, if there is such an i
 *        such that 0 <= i < n.
 *   -1,  if there is no such i.
 *
 * Pre-conditions:  A[0] <= ... <= A[n-1] and size of A is n.
 */
int bin_search(int[], int, int);

/* unimodal_search(A, n) = j, where A[j] = max{A[0],...,A[n-1]}.
 *
 * Pre-conditions:
 * - A has size n.
 * - There is j such that
 *     A[0] < A[1] < ... < A[j-1] < A[j] > A[j+1] > ... A[n-1].
 *   It is possible that j=0 or j=n-1.
 */
int unimodal_search(int[], int);

/* After calling as merge(A, m, B, n, C):
 * - C contains all the elements of A and B;
 * - C[0] <= ... <= C[m+n-1]
 *
 * Pre-conditions:
 * - A has size m and A[0] <= ... <= A[m-1].
 * - B has size n and B[0] <= ... <= B[n-1].
 * - C has size m+n.
 */
void merge(int A[], int n_A, int B[], int n_B, int C[]);
