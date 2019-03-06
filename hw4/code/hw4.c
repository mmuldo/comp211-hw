/* COMP 211, Spring 2019, Wesleyan University
 * Homework #4, Problems 2-4
 *
 * Arrays and searching.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "hw4.h"

/* bin_search(A, n, x) =
 *   i,   where A[i] == x and A[j] != x for j<i, if there is such an i
 *        such that 0 <= i < n.
 *   -1,  if there is no such i.
 *
 * Pre-conditions:  A[0] <= ... <= A[n-1] and size of A is n.
 */
int bin_search(int A[], int n, int x) {
	int l = 0; //lowest index
	int h = n-1; //highest index
	int m; //middle index
	int i = -1; //result

	while (l <= h) {
		m = (l + h) / 2;

		if (A[m] == x) {
			i = m;
			h = m - 1; //continue searching lower indices
		} else if (A[m] < x) {
			l = m + 1;
		} else {
			h = m - 1;
		}
	}

	return i;
}
/* unimodal_search(A, n) = j, where A[j] = max{A[0],...,A[n-1]}.
 *
 * Pre-conditions:
 * - A has size n.
 * - There is j such that
 *     A[0] < A[1] < ... < A[j-1] < A[j] > A[j+1] > ... A[n-1].
 *   It is possible that j=0 or j=n-1.
 */
int unimodal_search(int A[], int n) {
	int l = 0; //lowest index
	int h = n-1; //highest index
	int a, b; //a is 1/3 mark; b is 2/3 mark

	while (l < h) {
		a = (h - l + 1) / 3 + l;
		b = (h - l + 1) * 2 / 3 + l;

		if (A[a] > A[a+1] && (a == 0 || A[a] > A[a-1])) { //case 1: a is mode
			return a;
		} else if (A[b] > A[b-1] && (b == n-1 || A[b] > A[b+1])) { //case 2: b is mode
			return b;
		} else if (A[a-1] > A[a] && A[a] > A[a+1]) { //case 3: mode is in bottom 3rd
			h = a - 1;
		} else if (A[b-1] < A[b] && A[b] < A[b+1]) { //case 4: mode is in top 3rd
			l = b + 1;
		} else { //case 5: mode is in middle 3rd
			l = a + 1;
			h = b - 1;
		}
	}

	return l;
}

/* After calling merge(A, m, B, n, C):
 * - C contains all the elements of A and B;
 * - C[0] <= ... <= C[m + n -1]
 *
 * Pre-conditions:
 * - A has size m and A[0] <= ... <= A[m-1].
 * - B has size n and B[0] <= ... <= B[n-1].
 * - C has size m + n.
 */
void merge(int A[], int m, int B[], int n, int C[]) {
	int i = 0; //A index
	int j = 0; //B index

	while ((i < m) && (j < n) && (i+j < m+n)) {
		if (A[i] <= B[j]) { //if ith element of A is less than jth element of B, add A[i] to C and increment i
			C[i+j] = A[i];
			i++;
		} else { //otherwise, add B[j] to C and increment j
			C[i+j] = B[j];
			j++;
		}
	}

	if (i >= m) { //if all elements of A are in C, add remaining elements of B
		while (j < n) {
			C[i+j] = B[j];
			j++;
		}
	} else if (j >= n) { //if all elements of B are in C, add remaining elements of A
		while (i < m) {
			C[i+j] = A[i];
			i++;
		}
	}
}
