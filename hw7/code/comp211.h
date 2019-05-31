/*  comp211.h - Standard COMP 211 include file.
 *
 *  This file contains macros related to contracts, debugging, and testing.
 *
 *  Spring 2019
 */

#ifndef COMP211_H
#define COMP211_H

#include <assert.h>
#include <stdio.h>

// Contracts.
#ifdef VDEBUG
#define ENSURE(E) fprintf(stdout, "%s: ENSURE(%s)\n", __PRETTY_FUNCTION__, #E); fflush(stdout); assert(E)
#define REQUIRES(E) fprintf(stdout, "%s: REQUIRES(%s)\n", __PRETTY_FUNCTION__, #E); fflush(stdout); assert(E)
#else
#define ENSURE(E) assert(E)
#define REQUIRES(E) assert(E)
#endif

// Debugging printing.
#ifdef VDEBUG
#define dprintf(...) fprintf(stdout, __VA_ARGS__); fflush(stdout)
#else
#define dprintf(...) (void)0
#endif

// Testing.
#define dotest(TEST) fprintf(stdout, "%s...", #TEST); if (TEST) {fprintf(stdout, "pass.\n");} else {fprintf(stdout, "FAIL!\n");}

#endif

/* dotestmsg(TEST, fmt, ...):  execute test, report success or failure.  TEST
 * must be a boolean-valued expression.  On failure, print the message
 * specified by fmt, ... .
 */

#define dotestmsg(TEST, ...) \
    fprintf(stdout, __VA_ARGS__); \
    fprintf(stdout, "..."); \
    fflush(stdout); \
    if (TEST) {fprintf(stdout, "pass.\n");} \
    else { \
        fprintf(stdout, "FAIL!\n"); \
    }

