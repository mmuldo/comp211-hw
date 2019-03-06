/* Matt Muldowney
 * Homework 2 Part A due 2/12
 *
 * Converts non-negative integers to binary.
 */

#include <stdio.h>

int main(void) {
	int decimal;

	printf("Enter non-negative decimal integer to convert: ");
	scanf(" %d", &decimal); // Reads user input.

	printf("Conversion to binary: ");

	// Compares current value of decimal to b (ie 2^(15-iteration)).
	// If decimal is less, 0 is printed.
	// Else, 1 is printed and b is subtrated from decimal.
	for (int b = 32768; b > 0; b /= 2) {
		if (decimal < b) {
			printf("%d", 0);
		} else {
			printf("%d", 1);
			decimal -= b;
		}
	}
	(decimal == 0) ? printf("\n") : printf("\nError occurred\n");

	return decimal; // Fails if input is not non-negative or causes overflow.
}
