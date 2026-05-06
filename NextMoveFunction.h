/*
 Author: Hannah Ross, Aubrey Bedford, TJ Ojo,
            Emeka Umeezeoke, Madison Quinter
 Assignment Title:  Group One Function
 Assignment Description: This program inputs the 'a, b, and c'
            values of the quadratic formula
            from the user and uses them to calculate the formula's roots.
 Due Date: 5/6/2026
 Date Created: 4/19/2026
 Date Last Modified: 5/6/2026

 We began the process on 4/19 meeting as a group over zoom discussing different
 ideas for a general algorithm. We discussed BFS, DFS and a graph scenario, and we
 ultimately ended up deciding to write pseudocode for the BFS and DFS to begin.
 
 We split the group-work as follows: TJ and Meka would work on the pseudocode and
 implementation of BFS and DFS, and Hannah, Aubrey and Madison would work with SDL
 Plotter and creating test cases and files. Each respective subgroup met throughout
 the week to work on their sections.
 
 We met again the following week and tested the BFS and DFS implementations on SDL.
 After discussing during the meeting, we decided to try implementing one more
 algorithm, the A* algorithm, in order to decrease our time.
 
 On 5/3-5/6, we discussed again and tested the BFS and A* algorithm.
*/

#ifndef NEXTMOVEFUNCTION_H_
#define NEXTMOVEFUNCTION_H_

#include "Racer.h"
#include <stack> // for the stack data structure
#include <map> // for the map data structure
#include <queue> // for the queue data structure
#include <set> // for the set data structure
#include <utility> // for the pair data structure
#include <cassert> // for debugging with assert
#include <vector>
#include <algorithm>

using namespace std;

// BFS FUNCTIONS AND HELPER FUNCTIONS FOR TEAM ONE

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
void updateCurrentLocation(pair<int, int>& currentLocation, DIRECTION move) {
    switch (move) {
        case NORTH: currentLocation.second--; break;
        case SOUTH: currentLocation.second++; break;
        case EAST:  currentLocation.first++; break;
        case WEST:  currentLocation.first--; break;
    }
}

// function for reconstructPath_TeamOne()
stack<DIRECTION> reconstructPath_TeamOne(pair<int, int> start, 
    pair<int, int> end,
    map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap) {

    stack<DIRECTION> path;
    pair<int, int> current = end;

    while (!(current.first == start.first && current.second == start.second)) {
        pair<pair<int, int>, DIRECTION> parent = parentMap[{current.first, current.second}];
        path.push(parent.second);
        current = parent.first;
    }

    return path;
}

