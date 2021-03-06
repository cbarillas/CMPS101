/*
 * Carlos Barillas - cbarilla@ucsc.edu
 * CMPS101 - PA2 - Lex.c
 *
 * Takes two command line arguments. Input file can be any text file, output 
 * file will be the input arranged in alphabetical order. Uses Insertion Sort
 * to indirectly sort the array by building a List of indices in a certain order.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 256

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  int numLines = 0;
  char line[MAX_LEN];

  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");

  // Counts number of lines in input files
  while (fgets(line, MAX_LEN, in ) != NULL) {
    numLines++;
  }

  // Reset file pointer to start of file
  rewind(in);

  // Places the strings in file into an array
  int n = 0;
  char *array[numLines];
  for (int index = 0; index <= numLines; index++) {
    array[index] = calloc(1, sizeof(char *[MAX_LEN]) );
  }
  while (fgets(line, MAX_LEN, in) != NULL) {
    strcpy(array[n], line );
    n++;
  }

  // Insertion sort algorithm
  List myList = newList();  
  append(myList, 0);
  for (int i = 0; i < numLines - 1; i++) {
    moveFront(myList);
    for (int j = -i; j < 1; j++) {
      if (strcmp(array[get(myList)], array[i + 1]) > 0) {
        insertBefore(myList, i + 1);
        j = 1;
      } 
      else if (index(myList) == length(myList) - 1) {
        append(myList, i + 1);
        j = 1;
      } else
        moveNext(myList);
    }
  }

  // Print list to output file
  moveFront(myList);
  while (index(myList) != -1) {
    fprintf(out, "%s", array[get(myList)]);
    moveNext(myList);
  }

  fclose(in);
  fclose(out);

  // Free memory
  int m = 0;
  while (m <= numLines) {
    free(array[m]);
    m++;
  }
  freeList(&myList);
}
