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
static Vector vectorStorage[10];
static int vectorCount = 0;
int currentCommand = 0;
char *token;
char userInput[100];
#define MAX_VECTORS 10



char* trim(char* s) {
    if (!s) return s;
    while (isspace((unsigned char)*s)) s++;
    char *end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end)) *end-- = '\0';
    return s;
}

// Find vector index by name
int findVectorIndexByName(const char* name) {
    if (!name) return -1;
    for (int i = 0; i < vectorCount; i++)
        if (strcmp(vectorStorage[i].Name, name) == 0)
            return i;
    return -1;
}

// Vector add logic
Vector add() {
    Vector a = {0,0,0}, b = {0,0,0}, result = {0,0,0};
    int foundA = 0, foundB = 0;  // Flags to check existence

    char *first = strtok(userInput, "+");
    char *second = strtok(NULL, "+");
    if (!first || !second) return result;

    // Trim first token
    while (*first == ' ') first++;
    char *end1 = first + strlen(first) - 1;
    while (end1 > first && *end1 == ' ') *end1-- = '\0';

    // Trim second token
    while (*second == ' ') second++;
    char *end2 = second + strlen(second) - 1;
    while (end2 > second && *end2 == ' ') *end2-- = '\0';

    // Get vectors from storage
    for (int i = 0; i < vectorCount; i++) {
        if (strcmp(vectorStorage[i].Name, first) == 0) {
            a = vectorStorage[i];
            foundA = 1;
        }
        if (strcmp(vectorStorage[i].Name, second) == 0) {
            b = vectorStorage[i];
            foundB = 1;
        }
    }

    // Check if vectors exist
    if (!foundA) {
        printf("Error: vector '%s' not found.\n", first);
        return result;
    }
    if (!foundB) {
        printf("Error: vector '%s' not found.\n", second);
        return result;
    }

    // Add vectors
    result.xMag = a.xMag + b.xMag;
    result.yMag = a.yMag + b.yMag;
    result.zMag = a.zMag + b.zMag;

    // Debug print
    printf("a: %f %f %f\n", a.xMag, a.yMag, a.zMag);
    printf("b: %f %f %f\n", b.xMag, b.yMag, b.zMag);
    printf("result: %f %f %f\n", result.xMag, result.yMag, result.zMag);

    return result;
}

// Vector subtract logic
Vector subtract() {
    Vector a = {0,0,0}, b = {0,0,0}, result = {0,0,0};
    int foundA = 0, foundB = 0;  // Flags to check existence

    char *first = strtok(userInput, "-");
    char *second = strtok(NULL, "-");
    if (!first || !second) return result;

    // Trim first
    while (*first == ' ') first++;
    char *end1 = first + strlen(first) - 1;
    while (end1 > first && *end1 == ' ') *end1-- = '\0';

    // Trim second
    while (*second == ' ') second++;
    char *end2 = second + strlen(second) - 1;
    while (end2 > second && *end2 == ' ') *end2-- = '\0';

    // Get vectors from storage
    for (int i = 0; i < vectorCount; i++) {
        if (strcmp(vectorStorage[i].Name, first) == 0) {
            a = vectorStorage[i];
            foundA = 1;
        }
        if (strcmp(vectorStorage[i].Name, second) == 0) {
            b = vectorStorage[i];
            foundB = 1;
        }
    }

    // Check if vectors exist
    if (!foundA) {
        printf("Error: vector '%s' not found.\n", first);
        return result;
    }
    if (!foundB) {
        printf("Error: vector '%s' not found.\n", second);
        return result;
    }

    // Subtract vectors
    result.xMag = a.xMag - b.xMag;
    result.yMag = a.yMag - b.yMag;
    result.zMag = a.zMag - b.zMag;

    // Debug print
    printf("a: %f %f %f\n", a.xMag, a.yMag, a.zMag);
    printf("b: %f %f %f\n", b.xMag, b.yMag, b.zMag);
    printf("result (a-b): %f %f %f\n", result.xMag, result.yMag, result.zMag);

    return result;
}

// Vector multiply logic
Vector multiplyScalar() {
    Vector result = {0,0,0,""};
    Vector v = {0,0,0,""};
    int foundV = 0;  // Flag to check if vector exists

    // Token at '*'
    char *first = strtok(userInput, "*");
    char *second = strtok(NULL, "*");
    if (!first || !second) return result;

    // Trim first (vector name)
    while (*first == ' ') first++;
    char *end1 = first + strlen(first) - 1;
    while (end1 > first && *end1 == ' ') *end1-- = '\0';

    // Trim second (scalar string)
    while (*second == ' ') second++;
    char *end2 = second + strlen(second) - 1;
    while (end2 > second && *end2 == ' ') *end2-- = '\0';

    // Find vector in storage
    for (int i = 0; i < vectorCount; i++) {
        if (strcmp(vectorStorage[i].Name, first) == 0) {
            v = vectorStorage[i];
            foundV = 1;
            break;
        }
    }

    // Check if vector exists
    if (!foundV) {
        printf("Error: vector '%s' not found.\n", first);
        return result;
    }

    // Convert scalar to double
    char *endptr = NULL;
    double scalar = strtod(second, &endptr);
    if (endptr == second) {
        printf("Error: '%s' is not a valid number.\n", second);
        return result;
    }

    // Multiply vector by scalar
    result.xMag = v.xMag * scalar;
    result.yMag = v.yMag * scalar;
    result.zMag = v.zMag * scalar;

    // Copy vector name
    strcpy(result.Name, v.Name);

    // Debug
    printf("Multiplying vector '%s' by %g\n", v.Name, scalar);
    printf("v:      %f %f %f\n", v.xMag, v.yMag, v.zMag);
    printf("result: %f %f %f\n", result.xMag, result.yMag, result.zMag);

    return result;
}
  

