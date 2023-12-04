// Dijkstra API implementation
// COMP2521 Assignment 2
// z5361001, Bryan Le

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"

void freePredList(PredNode *curr);
PredNode *newPredNode(Vertex v);
PredNode *insertNewPredNode(PredNode *predList, Vertex v);


/**
 * Finds  the shortest paths from a given source node to all other nodes
 * in the given graph. See the spec for more details.
 *
 * The  function  returns  a  NodeData  array,  with length equal to the
 * number of nodes in the graph, where index v of the array contains the
 * distance and predecessor list for node v. The predecessor lists  must
 * be in ascending order of vertex number.
 */
NodeData *dijkstra(Graph g, Vertex src) {

	// Create NodeData array
	int numVertices = GraphNumVertices(g);
	NodeData *ndArr = malloc(numVertices * sizeof(NodeData));

	// Initialise NodeData array with dist costs to be INFINITY,
	// pred nodes to be NULL and initialise PQ.
	PQ verticesSet = PQNew();
	for (Vertex v = 0; v < numVertices; v++) {
		ndArr[v].dist = INFINITY;
		// The distance of the src vertex to itself is 0.
		if (v == src) {
			ndArr[src].dist = 0;
		}
		ndArr[v].pred = NULL;
		PQInsert(verticesSet, v, ndArr[v].dist);
	}

	while (!PQIsEmpty(verticesSet)) {
		Vertex v = PQDequeue(verticesSet);
		// Edge relaxation
		for (AdjList adjOut = GraphOutIncident(g, v); adjOut != NULL; 
		adjOut = adjOut->next) {
			if (ndArr[v].dist != INFINITY) {
				// If the new path found is shorter than the old path, replace 
				// old path with new shorter path and free the old path.
				if (ndArr[adjOut->v].dist > ndArr[v].dist + adjOut->weight) {
					ndArr[adjOut->v].dist = ndArr[v].dist + adjOut->weight;
					freePredList(ndArr[adjOut->v].pred);
					ndArr[adjOut->v].pred = newPredNode(v);
					PQUpdate(verticesSet, adjOut->v, ndArr[adjOut->v].dist);
				}
				// If the shortest paths are equal, add pred node to pred list. 
				else if (ndArr[adjOut->v].dist == ndArr[v].dist + adjOut->weight) {
					ndArr[adjOut->v].pred = insertNewPredNode(ndArr[adjOut->v].pred, v);
				}
			}
		}
	}
	PQFree(verticesSet);
	return ndArr;
}


/**
 * Frees  all  memory associated with the given NodeData array. The size
 * of the array is 'nV'.
 */
void freeNodeData(NodeData *data, int nV) {
	for (int i = 0; i < nV; i++) {
		freePredList(data[i].pred);
	}
	free(data);
}


////////////////////////////////////////////////////////////////
//                                                            //
//                         MY HELPERS                         //
//                                                            //
////////////////////////////////////////////////////////////////


/**
 * Frees all memory associated with the given NodeData's predeccessor list. 
 */
void freePredList(PredNode *curr) {
	if (curr == NULL) return;
	freePredList(curr->next);
	free(curr);
}


/**
 * Create a new predecessor node of vertex 'v' to be inserted into the predList.
 */
PredNode *newPredNode(Vertex v) {
	PredNode *new = malloc(sizeof(struct PredNode));
	if (new == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
	new->v = v;
	new->next = NULL;
	return new;
}


/**
 * Insert the newPredNode of vertex 'v' into the predList inorder 
 * and return predList. Raymond helped me with inorder insertion.
 */
PredNode *insertNewPredNode(PredNode *predList, Vertex v) {
	PredNode *predNode = newPredNode(v);
	PredNode *curr = predList;
	// If the list is empty, the new node is the head of the list.
	if (predList == NULL) {
		predList = predNode;
	}
	// If the head's 'v' is larger than the new node's 'v',
	// the new node is the head of the list. 
	else if (predList->v >= v) { 
		predNode->next = predList;
		return predNode;
	} else {
		// Insert new node into the predList inorder.
		while (curr->next != NULL) {
			if (curr->next->v >= v) {
				predNode->next = curr->next;
				curr->next = predNode;
				return predList;
			}
			curr = curr->next;
		}
	}
	curr->next = predNode;
	return predList;
}