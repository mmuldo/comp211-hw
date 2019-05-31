/* COMP 211, Spring 2019
 * Homework 9
 * Matt Muldowney
 *
 * Linked lists and an editor buffer
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "comp211.h"
#include "hw9.h"

/* Returns true if buffer is a valid buffer, false otherwise.
 * Invariants:
 *  (1) buffer is linear forwards and backwards
 *  (2) insertion point is within buffer
 *  (3) each node in buffer satisfies back-and-forth property
 */
bool buf_ok(buffer *b) {
	/* forward linearity check
	 */
	node *n1 = b->head->next; //slow pointer
	node *n2 = b->head->next; //fast pointer

	//traverse queue until one pointer reaches the end of the queue
	while (n1 != NULL && n2 != NULL && n2->next != NULL) {
		n1 = n1->next;
		n2 = n2->next->next;

		if (n1 == n2) {
			return false; //return false if pointers point to same node
		}
	}


	/* backward linearity check
	 */
	n1 = b->tail->prev;
	n2 = b->tail->prev;

	//traverse queue until one pointer reaches the end of the queue
	while (n1 != NULL && n2 != NULL && n2->prev != NULL) {
		n1 = n1->prev;
		n2 = n2->prev->prev;

		if (n1 == n2) {
			return false; //return false if pointers point to same node
		}
	}


	/* insertion point check
	 */
	if (b->idx.pos > b->size || b->idx.pos < 0) return false; // index position must be within bounds

	// index pointer must be in the buffer
	bool within_bounds = false;
	for (n1 = b->head->next; n1 != NULL; n1 = n1->next) {
		if (n1 == b->idx.n) within_bounds = true;
	}
	if (!within_bounds) return  false;

	// index pointer must be at supposed index position in buffer
	n1 = b->head->next;
	for (int i = 0; i < b->idx.pos; i++) {
		n1 = n1->next;
	}
	if (b->idx.n != n1) return false;


	/* back-and-forth check
	 */
	for (n1 = b->head->next; n1 != b->tail; n1 = n1->next) {
		if (n1->next == NULL || n1->prev == NULL) return false;
	}

	return true; //return true if all tests pass
}	


/* empty = an empty buffer.
*/
struct buffer *empty(void) {
	buffer *b = malloc(sizeof(buffer));

	node *n1 = malloc(sizeof(node)); //dummy head
	node *n2 = malloc(sizeof(node)); //dummy tail
	n1->val = '\0';
	n2->val = '\0';

	b->head = n1;
	n1->next = n2;
	n2->prev = n1;
	b->tail = n2;

	index idx;
	idx.n = n2;
	idx.pos = 0;
	b->idx = idx;

	b->size = 0;

	assert(buf_ok(b));
	return b;
}

/* insert(buf, c) inserts c to the left of the insertion point of buf.  After
 * the insertion, the insert mark is to the right of c.
 */
void insert(struct buffer *buf, char c) {
	node *new = malloc(sizeof(node));
	new->val = c;

	new->next = buf->idx.n;
	new->prev = buf->idx.n->prev;
	buf->idx.n->prev->next = new;
	buf->idx.n->prev = new;

	buf->idx.pos++;
	buf->size++;
	assert(buf_ok(buf));
}

/* delete_left(buf) deletes the character to the left of the insert mark.  If
 * there is no character to the left of the insert mark, this function has no
 * effect.
 */
void delete_left(struct buffer *buf) {
	if (buf->idx.pos == 0) return;

	node *del = buf->idx.n->prev;
	del->prev->next = del->next;
	del->next->prev = del->prev;
	free(del);

	buf->idx.pos--;
	buf->size--;
	assert(buf_ok(buf));
}

/* delete_right(buf) deletes the character to the right of the insert mark.  If
 * there is no character to the right of the insert mark, this function has no
 * effect.
 */
void delete_right(struct buffer *buf) {
	if (buf->idx.pos == buf->size) return;

	node *del = buf->idx.n;
	del->prev->next = del->next;
	del->next->prev = del->prev;
	buf->idx.n = del->next;
	free(del);

	buf->size--;
	assert(buf_ok(buf));
}

/* move_left(buf) moves the insert mark one character to the left.  If there is
 * no character to the left of the insert mark, this functdion has no effect.
 */
void move_left(struct buffer *buf) {
	set(buf, buf->idx.pos-1);
	assert(buf_ok(buf));
}

/* move_right(buf) moves the insert mark one character to the right.  If there
 * is no character to the right of the insert mark, this functdion has no
 * effect.
 */
void move_right(struct buffer *buf) {
	set(buf, buf->idx.pos+1);
	assert(buf_ok(buf));
}

/* set(buf, n) sets the insert mark so that it is to the left of the n-th
 * character.  Characters are 0-indexed, so set(buf, 0) sets the insert mark to
 * the beginning of the buffer.  n may be equal to the length of the buffer; in
 * this case, the insert mark is set to the right of the last character.
 *
 * Pre-condition:  0 <= n <= len(buf).
 */
void set(struct buffer *buf, int n) {
	//if user provides erroneous input
	if (n > buf->size) n = buf->size;
	else if (n < 0) n = 0;

	node *tmp = buf->idx.n;
	if (buf->idx.pos > n) {
		for (int i=0; i < buf->idx.pos - n; i++) {
			tmp = tmp->prev;
		}
	} else {
		for (int i=0; i < n - buf->idx.pos; i++) {
			tmp = tmp->next;
		}
	}

	buf->idx.n = tmp;
	buf->idx.pos = n;
	assert(buf_ok(buf));
}

/* contents(buf) = c, where c->left is the string to the left of the insert
 * mark and c->right is the string to the right of the insert mark.
 */
struct buffer_contents *contents(struct buffer *buf) {
	int l = buf->idx.pos + 1; //size of left contents
	int r = buf->size - buf->idx.pos + 1; //size of right contents
	node *tmp = buf->head->next;

	struct buffer_contents* cnt = calloc(1, sizeof(struct buffer_contents));
	cnt->left = calloc(l, sizeof(char));
	cnt->right = calloc(r, sizeof(char));

	for (int i=0; i<l-1; i++) {
		cnt->left[i] = tmp->val;
		tmp = tmp->next;
	}
	tmp = buf->idx.n;
	for (int i=0; i<r-1; i++) {
		cnt->right[i] = tmp->val;
		tmp = tmp->next;
	}

	//null terminate
	cnt->left[l-1] = '\0';
	cnt->right[r-1] = '\0';

	assert(buf_ok(buf));
	return cnt;
}
