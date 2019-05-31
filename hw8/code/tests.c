/* COMP 211, Spring 2019
 * Homework 8
 *
 * Queues
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "comp211.h"
#include "hw8.h"

/*  Make a non-linear collection of nodes.
 *
 *  Given the string s, first make a linear sequence of qnodes corresponding to
 *  the sequence s.  Then choose some 0 <= i <= j < strlen(s) and make the
 *  index-j node point to the index-i node.
 */

char* rand_string(int n) {
    char* s = malloc(n*sizeof(char) + 1);
    for (int i=0; i<n; ++i) {
        s[i] = 'a' + rand()%26;
    }
    s[n] = '\0';

    return s;
}

/*  from_string(s) is a linear sequence of nodes that represents the characters
 *  in s.
 */
qnode* from_string(char s[]) {
    qnode hd = {.key = '\0', .next = NULL};

    qnode* p = &hd;
    for (int i=0; i<strlen(s); ++i) {
        qnode* q = malloc(sizeof(qnode));
        q->key = s[i];
        q->next = NULL;
        p->next = q;
        p = p->next;
    }

    return hd.next;
}

qnode* make_circular(char s[], int i, int j) {
    qnode* q = from_string(s);

    qnode* back_node = q;
    for (int k=0; k<i; ++k) back_node = back_node->next;

    qnode* front_node = back_node;
    for (int k=i; k<j; ++k) front_node = front_node->next;

    front_node->next = back_node;

    return q;
}

void test_is_linear(char s[]) {
    qnode* q = from_string(s);
    dotestmsg(is_linear(q), "is_linear(%s)", s);
}

void test_not_linear(char s[], int i, int j) {
    qnode* q = make_circular(s, i, j);
    dotestmsg(!is_linear(q), "!is_linear(%s), %d -> %d", s, j, i);
}

/*  Test queue operations.
 *
 *  ops is a sequence of alphabetic characters and '-'.  An empty queue q is
 *  created, and then for each character c in ops:
 *
 *    - if c = '-', q is dequeued.
 *    - otherwise, c is enqueued.
 *
 *  The contents of q are then compared to exp.
 */
void test_queue(char ops[], char exp[]) {
    int n_ops = strlen(ops);
    queue q = create();
    for (int i=0; i<n_ops; ++i) {
        if (ops[i] == '-') dequeue(&q);
        else enqueue(&q, ops[i]);
    }

    int n = strlen(exp);
    char cs[n+1];
    as_array(&q, cs);

    fprintf(stderr, "\n");
    dotestmsg(is_empty(&q) == (n == 0), "is_empty(%s)", ops);
    dotestmsg(size(&q) == n, "size(%s) = %d", ops, n)
    dotestmsg(strncmp(cs, exp, n) == 0, "%s -> %s; got %s", ops, exp, cs);
    fprintf(stderr, "\n");
}

#define N_OPS 16
#define N_RAND_TESTS 10

int main() {
    {
        test_is_linear("");
        test_is_linear("a");
        test_is_linear("ab");

        for (int i=5; i<20; ++i) test_is_linear(rand_string(i));
        fprintf(stderr, "\n");
    }

    {
        test_not_linear("a", 0, 0);
        test_not_linear("ab", 0, 0);
        test_not_linear("ab", 0, 1);
        test_not_linear("ab", 1, 1);
        test_not_linear("abc", 0, 0);
        test_not_linear("abc", 0, 1);
        test_not_linear("abc", 1, 1);
        test_not_linear("abc", 0, 2);
        test_not_linear("abc", 1, 2);
        test_not_linear("abc", 2, 2);
    }

    {
        for (int i=0; i<N_RAND_TESTS; ++i) {
            int n = 5 + rand()%20;
            char* s = rand_string(n);
            int k = rand()%n;
            int j = rand()%(k+1);
            test_not_linear(s, j, k);
        }
        fprintf(stderr, "\n");
    }

    {
        test_queue("", "");

        test_queue("a", "a");
        test_queue("a-", "");

        test_queue("ab", "ab");
        test_queue("ab-", "b");
        test_queue("ab--", "");
        test_queue("a-b", "b");
        test_queue("a-b-", "");

        test_queue("abbc", "abbc");
        test_queue("abbc-", "bbc");
        test_queue("abbc--", "bc");
        test_queue("abbc---", "c");
        test_queue("abbc----", "");
        test_queue("ab-bc", "bbc");
        test_queue("a-b-bc", "bc");
        test_queue("ab--bc", "bc");

        /*  This loop performs N_RAND_TESTS tests.  Each test constructs an
         *  operation sequence of length N_OPS.  Each character of the
         *  operation sequence is either '-' (probability 50%) or an alphabetic
         *  character.  '-' is added to the operation sequence only if the
         *  queue represented by the sequence so far is non-empty.
         */
        for (int j=0; j<N_RAND_TESTS; ++j) {
            char ops[N_OPS + 1] = {'\0'};
            char exp[N_OPS + 1] = {'\0'};
            int size = 0;
            int front = 0;
            int back = 0;

            for (int i=0; i<N_OPS; ++i) {
                if (rand()%2 == 0 && size > 0) {
                    ops[i] = '-';
                    size = size - 1;
                    front = front + 1;
                } else {
                    ops[i] = 'a' + (rand()%26);
                    size = size + 1;
                    exp[back] = ops[i];
                    back = back + 1;

                }
            }

            for (int i=front; i<back; ++i) {
                exp[i-front] = exp[i];
            }
            exp[back-front] = '\0';

            test_queue(ops, exp);
        }

    }

    return 0;
}
