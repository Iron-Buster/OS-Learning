#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char buffer[1024];

    fp = popen("ps -e | iconv -f ISO-8859-1 -t UTF-8", "r");
    if (fp == NULL) {
        printf("Failed to run command");
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
    return 0;
}