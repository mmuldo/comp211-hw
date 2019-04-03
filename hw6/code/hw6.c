/* Matt Muldowney
 * COMP 211, Spring 2019, Wesleyan University
 * Homework #6
 *
 * Palindromes and sorting.
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "hw6.h"

/* palindrome_check(A, n) =
 *   true, where A[i] == A[n-1-i] for all i < (n-1-i)
 *   false otherwise
 *
 * Pre-conditions:
 */
bool is_palindrome(char A[])
{
	int n = strlen(A);

	for (int i=0; i < n-1-i; i++) {
		if (A[i] != A[n-1-i]) return false;
	}

	return true;
}

/*  Insertion sort
 *
 */
void insertion_sort(int A[], int n)
{
	int curr; //current element to be sorted
	int j; //index for checking previous elements
	
	for (int i=1; i<n; i++) {
		curr = A[i];
		j = i-1;
		//shift elements over until spot for curr is found
		while (j >= 0 && curr < A[j]) {
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = curr;
	}
}

/* min2
 * returns the minimum of a and b
 */
int min2(int a, int b) {
	return (a > b) ? b : a;
}

/* min3
 * returns the minimum of a, b, and c
 */
int min3(int a, int b, int c) {
	int x = min2(a,b);
	int y = min2(b,c);
	return (x > y) ? y : x;
}

/*  merge3: performs a 3-way merge
 *
 *  A is divided into 3 sub-arrays which are merged in sorted order
 *     -> lo:m1, m1:m2, m2:hi
 */
void merge3(int A[], int lo, int m1, int m2, int hi)
{
	int B[hi-lo]; //temporary array
	int i = lo; //index for first subarray
	int j = m1; //index for second subarray
	int k = m2; //index for third subarray
	int h = 0; //index for B
	int min;

	while (i < m1 && j < m2 && k < hi) {
		min = min3(A[i], A[j], A[k]);
		B[h++] = min;
		if (A[i] == min) {
			i++;
		} else if (A[j] == min) {
			j++;
		} else {
			k++;
		}
	}

	while (i < m1 && j < m2) {
		min = min2(A[i], A[j]);
		B[h++] = min;
		if (A[i] == min) {
			i++;
		} else {
			j++;
		}
	}

	while (j < m2 && k < hi) {
		min = min2(A[j], A[k]);
		B[h++] = min;
		if (A[j] == min) {
			j++;
		} else {
			k++;
		}
	}

	while (i < m1 && k < hi) {
		min = min2(A[i], A[k]);
		B[h++] = min;
		if (A[i] == min) {
			i++;
		} else {
			k++;
		}
	}

	while (i < m1) {
		B[h++] = A[i++];
	}

	while (j < m2) {
		B[h++] = A[j++];
	}

	while (k < hi) {
		B[h++] = A[k++];
	}

	for (int i=0; i<hi-lo; i++) {
		A[i+lo] = B[i];
	}
}

/*
 * Implements a recursive 3-way mergesort
 *   -> Divide array into thirds.
 *   -> Recursively sort each third.
 *   -> Merge thirds.
 */
void merge_sort3(int A[], int lo, int hi)
{
	//Base case
	if (hi - lo <= 1) {
		return;
	}

	//Divide array into thirds
	int m1 = (hi - lo) / 3 + lo;
	int m2 = (hi - lo) * 2 / 3 + lo;

	//Recursively sort each third
	merge_sort3(A, lo, m1);
	merge_sort3(A, m1, m2);
	merge_sort3(A, m2, hi);

	//Merge thirds
	merge3(A, lo, m1, m2, hi);
}

