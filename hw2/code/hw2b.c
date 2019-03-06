/* Matt Muldowney
 * Homework 2 Part B due 2/12
 *
 * Outputs Caesar shift of user input character
 */

#include <stdio.h>
#define ALPHABET 26

int main(void) {
	unsigned char letter, cipher;
	int shift;

	printf("Enter lower-case letter to encrypt: ");
	scanf(" %c", &letter); // Reads user input letter

	// check if lower-case letter
	if (letter > 'z' || letter < 'a') {
		printf("Error: user did not enter lower-case letter, exiting\n");
		return 1;
	}

	printf("Enter the shift amount for Caesar cipher: ");
	scanf(" %d", &shift);

	cipher = letter + shift;
	// check if shift is positive
	if (shift > 0) {
		while (cipher > 'z') {
			cipher -= ALPHABET;
		}
	} else {
		while (cipher < 'a') {
			cipher += ALPHABET;
		}
	}
	
	printf("Ciphertext is %c\n", cipher);

	return 0;
}
