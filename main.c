#include <stdio.h>
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
}

void copy() {
}

void delete() {
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

void selectFile() {
    FILE *fp;
    char fileName[1024];
    printf("Enter name of file (including file extension(.txt)): ");

    fgets(fileName, 1024, stdin);
    fp = fopen(fileName, "r+");

    while (1) {
        printf("Enter choice: ");
        char input[1024];
        fgets(input, 1024, stdin);
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
    printf("Enter one of the following options to use the program:\n\n");
    mainHelp();

    // Keep list of operations performed
    char commandLog[1024];
    int currentCommandNumber = 0;

    while (1) {
        currentCommandNumber += 1;

        printf("Enter choice: ");
        char input[1024];
        fgets(input, 1024, stdin);

        input[strlen(input) - 1] = '\0'; // Remove \n character from end of string
        printf("%s", input);

        if (!strcmp(input, "help")) { mainHelp(); } else if (!strcmp(input, "create")) { create(); } else if (
            !strcmp(input, "copy")) { copy(); } else if (!strcmp(input, "delete")) { delete(); } else if (!strcmp(
            input, "select")) {
            selectFile();
        } else if (!strcmp(input, "help")) { break; } else { printf("Invalid choice\n"); }
    }
    return 0;
}
