#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CopyFileContent(FILE* file1, FILE* file2) {
    char c = 0;
    while (c != EOF) {
        c = fgetc(file1);
        fputc(c, file2);
    }
    printf("Copying has been completed.\n");

}


/*Copies content of one file to another*/
int main()
{
    FILE* myfile1, * myfile2;
    char filename1[100] = { 0 }, filename2[100] = { 0 };
    int file_check, file_number;

    printf("Insert filename you want to open: \n");
    scanf_s("%s", filename1, sizeof(filename1));

    file_check = fopen_s(&myfile1, filename1, "r");

    if (!file_check) {
        printf("File %s was successfully opened!\n", filename1);
    }
    else {
        printf("File %s failed to open or doesn't exist!\n", filename1);
        exit(-1);
    }


    printf("Insert filename you want to copy file content: \n");
    scanf_s("%s", filename2, sizeof(filename2));

    file_check = fopen_s(&myfile2, filename2, "w+");

    if (!file_check) {
        printf("File %s was successfully opened!\n", filename2);
    }
    else {
        printf("File %s failed to open or doesn't exist!\n", filename2);
        exit(-1);
    }

    CopyFileContent(myfile1, myfile2);

    printf("Content of file '%s' is copied to file '%s'\n", filename1, filename2);

    int files_closed = _fcloseall();
    printf("Closed files: %d\n", files_closed);
#if 0
    printf("Insert filename you want to delete: \n");
    scanf_s("%s", filename1, sizeof(filename1));

    if (!remove(filename1)) {
        printf("File %s has been deleted!\n", filename1);
    }
    else {
        printf("File %s doesn't exist!\n", filename1);
    }
#endif
    return 0;
}