#include <stdio.h> // Import IO functionality i.e., Accessing files and printing to user
#include <string.h> // Gives extra use for strings e.g., string concatenation and comparison
#include <dirent.h> // Allows opening, reading, and closing directory
#include <stdlib.h>

void help() {
    // Display list of commands to user

    printf("help  -  Display list of commands\n"
        "create - Create a new file\n"
        "copy  -  Copy a specified file\n"
        "delete - Delete a file\n\n"

        "append  -  Create new line at end of file\n"
        "insert  -  Insert new line of content at line number\n\n"

        "showfile - Show content of file\n"
        "showline - Show content at particular line\n"
        "deleteline  -  Delete line at particular line number\n"
        "numlines - Show the number of lines in a file\n\n"

        "showlog - Show the sequence of all operations performed so far\n\n"

        "Additional Features:\n"
        "rename - Rename a file\n"
        "ls - Show operable files in current directory\n\n"

        "exit - Exit the application\n"
    );
}

void getUserInput(char *userInput, const int size) {
    // Get a string input from the user
    fgets(userInput, size, stdin);
    // Remove newline character from end of string
    userInput[strlen(userInput) - 1] = '\0';
}

int getUserInt() {
    // Get string input from user
    char tempString[99];
    fgets(tempString, sizeof(tempString), stdin);

    // Convert string input to integer
    const int userInt = (int) strtol(tempString, NULL, 10);
    // strtol converts string to long value, must cast to an integer
    return userInt;
}

int getNumLines(const char *fileName) {
    /*
     * This method calculates the number of lines in a file without asking the user for its name,
     * It receives the name of the file as a parameter when called
     */

    // Open file
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Count number of '\n' characters in file
    int lineCount = 0;
    while (1) {
        char c = (char) fgetc(fp);
        if (c == EOF) {
            if (lineCount == 0) {
                break;
            }
            break;
        }
        if (lineCount == 0) {
            // Increase line count to 1 if file is not empty
            lineCount++;
        }
        if (c == '\n') {
            lineCount++;
        }
    }

    fclose(fp);
    return lineCount;
}

void create() {
    // Get name of file from user
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));


    // Check file does not already exit
    FILE *check = fopen(strcat(fileName, ".txt"), "r");
    if (check != NULL) {
        printf("File already exists\n");
        return;
    }
    fclose(check);

    // Create file
    FILE *fp = fopen(fileName, "w");
    fclose(fp);

    printf("File created successfully\n");
}

int copy() {
    char c;

    // Get name of file to copy from user
    printf("Enter name of file to copy: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));


    // Open file to copy
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // Check file exists and return to main menu if not
    while (fp == NULL) {
        printf("File not found\n");
        return -1;
    }


    printf("Enter name of new file: ");
    char fileName2[99];
    getUserInput(fileName2, sizeof(fileName2));


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

int delete() {
    // Get name of file user wishes to delete
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));


    if (!remove(strcat(fileName, ".txt"))) {
        // If remove() returns 0, file has been deleted
        printf("File deleted\n");

        return 0;
    } else {
        printf("File not found\n");
        return 1;
    }
}

void showLog(char **commandLog) {
    // Check command log is not empty
    if (commandLog[0] == NULL) {
        printf("Command log is empty\n");
        return;
    }

    // Iterate through command log list and output n followed by the action
    for (int i = 0; commandLog[i] != NULL; i++) {
        // If item is null, list is over
        printf("%d: %s\n", i + 1, commandLog[i]);
    }
}

int append() {
    // Get name of file user wishes to append to
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));

    FILE *check = fopen(strcat(fileName, ".txt"), "r");
    // Check file exists and return to main menu if not
    while (check == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Open file in read mode to check if it is empty
    int fileEmpty = 0;
    if (getNumLines(fileName) == 0) {
        fileEmpty = 1;
    }

    // Open file in append mode
    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Get string user wishes to append to file
    printf("Enter content to append: ");
    char string[99];
    getUserInput(string, sizeof(string));


    // Add string to file
    if (!fileEmpty) {
        fputs("\n", fp);
    }
    fputs(string, fp);
    fclose(fp);

    printf("Content appended successfully\n");

    return getNumLines(fileName);
}

int insert() {
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));

    // File to insert into
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // New file with insertion
    FILE *fp2 = fopen("Copy.txt", "w");


    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Line to insert
    printf("Enter line number: ");
    int lineNum = getUserInt();

    // Enter string to insert
    printf("Enter string to insert: ");
    char string[99];
    getUserInput(string, sizeof(string));

    // Line currently checking
    int lineCount = 1;
    int lineInserted = 0;
    while (1) {
        // Get next character
        char c = (char) fgetc(fp);

        // Check not end of file
        if (c == EOF) {
            if (!lineInserted) {
                printf("File does not have this many lines");
                remove("Copy.txt");
                return -1;
            }
            fclose(fp);
            fclose(fp2);
            remove(fileName);
            rename("Copy.txt", fileName);
            printf("Line inserted successfully\n");

            return getNumLines(fileName);
        }


        // Insert new line into file 2
        if (lineCount == lineNum && !lineInserted) {
            for (int i = 0; string[i] != '\0'; i++) {
                fputc(string[i], fp2);
            }
            fputc('\n', fp2);
            lineInserted = 1;
        }
        // Put character in second file
        fputc(c, fp2);


        // Increase number of lines checked
        if (c == '\n') {
            lineCount++;
        }
    }
}

