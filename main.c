#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainHelp() {
    printf("help  -  Display list of commands\n"
        "create - Create a new file\n"
        "copy  -  Copy a specified file\n"
        "delete - Delete a file\n"
        "select - Select a file to perform additional operations\n\n"

        "showlog - Show the sequence of all operations performed so far\n\n"

        "exit - Exit the application\n\n"
    );
}

void fileHelp() {
    printf("help   -   display list of commands\n"
        "append  -  Create new line at end of file\n"
        "delete  -  Delete line at particular line number\n"
        "insert  -  Insert new line of content at line number\n\n"

        "showfile - Show content of file\n"
        "showline - Show content at particular line\n"
        "numlines - Show the number of lines in a file\n\n"

        "exit -  Return to main menu\n\n");
}

void create() {
    FILE *fp;
    char *fileName[99];

    printf("Enter name of file: ");
    scanf("%s", fileName);

    fp = fopen(strcat(fileName, ".txt"), "w");

    fclose(fp);

    printf("File created successfully\n");
}

int copy() {
    char fileName[99];
    char fileName2[99];
    char c;

    printf("Enter name of file to copy: ");
    scanf("%s", fileName);

    // Open file to copy
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // Check file exists and return to main menu if not
    while (fp == NULL) {
        printf("File not found\n");
        return 0;
    }

    printf("Enter name of new file: ");
    scanf("%s", fileName2);

    // Create new file
    FILE *fp2 = fopen(strcat(fileName2, ".txt"), "w");

    // Copy contents of first file to second
    int counter = 0;
    while ((c = fgetc(fp)) != EOF) {
        fputc(c, fp2);
        counter++;
    }


    printf("File copied successfully\n");

    fclose(fp);
    fclose(fp2);
    return counter;
}


void delete() {
    char fileName[99];
    printf("Enter name of file to delete: ");
    scanf("%s", fileName);

    if (!remove(strcat(fileName, ".txt"))) {
        printf("File deleted\n");
    } else {
        printf("File not found\n");
    }
}

void showLog() {
}

void append() {
}

void deleteLine() {
}

void insert() {
}

void showFile() {
}

void showLine() {
}

void numLines() {
}


void selectFile(char commandLog[]) {
    while (1) {
        printf("\nFile Menu\n");
        printf("Enter choice: ");
        char input[99];
        scanf("%s", input);

        input[strlen(input) - 1] = '\0'; // Remove \n character from end of string
        printf("%s\n", input);

        if (!strcmp(input, "help")) { mainHelp(); } else if (!strcmp(input, "append")) { append(); } else if (
            !strcmp(input, "delete")) { delete(); } else if (!strcmp(input, "insert")) { insert(); } else if (
            !strcmp(input, "showfile")) { showFile(); } else if (!strcmp(input, "showline")) { showLine(); } else if (
            !strcmp(input, "numlines")) { numLines(); } else if (!strcmp(input, "exit")) { break; } else {
            printf("Invalid choice\n");
        }
    }
}


int main(void) {
    printf("Welcome to the command-line file editor built in C!\n");
    printf("There is one rule: Always exclude the file extension when entering the name of a file.\n");
    printf("Enter one of the following options to use the program:\n\n");
    mainHelp();

    // Keep list of operations performed
    char *commandLog[100];
    int currentOp = 0;
    int lines = 0; // Number of lines following each operation

    while (1) {
        printf("\nMain Menu\n");
        printf("Enter choice: ");
        char input[99];
        scanf("%s", input);

        if (!strcmp(input, "help")) {
            mainHelp();
        } else if (!strcmp(input, "create")) {
            commandLog[currentOp++] = "Created File";
        } else if (!strcmp(input, "copy")) {
            copy();
        } else if (!strcmp(input, "delete")) {
            delete();
            lines = 0;
        } else if (!strcmp(input, "select")) {
            selectFile(commandLog);
        } else if (!strcmp(input, "exit")) {
            printf("Bye!");
            break;
        } else {
            printf("Invalid input\n");
        }
    }
    return 0;
}
