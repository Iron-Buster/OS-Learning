#include "thread.h"

void T_a() {
    while (1) {
        printf("a");
    }
}

void T_b() {
    while (1) {
        printf("b");
    }
}

// pthead库不是标准linux库 -> 执行gcc thread.c -lpthread
int main() {
    create(T_a);
    create(T_b);
}