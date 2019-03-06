/* Matt Muldowney
 * Homework 5 due 3/5
 *
 * Nim
 * There are three piles of sticks. Each turn a player may take as many sticks
 * as they wish from one pile, but must take at least one stick. The player who
 * takes the last stick loses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/* removes specified number of sticks from one of the piles
 */
int turn(int* piles, int pile, int sticks) {
	piles[pile] -= sticks;

	return 0;
}

/* returns true if there are sticks left;
 * 	   false otherwise
 */
bool sticks_remain(int* piles, int n) {
	int sum = 0;

	for (int i=0; i<n; i++) {
		sum += piles[i];
	}

	return (sum > 0) ? true : false;
}

/* prints number of sticks in each pile
 */
int display_piles(int* piles, int n) {
	for (int i=0; i<3; i++) {
		printf("Pile %d: %d sticks.\n", i, piles[i]);
	}

	return 0;
}

int main(void) {
	srand(time(NULL));
	const int N = 10; // max number of sticks in each pile

	int piles[3];
	int pile, sticks;
	bool player_loss = false;

	for (int i=0; i<3; i++) {
		piles[i] = rand() % N + 1;
	} /* put random number of sticks in each pile */

	while (sticks_remain(piles, 3)) {
		display_piles(piles, 3);

		printf("From which pile (0-2) do you want to remove sticks? ");
		scanf(" %d", &pile);
		while (pile < 0 || pile > 2 || piles[pile] == 0) {
			printf("You must choose a pile between 0 and 2 that still has sticks.\n");
			printf("From which pile (0-2) do you want to remove sticks? ");
			scanf(" %d", &pile);
		}/* loops while invalid input from user */

		printf("How many sticks (1-%d) do you want to remove? ", piles[pile]);
		scanf(" %d", &sticks);
		while (sticks < 1 || sticks > piles[pile]) {
			printf("You must choose a number between 1 and %d.\n", piles[pile]);
			printf("How many sticks (1-%d) do you want to remove? ", piles[pile]);
			scanf(" %d", &sticks);
		} /* loops while invalid input from user */

		turn(piles, pile, sticks); // player takes turn
		player_loss = !sticks_remain(piles, 3);

		if (!player_loss) {
			display_piles(piles, 3);
			
			do {
				pile = rand() % 3;
			} while (piles[pile] <=  0);
			sticks = rand() % piles[pile] + 1;

			printf("I choose to remove %d sticks from pile %d\n", sticks, pile);

			turn(piles, pile, sticks); //computer takes turn
		} /* if player hasn't lost */
	} /* loops while game isn't over i.e. while there are sticks left */

	player_loss ? printf("You lose!\n") : printf("Oh no! I lose!\n");

	return 0;
}
