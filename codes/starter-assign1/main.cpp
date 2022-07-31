#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "perfect.h"
#include "soundex.h"
#include <vector.h>
#include <algorithm>
using namespace std;

STUDENT_TEST("Time operation vector sort on tiny input")
{
    vector<int> v = {3, 7, 2, 45, 2, 6, 3, 56, 12};
    Vector<int> V;
    for (std::size_t i = 0; i < 100000; ++i) {
        V.add(i + 1);
    }
    TIME_OPERATION(V.size(), sort(V.begin(), V.end()));
}
int main() {
    // if (runSimpleTests(SELECTED_TESTS)) {
    //     return 0;
    // }
    // soundex("liu");

   // findPerfects(40000);
    // Comment out the above line and uncomment below line 
    // to switch between running perfect.cpp and soundex.cpp
    soundexSearch("res/surnames.txt");

    cout << endl << "main() completed." << endl;
    return 0;
}


// Do not remove or edit below this line. It is here to to confirm that your code
// conforms to the expected function prototypes needed for grading
void confirmFunctionPrototypes() {
    long n = 0;
    bool b;
    string s;

    n = divisorSum(n);
    b = isPerfect(n);
    findPerfects(n);

    n = smarterSum(n);
    b = isPerfectSmarter(n);
    findPerfectsSmarter(n);

    n = findNthPerfectEuclid(n);

    s = removeNonLetters(s);
    s = soundex(s);
    soundexSearch(s);
}