void showFile() {
    // Get name of file user wishes to show
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));

    // Open file in read mode
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // Check file exists
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    // Output each character until end of file is reached
    while (1) {
        char c = (char) fgetc(fp);
        if (c == EOF) {
            break;
        }
        printf("%c", c);
    }
    fclose(fp);
}

void showLine() {
    // Get name of file user wishes to read line of
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));

    // Open file
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // Check file exists
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    // Get line to print from user
    printf("Enter line number: ");
    int lineNum = getUserInt();

    // List through each character of file until desired file is reached
    int lineCount = 1; // Line currently checking
    while (1) {
        char c = (char) fgetc(fp);
        // If end of file is reached, number of lines in file is less than input
        if (c == EOF) {
            printf("File does not have this many lines");
            break;
        }

        // If end of line is reached, add to count
        if (c == '\n') {
            lineCount++;

            if (lineCount == lineNum) {
                // If current line is desired line to print
                while (1) {
                    // Continue printing characters until newline character is reached
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
    /*
     * The deleteLine() method works by creating a new file,
     * Copying every character
     * Until line to 'delete' is reached
     * In which case, do nothing
     */

    // Get name of file to delete line of
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));

    // File to delete line in

    // New file without specified line
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // Open file to delete line from and new file without said line
    FILE *fp2 = fopen("Copy.txt", "w");

    // Check first file exists
    if (fp == NULL) {
        printf("File not found\n");
        return -1;
    }

    // Line number to delete
    printf("Enter line number: ");
    int lineNum = getUserInt();

    // Line currently checking
    int lineCount = 1;
    int lineDeleted = 0;
    while (1) {
        // Get next character
        char c = (char) fgetc(fp);

        if (c == EOF) {
            if (!lineDeleted) {
                // If end of file is reached and line has not been 'deleted'
                printf("File does not have this many lines");
                remove("Copy.txt");
                return -1;
            }
            // else:
            /*
             * If end of file is reached and line HAS been deleted
             * Close both files
             * Delete first file
             * Rename second file to first
             */
            fclose(fp);
            fclose(fp2);
            remove(fileName);
            rename("Copy.txt", fileName);
            printf("Line deleted successfully\n");
            return getNumLines(fileName);
        }

        if (lineCount == lineNum) {
            /*
             * If current line is to be deleted,
             * Ignore all characters on this line
             */
            lineDeleted = 1;
        } else {
            // Put character in second file
            fputc(c, fp2);
        }

        // Increase number of lines checked
        if (c == '\n') {
            lineCount++;
        }
    }
}

void numLines() {
    // Get name of file from user
    printf("Enter name of file: ");
    char fileName[99];
    getUserInput(fileName, sizeof(fileName));

    // Open file
    FILE *fp = fopen(strcat(fileName, ".txt"), "r");

    // Check file exists
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    // Count number of '\n' characters in file
    int lineCount = 1;
    while (1) {
        char c = (char) fgetc(fp);
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            lineCount++;
        }
    }

    // Close file
    fclose(fp);

    // Output answer
    if (lineCount == 1) {
        printf("File has 1 line \n");
        return;
    }
    printf("File has %d lines \n", lineCount);
}

int renameFile() {
    // Get name of file user wishes to rename
    printf("Enter name of file: ");
    char oldName[99];
    getUserInput(oldName, sizeof(oldName));

    // Check file exists
    FILE *fp1 = fopen(strcat(oldName, ".txt"), "r");
    while (fp1 == NULL) {
        printf("File not found\n");
        fclose(fp1);
        return -1;
    }
    fclose(fp1);

    // Get new name of file
    printf("Enter new name: ");
    char newName[99];
    getUserInput(newName, sizeof(newName));

    // Check file with new name does not already exist
    FILE *fp2 = fopen(strcat(newName, ".txt"), "r");
    if (fp2 != NULL) {
        printf("File with this name already exists\n");
        fclose(fp2);
        return -1;
    }
    fclose(fp2);

    // Rename file and return number of lines
    rename(oldName, newName);
    printf("File renamed successfully\n");
    return getNumLines(newName);
}

void ls() {
    // Directory stream variable - essentially list of all entries in cwd
    DIR *dir = opendir("."); // Open current working directory

    // Check directory opened successfully
    if (dir == NULL) {
        printf("Error: directory not opened\n");
        return;
    }


    // Repeat until no more entries in directory
    while (1) {
        // Represents what type of thing is in directory (file,folder...)
        struct dirent *entry = readdir(dir); // Read next entry in directory and store in entry

        if (entry == NULL) {
            // No more entries in directory
            break;
        }

        // Check type of entry (.txt, .c, folder)
        if (entry->d_type == DT_REG) {
            // DT_REG means Regular file (not folder/ another directory)
            char fileName[99];
            sprintf(fileName, "%s", entry->d_name);

            if (!strcmp(fileName + strlen(fileName) - 4, ".txt")) {
                // If entry is a txt file (ends in .txt)

                // Print filename
                printf("%s\n", fileName);
            }
        }
    }

    if (closedir(dir) == -1) {
        printf("Error closing directory\n");
    }
}


