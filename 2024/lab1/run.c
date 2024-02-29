#include <stdio.h>
#include <assert.h>


int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        assert(argv[i]); // C 标准保证
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    assert(!argv[argc]); // C 标准保证
    return 0;
}