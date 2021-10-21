#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    DIR             *dir0;
    DIR             *dir1;
    char            direc[256];
    struct stat     fstat;
    struct dirent   *dp;
    struct dirent   *li;

    dir0 = opendir("tmp");
    strcpy(direc, "tmp/");

    while ((dp = readdir(dir0)) != NULL)
    {
        stat(direc, &fstat);
        strcat(direc, dp->d_name);

        if (fstat.st_nlink > 1)
        {
            printf("%s:\n", dp->d_name);

            dir1 = opendir("tmp");
            while ((li = readdir(dir1)) != NULL)
            {
                if ((li->d_ino == dp->d_ino) & (strcmp(li->d_name, dp->d_name) != 0))
                    printf("%s\n", li->d_name);
            }
            printf("\n");
        }
        else
            printf("%s - no links\n", dp->d_name);
    }

    return (0);
}
