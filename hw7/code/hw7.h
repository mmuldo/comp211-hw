/* COMP 211, Spring 2019, Wesleyan University
 * Homework #7
 *
 * More arrays
 */


#define BUF_LEN 48

typedef struct buffer {
	char data[BUF_LEN];
	int index; //left of insertion point
	int end; //end of text
} buffer;

/*
 * DO NOT MODIFY ANY CODE BELOW THIS LINE.
 *
 */

/* empty = an empty buffer.
*/
buffer empty();

/* insert(buf, c) inserts c to the left of the insertion point of buf.  After
 * the insertion, the insert mark is to the right of c.
 */
void insert(buffer *, char);

/* delete_left(buf) deletes the character to the left of the insert mark.  If
 * there is no character to the left of the insert mark, this function has no
 * effect.
 */
void delete_left(buffer *);

/* delete_right(buf) deletes the character to the right of the insert mark.  If
 * there is no character to the right of the insert mark, this function has no
 * effect.
 */
void delete_right(buffer *);

/* move_left(buf) moves the insert mark one character to the left.  If there is
 * no character to the left of the insert mark, this functdion has no effect.
 */
void move_left(buffer *);

/* move_right(buf) moves the insert mark one character to the right.  If there
 * is no character to the right of the insert mark, this functdion has no
 * effect.
 */
void move_right(buffer *);

/* set(buf, n) sets the insert mark so that it is to the left of the n-th
 * character.  Characters are 0-indexed, so set(buf, 0) sets the insert mark to
 * the beginning of the buffer.  n may be equal to the length of the buffer; in
 * this case, the insert mark is set to the right of the last character.
 *
 * Pre-condition:  0 <= n <= len(buf).
 */
void set(buffer *, int);

/* contents(buf, left, right).
 *
 * Post-condition:  left and right are NULL-terminated strings corresponding to
 * the contents of buf to the left and right of the insert mark, respectively.
 *
 * Pre-conditions:  the sizes of left and right are at least one greater than
 * the contents of the buffer to the left and right of the insert mark,
 * respectively.
 */
void contents(buffer*, char[], char[]);

/*  print_buffer(buf).
 *
 *  Post-condition:  Some information about buf will be printed to ther
 *  terminal.
 *
 *  The implementation of this function is entirely up to you.  It is here to
 *  help you with debugging.  We will never use it, but there is an option in
 *  the driver program that will call this function with the current buffer.
 */
void print_buffer(buffer *);

bool buf_ok(buffer *);
