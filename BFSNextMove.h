#ifndef BFSNEXTMOVE_H_
#define BFSNEXTMOVE_H_

//////////////////////////////////////////////////////////////////////////////////////
// JUST IMAGINE THAT YOU ARE IN THE DRIVER PUBLIC SPACE AND YOU CAN USE car->look() //
//////////////////////////////////////////////////////////////////////////////////////

// libraries needed (add any if need be)
#include "RaceCarDriver.h"
#include <stack>
#include <map>
#include <queue>
#include <set>


using namespace std;

// declaration and implementation of the point Struct
struct Point_TeamOne {
    int x;
    int y;
};

// function for inverting a direction (used for backtracking)
DIRECTION invertDirection(DIRECTION dir) {
    switch (dir) {
        case NORTH: return SOUTH;
        case SOUTH: return NORTH;
        case EAST:  return WEST;
        case WEST:  return EAST;
        default: return NORTH; // default case, should never reach here
    }
}

// function to update currentLocation with each movement
void updateCurrentLocation(Point_TeamOne& currentLocation, DIRECTION move) {
    switch (move) {
        case NORTH: currentLocation.y--; break;
        case SOUTH: currentLocation.y++; break;
        case EAST:  currentLocation.x++; break;
        case WEST:  currentLocation.x--; break;
    }
}

// function for reconstructPath_TeamOne()
stack<DIRECTION> reconstructPath_TeamOne(Point_TeamOne start, 
    Point_TeamOne end,
    map<pair<int,int>, pair<Point_TeamOne, DIRECTION>>& parentMap) {

    stack<DIRECTION> path;
    Point_TeamOne current = end;

    while (!(current.x == start.x && current.y == start.y)) {
        pair<Point_TeamOne, DIRECTION> parent = parentMap[{current.x, current.y}];
        path.push(parent.second);
        current = parent.first;
    }

    return path;
}

// function for reconstructPath_Backtrack_TeamOne()
stack<DIRECTION> reconstructPath_Backtrack_TeamOne(Point_TeamOne start, 
    Point_TeamOne end, 
    map<pair<int,int>, pair<Point_TeamOne, DIRECTION>>& parentMap) {

    vector<DIRECTION> reversed;
    Point_TeamOne current = end;

    while (!(current.x == start.x && current.y == start.y)) {
        pair<Point_TeamOne, DIRECTION> parent = parentMap[{current.x, current.y}];
        reversed.push_back(invertDirection(parent.second));
        current = parent.first;
    }

    // reverse so first move is on top of stack
    stack<DIRECTION> path;
    for (int i = reversed.size() - 1; i >= 0; i--) {
        path.push(reversed[i]);
    }
    return path;
}

// function for initializing the BFS PointQueue
void initializeBFS_TeamOne(Point_TeamOne& startPos, 
    queue<Point_TeamOne>& pointQueue, 
    map<pair<int,int>, pair<Point_TeamOne, DIRECTION>>& parentMap, 
    bool& isQueueInitialized) {

	Point_TeamOne start = startPos;
	pointQueue.push(start);
	parentMap[{start.x, start.y}] = {start, NORTH}; // dummy value to represent the start point
	isQueueInitialized = true;
}

// function for BFS' next move (meant to be called in nextMoveTeamOne() when run == 0)
DIRECTION BFSNextMove_TeamOne() {
    // static variables declarations inside function

    // Note from TJ: I'm contemplating whether or not I should use color so I'm omitting for now
    static stack<DIRECTION> pathToTarget;
    static Point_TeamOne currentLocation = {0, 0};
    static Point_TeamOne targetLocation = {0, 0};
    static Point_TeamOne startLocation = {0, 0};
    static Point_TeamOne endLocation = {0, 0};
    static bool isPathing = false;
    static bool isQueueInitialized = false;
    static queue<Point_TeamOne> pointQueue;
    static map<pair<int,int>, pair<Point_TeamOne, DIRECTION>> parentMap;
    // note: walls will also be present in this function because the 
    // TeamOneNextMove() has it statically declared

    // BFS Logic here!

}

#endif // BFSNEXTMOVE_H_