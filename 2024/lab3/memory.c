#include "thread.h"


// 多个线程之间是共享内存
int n;

void T_hello(int id) {
    int i = n++;
    printf("%d\n", i);
}

int main() {
    for (int i = 0; i < 10; i++) {
        create(T_hello);
    }
}