/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "testing/SimpleTest.h"

using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
string operatorsFrom(string str) {
    /* TODO: Implement this function. */
    if (str.size() == 0) {
        return "";
    }
    if (str[0] == '(' || str[0] == ')'
     || str[0] == '[' || str[0] == ']'
     || str[0] == '{' || str[0] == '}') {
        return str[0] + operatorsFrom(str.substr(1, str.length() - 1));
    } else {
        return operatorsFrom(str.substr(1, str.length() - 1));
    }
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool operatorsAreMatched(string ops) {
    /* TODO: Implement this function. */
    size_t pos;
    string deleteMathched = "";
    if (ops == "") {
        return true;
    } else if ((pos = ops.find("()")) != string::npos ||
               (pos = ops.find("{}")) != string::npos ||
               (pos = ops.find("[]")) != string::npos  ) {
        // can be replace by string::erase()
        for (size_t i = 0; i < ops.size(); i++) {
            if (i != pos && i != pos + 1) {
                deleteMathched += ops[i];
            }
        }
        return operatorsAreMatched(deleteMathched);
    }

    return false;
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("operatorsFrom on simple example2") {
    EXPECT_EQUAL(operatorsFrom("{})__(_DSA}I!}"), "{})(}}");
}

STUDENT_TEST("operatorsFrom on simple example3") {
    EXPECT_EQUAL(operatorsFrom("[3]{}}{}{()4}"), "[]{}}{}{()}");
}

STUDENT_TEST("operatorsFrom on simple example4") {
    EXPECT_EQUAL(operatorsFrom("vec[3{]"), "[{]");
}
