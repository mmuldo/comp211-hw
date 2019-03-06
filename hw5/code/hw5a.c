/* COMP 211, Spring 2019, Wesleyan University
 * Homework #5, Problem 2
 *
 * Recursion.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "hw5a.h"

/* returns i such that A[i] is the mode of A. that is,
 * 	A[l] < A[l+1] < A[l+2] < ... < A[i] > ... > A[h-2] > A[h-1] > A[h]
 * note that h is the last index of the arrary, i.e. h = n-1 where n is 
 * size of the array.
 */
int unimodal_search_r(int A[], int l, int h) {
	int a = (h - l + 1) / 3 + l;
	int b = (h - l + 1) * 2 / 3 + l;

	//base case
	if (l == h) {
		return l;
	}

	if (A[a] > A[a+1] && (a == l || A[a] > A[a-1])) { //case 1: a is mode
		return a;
	} else if (A[b] > A[b-1] && (b == h || A[b] > A[b+1])) { //case 2: b is mode
		return b;
	} else if (A[a-1] > A[a] && A[a] > A[a+1]) { //case 3: mode is in bottom 3rd
		return unimodal_search_r(A, l, a-1);
	} else if (A[b-1] < A[b] && A[b] < A[b+1]) { //case 4: mode is in top 3rd
		return unimodal_search_r(A, b+1, h);
	} else { //case 5: mode is in middle 3rd
		return unimodal_search_r(A, a+1, b-1);
	}
}
