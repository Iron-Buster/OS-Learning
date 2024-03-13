#include "thread.h"


#define N 4

char * volatile low[N];
char * volatile high[N];


void update_range(int T, char *ptr) {
    if (ptr < low[T]) {
        low[T] = ptr; 
    }
    if (ptr > high[T]) {
        high[T] = ptr;
    }
}


void probe(int T, int n) {
    char scratch[64];
    update_range(T, scratch);

    printf("Stack(T%d) >= %ld KB\n", T, (high[T] - low[T]) / 1024);

    probe(T, n + 1); 
}

void T_probe(int T) {
    T -= 1;
    low[T] = (char *)-1;
    high[T] = (char *)0;
    probe(T, 0);
}

int main() {
    setbuf(stdout, NULL);
    
    for (int i = 0; i < N; i++) {
        create(T_probe);
    }
}