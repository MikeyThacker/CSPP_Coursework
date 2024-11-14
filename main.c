#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
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

int getNumLines(char *fileName) {
    FILE *fp;
    char c;

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    int lineCount = 1;
    while (1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            lineCount++;
        }
    }

    fclose(fp);
    return lineCount;
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
        if (commandLog[0] == '\0') {
            printf("Command log is empty\n");
            return;
        }
        if (commandLog[i] == NULL) {
            return;
        }
        printf("%d: %s\n", i + 1, commandLog[i]);
    }
}

int append() {
    char fileName[99];
    printf("Enter name of file to append to: ");
    scanf("%s", fileName);

    FILE *fp = fopen(strcat(fileName, ".txt"), "a");
    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    char string[100];
    printf("Enter content to append: ");
    scanf("%s", string);

    fputs("\n", fp);
    fputs(string, fp);
    fclose(fp);
    return getNumLines(fileName);
}

int insert() {
    char fileName[99];
    printf("Enter name of file: ");
    scanf("%s", fileName);

    // File to insert into
    FILE *fp;
    char c;

    // New file with insertion
    FILE *fp2;

    fp = fopen(strcat(fileName, ".txt"), "r");
    fp2 = fopen("Copy.txt", "w");


    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Line to insert
    int lineNum;
    printf("Enter line number: ");
    scanf("%d", &lineNum);

    // Enter string to insert
    char string[100];
    printf("Enter string to insert: ");
    scanf("%s", string);

    // Line currently checking
    int lineCount = 1;
    int lineInserted = 0;
    while (1) {
        // Get next character
        c = fgetc(fp);

        // Check not end of file
        if (c == EOF && !lineInserted) {
            printf("File does not have this many lines");
            remove("Copy.txt");
            return -1;
        }
        if (c == EOF && lineInserted) {
            fclose(fp);
            fclose(fp2);
            remove(fileName);
            rename("Copy.txt", fileName);
            printf("Line inserted successfully\n");
            return getNumLines(fileName);
        }

        // Put character in second file
        fputc(c, fp2);

        // Increase number of lines checked
        if (c == '\n') {
            lineCount++;
        }

        // Insert new line into file 2
        if (lineCount == lineNum && !lineInserted) {
            for (int i = 0; string[i] != '\0'; i++) {
                fputc(string[i], fp2);
            }
            fputc('\n', fp2);
            lineInserted = 1;
        }
    }
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

int deleteLine() {
    char fileName[99];
    printf("Enter name of file: ");
    scanf("%s", fileName);

    // File to delete line in
    FILE *fp;
    char c;

    // New file without specified line
    FILE *fp2;

    fp = fopen(strcat(fileName, ".txt"), "r");
    fp2 = fopen("Copy.txt", "w");


    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Line to delete
    int lineNum;
    printf("Enter line number: ");
    scanf("%d", &lineNum);

    // Line currently checking
    int lineCount = 1;
    int lineDeleted = 0;
    while (1) {
        // Get next character
        c = fgetc(fp);

        // Check not end of file
        if (c == EOF && !lineDeleted) {
            printf("File does not have this many lines");
            remove("Copy.txt");
            return -1;
        }
        if (c == EOF && lineDeleted) {
            fclose(fp);
            fclose(fp2);
            remove(fileName);
            rename("Copy.txt", fileName);
            printf("Line deleted successfully\n");
            return getNumLines(fileName);
        }


        // Increase number of lines checked
        if (c == '\n') {
            lineCount++;
        }

        if (lineCount == lineNum) {
            // If current line is to be deleted
            lineDeleted = 1;
            continue;
        } else {
            // Put character in second file
            fputc(c, fp2);
        }
    }
}

void numLines() {
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

    int lineCount = 1;
    while (1) {
        c = fgetc(fp);
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            lineCount++;
        }
    }

    fclose(fp);
    if (lineCount == 1) {
        printf("File has 1 line \n");
        return;
    }
    printf("File has %d lines \n", lineCount);
}





int main(void) {
    printf("Welcome to the command-line file editor built in C!\n");
    printf("There is one rule: Always exclude the file extension when entering the name of a file.\n");
    printf("Enter one of the following options to use the program:\n\n");
    help();

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
            help();
        } else if (!strcmp(input, "create")) {
            commandLog[currentOp++] = "Created File";
            create();
        } else if (!strcmp(input, "copy")) {
            lines = copy();
            if (lines >= 0) {
                char toAdd[100];
                sprintf(toAdd, "Copied file of %d lines", lines);
                commandLog[currentOp++] = toAdd;
            }
        } else if (!strcmp(input, "delete")) {
            delete();
            commandLog[currentOp++] = "Deleted File";
        } else if (!strcmp(input, "append")) {
            lines = append();
            if (lines >=0) {
                char toAdd[100];
                sprintf(toAdd, "Appended to file of %d lines", lines);
                commandLog[currentOp++] = toAdd;
            }
        } else if (!strcmp(input, "insert")) {
            lines = insert();
            if (lines > 0) {
                char toAdd[100];
                sprintf(toAdd, "Inserted line into file of %d lines", lines);
                commandLog[currentOp++] = toAdd;
            }
        } else if (!strcmp(input, "showfile")) {
            showFile();
        } else if (!strcmp(input, "showline")) {
            showLine();
        } else if (!strcmp(input, "deleteline")) {
            lines = deleteLine();
            if (lines >= 0) {
                char toAdd[100];
                sprintf(toAdd, "Deleted line in file of %d lines", lines);
                commandLog[currentOp++] = toAdd;
            }
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
