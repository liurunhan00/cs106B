// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "strlib.h"
#include "vector.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
using namespace std;


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string cleanToken(string s)
{
    string res{""};
    int i = 0;
    while (!isalpha(s[i])) {
        i++;
    }

    int j = s.length() - 1;
    while (!isalpha(s[j])) {
        j--;
    }

    if (i > j) return res;

    for (int t = i; t <= j; t++) {
        if (isalpha(s[t])) {
            if (isupper(s[t])) {
                s[t] = toLowerCase(s[t]);
            }
        }
        res += s[t];
    }

    return res;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Set<string> gatherTokens(string text)
{
    Set<string> tokens;
    auto gatherVec = stringSplit(text, " ");
    for (auto g: gatherVec) {
        auto Token = cleanToken(g);
        if (Token == "") continue;
        tokens.add(Token);
    }

    return tokens;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
int buildIndex(string dbfile, Map<string, Set<string>>& index)
{
    ifstream in;

    if (!openFile(in, dbfile)) {
        error("Can not open file: " + dbfile);
    }

    Vector<string> lines;
    readEntireFile(in, lines);

    for (size_t i = 0; i < lines.size() / 2; i++) {
        auto url = cleanToken(lines[i * 2]);
        auto tokens   = gatherTokens(lines[i * 2 + 1]);

        for (auto t: tokens) {
            index[t].add(url);
        }

    }

    return lines.size() / 2;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
Set<string> findQueryMatches(Map<string, Set<string>>& index, string query)
{
    Set<string> result;
    // TODO: your code here
    // + must include
    // - not include
    auto queryCompounds = stringSplit(query, " ");
    for (auto q: queryCompounds) {
        if (q[0] == '-' || q[0] == '+' ) {
            string realq = q.substr(1, q.size());
            auto setq = index[realq];
            if (q[0] == '-') {
                for (auto &s: setq) {
                    if (result.contains(s)) {
                        result.remove(s);
                    }
                }
            } else {
                // + intersected
                for(auto &s: setq) {
                    if (!result.contains(s)) {
                        result.remove(s);
                    }
                }

                Set<string> tmpSet;
                for (auto &r: result) {
                    if (setq.contains(r)) {
                        tmpSet.add(r);
                    }
                }

                result = tmpSet;

            }
        } else {
            auto setq = index[q];
            for (auto &s: setq) {
                result.add(s);
            }
        }
    }
    return result;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string dbfile)
{
    // TODO: your code here
    Map<string, Set<string>> index;
    buildIndex(dbfile, index);
    string input;
    while (1) {
        cout << "Enter query sentence (RETURN to quit): ";
        if ((input = getLine()) == "") {
            cout << "ALL done!" << endl;
            break;
        }
        auto result = findQueryMatches(index, input);
        cout << "Found " << result.size() << " matching pages" << endl;
        cout << "{";
        for (auto &r: result) {
            cout << r << endl;
        }
        cout << "}";
    }
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings with no punctuation at beginning or end") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS*106B"), "cs*106b");
}

PROVIDED_TEST("cleanToken on strings with some punctuation at beginning and end") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
}

PROVIDED_TEST("cleanToken on non-word strings (no letters)"){
    EXPECT_EQUAL(cleanToken("106"), "");
    EXPECT_EQUAL(cleanToken("~!106!!!"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs*106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 5 unique words, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 5);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 11 unique tokens") {
    Map<string, Set<string>> index;
    int nPages = buildIndex("res/tiny.txt", index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 11);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Map<string, Set<string>> index;
    buildIndex("res/tiny.txt", index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here
