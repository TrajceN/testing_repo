#include <stdio.h>
#include <stdlib.h>


int main()
{
    FILE* fp;
    char buff[50];

    fp = fopen("newfile.txt", "r");
    if (fp == NULL) {
        perror("Error in opening file");
        return(-1);
    }

    fgets(buff, sizeof(buff), fp);
    printf("Buff content: %s", buff);

    fclose(fp);


	return 0;
}