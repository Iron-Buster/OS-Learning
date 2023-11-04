#include <stdio.h>
#include <unistd.h>

using namespace std;
#define REGS_FOREACH(_) _(A) _(Y)
#define RUN_LOGIC       A1 = !A && Y; \
                        Y1 = !A && Y;
#define DEFINE(X)       static int X, X##1;
#define UPDATE(X)       X = X##1
#define PRINT(X)        printf(#X " = %d; ", X);

int main() {
    REGS_FOREACH(DEFINE)
    while (1) {
        RUN_LOGIC;
        REGS_FOREACH(PRINT);
        REGS_FOREACH(UPDATE);
        putchar('\n'); sleep(1);
    }
}
