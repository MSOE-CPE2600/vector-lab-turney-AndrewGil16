
/**
 * Author: Andrew Gilpatrick
 * Assignment: Lab 7
 * Date: 10/27/2025
 * lab5main.c
 * Compile: gcc -o lab5main lab5main.c lab5controller.c gptcontroller.c
 */
#include <stdio.h>
#include <string.h>
#include "vector.h"

int main (int argc, char *argv[]){
    // Help flag
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        }
    }

    printf("\nVector Calculator - Lab 5 (dynamic + CSV)\n");
    printf("Type '-h' for help. Commands: display, load <file>, save <file>, clear, quit\n\n");

    while (running) {
        parseTest();
    }

    cleanupMemory();
    return 0;
}
