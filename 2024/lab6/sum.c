#include "thread.h"

#define T       3
#define N       1000000


#define LOCKED      1
#define UNLOCKED    0

int status = UNLOCKED;


void lock() {
    int expected;
    do {
        expected = UNLOCKED;
        // compare and swap
        asm volatile (
            "lock cmpxchgl %2, %1"
            : "+a" (expected)
            : "m" (status),
              "r" (LOCKED)
            : "memory", "cc"
        );
    } while (expected != UNLOCKED);
}


void unlock() {
    status = UNLOCKED;
}

long volatile sum = 0;

void T_sum() {
    for (int i = 0; i < N; i++) {
        lock();

        for (int _ = 0; _ < 10; _++) {
            sum++;
        }
        unlock();
    }
}

int main() {
    for (int i = 0; i < T; i++) {
        create(T_sum);
    }

    join();
    printf("sum  = %ld\n", sum);
    printf("%d*n = %ld\n", T * 1, T * 10L * N);
}