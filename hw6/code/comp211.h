/*  comp211.h - Standard COMP 211 include file.
 *
 *  This file contains macros related to contracts, debugging, and testing.
 *
 *  N. Danner
 *  Spring 2019
 */

#ifndef COMP211_H
#define COMP211_H

#include <assert.h>
#include <stdio.h>

// Contracts.
#ifdef VDEBUG
#define ENSURE(E) fprintf(stderr, "%s: ENSURE(%s)\n", __PRETTY_FUNCTION__, #E) ; fflush(stderr) ; assert(E)
#define REQUIRES(E) fprintf(stderr, "%s: REQUIRES(%s)\n", __PRETTY_FUNCTION__, #E) ; fflush(stderr) ; assert(E)
#else
#define ENSURE(E) assert(E)
#define REQUIRES(E) assert(E)
#endif

// Debugging printing.
#ifdef VDEBUG
#define dprintf(...) fprintf(stderr, __VA_ARGS__) ; fflush(stderr)
#else
#define dprintf(...) (void)0
#endif

// Testing.
#define dotest(TEST) fprintf(stderr, "%s...", #TEST) ; if (TEST) {fprintf(stderr, "pass.\n") ;} else {fprintf(stderr, "FAIL!\n") ;}

#endif

/* dotestmsg(TEST, fmt, ...):  execute test, report success or failure.  TEST
 * must be a boolean-valued expression.  On failure, print the message
 * specified by fmt, ... .
 */

#define dotestmsg(TEST, ...) \
    fprintf(stderr, __VA_ARGS__) ; \
    fprintf(stderr, "...") ; \
    if (TEST) {fprintf(stderr, "pass.\n") ;} \
    else { \
        fprintf(stderr, "FAIL!\n") ; \
    }

