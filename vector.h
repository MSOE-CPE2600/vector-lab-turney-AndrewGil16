
/**
 * Author: Andrew Gilpatrick
 * Assignment: Lab 7
 * Date: 10/27/2025
 * vector.h
 */

#ifndef VECTOR_H
#define VECTOR_H     
#include <stdio.h>

typedef struct {
    double xMag; 
    double yMag;
    double zMag; 
    char Name[20];
} Vector;

//dynamic storage
extern Vector *vectorStorage;
extern int vectorCount;
extern int vectorCapacity;

//memory management
void expandVectorStorage(void);
void clearArray(void);     
void cleanupMemory(void);
void quitProgram(void);

//CSV I/O
int loadVectorsFromCSV(const char *filename);
int saveVectorsToCSV(const char *filename);


int getCommandCode(void);
void printHelp(void);
extern int currentCommand;
extern int running;
void newVector(void);
void entryPoint(void);
void helpFunction(void);
void parseTest(void);
extern char charNames[100];
extern char userInput[100];


Vector add(const char *expr);
Vector subtract(const char *expr);
Vector multiplyScalar(const char *expr);

// Display
void displayVector(void);

#endif 
