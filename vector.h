/**
 * Author: Andrew Gilpatrick
 * Assignment: Lab 4
 * Date: 09/30/2025
 * vector.h
 */



#ifndef VECTOR_H
#define VECTOR_H
typedef struct {
    double xMag; //X Val
    double yMag; //Y Val
    double zMag; //Z Val
    char Name[20];
} Vector;

// storage
extern Vector *vectorStorage;
extern int vectorCount;
extern int vectorCapacity;


// memory management
void expandVectorStorage(void);
void clearArray(void);
void quitProgram(void):

//csv
int loadVectorsFromCSV(const char *filename);
int saveVectorsToCSV(const char *filename);

// lab 5 functions
int getCommandCode();
void printHelp();
extern int currentCommand;
extern int running;
void newVector();
void entryPoint();
void helpFunction();
void parseTest();
extern char charNames[100];
extern char userInput[100];

//Vector vectorList[10]; // Vector Storage Array
void displayVector(); //display specific vector if possible
void clearArray(); // Clear the vector storage array
void quitProgram(); // Quit the calculator program
Vector add(); // Vector add
Vector subtract(); // Vector subtract
Vector multiplyScalar(); // Vector multiply

#endif