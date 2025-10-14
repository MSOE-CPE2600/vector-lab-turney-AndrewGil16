/**
 * Author: Andrew Gilpatrick
 * Assignment: Lab 4
 * Date: 09/30/2025
 * lab5main.c
 * Compile: make sss
 */
#include <stdio.h>
#include "vector.h"
#include <string.h>
int main (int argc, char *argv[]){
 // Check for help flag
 for (int i = 1; i < argc; i++) {
 if (strcmp(argv[i], "-h") == 0) {
 printHelp();
 return 0; // exit after printing help
 }
 }
 int running = 1;
 // main loop
 while(running){
 parseTest();
 switch(currentCommand){
 case 1:
 newVector();
 break;
 case 2:
 add();
 break;
 case 3:
 subtract();
 break;
 case 4:
 multiplyScalar();
 break;
 case 5:
 displayVector();
 break;
 case 6:
 clearArray();
 break;
 case 7:
 quitProgram();
 }
 }

}