int main(void) {
    printf("Welcome to the command-line file editor built in C!\n");
    printf("There is one rule: Always exclude the file extension when entering the name of a file.\n");
    printf("Enter one of the following options to use the program:\n\n");
    help();

    // Keep list of operations performed
    char *commandLog[100];
    int currentOp = 0;

    int lines = 0; // Number of lines following each operation, if -1, command has failed.

    while (1) {
        printf("\n\nMain Menu\n");

        // Get user choice
        printf("Enter choice: ");
        char input[99];
        getUserInput(input, sizeof(input));

        // Perform action based on user input and add action to command Log if applicable
        if (!strcmp(input, "help")) {
            help();
        } else if (!strcmp(input, "create")) {
            // Allocate enough memory in commandLog[i] to fit string
            commandLog[currentOp] = malloc(13);

            // Add string to commandLog[currentOp] and increment
            strcpy(commandLog[currentOp++], "Created File");
            create();
        } else if (!strcmp(input, "copy")) {
            lines = copy();
            if (lines >= 0) {
                // Allocate enough memory for string
                char *toAdd = malloc(36);

                // Insert number of lines into string
                snprintf(toAdd, 36, "Copied file of %d lines", lines);

                // Allocate enough memory in commandLog[i] to fit string
                commandLog[currentOp] = malloc(strlen(toAdd) + 1);

                // Add string to commandLog[currentOp] and increment
                strcpy(commandLog[currentOp++], toAdd);
                free(toAdd); // Free memory used by toAdd
            }
        } else if (!strcmp(input, "delete")) {
            if (!delete()) {
                commandLog[currentOp] = malloc(13); // Allocate enough memory in commandLog[i] to fit string
                strcpy(commandLog[currentOp++], "Deleted File"); // Add string to commandLog[currentOp] and increment
            }
        } else if (!strcmp(input, "append")) {
            lines = append();
            if (lines >= 0) {
                // Allocate enough memory for string
                char *toAdd = malloc(36);
                // Insert number of lines into string
                snprintf(toAdd, 36, "Appended line to file of %d lines", lines - 1);

                // Allocate enough memory in commandLog[i] to fit string
                commandLog[currentOp] = malloc(strlen(toAdd) + 1);

                // Add string to commandLog[currentOp] and increment
                strcpy(commandLog[currentOp++], toAdd);
                free(toAdd); // Free memory used by toAdd
            }
        } else if (!strcmp(input, "insert")) {
            lines = insert();
            if (lines > 0) {
                // Allocate enough memory for string
                char *toAdd = malloc(36);
                // Insert number of lines into string
                snprintf(toAdd, 36, "Inserted line into file of %d lines", lines - 1);

                // Allocate enough memory in commandLog[i] to fit string
                commandLog[currentOp] = malloc(strlen(toAdd) + 1);

                // Add string to commandLog[currentOp] and increment
                strcpy(commandLog[currentOp++], toAdd);
                free(toAdd); // Free memory used by toAdd
            }
        } else if (!strcmp(input, "showfile")) {
            showFile();
        } else if (!strcmp(input, "showline")) {
            showLine();
        } else if (!strcmp(input, "deleteline")) {
            lines = deleteLine();
            if (lines >= 0) {
                // Allocate enough memory for string
                char *toAdd = malloc(36);
                // Insert number of lines into string
                snprintf(toAdd, 36, "Deleted line in file of %d lines", lines + 1);

                // Allocate enough memory in commandLog[i] to fit string
                commandLog[currentOp] = malloc(strlen(toAdd) + 1);

                // Add string to commandLog[currentOp] and increment
                strcpy(commandLog[currentOp++], toAdd);
                free(toAdd); // Free memory used by toAdd
            }
        } else if (!strcmp(input, "numlines")) {
            numLines();
        } else if (!strcmp(input, "showlog")) {
            showLog(commandLog);
        } else if (!strcmp(input, "rename")) {
            lines = renameFile();
            if (lines >= 0) {
                // Allocate enough memory for string
                char *toAdd = malloc(36);
                // Insert number of lines into string
                snprintf(toAdd, 36, "Renamed file of %d lines", lines);

                // Allocate enough memory in commandLog[i] to fit string
                commandLog[currentOp] = malloc(strlen(toAdd) + 1);

                // Add string to commandLog[currentOp] and increment
                strcpy(commandLog[currentOp++], toAdd);
                free(toAdd); // Free memory used by toAdd
            }
        } else if (!strcmp(input, "ls")) {
            ls();
        } else if (!strcmp(input, "exit")) {
            printf("Bye!");
            break;
        } else {
            printf("Invalid input\n");
        }
    }
    return 0;
}
