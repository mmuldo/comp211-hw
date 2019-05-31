/* COMP 211, Spring 2019, Wesleyan University
 * Homework #7
 *
 * More arrays
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "comp211.h"
#include "hw7.h"

#define max(a, b) ((a) <= (b) ? (b) : (a))
#define min(a, b) ((a) <= (b) ? (a) : (b))

typedef struct string_int {
    char s[BUF_LEN];
    int n;
} string_int;

string_int rand_string_int(int n) {
    string_int si;

    for (int i=0; i<n; ++i) {
        si.s[i] = (char)('A' + (rand()%26));
    }
    si.s[n] = '\0';

    si.n = rand()%(n+1);

    return si;
}

void split_range(char src[], int m, int n, char left[], char right[]) {
    int j;
    for (j=0; j<m; ++j) left[j] = src[j];
    left[m] = '\0';
    for (j=n; src[j] != '\0'; ++j) right[j-n] = src[j];
    right[j-n] = '\0';
}

void split(char src[], int n, char left[], char right[]) {
    split_range(src, n, n, left, right);
}

static void shift_right(char s[], int i) {
    for (int j=strlen(s); j>i; --j) {
        s[j] = s[j-1];
    }
}

static void shift_left(char s[], int i) {
    for (int j=i; j<strlen(s); ++j) {
        s[j] = s[j+1];
    }
    // s[strlen(s)-1] = '\0';
}

struct buffer _from_string(char s[]) {
    struct buffer b = empty();
    for (int i = 0; s[i] != '\0'; ++i) insert(&b, s[i]);
    return b;
}

bool test_insert(char s[]) {
    struct buffer b = _from_string(s);
    char exp_left[BUF_LEN], exp_right[BUF_LEN];
    char act_left[BUF_LEN], act_right[BUF_LEN];

    split_range(s, strlen(s), strlen(s), exp_left, exp_right);
    contents(&b, act_left, act_right);

    return strncmp(act_left, exp_left, strlen(exp_left)) == 0 &&
        strncmp(act_right, exp_right, strlen(exp_right)) == 0;
}

bool test_setpos(char s[], int pos) {
    struct buffer b = _from_string(s);
    set(&b, pos);

    char exp_left[BUF_LEN], exp_right[BUF_LEN];
    char act_left[BUF_LEN], act_right[BUF_LEN];

    split_range(s, pos, pos, exp_left, exp_right);
    contents(&b, act_left, act_right);

    return strncmp(act_left, exp_left, strlen(exp_left)) == 0 &&
        strncmp(act_right, exp_right, strlen(exp_right)) == 0;

}

bool test_ins_set_delleft(char s[], int n) {
    struct buffer b = _from_string(s);
    set(&b, n);
    delete_left(&b);

    char exp_left[BUF_LEN], exp_right[BUF_LEN];
    char act_left[BUF_LEN], act_right[BUF_LEN];

    split_range(s, max(n-1, 0), n, exp_left, exp_right);
    contents(&b, act_left, act_right);

    return strncmp(act_left, exp_left, strlen(exp_left)) == 0 &&
        strncmp(act_right, exp_right, strlen(exp_right)) == 0;
}

bool test_ins_set_delright(char s[], int n) {
    struct buffer b = _from_string(s);
    set(&b, n);
    delete_right(&b);

    char exp_left[BUF_LEN], exp_right[BUF_LEN];
    char act_left[BUF_LEN], act_right[BUF_LEN];

    split_range(s, n, min(n+1, strlen(s)), exp_left, exp_right);
    contents(&b, act_left, act_right);

    return strncmp(act_left, exp_left, strlen(exp_left)) == 0 &&
        strncmp(act_right, exp_right, strlen(exp_right)) == 0;
}

void test_rep_insmove(double ins_prob) {
    struct buffer b = empty();

    int max_ops = 2*ins_prob/(1-ins_prob) + 1;
    max_ops += 2;
    dprintf("test_rep_insmove: max_ops = %d\n", max_ops);
    int n_ops = 20 + rand()%20;

    int cursor = 0;

    char exp[BUF_LEN] = {'\0'};
    char ops_str[n_ops+1];
    for (int i=0; i<n_ops+1; ++i) ops_str[i] = '\0';

    int n_added = 0;

    for (int i=0; i<n_ops; ++i) {
        assert(strlen(exp) < BUF_LEN);
        assert(0 <= cursor);
        assert(cursor <= strlen(exp));

        int op = rand()%max_ops;
        dprintf("op = %d\n", op);
        sprintf(&ops_str[i], "%1d", op);
        if (op == 0) {
            move_left(&b);
            cursor = max(cursor - 1, 0);
        }
        else if (op == 1) {
            move_right(&b);
            cursor = min(cursor + 1, strlen(exp));
        }
        else if (op < max_ops) {
            char c = 'A' + n_added%26;
            insert(&b, c);
            shift_right(exp, cursor);
            exp[cursor] = c;
            cursor += 1;
            n_added += 1;
        }
        else {
            assert(false);
        }
        dprintf("exp = %s; cursor = %d\n", exp, cursor);
    }

    char exp_left[BUF_LEN], exp_right[BUF_LEN];
    char act_left[BUF_LEN], act_right[BUF_LEN];

    split(exp, cursor, exp_left, exp_right);
    contents(&b, act_left, act_right);

    dotestmsg(strncmp(act_left, exp_left, strlen(exp_left)) == 0 &&
            strncmp(act_right, exp_right, strlen(exp_right)) == 0,
            "rep_insmove(%s)", ops_str);

}

void test_rep_insmove0() {
    test_rep_insmove(.70);
}

void test_rep_insmove1() {
    test_rep_insmove(1.0/3);
}

void test_rep_all(double ins_prob) {
    struct buffer b = empty();

    int max_ops = 4*ins_prob/(1-ins_prob) + 1;
    max_ops += 4;
    dprintf("test_rep_insmove: max_ops = %d\n", max_ops);
    int n_ops = 20 + rand()%20;

    int cursor = 0;

    char exp[BUF_LEN] = {'\0'};
    char ops_str[n_ops+1];
    for (int i=0; i<n_ops+1; ++i) ops_str[i] = '\0';

    int n_added = 0;

    for (int i=0; i<n_ops; ++i) {
        assert(strlen(exp) < BUF_LEN);
        assert(0 <= cursor);
        assert(cursor <= strlen(exp));

        int op = rand()%max_ops;
        dprintf("op = %d\n", op);
        sprintf(&ops_str[i], "%1d", op);
        if (op == 0) {
            move_left(&b);
            cursor = max(cursor - 1, 0);
        }
        else if (op == 1) {
            move_right(&b);
            cursor = min(cursor + 1, strlen(exp));
        }
        else if (op == 2) {
            delete_left(&b);
            if (cursor > 0) {
                shift_left(exp, cursor - 1);
                cursor -= 1;
            }
        }
        else if (op == 3) {
            delete_right(&b);
            if (cursor < strlen(exp)) {
                shift_left(exp, cursor);
            }
        }
        else if (op < max_ops) {
            char c = 'A' + n_added%26;
            insert(&b, c);
            shift_right(exp, cursor);
            exp[cursor] = c;
            cursor += 1;
            n_added += 1;
        }
        else {
            assert(false);
        }
        dprintf("exp = %s; cursor = %d\n", exp, cursor);
    }

    char exp_left[BUF_LEN], exp_right[BUF_LEN];
    char act_left[BUF_LEN], act_right[BUF_LEN];

    split(exp, cursor, exp_left, exp_right);
    contents(&b, act_left, act_right);

    dotestmsg(strncmp(act_left, exp_left, strlen(exp_left)) == 0 &&
            strncmp(act_right, exp_right, strlen(exp_right)) == 0,
            "rep_all(%s)", ops_str);

}

int main() {

    srand(2);

    {
        printf("\ninsert.\n\n");

        dotest(test_insert(""));
        dotest(test_insert("A"));
        dotest(test_insert("AB"));
        dotest(test_insert("ABC"));

        printf("\n");

        for (int i=0; i<5; ++i) {
            string_int si = rand_string_int(15);
            dotestmsg(test_insert(si.s), "test_insert(%s)", si.s);
        }
    }

    {
        printf("\ninsert; set position.\n\n");
        dotest(test_setpos("", 0));
        dotest(test_setpos("A", 0));
        dotest(test_setpos("A", 1));
        dotest(test_setpos("AB", 0));
        dotest(test_setpos("AB", 1));
        dotest(test_setpos("AB", 2));
        dotest(test_setpos("ABC", 0));
        dotest(test_setpos("ABC", 1));
        dotest(test_setpos("ABC", 2));
        dotest(test_setpos("ABC", 3));

        printf("\n");

        for (int i=0; i<10; ++i) {
            string_int si = rand_string_int(10);
            dotestmsg(test_setpos(si.s, si.n),
                    "test_setpos(%s, %d)", si.s, si.n);
        }
    }

    {
        printf("\ninsert; set position; delete left.\n\n");

        dotest(test_ins_set_delleft("", 0));
        dotest(test_ins_set_delleft("A", 0));
        dotest(test_ins_set_delleft("A", 1));
        dotest(test_ins_set_delleft("AB", 0));
        dotest(test_ins_set_delleft("AB", 1));
        dotest(test_ins_set_delleft("AB", 2));
        dotest(test_ins_set_delleft("ABC", 0));
        dotest(test_ins_set_delleft("ABC", 1));
        dotest(test_ins_set_delleft("ABC", 2));
        dotest(test_ins_set_delleft("ABC", 3));

        printf("\n");

        for (int i=0; i<10; ++i) {
            string_int si = rand_string_int(10);
            dotestmsg(test_ins_set_delleft(si.s, si.n),
                    "ins_set_delleft(%s, %d)", si.s, si.n);
        }
    }

    {
        printf("\ninsert; set position; delete right.\n\n");

        dotest(test_ins_set_delright("", 0));
        dotest(test_ins_set_delright("A", 0));
        dotest(test_ins_set_delright("A", 1));
        dotest(test_ins_set_delright("AB", 0));
        dotest(test_ins_set_delright("AB", 1));
        dotest(test_ins_set_delright("AB", 2));
        dotest(test_ins_set_delright("ABC", 0));
        dotest(test_ins_set_delright("ABC", 1));
        dotest(test_ins_set_delright("ABC", 2));
        dotest(test_ins_set_delright("ABC", 3));

        printf("\n");

        for (int i=0; i<10; ++i) {
            string_int si = rand_string_int(10);
            dotestmsg(test_ins_set_delright(si.s, si.n),
                    "ins_set_delright(%s, %d)", si.s, si.n);
        }
    }

    {
        printf("\nrepeated insert and move, mostly insert.\n\n");

        for (int i=0; i<10; ++i) test_rep_insmove0();
    }

    {
        printf("\nrepeated insert and move, equally likely.\n\n");

        for (int i=0; i<10; ++i) test_rep_insmove1();
    }

    {
        printf("\nrepeated ops, mostly insert.\n\n");

        for (int i=0; i<10; ++i) test_rep_all(0.70);
    }

    {
        printf("\nrepeated ops, all equally likely.\n\n");

        for (int i=0; i<10; ++i) test_rep_all(0.20);
    }

    return 0;

}
