
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 读取/proc/<pid>/stat文件中的第三个字段（即父进程ID）
int get_parent_pid(int pid) {
    char filename[256];
    snprintf(filename, sizeof(filename), "/proc/%d/stat", pid);
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open status file for PID");
        return -1;
    }

    char line[1024];
    fgets(line, sizeof(line), fp);
    fclose(fp);

    // 第三个字段前后的字符是固定的，如'(pid)'，因此可以这样解析
    char *parent_pid_str = strchr(line, ')') + 3; // 跳过'('和PID以及')'
    int parent_pid = atoi(parent_pid_str); // 转换为整数

    return parent_pid;
}

void list_processes_and_parents() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/proc")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // 只考虑数字命名的目录，它们代表进程ID
            if (isdigit(ent->d_name[0])) {
                int pid = atoi(ent->d_name);
                int parent_pid = get_parent_pid(pid);
                
                printf("PID: %d, Parent PID: %d\n", pid, parent_pid);
            }
        }
        closedir(dir);
    } else {
        perror("Error opening /proc directory");
    }
}

int main() {
    list_processes_and_parents();
    return 0;
}