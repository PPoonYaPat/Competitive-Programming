/*
SAMPLE GRADER for task ART

USAGE:
place together with your solution and art.h in the same directory, then open the terminal in this directory
(right-click onto an empty spot in the directory, left click on "Open in terminal") and enter:
    g++ <flags> sample_grader.cpp <solution_file>
e.g.:
    g++ -std=c++17 sample_grader.cpp art.cpp
This will create a file a.out in the current directory which you can execute from the terminal as ./a.out

INPUT/OUTPUT:
The sample grader first expects on standard input two lines. The first line should
contain the integer N. The second line should contain a list of N space-separated
integers, the correct ranking of the collections in the same format as for publish
and answer. Then, the grader calls solve(N) and writes to standard output a protocol
of all grader functions called by your program. Upon termination, it writes your
verdict to standard output.
*/
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>

#include "art.h"

using namespace std;

void __attribute__((noreturn)) __attribute__((format(printf, 1, 2))) result(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\n");
    va_end(args);
    exit(0);
}

namespace {
    int N;
    int Q = 0;
    const int MAX_Q = 4000;
    const int MAX_N = 4000;
    vector<int> solution;
}  // namespace

int publish(vector<int> R) {
    printf("publish({");
    for(int i = 0; i < int(R.size()); ++i) {
        if(i == 0)
            printf("%d", R[i]);
        else
            printf(", %d", R[i]);
    }
    printf("})\n");
    fflush(stdout);

    if (++Q > MAX_Q)
        result("Too many published rankings!");

    if (int(R.size()) != N)
        result("Invalid published ranking!");

    set<int> chosen;
    for(auto &x : R) {
        if(x < 1 || x > N || chosen.count(x))
            result("Invalid published ranking!");
        chosen.insert(x);
    }
    vector<int> positions(N+1);
    for(int i = 0; i < N; ++i)
        positions[R[i]] = i;

    int complaints = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            if(positions[solution[i]] > positions[solution[j]])
                ++complaints;
        }
    }

    return complaints;
}

void __attribute__((noreturn)) answer(vector<int> R) {
    printf("answer({");
    for(int i = 0; i < int(R.size()); ++i) {
        if(i == 0)
            printf("%d", R[i]);
        else
            printf(", %d", R[i]);
    }
    printf("})\n");
    fflush(stdout);


    if(R == solution)
        result("Correct: %d published ranking(s).", Q);
    else
        result("Wrong answer!");
}

int main() {
    if (scanf("%d", &N) != 1 || N < 2 || N > MAX_N)
        result("Invalid input!");

    solution.resize(N);
    set<int> chosen;
    for(auto &x : solution) {
        if(scanf("%d", &x) != 1 || x < 1 || x > N || chosen.count(x))
            result("Invalid input!");
        chosen.insert(x);
    }

    solve(N);

    result("No answer!");
}
