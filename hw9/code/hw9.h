/* COMP 211, Spring 2019
 * Homework 9
 * Matt Muldowney
 *
 * Linked lists and an editor buffer
 */

/* A doubly-linked node structure.
 */
typedef struct node {
	struct node* next;
	struct node* prev;
	char val;
} node;

/* A structure used to represent an index in a linked-list
 */
typedef struct index {
	node *n; //node to the right of index
	int pos; //position of index in linked-list
} index;

/* Your buffer structure ought to include at least two things:
 * (1) Some form of a linked list using your node structure;
 * (2) A pointer to of the of the nodes in your list to represent the current
 *     insertion point.
 */
typedef struct buffer {
	node* head;
	node* tail;
	index idx;
	int size;
} buffer;

/* A structure that is used to represent the buffer contents as two strings:
 * - left:  the string to the left of the insertion mark;
 * - right:  the string to the right of the insertion mark.
 *
 * You may not change the definition of this structure.
 */
struct buffer_contents {
    // The contents of the buffer to the left of the insert mark.
    char *left;

    // The contents of the buffer to the right of the insert mark.
    char *right;
};

/* empty = an empty buffer.
 */
struct buffer *empty(void);

/* insert(buf, c) inserts c to the left of the insertion point of buf.  After
 * the insertion, the insert mark is to the right of c.
 */
void insert(struct buffer *, char);

/* delete_left(buf) deletes the character to the left of the insert mark.  If
 * there is no character to the left of the insert mark, this function has no
 * effect.
 */
void delete_left(struct buffer *);

/* delete_right(buf) deletes the character to the right of the insert mark.  If
 * there is no character to the right of the insert mark, this function has no
 * effect.
 */
void delete_right(struct buffer *);

/* move_left(buf) moves the insert mark one character to the left.  If there is
 * no character to the left of the insert mark, this functdion has no effect.
 */
void move_left(struct buffer *);

/* move_right(buf) moves the insert mark one character to the right.  If there
 * is no character to the right of the insert mark, this functdion has no
 * effect.
 */
void move_right(struct buffer *);

/* set(buf, n) sets the insert mark so that it is to the left of the n-th
 * character.  Characters are 0-indexed, so set(buf, 0) sets the insert mark to
 * the beginning of the buffer.  n may be equal to the length of the buffer; in
 * this case, the insert mark is set to the right of the last character.
 *
 * Pre-condition:  0 <= n <= len(buf).
 */
void set(struct buffer *, int);

/* contents(buf) = c, where c->left is the string to the left of the insert
 * mark and c->right is the string to the right of the insert mark.
 */
struct buffer_contents *contents(struct buffer *);

