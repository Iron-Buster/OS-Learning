#include "thread.h"

#define N 100000000

long sum = 0;

void T_sum() {
    for (int i = 0; i < N; i++) {
        sum++;

        // asm volatile(
        //     "incp %0" : "+m"(sum)
        // );
    }
}


int main() {
    create(T_sum);
    create(T_sum);
    join();
    printf("sum = %ld\n", sum);
    printf("2*n = %ld\n", 2L * N);
}