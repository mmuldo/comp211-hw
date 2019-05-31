typedef struct queue {
	int data[MAX_LEN];
	int end;
}

void enqueue(queue* q, int val) {
	int loc;
	for (int i = q->end-1; q->data[i] >= val; i--) {
		q->data[i+1] = q->data[i];
		loc = i;
	}

	q->data[loc] = val;
	q->end++;
}

int dequeue(queue* q) {
	return q->data[q->(--end)];
}
