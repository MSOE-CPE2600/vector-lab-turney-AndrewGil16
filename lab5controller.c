
/**
 * Author: Andrew Gilpatrick
 * Assignment: Lab 7
 * Date: 10/27/2025
 * lab5controller.c
 * Compile: make
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vector.h"


Vector *vectorStorage = NULL;
int vectorCount = 0;
int vectorCapacity = 0;

// ================= Memory Management =================
void expandVectorStorage(void) {
    int newCap = (vectorCapacity == 0) ? 4 : vectorCapacity * 2;
    Vector *temp = realloc(vectorStorage, newCap * sizeof(Vector));
    if (!temp) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    vectorStorage = temp;
    vectorCapacity = newCap;
}

void clearArray(void) {
    free(vectorStorage);
    vectorStorage = NULL;
    vectorCount = 0;
    vectorCapacity = 0;
}

void cleanupMemory(void) {
    clearArray();
}

void quitProgram(void) {
    cleanupMemory();
    exit(0);
}
int currentCommand = 0;
int running = 1;
char userInput[100];
char charNames[100]; 

//Helpers
static char* trim(char* s) {
    if (!s) return s;
    while (isspace((unsigned char)*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end >= s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

static int findVectorIndexByName(const char* name) {
    if (!name) return -1;
    for (int i = 0; i < vectorCount; i++) {
        if (strcmp(vectorStorage[i].Name, name) == 0) return i;
    }
    return -1;
}

//operations
Vector add(const char *expr) {
    Vector a = {0}, b = {0}, result = {0};
    char buffer[128];
    strncpy(buffer, expr, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';
    char *first = strtok(buffer, "+");
    char *second = strtok(NULL, "+");
    if (!first || !second) return result;
    first = trim(first);
    second = trim(second);

    int foundA = 0, foundB = 0;
    for (int i = 0; i < vectorCount; i++) {
        if (!foundA && strcmp(vectorStorage[i].Name, first) == 0) { a = vectorStorage[i]; foundA = 1; }
        if (!foundB && strcmp(vectorStorage[i].Name, second) == 0) { b = vectorStorage[i]; foundB = 1; }
    }
    if (!foundA || !foundB) return result;
    result.xMag = a.xMag + b.xMag;
    result.yMag = a.yMag + b.yMag;
    result.zMag = a.zMag + b.zMag;
    return result;
}

Vector subtract(const char *expr) {
    Vector a = {0}, b = {0}, result = {0};
    char buffer[128];
    strncpy(buffer, expr, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';
    char *first = strtok(buffer, "-");
    char *second = strtok(NULL, "-");
    if (!first || !second) return result;
    first = trim(first);
    second = trim(second);

    int foundA = 0, foundB = 0;
    for (int i = 0; i < vectorCount; i++) {
        if (!foundA && strcmp(vectorStorage[i].Name, first) == 0) { a = vectorStorage[i]; foundA = 1; }
        if (!foundB && strcmp(vectorStorage[i].Name, second) == 0) { b = vectorStorage[i]; foundB = 1; }
    }
    if (!foundA || !foundB) return result;
    result.xMag = a.xMag - b.xMag;
    result.yMag = a.yMag - b.yMag;
    result.zMag = a.zMag - b.zMag;
    return result;
}

Vector multiplyScalar(const char *expr) {
    Vector v = {0}, result = {0};
    char buffer[128];
    strncpy(buffer, expr, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';
    char *first = strtok(buffer, "*");
    char *second = strtok(NULL, "*");
    if (!first || !second) return result;
    first = trim(first);
    second = trim(second);

    int found = 0;
    for (int i = 0; i < vectorCount; i++) {
        if (strcmp(vectorStorage[i].Name, first) == 0) { v = vectorStorage[i]; found = 1; break; }
    }
    if (!found) return result;
    double scalar = atof(second);
    result.xMag = v.xMag * scalar;
    result.yMag = v.yMag * scalar;
    result.zMag = v.zMag * scalar;
    return result;
}

// display and storage
void displayVector(void){
    printf("\n%-10s %-10s %-10s %-10s\n", "Name", "X", "Y", "Z");
    printf("-----------------------------------------\n");
    for (int i = 0; i < vectorCount; i++) {
        printf("%-10s %-10.2f %-10.2f %-10.2f\n",
               vectorStorage[i].Name,
               vectorStorage[i].xMag,
               vectorStorage[i].yMag,
               vectorStorage[i].zMag);
    }
    printf("-----------------------------------------\n\n");
}

void newVector(void) {
    userInput[strcspn(userInput, "\n")] = '\0';
    char *name = trim(strtok(userInput, "="));
    char *values = trim(strtok(NULL, ""));
    if (!name || !values) { printf("Error: format is a = x y z\n"); return; }

    double vals[3];
    int count = 0;
    for (char *tok = strtok(values, " ,"); tok && count < 3; tok = strtok(NULL, " ,")) {
        vals[count++] = atof(tok);
    }
    if (count != 3) { printf("Error: provide 3 numeric values for the vector.\n"); return; }

    Vector v = { .xMag=vals[0], .yMag=vals[1], .zMag=vals[2] };
    strncpy(v.Name, name, sizeof(v.Name)-1);
    v.Name[sizeof(v.Name)-1] = '\0';

    int idx = findVectorIndexByName(v.Name);
    if (idx >= 0) {
        vectorStorage[idx] = v;
    } else {
        if (vectorCount >= vectorCapacity) expandVectorStorage();
        vectorStorage[vectorCount++] = v;
    }
    printf("Stored vector '%s': %.2f %.2f %.2f\n", v.Name, v.xMag, v.yMag, v.zMag);
}

//parse and commands
void parseTest(void) {
    printf("Minimat> ");
    if (!fgets(userInput, sizeof(userInput), stdin)) {
        puts("Input error; quitting.");
        quitProgram();
        return;
    }
    userInput[strcspn(userInput, "\n")] = '\0';
    char *input = trim(userInput);

    //CSV commands
    if (strncmp(input, "load ", 5) == 0) {
        const char *fn = trim(input + 5);
        if (fn[0] == '\0') { puts("Usage: load <file.csv>"); return; }
        //clear current storage before loading
        clearArray();
        int rc = loadVectorsFromCSV(fn);
        if (rc == 0) displayVector();
        return;
    }
    if (strncmp(input, "save ", 5) == 0) {
        const char *fn = trim(input + 5);
        if (fn[0] == '\0') { puts("Usage: save <file.csv>"); return; }
        saveVectorsToCSV(fn);
        return;
    }

    //assignment
    if (strchr(input, '=') && (strchr(input, '+') || strchr(input, '-') || strchr(input, '*'))) {
        char *lhs = trim(strtok(input, "="));
        char *rhs = trim(strtok(NULL, ""));
        if (!lhs || !rhs) return;
        Vector res = {0};
        if (strchr(rhs, '+')) res = add(rhs);
        else if (strchr(rhs, '-')) res = subtract(rhs);
        else                      res = multiplyScalar(rhs);
        strncpy(res.Name, lhs, sizeof(res.Name)-1);
        res.Name[sizeof(res.Name)-1] = '\0';

        int idx = findVectorIndexByName(res.Name);
        if (idx >= 0) vectorStorage[idx] = res;
        else {
            if (vectorCount >= vectorCapacity) expandVectorStorage();
            vectorStorage[vectorCount++] = res;
        }
        printf("Result '%s': x=%.2f y=%.2f z=%.2f\n", res.Name, res.xMag, res.yMag, res.zMag);
        return;
    }

    //direct operations
    if (strchr(input, '+') || strchr(input, '-') || strchr(input, '*')) {
        Vector res = {0};
        if (strchr(input, '+')) res = add(input);
        else if (strchr(input, '-')) res = subtract(input);
        else                         res = multiplyScalar(input);
        printf("Result: x=%.2f y=%.2f z=%.2f\n", res.xMag, res.yMag, res.zMag);
        return;
    }

    //display single vector by name
    if (strlen(input) == 1 && isalpha((unsigned char)input[0])) {
        int idx = findVectorIndexByName(input);
        if (idx >= 0) {
            Vector v = vectorStorage[idx];
            printf("%s = (%.2f, %.2f, %.2f)\n", v.Name, v.xMag, v.yMag, v.zMag);
        } else {
            printf("Error: vector '%s' not found.\n", input);
        }
        return;
    }

    // Display all, clear, quit, or define new
    if (strcmp(input, "display") == 0) {
        displayVector();
    } else if (strcmp(input, "clear") == 0) {
        clearArray();
    } else if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
        printf("Quitting program...\n");
        quitProgram();
    } else if (strchr(input, '=') != NULL) {
        // define vector: a = 1 2 3
        newVector();
    } else if (strlen(input) > 0) {
        printf("Error: unrecognized command '%s'\n", input);
    }
}

//CSV I/O
int loadVectorsFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    clearArray(); //start fresh
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '\n' || line[0] == '#') continue;

        Vector v;
        memset(&v, 0, sizeof(v));

        if (sscanf(line, " %19[^,],%lf,%lf,%lf",
                   v.Name, &v.xMag, &v.yMag, &v.zMag) == 4) {
            if (vectorCount >= vectorCapacity) expandVectorStorage();
            vectorStorage[vectorCount++] = v;
        }
    }

    fclose(file);
    printf("Loaded %d vectors from %s\n", vectorCount, filename);
    return 0;
}

int saveVectorsToCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    fprintf(file, "Name,x,y,z\n");
    for (int i = 0; i < vectorCount; i++) {
        fprintf(file, "%s,%.6f,%.6f,%.6f\n",
                vectorStorage[i].Name,
                vectorStorage[i].xMag,
                vectorStorage[i].yMag,
                vectorStorage[i].zMag);
    }

    fclose(file);
    printf("Saved %d vectors to %s\n", vectorCount, filename);
    return 0;
}

//Help
void printHelp(void) {
    printf("Lab Vector Program Help\n");
    printf("=======================\n");
    printf("Usage: ./lab5main [-h]\n");
    printf("Commands:\n");
    printf(" a = x y z           -> define vector a\n");
    printf(" a = a + b           -> add vectors\n");
    printf(" a = a - b           -> subtract vectors\n");
    printf(" a = a * scalar      -> multiply by scalar\n");
    printf(" display             -> list all vectors\n");
    printf(" load <file.csv>     -> load vectors from CSV (Name,x,y,z)\n");
    printf(" save <file.csv>     -> save vectors to CSV\n");
    printf(" clear               -> clear all vectors\n");
    printf(" quit/exit           -> exit program\n");
}
