#include "thread.h"


unsigned long balance = 100;


void Alipay_withdraw(int amt) {
    if (balance >= amt) {
        usleep(1);
        balance -= amt;
    }
}

void T_alipay() {
    Alipay_withdraw(100);
}

int main() {
    create(T_alipay);
    create(T_alipay);
    join();
    printf("balance = %lu\n", balance);
}