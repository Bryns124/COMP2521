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


/**
 * Initialising a new BST.
 */
InvertedIndexBST BSTNewTree() {
	return NULL;
}

/**
 * Initialising a new BST node with the given word.
 */
InvertedIndexBST BSTNewNode(char *word_str) {
    char *normalised_word = normalise(word_str);
	InvertedIndexBST newTree = malloc(sizeof(struct InvertedIndexNode));

	if (newTree == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Memory allocated for word in normalise().
	newTree->word = normalised_word;
	newTree->fileList = FileListNew();
	newTree->left = newTree->right = NULL;
	return newTree;
}

/**
 * Insert a new tree into a Tree t with the normalised word.
 */
InvertedIndexBST BSTTreeInsert(InvertedIndexBST tree, char *filename_str, char *normalised_word) {
    // Initialise a new tree and attach file list to it if tree is empty.
    if (tree == NULL) {
        tree = BSTNewNode(normalised_word);
        FileList newFile = FileNewNode(filename_str, normalised_word);
        tree->fileList = FileListInsert(newFile, filename_str, normalised_word);
    } else {
        int word_compare = strcmp(normalised_word, tree->word);
        // Insert file into word's file list if word is found.
        if (word_compare == 0) {
            tree->fileList = FileListInsert(tree->fileList, filename_str, normalised_word);
        }
        else if (word_compare < 0) {
            tree->left = BSTTreeInsert(tree->left, filename_str, normalised_word);
        }
        else if (word_compare > 0) {
            tree->right = BSTTreeInsert(tree->right, filename_str, normalised_word);
        }
    }
	return tree;
}

/**
 * Initialising a new FileList.
 */
FileList FileListNew() {
	return NULL;
}


/** 
 * Initialising a new FileList node with the given filename
 * and normalised word.
 */
FileList FileNewNode(char *filename_str, char *normalised_word) {
	FileList newFile = malloc(sizeof(struct FileNode));
    double tf_val = calculateTf(filename_str, normalised_word);

	if (newFile == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Allocate memory for filename via strdup().
	newFile->filename = strdup(filename_str);
	newFile->tf = tf_val;
	newFile->next = FileListNew();
	return newFile;
}

/**
 * Insert a new filelist into filelist with the given filename. 
 */
FileList FileListInsert(FileList fl, char *filename_str, char *normalised_word) {
    FileList newFile = FileNewNode(filename_str, normalised_word);

    // If filename matches filename at head, return. 
    if (strcmp(fl->filename, filename_str) == 0) {
        return fl;
    }
    // Inserting the file at head.
	if (fl == NULL || strcmp(fl->filename, filename_str) > 0) {
        newFile->next = fl;
    	fl = newFile;
    } else {
        FileList temp = fl;
        // Inserting the file in a sorted file list.
        while (temp->next != NULL && strcmp(temp->next->filename, filename_str) < 0) {
            temp = temp->next;
        }
        // If the word is found more than once is a file, return.
        if (temp->next != NULL && strcmp(temp->next->filename, filename_str) == 0) {
            return fl;
        }
        newFile->next = temp->next;
        temp->next = newFile;
    }
    return fl;
}


/**
 * Calculates the value of Tf by finding normalised word in file
 * and incrementing respective word counts. Then return division
 * of frequency of word over the number of words in file. 
 */
double calculateTf(char *filename_str, char *normalised_word) {
    int normalised_word_count = 0;
    int total_word_count = 0;
    char word[MAX_CHARS + 1];

    FILE *word_in_file_input = fopen(filename_str, "r");
    if (word_in_file_input == NULL) {
		fprintf(stderr, "error: failed to open %s.\n", filename_str);
		exit(EXIT_FAILURE);
	}

    while (fscanf(word_in_file_input, "%s", word) == 1) {
        char *normalise_file_word = normalise(word);
        // Not added to total word count since normalising punctuation 
        // returns a NULL terminator.
        if (normalise_file_word[0] == '\0') {
            continue;
        }
        if (strcmp(normalised_word, normalise(word)) == 0) {
            normalised_word_count++;
        }
		total_word_count++;
	}
    fclose(word_in_file_input);
    return ((double)normalised_word_count/total_word_count);
}


/**
 * Normalise the word with the given word by making uppercase letters
 * into lowercase and removing specified punctuation. 
 */
char *normalise(char *word_str) {
    // Allocate memory for normalised word with strcpy().
	char *normalised_word = malloc((MAX_CHARS + 1) * sizeof(char));
    strcpy(normalised_word, word_str);

    for (int i = 0; i < strlen(word_str); i++) {
        normalised_word[i] = tolower(word_str[i]);
    }
    // Removes punctuation by replacing with NULL terminator and breaks 
    // when encountering non-punctuation.
    for (int i = (strlen(normalised_word) - 1); i >= 0 ; i--) {
        if (normalised_word[i] == '.' || normalised_word[i] == ',' || normalised_word[i] == ':' || 
            normalised_word[i] == ';' || normalised_word[i] == '?' || normalised_word[i] == '*') {
            normalised_word[i] = '\0';
        } else {
            break;
        }
    }
    return normalised_word;
}


/**
 * Prints the tree's words and it's files via recursion into 
 * file_output's stream.
 */
void doPrintTreeRecursive(FILE *file_output, InvertedIndexBST tree) {
    if (tree == NULL) {
		return;
    }

    FileList temp = tree->fileList;
    doPrintTreeRecursive(file_output, tree->left);
    fprintf(file_output, "%s ", tree->word);
    // Prints the files the word is found in.
    while (temp != NULL) {
        fprintf(file_output, "%s (%.7lf) ", temp->filename, temp->tf);
        temp = temp->next;
    }
    fprintf(file_output, "\n");
    doPrintTreeRecursive(file_output, tree->right);
}

/**
 * Frees memory accessed by given list. Sourced from Stack Overflow.
 */
void freeList(FileList fl) {
   FileList tmp;

   while (fl != NULL) {
       tmp = fl;
       fl = fl->next;
       free(tmp->filename);
       free(tmp);
    }
}
