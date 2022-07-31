/**
 * File: warmup.cpp
 * ----------------
 * This code is provided as part of an exercise to practice using a
 * debugger. This program has buggy use of recursion.
 */

#include <iostream>    // for cout, endl
#include "error.h"
#include "random.h"
#include "testing/SimpleTest.h"
using namespace std;


/* This is a recursive implementation of a function to calculate
 * factorials. This function works correctly for positive values
 * of n whose computed factorial value does not overflow the int
 * data type (n <= 12).
 *
 * As currently written, this function does not correctly handle
 * negative inputs.
 */
int factorial(int n) {
    if (n < 0) {
        error("param shouldn't blow 0!");
    }
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}


/* The myPower function computes exponentiation.
 * The call myPower(base, exp) returns base raised to the power exp.
 * Note that either/both of base and exp can be negative.
 * The calculation is done using type double to allow for the result
 * to have a fractional component, such as would be needed for
 * a negative exponent.
 *
 * WARNING: The given implementation is BUGGY! It works mostly correctly
 * but it has some bugs that you should find and fix. Refer to the
 * writeup for further instructions on how to do so.
 */
// zero && base no need to check
double myPower(int base, int exp) {
    if (exp == 0) {         // handle zero exp
        return 1;
    } else if (exp < 0) {   // handle negative exp
        return 1.0 / myPower(base, -exp);
    } else {                // both base and exp are positive
        return base * myPower(base, exp - 1);
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("Confirm result of factorial(7)") {
    EXPECT_EQUAL(factorial(7), 7*6*5*4*3*2);
}

PROVIDED_TEST("myPower(), compare to library pow(), fixed inputs") {
    EXPECT_EQUAL(myPower(7, 0), pow(7, 0));
    EXPECT_EQUAL(myPower(10, 2), pow(10, 2));
    EXPECT_EQUAL(myPower(5, -1), pow(5, -1));
    EXPECT_EQUAL(myPower(-3, 3), pow(-3, 3));
}

PROVIDED_TEST("myPower(), generated inputs") {
    for (int base = 1; base < 25; base++) {
        for (int exp = 1; exp < 10; exp++) {
            EXPECT_EQUAL(myPower(base, exp), pow(base, exp));
        }
    }
}

STUDENT_TEST(("Stack overflow")) {
    EXPECT_ERROR(factorial(-3));
}


STUDENT_TEST("myPower(), compare to library pow(), find bugs") {
    EXPECT_EQUAL(myPower(7, -1), pow(7, -1));
    EXPECT_EQUAL(myPower(-3, -2), pow(-3, -2));
}

/* WINDOWS API BUG
 * [^1]: Late-breaking news (10/8/2021):
 * The version of pow in the library used
 * on Windows turns out to not be a reliable reference.
 * I just confirmed it takes a computational shortcut in
 * calculating the result which can sometimes cause the last
 * decimal place to be minutely different than the result computed by
 * repeated multiplication/division (e.g. how myPower function calculates it).
 * Comparing the result of myPower to pow will match for most inputs, but also
 * can happen that result is very very close, but not perfectly equal, and give
 * erroneous test case failure. If you encounter these tiny discrepancies, just
 * ignore them (and take CS107 to learn more about why precision in floating point
 * comparison is hard for binary computers!)
 */
STUDENT_TEST("myPower(), generated negitive inputs") {
    for (int base = -25; base < -1; base++) {
        for (int exp = -10; exp < -1; exp++) {
            EXPECT_EQUAL(myPower(base, exp), pow(base, exp));
        }
    }
}
