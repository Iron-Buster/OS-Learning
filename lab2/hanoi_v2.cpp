// 非递归汉诺塔

#include <stdio.h>
#include <unistd.h>
#include <assert.h>

using namespace std;

typedef struct {
    int pc, n;
    char from, to, via;
} Frame;
#define call(...) ({ *(++top) = (Frame) { .pc = 0, __VA_ARGS__}; })
#define ret()     ({ top--; })
#define goto(loc) ({ f->pc = (loc) - 1; })

void hanoi(int n, char from, char to, char via) {
    Frame stk[64], *top = stk - 1;
    call(n, from, to, via);
    for (Frame *f; (f = top) >= stk; f->pc++) {
        switch (f->pc)
        {
        case 0: 
            if (f->n == 1) { 
                printf("%c -> %c\n", f->from, f->to); 
                goto(4); 
            } 
            break;        
        case 1: call(f->n - 1, f->from, f->via, f->to); break;
        case 2: call(       1, f->from, f->to, f->via); break;
        case 3: call(f->n - 1, f->via, f->to, f->from); break;
        case 4: ret();
        default: assert(0);
        }
    }
}

int main() {
    hanoi(3, 'A', 'B', 'C');
}