// function for reconstructPath_Backtrack_TeamOne()
stack<DIRECTION> reconstructPath_Backtrack_TeamOne(pair<int, int> start, 
    pair<int, int> end, 
    map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap) {

    vector<DIRECTION> reversed;
    pair<int, int> current = end;

    while (!(current.first == start.first && current.second == start.second)) {
        pair<pair<int, int>, DIRECTION> parent = parentMap[{current.first, current.second}];
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

void exploreNeighbors_TeamOne(pair<int, int> currentLocation, 
    map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap, 
    queue<pair<int, int>>& pointQueue, 
    set<pair<int,int>>& walls, 
    Racer* car) {
    
    const int NUM_DIRECTIONS = 4;
    DIRECTION directions[NUM_DIRECTIONS] = {EAST, SOUTH, WEST, NORTH}; // order of exploration: right, down, left, up
    
    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        bool isWalll = car->look(directions[i]);
        pair<int, int> neighbor = currentLocation;
        updateCurrentLocation(neighbor, directions[i]);

        // case where there is a wall in the direction we are looking, so we add it to the walls set
        if (isWalll) {
            walls.insert({neighbor.first, neighbor.second});
        }

        // case where there is no wall and there is a neighboring point to add
        // however, we don't add it willy-nilly, we check if it's already in the parentMap to ensure 
        // we don't add duplicates to the queue, then we add it to the parentMap and the queue
        // if its not in the parentMap already
        else {
            if (parentMap.find({neighbor.first, neighbor.second}) == parentMap.end()) {
                parentMap[{neighbor.first, neighbor.second}] = {currentLocation, directions[i]};
                pointQueue.push(neighbor);
            }
        }
    }
}

// function for initializing the BFS PointQueue
void initializeBFS_TeamOne(pair<int, int>& startPos, 
    queue<pair<int, int>>& pointQueue, 
    map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap, 
    bool& isQueueInitialized) {

	pair<int, int> start = startPos;
	pointQueue.push(start);
	parentMap[{start.first, start.second}] = {start, NORTH}; // dummy value to represent the start point
	isQueueInitialized = true;
}

// function for BFS' next move (meant to be called in nextMoveTeamOne() when run == 0)
DIRECTION BFSNextMove_TeamOne(set<pair<int,int>>& walls,
    pair<int, int>& startLocation,
    pair<int, int>& currentLocation, 
    Racer* car) {
    // static variables declarations inside function

    // Note from TJ: I'm contemplating whether or not I should use color so I'm omitting for now
    static stack<DIRECTION> pathToTarget;
    static pair<int, int> targetLocation = {0, 0};
    // start and end location were moved to be local to the TeamOneNextMove()
    static bool isPathing = false;
    static bool isQueueInitialized = false;
    static queue<pair<int, int>> pointQueue;
    static map<pair<int,int>, pair<pair<int, int>, DIRECTION>> parentMap;
    // note: walls will also be present in this function because the 
    // TeamOneNextMove() has it statically declared

    // BFS Logic here!

    // if there is nothing in the Queue, give it the starting position
    if (!isQueueInitialized) {
        initializeBFS_TeamOne(currentLocation, pointQueue, parentMap, isQueueInitialized);
    }

    // if the pathing buffer has stuff in it, pop and return the next move
    if (!pathToTarget.empty()) {
        DIRECTION nextMove = pathToTarget.top();
        pathToTarget.pop();
        updateCurrentLocation(currentLocation, nextMove);
        return nextMove;
    }

    // set boolean to false so we can start the pathfinding and traversal process again
    isPathing = false;

    // loop while the pointQueue is not empty and we are not currently pathing to a target
    // literally should never stop :)
    while (!pointQueue.empty() && !isPathing) {
        // peek at the targetLocation from the from of the queue
        targetLocation = pointQueue.front();

        // if we aren't at the targetLocation yet, take this branch
        // we want to build the path to be able to explore targetLocation
        if (!(currentLocation.first == targetLocation.first && 
            currentLocation.second == targetLocation.second)) {
            pathToTarget = reconstructPath_TeamOne(currentLocation, targetLocation, parentMap);
            isPathing = true;
            DIRECTION nextMove = pathToTarget.top();
            pathToTarget.pop();
            updateCurrentLocation(currentLocation, nextMove);
            return nextMove;
        }
        // if we are at the targetLocation, we now want to explore the area around us
        else {
            // dequeue the targetLocation since we are now exploring it
            pointQueue.pop();
            // we aren't pathing to a target now, so set it to false
            isPathing = false;
            // explore the neighbors of the targetLocation and add them to the queue if they are valid
            // also add the walls to the walls map that will be globally relative to this function and 
            // local relative to the TeamOneNextMove() function
            exploreNeighbors_TeamOne(currentLocation, parentMap, pointQueue, walls, car);
            pathToTarget = reconstructPath_Backtrack_TeamOne(currentLocation, startLocation, parentMap);
            isPathing = true;
            DIRECTION nextMove = pathToTarget.top();
            pathToTarget.pop();
            updateCurrentLocation(currentLocation, nextMove);
            return nextMove;
        }
    }
    // if you are getting here, it means the queue is empty and you haven't found the target
    // which should never happen since the mazes are guaranteed to have a solution, but if it does 
    // just return something
    assert(false); // should never reach here
}

// A* FUNCTIONS AND HELPER FUNCTIONS FOR TEAM ONE - Hannah's Implementation

// TEAM ONE'S NEXTMOVE FUNCTION

#endif
