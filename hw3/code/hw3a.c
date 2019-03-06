/* Matt Muldowney
 * Homework 3 Part A due 2/20
 *
 * Caesar shift a string
 */

#include <stdio.h>
#include <string.h>
#define ASCII 95
#define MAX_LENGTH 256

char cshift(unsigned char letter, int shift) {
	unsigned char cipher = letter + shift;

	if (shift > 0) {
		while (cipher > '~') {
			cipher -= ASCII;
		}
	} else {
		while (cipher < ' ') {
			cipher += ASCII;
		}
	}

	return cipher;
}

int main(void) {
	unsigned char plaintext[MAX_LENGTH];
	int shift;

	printf("Enter a string to encrypt: ");
	fgets(plaintext, MAX_LENGTH, stdin);
	printf("Enter the shift amount for Caesar cipher: ");
	scanf(" %d", &shift);

	printf("Ciphertext is ");
	for (int i=0; plaintext[i] != '\n'; i++) {
		printf("%c", cshift(plaintext[i], shift));
	}

	printf("\n");

	return 0;
}
