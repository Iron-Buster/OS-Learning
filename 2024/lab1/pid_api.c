#include <stdio.h>
#include <unistd.h>


int main() {
    pid_t pid = getpid(); // 获取当前进程的id
    printf("current process id: %d", pid);

    // windows中没有getppid函数
    // The getppid function returns the process ID of the parent of the current process.
    // pid_t ppid = getppid();
    // printf("current parent process id: %d", ppid);

    // The gettid function returns the thread ID of the current thread
    // pid_t ptid = gettid();
    // printf("current thread id: %d", ptid);
    return 0;
}