// Centrality Measures API implementation
// COMP2521 Assignment 2
// z5361001, Bryan Le

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "Graph.h"

int calculatePaths(NodeData *path, Vertex start, Vertex end);
int calculateSumPaths(NodeData *path, int nV);
int countReachableV(NodeData *path, int nV);
double calculateClose(int sumShortPath, int n, int N);
double calculateBetw(NodeData *path, Vertex v, Vertex s, Vertex t);
bool vertexIsIsolated(Graph g, Vertex v);
bool verticesNotEqual(Vertex v, Vertex s, Vertex t);


/**
 * Finds  the  closeness centrality for each node in the given graph and
 * returns the results in an array where index v of the  array  contains
 * the closeness centrality of node v.
 */
double *closenessCentrality(Graph g) {
	int numVertices = GraphNumVertices(g);
	int sumPaths, reachableVertices;
	double *values = malloc(numVertices * sizeof(double));
	// Get number of reachable nodes and total sum of shortest path distance.
	for (Vertex src = 0; src < numVertices; src++) {
		NodeData *shortestPaths = dijkstra(g, src);
		sumPaths = calculateSumPaths(shortestPaths, numVertices);
		reachableVertices = countReachableV(shortestPaths, numVertices);
		// Calculate closeness centrality.
		if (!vertexIsIsolated(g, src) && sumPaths != 0) {
			values[src] = calculateClose(sumPaths, reachableVertices - 1, numVertices);
		} else {
			values[src] = 0;
		}
		// freeNodeData(shortestPaths, numVertices);
	}
	return values;
}


/**
 * Finds the betweenness centrality for each node in the given graph and
 * returns the results in an array where index v of the  array  contains
 * the betweenness centrality of node v.
 */
double *betweennessCentrality(Graph g) {
	int numVertices = GraphNumVertices(g);
	double sumPaths;
	double *values = malloc(numVertices * sizeof(double));
	// Get the 'mid' vertex in between the 'src' and 'dest' vertices.
	for (Vertex mid = 0; mid < numVertices; mid++) {
		sumPaths = 0;
		for (Vertex src = 0; src < numVertices; src++) {
			NodeData *shortestPaths = dijkstra(g, src);
			for (Vertex dest = 0; dest < numVertices; dest++) {
				// Calculate betweenness centrality
				if (verticesNotEqual(mid, src, dest)) {
					sumPaths += calculateBetw(shortestPaths, mid, src, dest);
					values[mid] = sumPaths;
				}
			}
			// freeNodeData(shortestPaths, numVertices);
		}
	}
	return values;
}


////////////////////////////////////////////////////////////////
//                                                            //
//                         MY HELPERS                         //
//                                                            //
////////////////////////////////////////////////////////////////


/**
 * Calculates the sum of the shortest paths distances.
 */
int calculateSumPaths(NodeData *path, int nV) {
	int pathcount = 0;
	for (int i = 0; i < nV; i++) {
		if (path[i].dist != INFINITY) {
			pathcount += path[i].dist;
		}
	}
	return pathcount;
}


/**
 * Counts the number of nodes that the source node can reach.
 */
int countReachableV(NodeData *path, int nV) {
	int reachableV = 1;
	for (int i = 0; i < nV; i++) {
		if (path[i].dist != INFINITY) {
			reachableV++;
		}
	}
	return reachableV;
}


/**
 * Calculates the number of paths of a given data's predList recursively 
 * from a given 'start' to 'end' vertex using "backtracking." Got idea from:
 * https://www.geeksforgeeks.org/count-possible-paths-two-vertices/
 */
int calculatePaths(NodeData *paths, Vertex start, Vertex end) {
	int numPathsTotal = 0;
	// There is a single path if the start vertex is the same as the end.
	if (start == end) return 1;
	// Backtracking recursion.
	for (PredNode *curr = paths[end].pred; curr != NULL; curr = curr->next) {
		numPathsTotal += calculatePaths(paths, start, curr->v);
	}
	return numPathsTotal;
}


/**
 * Calculates the Closeness Centrality value with the formula specified 
 * in the specs, where 'n' is the reachable vertices, 'N' is the total vertices
 * in the graph and 'sumShortPath' is the shortest-path distance from the
 * source vertex to destination vertex.
 */
double calculateClose(int sumShortPath, int n, int N) {
	return (double)(n - 1) / (N - 1) * (n - 1) / (sumShortPath);
}


/**
 * Calculates the Betweenness Centrality value with the formula specified 
 * in the specs, where 'numPathsMid' is the number of paths that pass through
 * the 'v' vertex and 'numPathsTotal' is the total number of paths from the
 * 's' vertex to 't' vertex.
 * 
 * The 'numPathsMid' needs multiplication to get the result as paths can 
 * branch out.
 */
double calculateBetw(NodeData *paths, Vertex v, Vertex s, Vertex t) {
	double numPathsMid = calculatePaths(paths, s, v) * calculatePaths(paths, v, t);
	double numPathsTotal = calculatePaths(paths, s, t);
	// Denominator cannot be 0.
	if (numPathsTotal != 0) return (double)(numPathsMid / numPathsTotal);
	return 0;
}


/**
 * Checks if the given vertex 'v' in graph 'g' is isolated.
 */
bool vertexIsIsolated(Graph g, Vertex v) {
	if (GraphInIncident(g, v) == NULL && GraphOutIncident(g, v) == NULL) return true;
	return false;
}


/**
 * Checks that the 'v', 's' and 't' vertices are not the same.
 */
bool verticesNotEqual(Vertex v, Vertex s, Vertex t) {
	if (s != v && v != t && s != t) return true;
	return false;
}