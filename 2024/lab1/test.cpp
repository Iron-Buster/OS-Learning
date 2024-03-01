#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include<string>  
#include<iostream>  
#include<unordered_map>
#include <vector>
#include <deque>
using namespace std; 


vector<int> roots;
unordered_map<int, int> fmap;
unordered_map<int, vector<int>> map;


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

    char *parent_pid_str = strchr(line, ')') + 3;
    int parent_pid = atoi(parent_pid_str);

    return parent_pid;
}

void list_processes_and_parents() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("/proc")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_name[0] >= '0' && ent->d_name[0] <= '9') {
                int pid = atoi(ent->d_name);
                int parent_pid = get_parent_pid(pid);
                fmap[pid] = parent_pid;
                if (parent_pid == 0) {
                    roots.push_back(pid);
                }
                printf("PID: %d, Parent PID: %d\n", pid, parent_pid);
            }
        }
        closedir(dir);
    } else {
        perror("Error opening /proc directory");
    }
}

void bfs() {
    deque<int> dq;
    for (int i = 0; i < roots.size(); i++) {
    }
}

int main() {
    list_processes_and_parents();
    bfs();
    return 0;
}

