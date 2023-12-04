// COMP2521 Assignment 1

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertedIndex.h"

#define MAX_CHARS 100

/**
 * Initialising a new BST.
 */
InvertedIndexBST BSTNewTree();

/**
 * Initialising a new BST node with the given word
 */
InvertedIndexBST BSTNewNode(char *word_str);

/**
 * Insert a new tree into a Tree t with the normalised word
 */
InvertedIndexBST BSTTreeInsert(InvertedIndexBST tree, char *filename_str, char *normalised_word);

/**
 * Initialising a new FileList
 */
FileList FileListNew();

/**
 * Initialising a new FileList node with the given filename and normalised word
 */
FileList FileNewNode(char *filename_str, char *normalised_word);

/**
 * Insert a new filelist into filelist with the given filename. 
 */
FileList FileListInsert(FileList fl, char *filename_str, char *normalised_word);

/**
 * Calculates the value of Tf with the filename and normalised word. 
 */
double calculateTf(char *filename_str, char *word_check);

/**
 * Normalise the word with the given word
 */
char *normalise(char *word_str);

/**
 * Prints the tree's words and it's files via recursion into file_output's stream.
 */
void doPrintTreeRecursive(FILE *file_output, InvertedIndexBST tree);

/**
 * Frees list
 */
void freeList(FileList fl);