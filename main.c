#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LEN 256

// Array to hold lines of text
char *document[MAX_LINES];
int total_lines = 0;
void display_document() {
    if (total_lines == 0) {
        printf("\n[ Document is empty ]\n");
        return;
    }
    printf("\n--- Document Start ---\n");
    for (int i = 0; i < total_lines; i++) {
        // i + 1 converts 0-indexed array to 1-indexed user line numbers
        printf("%d: %s", i + 1, document[i]);
    }
    printf("--- Document End ---\n");
}
void insert_line(int pos, const char *text) {
    // Check for valid line number
    if (pos < 1 || pos > total_lines + 1 || total_lines >= MAX_LINES) {
        printf("Error: Invalid line number!\n");
        return;
    }

    int index = pos - 1; // Convert to array index

    // Shift existing lines down to make room
    for (int i = total_lines; i > index; i--) {
        document[i] = document[i - 1];
    }

    // Allocate memory for the new line and copy text
    document[index] = strdup(text);
    total_lines++;
    printf("Line inserted successfully.\n");
}
void delete_line(int pos) {
    if (pos < 1 || pos > total_lines) {
        printf("Error: Line number %d does not exist!\n", pos);
        return;
    }

    int index = pos - 1; // Convert to array index

    // Free allocated memory for the deleted line
    free(document[index]);

    // Shift lines below it UP
    for (int i = index; i < total_lines - 1; i++) {
        document[i] = document[i + 1];
    }

    total_lines--;
    printf("Line %d deleted.\n", pos);
}
void save_document(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < total_lines; i++) {
        fputs(document[i], fp);
    }
    fclose(fp);
    printf("Document saved to %s successfully.\n", filename);
}

void load_document(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found or couldn't be opened.\n");
        return;
    }
    // Clear current document
    for (int i = 0; i < total_lines; i++) {
        free(document[i]);
    }
    total_lines = 0;

    char line_buf[MAX_LEN];
    while (fgets(line_buf, sizeof(line_buf), fp) && total_lines < MAX_LINES) {
        document[total_lines++] = strdup(line_buf);
    }
    fclose(fp);
    printf("Document loaded from %s successfully.\n", filename);
}
int main() {
    char input[MAX_LEN];

    printf("--- Welcome to C Line Editor ---\n");
    printf("Commands:\n");
    printf("  P              - Print document\n");
    printf("  I <line> <text>- Insert text at line\n");
    printf("  D <line>       - Delete line\n");
    printf("  Q              - Quit\n");

    while (1) {
        printf("\nEditor > ");
        if (!fgets(input, sizeof(input), stdin)) break;

        // Command: Print
        if (input[0] == 'P' || input[0] == 'p') {
            display_document();
        } 
        // Command: Insert
        else if (input[0] == 'I' || input[0] == 'i') {
            int line_num;
            char text[MAX_LEN];
            if (sscanf(input + 1, "%d %[^\n]", &line_num, text) == 2) {
                strcat(text, "\n"); // Add newline character
                insert_line(line_num, text);
            } else {
                printf("Usage: I <line_number> <text>\n");
            }
        } 
        // Command: Delete
        else if (input[0] == 'D' || input[0] == 'd') {
            int line_num;
            if (sscanf(input + 1, "%d", &line_num) == 1) {
                delete_line(line_num);
            } else {
                printf("Usage: D <line_number>\n");
            }
        } 
        // Command: Quit
        else if (input[0] == 'Q' || input[0] == 'q') {
            printf("Exiting editor...\n");
            break;
        } 
        // Command: Save
else if (input[0] == 'S' || input[0] == 's') {
    char filename[100];
    if (sscanf(input + 1, "%s", filename) == 1) {
        save_document(filename);
    } else {
        printf("Usage: S <filename.txt>\n");
    }
}
// Command: Load
else if (input[0] == 'L' || input[0] == 'l') {
    char filename[100];
    if (sscanf(input + 1, "%s", filename) == 1) {
        load_document(filename);
    } else {
        printf("Usage: L <filename.txt>\n");
    }
}
        else {
            printf("Unknown command! Use P, I, D, or Q.\n");
        }
    }

    // Clean up allocated memory before exiting
    for (int i = 0; i < total_lines; i++) {
        free(document[i]);
    }

    return 0;
}