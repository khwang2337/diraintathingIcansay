#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

char * fileSize(int size) {
    char *list[5] = {"","K","M","G","T"};
    unsigned long num = size;
    int i = 0;
    if (num / 1024 > 0) {
        num /= 1024;
        i++;
    }
    char *ret = malloc(10);
    sprintf(ret, "%lu%sB",num,list[i]);
    return ret;
}

int main() {
    DIR * whatsup = opendir("euler");
    struct dirent *ceiling = readdir(whatsup);
    int size = 0;;
    struct stat buffer;
    char * retdir = malloc(1);
    char * retreg = malloc(1);
    char * temp;
    while (ceiling != NULL) {
        stat(ceiling->d_name, &buffer);
        size += buffer.st_size;
        if (ceiling->d_type == DT_DIR) {
            temp = malloc(strlen(retdir));
            strcpy(temp,retdir);
            free(retdir);
            retdir = malloc(strlen(ceiling->d_name)+strlen(temp)+2);
            strcpy(retdir,temp);
            strcat(retdir,ceiling->d_name);
            strcat(retdir, "\n");
            strcpy(temp,"");
            free(temp);
        }
        else if (ceiling->d_type == DT_REG) {
            strcpy(temp,retreg);
            free(retreg);
            retreg = malloc(strlen(ceiling->d_name)+strlen(temp)+2);
            strcpy(retreg,temp);
            strcat(retreg,ceiling->d_name);
            strcat(retreg, "\n");
            strcpy(temp,"");
        }
        ceiling = readdir(whatsup);
    }
    printf("\nDirectory:\n\nSize: %s\n\nDirFiles:\n%s\nRegFiles:\n%s",fileSize(size),retdir,retreg);
    return 0;
}
