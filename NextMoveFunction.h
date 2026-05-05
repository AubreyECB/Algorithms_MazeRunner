/*
 Author: Hannah Ross, Aubrey Bedford, TJ Ojo,
            Emeka Umeezeoke, Madison Quinter
 Assignment Title:  Group One Function
 Assignment Description: This program inputs the 'a, b, and c'
            values of the quadratic formula
            from the user and uses them to calculate the formula's roots.
 Due Date: 5/5/2026
 Date Created: 4/19/2026
 Date Last Modified: 5/5/2026

 We began the process on 4/19 meeting as a group over zoom discussing different
 ideas for a general algorithm. We discussed BFS, DFS and a graph scenario, and we
 ultimately ended up deciding to write pseudocode for the BFS and DFS to begin.
 
 We split the group-work as follows: TJ and Meka would work on the pseudocode and
 implementation of BFS and DFS, and Hannah, Aubrey and Madison would work with SDL
 Plotter and creating test cases and files. Each respective subgroup met throughout
 the week to work on their sections.
 
 We met again the following week and tested the BFS and DFS implementations on SDL.
 After discussing during the meeting, we decided to try implementing one more
 algorithm, the flood filled algorithm, in order to decrease our time.
 
 On 5/3, we discussed again and tested the flood filled algorithm; we achived a
 faster runtime and so we decided to use that in our main function.
*/

#ifndef NEXTMOVEFUNCTION_H_
#define NEXTMOVEFUNCTION_H_

#include "Racer.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cassert>

using namespace std;

// Stack used to track taken by car
stack<DIRECTION> dfsPath;

// Using a set to track visited locations
set<pair<int,int> > visited;

// Current direction of the car
DIRECTION currDir = EAST;

// description: initialize iteration direction to start (EAST)
// return: void
// precondition: currDir is defined
// postcondition: currDir is set to EAST
void iterationBegin(){
    currDir = EAST;
}

// description: compute next point based on current direction
// return: point
// precondition: currP is a valid point, currDir is set
// postcondition: returns updated point after moving one step
// Utilized for iterating through the current direction and returning the resulting point
point iterationCurrent(point currP) {
    switch(currDir){
        case EAST:  currP.x++; break;
        case SOUTH: currP.y++; break;
        case WEST:  currP.x--; break;
        case NORTH: currP.y--; break;
    }
    return currP;
}

// Utilzied for iterating through directions in a clockwise manner
void iterationAdvance(){
    switch(currDir){
        case EAST:  currDir = SOUTH; break;
        case SOUTH: currDir = WEST; break;
        case WEST:  currDir = NORTH; break;
        case NORTH: currDir = EAST; break;
    }
}

// Utilzied for backtracking when all directions have been iterated through in a counter-clockwise manner
DIRECTION iterationFlipped(DIRECTION newDir){
    switch(newDir){
        case EAST:  newDir = WEST; break;
        case SOUTH: newDir = NORTH; break;
        case WEST:  newDir = EAST; break;
        case NORTH: newDir = SOUTH; break;
    }
    return newDir;
}

// Check if the current direction has been fully iterated through
bool iterationDone(int count) const {
    return count >= 4;
}

DIRECTION nextMoveTeamOne() {

    // Retrive the current location of the car FIXME: Must remove
    point currLoc = car->getLocation();

    // Utilized to track that if all directions have been iterated through
    int directionsTried = 0;

    while (!iterationDone(directionsTried)) {
        // Getting the neighboring point in the current direction
        point neighbor = iterationCurrent(currLoc);

        // Check if the neighboring point is open and unvisited
        if (!car->look(currDir) && visited.find({neighbor.x, neighbor.y}) == visited.end()) {
             DIRECTION moveDir = currDir; // Store the direction to move before modifying currDir

            // If it is, push the current direction to the stack and return it
            iterationBegin(); // Reset the current direction to EAST for the next iteration

            // Mark the current location as visited
            visited.insert({neighbor.x, neighbor.y});
            
            dfsPath.push(moveDir); // Push the direction to the stack before returning
            return moveDir;
        }
        
        else {
            // If it isn't, advance to the next direction and increment the directionsTried counter
            iterationAdvance();
            directionsTried++;
        }
    }

    // If all directions have been tried, we need to backtrack
    if (!dfsPath.empty()) {
        DIRECTION backtrackDir = dfsPath.top();
        dfsPath.pop();
        return iterationFlipped(backtrackDir); // Return the direction to backtrack
    }

    // If the stack is empty, then we have backtracked all the way to the start and there are no more moves to make
    return EAST; // Default return value (can be changed as needed)

    

}

void initializeBFS() {
    point start = car->getLocation();
    pointQueue.push(start);
    parentMap[{start.x, start.y}] = {start, NORTH}; // dummy value to represent the start point
    isQueueInitialized = true;
}

#endif
