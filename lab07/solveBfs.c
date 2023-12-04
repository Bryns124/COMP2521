// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "helpers.h"
#include "Maze.h"
#include "Queue.h"

bool solve(Maze m) {
    bool **visited = createBoolMatrix(MazeHeight(m), MazeWidth(m));
    Cell **path = createCellMatrix(MazeHeight(m), MazeWidth(m));

    Cell start = MazeGetStart(m);
    visited[start.row][start.col] = true;
    path[start.row][start.col] = start;

    Queue q = QueueNew();
    QueueEnqueue(q, start);
    Cell c = start;
    while (!QueueIsEmpty(q)) {
        c = QueueDequeue(q);

    }
    return false;
}