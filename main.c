#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainHelp() {
    printf("help  -  Display list of commands\n"
        "create - Create a new file\n"
        "copy  -  Copy a specified file\n"
        "delete - Delete a file\n"

        "append  -  Create new line at end of file\n"
        "insert  -  Insert new line of content at line number\n\n"

        "showfile - Show content of file\n"
        "showline - Show content at particular line\n"
        "deleteline  -  Delete line at particular line number\n"
        "numlines - Show the number of lines in a file\n\n"

        "showlog - Show the sequence of all operations performed so far\n\n"

        "exit - Exit the application\n\n"
    );
}

void create() {
    char *fileName[99];

    printf("Enter name of file: ");
    scanf("%s", fileName);


    // Check file does not already exit
    FILE *check = fopen(strcat(fileName, ".txt"), "r");
    if (check != NULL) {
        printf("File already exists\n");
        return;
    }

    FILE *fp = fopen(fileName, "w");

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
    FILE *fp;
    fp = fopen(strcat(fileName, ".txt"), "r");

    // Check file exists and return to main menu if not
    while (fp == NULL) {
        printf("File not found\n");
        return 0;
    }

    printf("Enter name of new file: ");
    scanf("%s", fileName2);


    // Check file does not already exit
    FILE *check = fopen(strcat(fileName2, ".txt"), "r");
    if (check != NULL) {
        printf("File already exists\n");
        return -1;
    }

    // Create new file
    FILE *fp2 = fopen(fileName2, "w");

    // Copy contents of first file to second
    int counter = 0;
    while ((c = (char) fgetc(fp)) != EOF) {
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

void showLog(char **commandLog) {
    for (int i = 0; i < sizeof(commandLog); i++) {
        if (commandLog[i] == NULL) {
            return;
        }
        printf("%d: %s\n", i + 1, commandLog[i]);
    }
}

void append() {
}

void deleteLine() {
}

void insert() {
}

void showFile() {
    char fileName[99];
    printf("Enter name of file: ");
    scanf("%s", fileName);

    FILE *fp;
    char c;

    fp = fopen(strcat(fileName, ".txt"), "r");

    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    while (1) {
        c = (char) fgetc(fp);
        if (c == EOF) {
            break;
        } else {
            printf("%c", c);
        }
    }
    fclose(fp);
}

void showLine() {
    char fileName[99];
    printf("Enter name of file: ");
    scanf("%s", fileName);

    FILE *fp;
    char c;

    fp = fopen(strcat(fileName, ".txt"), "r");

    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    // Line to print
    int lineNum;
    printf("Enter line number: ");
    scanf("%d", &lineNum);

    // Line currently checking
    int lineCount = 1;
    while (1) {
        c = fgetc(fp);
        if (c == EOF) {
            printf("File does not have this many lines");
            break;
        } else {
            if (c == '\n') {
                lineCount++;
            }

            if (lineCount == lineNum) {
                while (1) {
                    c = (char) fgetc(fp);
                    if (c == EOF || c == '\n') {
                        break;
                    } else {
                        printf("%c", c);
                    }
                }
                fclose(fp);
                break;
            }
        }
    }
    fclose(fp);
}

void numLines() {
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
            create();
        } else if (!strcmp(input, "copy")) {
            lines = copy();
            if (lines >= 0) {
                char *toAdd[100];
                sprintf(toAdd, "Copied file of %d Lines", lines);
                commandLog[currentOp++] = toAdd;
            }
        } else if (!strcmp(input, "delete")) {
            delete();
            commandLog[currentOp++] = "Deleted File";
        } else if (!strcmp(input, "append")) {
            append();
        } else if (!strcmp(input, "insert")) {
            insert();
        } else if (!strcmp(input, "showfile")) {
            showFile();
        } else if (!strcmp(input, "showline")) {
            showLine();
        } else if (!strcmp(input, "deleteline")) {
            deleteLine();
        } else if (!strcmp(input, "numlines")) {
            numLines();
        } else if (!strcmp(input, "showlog")) {
            showLog(commandLog);
        } else if (!strcmp(input, "exit")) {
            printf("Bye!");
            break;
        } else {
            printf("Invalid input\n");
        }
    }
    return 0;
}