// Display vector logic
void displayVector(int columns){
    printf("\n%-10s %-10s %-10s %-10s\n", "Name", "X", "Y", "Z");
    printf("-----------------------------------------\n");

    for (int i = 0; i < MAX_VECTORS; i++){
         printf("%-10s %-10.2f %-10.2f %-10.2f\n",
               vectorStorage[i].Name,
               vectorStorage[i].xMag,
               vectorStorage[i].yMag,
               vectorStorage[i].zMag);
    }
     printf("-----------------------------------------\n\n");
}


// Clear array logic
void clearArray(){
    for (int i = 0; i < 10; i++) {
        vectorStorage[i].xMag = 0.0;
        vectorStorage[i].yMag = 0.0;
        vectorStorage[i].zMag = 0.0;
        strcpy(vectorStorage[i].Name, "");   // Copy string to array
    }
    vectorCount = 0; // Reset count
    printf("All stored vectors have been cleared.\n");
}

// Add vector to storage
void newVector() {
    double x = 0.0, y = 0.0, z = 0.0;

    // Remove newline
    userInput[strcspn(userInput, "\n")] = '\0';

    // Split into name and values
    char *name = strtok(userInput, "=");
    char *values = strtok(NULL, "=");
    if (!name || !values) return;

    // Trim name
    while (*name == ' ') name++;
    char *end = name + strlen(name) - 1;
    while (end > name && *end == ' ') *end-- = '\0';

    // Parse x, y, z values (spaces or commas)
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

    x = vals[0];
    y = vals[1];
    z = vals[2];

    // Store vector
    Vector v;
    v.xMag = x;
    v.yMag = y;
    v.zMag = z;
    strcpy(v.Name, name);

    if (vectorCount < MAX_VECTORS) {
        vectorStorage[vectorCount++] = v;
        printf("Stored vector '%s': %.2f %.2f %.2f\n", v.Name, v.xMag, v.yMag, v.zMag);
    } else {
        printf("Vector storage full!\n");
    }
}

void parseTest() {
    printf("Minimat> ");
    fgets(userInput, 100, stdin);
    userInput[strcspn(userInput, "\n")] = '\0';
    if (strchr(userInput, '=') && (strchr(userInput, '+') || strchr(userInput, '-') || strchr(userInput, '*'))) {
    char *lhs = trim(strtok(userInput, "="));  // Right hand side 
    char *rhs = trim(strtok(NULL, ""));        // Left hand side
    if (!lhs || !rhs) return;

    strcpy(userInput, rhs); 
    Vector res = strchr(rhs,'+') ? add() : strchr(rhs,'-') ? subtract() : multiplyScalar();
    strcpy(res.Name, lhs);

    int idx = findVectorIndexByName(lhs);
    if (idx >= 0) vectorStorage[idx] = res;
    else if (vectorCount < MAX_VECTORS) vectorStorage[vectorCount++] = res;
    else { printf("No space for result vector!\n"); return; }

    printf("Result '%s': x=%.2f y=%.2f z=%.2f\n", res.Name, res.xMag, res.yMag, res.zMag);
    return;
}

    if (strchr(userInput, '=') != NULL) {
        currentCommand = 1;
    }
    // handle addition
    if (strchr(userInput, '+') != NULL) {
        currentCommand = 2;
    }
    // handle subtraction
    if (strchr(userInput, '-') != NULL) {
        currentCommand = 3;
    }
    // handle multiplication
    if (strchr(userInput, '*') != NULL) {
        currentCommand = 4;
    }
    // handle clear
    if (strcmp(userInput, "clear") == 0) {
        printf("Clearing all variables...\n");
        currentCommand = 6;
    }
    // handle display
    if (strcmp(userInput,"display") == 0){
        printf("Listing all vectors in storage...\n");
        currentCommand = 5;
    }
    // handle quit
    if (strcmp(userInput, "quit") == 0) {
    printf("Quitting program...\n");
    currentCommand = 7;
}
}


void printHelp() {
    printf("Lab 4 Vector Program Help\n");
    printf("========================\n");
    printf("Usage: ./lab5main [-h]\n");
    printf("Options:\n");
    printf("  -h    Show this help screen\n\n");
    printf("Program Commands:\n");
    printf("1)  (a = x y z): Assign X,Y,Z values to vector a\n");
    printf("2)  (a + b): Add a and b\n");
    printf("3)  (a - b): Subtract a from b\n");
    printf("4)  (a * scalar): Multiply vector by scalar\n");
    printf("5)  (a = b + c): Assign return value to given vector\n");
    printf("6)  (a): Display values for given vector\n");
    printf("7)  (list): List all vectors in storage\n");
    printf("8)  (clear): Clear all vectors in storage\n");
    printf("9)  (quit): Quit program\n");
}

// Quit function
void quitProgram(){
    exit(0);
}