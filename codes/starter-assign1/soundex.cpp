/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
#include <map.h>
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */
string removeNonLetters(string s) {
    // s = ""
    if (s.length() == 0) return "";
    int i = 0;
    string result = "";
    for (; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
static char replaceMap[] = {
    '0', '1', '2', '3', '0', '1', '2', '0', '0', '2', '2', '4', '5',
    '5', '0', '1', '2', '6', '2', '3', '0', '1', '0', '2', '0', '2'
};


string removeSameLetter(string s) {
    if (s.length() <= 1) return s;
    string res = "";
    res += s[0];
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == s[i - 1]) {
            continue;
        }
        res += s[i];
    }
    return res;
}

string removeZeroLetter(string s) {
    string res = "";
    for (auto ch: s) {
        if (ch == '0') {
            continue;
        }
        res += ch;
    }
    return res;
}

string soundex(string s) {

    // removeNonLetters
    string letters = removeNonLetters(s);
    if (letters == "") return "";

    auto upperLetter = toUpperCase(letters);
    const char tmp = upperLetter[0]; // recording first letter
    string res = "";
    for (int i = 0; i < upperLetter.length(); ++i) {
        upperLetter[i] = replaceMap[upperLetter[i] - 'A'];
    }
    res = removeSameLetter(upperLetter);
    res[0] = tmp;
    res = removeZeroLetter(res);
    int len = res.length();
    if (len < 4) {
        for (int i = 0; i < 4 - len; ++i) {
            res.push_back('0');
        }
    }
    return res.substr(0, 4);
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */
    map<string, Vector<string>> codeMapNames;
    Vector<string> codeName;
    for (int i = 0; i < databaseNames.size(); ++i) {
        codeName.add(soundex(databaseNames[i]));
        codeMapNames[codeName[i]].add(databaseNames[i]);
    }

    string input;
    while (1) {
        cout << "Enter a surname (RETURN to quit):";
        if ((input = getLine()) == "") {
            cout << "All done!" << endl;
            break;
        }
        string code = soundex(input);
        cout << "Soundex code is: " << code << endl;
        cout << "Matches from database: {";
        for (auto v: codeMapNames[code]) {
            cout << " " << v <<" ";
        }
        cout << "}" << endl;

    }
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}

STUDENT_TEST("Test remove puntuation, digits, and spaces") {
    string s = "";
    string res = removeNonLetters(s);
    EXPECT_EQUAL(res, "");
    s = "^%&**)((";
    res = removeNonLetters(s);
    EXPECT_EQUAL(res, "");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here


