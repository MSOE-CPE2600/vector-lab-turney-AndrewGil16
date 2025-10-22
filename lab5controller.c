/**
 * Author: Andrew Gilpatrick
 * Assignment: Lab 4
 * Date: 09/30/2025
 * lab5controller.c
 * Compile: make
 */
#include <stdio.h>
#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
Vector *vectorStorage = NULL;
int vectorCount = 0;
int vectorCapacity = 0;


//memory management
void expandVectorStorage(void){
    int newCap = (vectorCapacity == 0) ? 4 : vectorCapacity * 2;
    Vector *temp = realloc(vectorStorage, newCap * sizeof(Vector));
    if(!temp){
        printf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    vectorStorage = temp;
    vectorCapacity = newCap;
}

void clearArray(void){
    free(vectorStorage);
    vectorStorage = NULL;
    vectorCount = 0;
    vectorCapacity = 0;
}

void cleanupMemory(void){
    clearArray();
}

void quitProgram(void){
    cleanupMemory();
    exit(0);
}
int currentCommand = 0;
int running = 1;
char userInput[100];
char charNames[100];


//helpers
static char* trim(char* s) {
    if (!s) return s;
    while (isspace((unsigned char)*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

static int findVectorIndexByName(const char* name) {
    if (!name) return -1;
    for (int i = 0; i < vectorCount; i++)
    if (strcmp(vectorStorage[i].Name, name) == 0)
    return i;
    return -1;
}


// Vector Operations
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
        if (!foundA && strcmp(vectorStorage.[i].Name, first == 0) {
        a = vectorStorage[i]; foundA = 1;
        }
    if (!foundB && strcmp(vectorStorage.[i].Name, second) == 0) {
        b = vectorStorage[i]; foundB = 1;
        }
    }
    if (!foundA || !foundB) return result;
    result.xMag = a.xMag + b.xMag;
    result.yMag = a.yMag + b.yMag;
    result.zMag = a.zMag + b.zMag;
    return result;
}
Vector subtract(const char *expr) {
    Vector a = {0}, b = {0}, result = {0};
    char buffer[128 ];
    strncpy(buffer, expr, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';
    char *first = strtok(buffer, "-");
    char *second = strtok(NULL, "-");
    if (!first || !second) return result;
    first = trim(first);
    second = trim(second);
    int foundA = 0, foundB = 0;

    for (int i = 0; i < vectorCount; i++) {
        if (!foundA && strcmp(vectorStorage.[i].Name, first == 0) {
        a = vectorStorage[i]; foundA = 1;
        }
    if (!foundB && strcmp(vectorStorage.[i].Name, second) == 0) {
        b = vectorStorage[i]; foundB = 1;
        }
    }
    if (!foundA || !foundB) return result;
    result.xMag = a.xMag - b.xMag;
    result.yMag = a.yMag - b.yMag;
    result.zMag = a.zMag - b.zMag;
    return result;
}


Vector multiplyScalar(const char *expr) {
    Vector v = {0}, result = {0};
    char buffer[100];
    strncpy(buffer, expr, sizeof(buffer));
    buffer[sizeof(buffer)-1] = '\0';
    char *first = strtok(buffer, "*");
    char *second = strtok(NULL, "*");
    if (!first || !second) return result;
    first = trim(first);
    second = trim(second);
    int found = 0;
    for (int i = 0; i < vectorCount; i++) {
    if (strcmp(vectorStorage[i].Name, first) == 0) {
        v = vectorStorage[i];
        found = 1;
        break;
        }
    }
    if (!found) return result;
    double scalar = atof(second);
    result.xMag = v.xMag * scalar;
    result.yMag = v.yMag * scalar;
    result.zMag = v.zMag * scalar;
    return result;
}
// Vector display
void displayVector(){
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



void clearArray(){
    for (int i = 0; i < MAX_VECTORS; i++) {
    vectorStorage[i].xMag = 0.0;
    vectorStorage[i].yMag = 0.0;
    vectorStorage[i].zMag = 0.0;
    strcpy(vectorStorage[i].Name, "");
    }
    vectorCount = 0;
    printf("All stored vectors have been cleared!!.\n");
}
void newVector() {
    userInput[strcspn(userInput, "\n")] = '\0';
    char *name = strtok(userInput, "=");
    char *values = strtok(NULL, "=");
    if (!name || !values) return;

    name = trim(name);
    values = trim(values);
    double vals[3];
    int count = 0;
    char *tok = strtok(values, " ,");
    while (tok && count < 3) {
    vals[count++] = atof(tok);
    tok = strtok(NULL, " ,");
    }

    if (count != 3) {
    printf("Error: provide 3 numeric values for the vector.\n");
    return;
    }

    Vector v = {vals[0], vals[1], vals[2], ""};
    strcpy(v.Name, name);
    int idx = findVectorIndexByName(name);
    if (idx >= 0) vectorStorage[idx] = v;
    else if (vectorCount < MAX_VECTORS) vectorStorage[vectorCount++] = v;
    else printf("Vector storage full!\n");
    printf("Stored vector '%s': %.2f %.2f %.2f\n", v.Name, v.xMag, v.yMag, v.zMag);
}

// Command Parsing
void parseTest() {
    printf("Minimat> ");
    fgets(userInput, 100, stdin);
    userInput[strcspn(userInput, "\n")] = '\0';
    char *input = trim(userInput);
// Assignment
if (strchr(input, '=') && (strchr(input, '+') || strchr(input, '-') || strchr(input, '*'))) {
    char *lhs = trim(strtok(input, "="));
    char *rhs = trim(strtok(NULL, ""));
    if (!lhs || !rhs) return;
    Vector res;
    if (strchr(rhs, '+')) res = add(rhs);
    else if (strchr(rhs, '-')) res = subtract(rhs);
    else res = multiplyScalar(rhs);
    strcpy(res.Name, lhs);
    int idx = findVectorIndexByName(lhs);
    if (idx >= 0) vectorStorage[idx] = res;
    else if (vectorCount < MAX_VECTORS) vectorStorage[vectorCount++] = res;
    printf("Result '%s': x=%.2f y=%.2f z=%.2f\n",
    res.Name, res.xMag, res.yMag, res.zMag);
    return;
 }

 // Direct operations
    if (strchr(input, '+') || strchr(input, '-') || strchr(input, '*')) {
    Vector res;
    if (strchr(input, '+')) res = add(input);
    else if (strchr(input, '-')) res = subtract(input);
    else res = multiplyScalar(input);
    printf("Result: x=%.2f y=%.2f z=%.2f\n",
    res.xMag, res.yMag, res.zMag);
    return;
}
// Display single vector
if (strlen(input) == 1 && isalpha(input[0])) {
    int idx = findVectorIndexByName(input);
    if (idx >= 0) {
        Vector v = vectorStorage[idx];
        printf("%s = (%.2f, %.2f, %.2f)\n",
        v.Name, v.xMag, v.yMag, v.zMag);
    } else {
    printf("Error: vector '%s' not found.\n", input);
    }
    return;
}
// Display all, clear, quit, or define new
if (strcmp(input, "display") == 0) {
    displayVector(0);
} else if (strcmp(input, "clear") == 0) {
    clearArray();
} else if (strcmp(input, "quit") == 0) {
    printf("Quitting program...\n");
    exit(0);
} else if (strchr(input, '=') != NULL) {
    newVector(); // a = 1 2 3
} else if (strlen(input) > 0) {
    printf("Error: unrecognized command '%s'\n", input);
}
}
// Help and Quit
void printHelp() {
    printf("Lab 4 Vector Program Help\n");
    printf("========================\n");
    printf("Usage: ./lab5main [-h]\n");
    printf("Commands:\n");
    printf(" a = x y z → define vector a\n");
    printf(" a = a + b → add vectors\n");
    printf(" a = a - b → subtract vectors\n");
    printf(" a = a * scalar → multiply by scalar\n");
    printf(" display → list all vectors\n");
    printf(" clear → clear all\n");
    printf(" quit → exit program\n");
}
