#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// check dir
int is_directory(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) {
        return -1;
    }
    return S_ISDIR(info.st_mode);
}

// dfs dir
void dfs(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    char path[1024];

    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("can't open dir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        // build full path
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        // skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        // do dfs if directory
        if (is_directory(path) == 1) {
            // start with digits
            if (isdigit(entry->d_name[0])) {
                printf("dir: %s", path);
                dfs(path);
            }
        } else {
            printf("文件： %s", path);
        }
    }

    closedir(dir);
}

int main() {
    const char *dir_path = "/proc"; // replace your dir_path
    dfs(dir_path);
    return 0;
}
