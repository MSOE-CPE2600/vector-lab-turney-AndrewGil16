# Vector Calculator

## This is a C program that allows users to do vector calculations as well as "store" vectors and load/save CSV files with vectors. Also has functions for polar and rectangular form.


## Features
- Add, Subtract, Multiply, Divide vectors
- Load/Save vectors with CSV files
- Convert vectors from rectangular and polar forms
- Store vectors using MALLOC

## Project Structure
|-- Vector Lab

|---- lab5controller.c

|---- lab5main.c

|---- vector.h

|---- Makefile

## Commands
- a = x y z           -> define vector a
- a = a + b           -> add vectors
- a = a - b           -> subtract vectors
- a = a * scalar      -> multiply by scalar
- display             -> list all vectors
- load <file.csv>     -> load vectors from CSV (Name,x,y,z)
- <file.csv>    -> save vectors to CSV
- clear         -> clear all vectors
- quit          -> exit program

## Build Commands
- -h to display the help screen


## Dynamic Memory
- v2 uses malloc to allocate memory as you create/remove vectors rather than have a fixed size array




## Installation/Setup
1.  git clone https://github.com/MSOE-CPE2600/vector-lab-turney-AndrewGil16
2.  run make command
3. ./lab5


## Author
Andrew Gilpatrick
gilpatricka@msoe.edu
