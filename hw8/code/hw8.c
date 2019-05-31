/* COMP 211, Spring 2019
 * Homework 8
 * Matt Muldowney
 *
 * Queues
 */

#include <assert.h>
#include <stdlib.h>

#include "comp211.h"
#include "hw8.h"

bool is_linear(qnode *hd) {
	if (hd == NULL) return true; //return true if nothing is queued

	qnode *n1 = hd; //slow pointer
	qnode *n2 = hd; //fast pointer

	//traverse queue until one pointer reaches the end of the queue
	while (n1 != NULL && n2 != NULL && n2->next != NULL) {
		n1 = n1->next;
		n2 = n2->next->next;

		if (n1 == n2) {
			return false; //return false if pointers point to same node
		}
	}

	return true; //return true if either pointer reaches end of queue
}

queue create() {
	queue q;
	q.front = NULL;
	q.back = NULL;
	q.size = 0;
	return q;
}

bool is_empty(queue *q) {
	return size(q) == 0;
}

void enqueue(queue *q, char c) {
	//create new node
	qnode *new = malloc(sizeof(qnode));
	new->key = c;

	//queue new node at the back
	if (is_empty(q)) {
		q->back = new;
		q->front = new;
	} else {
		q->back->next = new;
		q->back = new;
	}

	q->size++; //increment size

}

char dequeue(queue *q) {
	if (is_empty(q)) return -1;

	qnode *del = q->front; //create new pointer to element being dequeued
	
	char c = del->key;
	q->front = del->next; //point front to next in queue
	free(del);

	q->size--;

	return c;
}

void as_array(queue* q, char A[]) {
	qnode *tmp = q->front;

	//traverse array and queue analogously
	for (int i=0; i < q->size; i++) {
		A[i] = tmp->key;
		tmp = tmp->next;
	}
}

int size (queue *q) {
	return q->size;
}

void print(queue *q) {
	qnode *tmp = q->front;

	while (tmp != NULL) {
		printf("%c", tmp->key);
		//print commas between elements and nothing if it's the last element
		(tmp != q->back) ? printf(", ") : printf("\n");
		tmp = tmp->next;
	}
}
