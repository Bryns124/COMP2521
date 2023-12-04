// COMP2521 Assignment 1

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "invertedIndex.h"
#include "helperfunctions.h"

// Part 1
/**
 * This function opens the collection file with the given name, and then
 * generates  an  inverted index from the files listed in the collection
 * file. It returns the generated inverted index.
 */
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
	InvertedIndexBST treeRoot = BSTNewTree();
	FILE *file_input = fopen(collectionFilename, "r");

	if (file_input == NULL) {
		fprintf(stderr, "error: failed to open %s.\n", collectionFilename);
		exit(EXIT_FAILURE);
	}
	char filename[MAX_CHARS + 1];
	while (fscanf(file_input, "%s", filename) == 1) {
		FILE *word_in_file_input = fopen(filename, "r");
		if (word_in_file_input == NULL) {
			fprintf(stderr, "error: failed to open %s.\n", filename);
			exit(EXIT_FAILURE);
		}
		char word[MAX_CHARS + 1];
		while (fscanf(word_in_file_input, "%s", word) == 1) {
			// If normalise returns a NULL terminator, move to next iteration.
			char *normalisedWord = normalise(word);
			if (normalisedWord[0] == '\0') {
				continue;
			}
			treeRoot = BSTTreeInsert(treeRoot, filename, normalisedWord);
		}
		fclose(word_in_file_input);
	}
	fclose(file_input);
	return treeRoot;
}


/**
 * Prints an inverted index to a file with the given name.
 */
void printInvertedIndex(InvertedIndexBST tree, char *filename) {
	if (tree == NULL) {
		return;
	}
	
	FILE *file_output = fopen(filename, "w");
	if (file_output == NULL) {
		fprintf(stderr, "error: failed to open %s.\n", filename);
		exit(EXIT_FAILURE);
	}
	// Need this function because recursive printInvertedIndex would
	// constantly fopen in "w" and overwrite the words in collection.
	doPrintTreeRecursive(file_output, tree);
	fclose(file_output);
	freeInvertedIndex(tree);
}


/**
 * Frees all memory associated with the given inverted index.
 */
void freeInvertedIndex(InvertedIndexBST tree) {
	if (tree == NULL) {
		return;
	freeInvertedIndex(tree->left);
	freeList(tree->fileList);
	freeInvertedIndex(tree->right);
	free(tree);
	}
}

// Part 2


/**
 * Returns  an  ordered list where each node contains a filename and the
 * corresponding tf-idf value for a given searchWord. You only  need  to
 * include documents (files) that contain the given searchWord. The list
 * must  be  in  descending order of tf-idf value. If there are multiple
 * files with same  tf-idf  value,  order  them  by  their  filename  in
 * ascending order.
*/
TfIdfList searchOne(InvertedIndexBST tree, char *searchWord, int D) {
	return NULL;
}


/**
 * Returns  an  ordered list where each node contains a filename and the
 * summation of tf-idf values of all the matching search words for  that
 * file.  You only need to include documents (files) that contain one or
 * more of the given search words. The list must be in descending  order
 * of summation of tf-idf values (tfIdfSum). If there are multiple files
 * with  the  same tf-idf sum, order them by their filename in ascending
 * order.
 */
TfIdfList searchMany(InvertedIndexBST tree, char *searchWords[], int D) {
	return NULL;
}


/**
 * Frees all memory associated with the given tf-idf list.
 */
void freeTfIdfList(TfIdfList list) {

}
