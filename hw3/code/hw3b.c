/* Matt Muldowney
 * Homework 3 Part B due 2/20
 * 
 * Decrypts Caesar shifted string of characters.
 */ 


#include <stdio.h>
#include <string.h>
#define ASCII 95
#define MAX_LENGTH 256

char decrypt(unsigned char cipher, int shift) {
	char letter = cipher - shift;

	if (shift > 0) {
		while (letter < ' ') {
			letter += ASCII;
		}
	} else {
		while (letter > '~') {
			letter -= ASCII;
		}
	}

	return letter;
}

int main(void) {
	unsigned char ciphertext[MAX_LENGTH];

	printf("Enter a string to decrypt: ");
	fgets(ciphertext, MAX_LENGTH, stdin);

	for (int i=0; i < ASCII; i++) {
		printf("Possible plaintext is ");
		for (int j=0; ciphertext[j] != '\n'; j++) {
			printf("%c", decrypt(ciphertext[j], i));
		}

		printf(" using shift of %d\n", i);
	}

	return 0;
}

