/* COMP 211, Spring 2019, Wesleyan University
 * Homework #7
 *
 * More arrays
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "hw7.h"

buffer empty()
{
	buffer b = {};
	b.index = b.end = 0;
	return b;
}

void insert(buffer* b, char c)
{
	//check if there is still room
	if (b->end >= BUF_LEN) {
		printf("No more room.\n");
		return;
	}

	//shift characters to the right to make room
	for (int i = b->end; i > b->index; i--) {
		b->data[i] = b->data[i-1];
	}

	//insert
	b->data[b->index++] = c;
	b->end++;
	assert(buf_ok(b));
}

void delete_left(buffer* b)
{
	//check if there is text to left
	if (b->index <= 0) return;

	//shift characters right of insertion point
	//one place to the left
	for (int i = b->index; i < b->end; i++) {
		b->data[i-1] = b->data[i];
	}

	b->index--;
	b->end--;
	assert(buf_ok(b));
}

void delete_right(buffer* b)
{
	//check if there is text to right
	if (b->index >= b->end) return;

	//shift characters right of insertion
	//point one place to left
	for (int i = b->index + 1; i < b->end; i++) {
		b->data[i-1] = b->data[i];
	}

	b->end--;
	assert(buf_ok(b));
}

void move_left(buffer* b)
{
	set(b, b->index-1);
	assert(buf_ok(b));
}

void move_right(buffer* b)
{
	set(b, b->index+1);
	assert(buf_ok(b));
}

void set(buffer* b, int n)
{
	if (n <= b->end && n >= 0) b->index = n;
	assert(buf_ok(b));
}

void contents(buffer* b, char left[], char right[])
{
	left[0] = '\0'; //in case index is 0
	right[0] = '\0'; //in case end is 0

	for (int i=0; i < b->index; i++) {
		left[i] = b->data[i];
	}
	left[b->index] = '\0'; //null terminate

	for (int i = b->index; i < b->end; i++) {
		right[i - b->index] = b->data[i];
	}
	right[b->end - b->index] = '\0'; //null terminate

	assert(buf_ok(b));
}

void print_buffer(buffer* b)
{
	//print data
	printf("data : { ");
	for (int i=0; i<b->end; i++) {
		printf("%c,", b->data[i]);
	}
	printf("\b }\n");

	//print insert point
	printf("index: %d\n", b->index);

	assert(buf_ok(b));
}

/* buf_ok(buf)
 * 
 * invariant for buffer
 *
 * conditions:
 * (1) insert point must be within end of text
 * (2) text cannot take more space than BUF_LEN
 */
bool buf_ok(buffer* b) {
	if (b->index > b->end || b->index < 0) return false;

	if (b->end > BUF_LEN || b->end < 0) return false;

	return true;
}
