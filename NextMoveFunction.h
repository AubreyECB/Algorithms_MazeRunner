/**
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
 
 After reanalyzing our approach to the project, we decided that implementing BFS would be the
 best course of action. After completing the maze, and finding the start location, end location
 and the walls, BFS was able to optimize its path for each 3 runs. 

 We have copied eveyrthing under public, as well as our global functions. 
 */

#ifndef RACECARDRIVER_H_
#define RACECARDRIVER_H_

#include "Racer.h"
#include <vector>
#include <queue>
#include <algorithm>


using namespace std;

/*
 * Description: Determines the next move for A*; computes a path once and returns directions one step at a time.
 * Return: A DIRECTION value representing the next movement for the racer.
 * Precondition: Maze data exists.
 * Postcondition: Next direction is returned or fallback direction is returned (if no path exists).
 *
*/
DIRECTION nextMovePlaceInside_TeamOne();

/*
 * Description: Returns the opposite of the provided direction.
 * Return: The inverse DIRRECTION of the given direction. 
 * Precondition: dir is a DIRECTION.
 * Postcondition: The opposite direction of dir.
 *
*/
DIRECTION invertDirection(DIRECTION dir);

/*
 * Description: Updates a coordinate pair to reflect movement in the specified direction.
 * Return: None.
 * Precondition: currentLocation must be a pair<int,int> and move is a DIRECTION.
 * Postcondition: currentLocation is modified to represent the new location after moving.
 *
*/
void updateCurrentLocation(pair<int, int>& currentLocation, DIRECTION move);

/*
 * Description: Reconstructs a path from the start location to the end location using the parent map.
 * Return: Stack containing the directions required to travel from start to the end.
 * Precondition: parentMap must contain traversal history connecting start and end.
 * Postcondition: A stack of directions represneting the reconstructed path is returned.
 *
*/
stack<DIRECTION> reconstructPath_TeamOne(pair<int, int> start,
                                         pair<int, int> end,
                                         map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap);

/*
 * Description: Builds a path that backtracks from the current position to the start and then proceeds toward a target node.
 * Return: Stack containing the directions required for traversal.
 * Precondition: parentMap must contain valid parent relationships for all required nodes.
 * Postcondition: A valid traversal path is returned in stack form.
 *
*/
stack<DIRECTION> reconstructPath_Backtrack_TeamOne(pair<int, int> start,
                                                   pair<int, int> end,
                                                   map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap);

/*
 * Description: Explores all neighboring cells adjacent to the current location.
 * Return: None.
 * Precondition: currentLocation must represent a valid explored position and car must point to a valid Racer object.
 * Postcondition:parentMap, pointQueue, and walls may be updated with newly discovered
 * information about neighboring cells.
 *
*/
void exploreNeighbors_TeamOne(pair<int, int> currentLocation,
                              map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap,
                              queue<pair<int, int>>& pointQueue,
                              set<pair<int,int>>& walls,
                              Racer* car);

/*
 * Description: Initializes the BFS traversal structures by inserting the starting position into the queue and parent map.
 * Return: None.
 * Precondition: startPos must contain a valid starting coordinate.
 * Postcondition: The BFS queue and parent map are initialized and the initialization flag is set to true.
 *
*/
void initializeBFS_TeamOne(pair<int, int>& startPos,
                           queue<pair<int, int>>& pointQueue,
                           map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap,
                           bool& isQueueInitialized);

/*
 * Description: Determines the next movement needed to continue traversing and exploring
 * the maze environment.
 * Return: The next DIRECTION the racer should move.
 * Precondition: BFS data structures and the Racer pointer must be properly initialized.
 * Postcondition: BFS traversal state, queue contents, parent map, and current location
 * may be updated.
 *
*/
DIRECTION BFSNextMove_TeamOne(set<pair<int,int>>& walls,
                              pair<int, int>& startLocation,
                              pair<int, int>& currentLocation,
                              queue<pair<int, int>>& pointQueue,
                              Racer* car, map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap);

/*
 * Description: Performs BFS from start and end location while avoiding known wall locations.
 * Return: A vector containing directions required to reach the destination.
 * Precondition: Start and end coordinates must be valid positions within the maze/grid.
 * Postcondition: A computed shortest-path direction vector is returned if a path exists.
 *
*/
vector<DIRECTION> nextMove_A_TeamOne(pair<int,int> start, pair<int,int> end, set<pair<int,int>>& wallsM);


class RaceCarDriver{
private:
    Racer* car;

public:
    RaceCarDriver(Racer* p = nullptr): car{p}{}

    DIRECTION nextMoveTeamOne(int run = 0) {
        // FOR BSF
        static set<pair<int,int>> walls;
        static set<pair<int,int>> freeSpaces;
        static set<pair<int,int>> visited;
        static queue<pair<int, int>> pointQueue;

        // from TJ
        static pair<int, int> startLocation = {0, 0};
        static pair<int, int> endLocation = {0, 0};
        static pair<int, int> currentLocation = {0, 0};
        static map<pair<int,int>, pair<pair<int, int>, DIRECTION>> parentMap;

        static stack<DIRECTION> pathToEnd;

        if(run == 0) {
            // RUN BSF 1 HERE
            return BFSNextMove_TeamOne(walls, startLocation, currentLocation, pointQueue, car, parentMap);
        } else if (run == 1) {
            cout << "NEW RUN" << endl;
            //If the end loc. is 0,0 that means it has not been set
            if (endLocation == startLocation) {
                //We have teleported to the beginning so currentLocation is the endLocation
                endLocation = currentLocation;
                currentLocation = startLocation;
                pathToEnd = reconstructPath_TeamOne(startLocation, endLocation, parentMap);
                DIRECTION nextMove = pathToEnd.top();
                pathToEnd.pop();
                updateCurrentLocation(currentLocation, nextMove);
                return nextMove;
            }
            // RUN BETTER
            if(!pathToEnd.empty()) {
                DIRECTION nextMove = pathToEnd.top();
                pathToEnd.pop();
                updateCurrentLocation(currentLocation, nextMove);
                return nextMove;
            }

            // set endLocation to currentLocation here because
            // at this point, currentLocation is at the end
        } else {
            // RUN HEURISTIC
            auto d = nextMovePlaceInside_TeamOne();
            return d;
        }
    }
};

DIRECTION nextMovePlaceInside_TeamOne() {
    static vector<DIRECTION> path;
    static int pathIndex = 0;

    cout << "inside helper " << endl;
    // Only compute path once
    if (path.empty()) {
        set<pair<int,int>> wallsM;
        path = nextMove_A_TeamOne({0, 0}, {2, 0}, wallsM={}); // FIXME: actual walls
        for (auto& d : path){
            if(d == EAST)  cout << "EAST" << endl;
            if(d == WEST)  cout << "WEST" << endl;
            if(d == NORTH) cout << "NORTH" << endl;
            if(d == SOUTH) cout << "SOUTH" << endl;
        }
    }

    if (pathIndex < path.size()) {
        return path[pathIndex++];
    }

    path.clear();
    pathIndex = 0;

    return EAST; // fallback
}

struct A_Details_TeamOne{

    int g;
    double f, h;
    int parent1, parent2;
    int x, y; // where node is in maze

};

bool isValid_TeamOne(int x, int y){
    return true;
}

bool isWall_TeamOne(set<pair<int,int>>& wallsM, int r, int c){
    for (auto& w : wallsM){
        if (w.first == r && w.second == c) return true;
    }
    return false;
}

vector<DIRECTION> nextMove_A_TeamOne(pair<int, int> start, pair<int, int> end, set<pair<int,int>>& wallsM){
    A_Details_TeamOne begin{};
    begin.f = 0;
    vector<A_Details_TeamOne> open; // open to exploration
    vector<A_Details_TeamOne> closed; // closed for eval

    // FINAL PATHS FOR FINAL
    vector<DIRECTION> finalDirection;

    begin.x = start.first;
    begin.y = start.second; // x and y of current
    begin.parent1 = -1; // needs init before starting
    begin.parent2 = -1;
    begin.g = 0;
    begin.h = 0;
    begin.f = 0;

    open.push_back(begin);

    while(!open.empty()){
        cout << "OPEN SIZE: " << open.size() << endl;

        int bestIndex = 0;
        for (int i = 1; i < open.size(); i++) {
            if (open[i].f < open[bestIndex].f) {
                bestIndex = i;
            }
        }

        A_Details_TeamOne q = open[bestIndex];
        open.erase(open.begin() + bestIndex);

        closed.push_back(q);

        cout << "q: " << q.x << "," << q.y << " open:" << open.size() << endl;

        //  Finding Successors:
        A_Details_TeamOne succ1{}; A_Details_TeamOne succ2{};
        A_Details_TeamOne succ3{}; A_Details_TeamOne succ4{};

        succ1.x = q.x + 1; succ1.y = q.y; // EAST
        succ2.x = q.x-1; succ2.y = q.y; //WEST
        succ3.x = q.x; succ3.y = q.y-1; // NORTH
        succ4.x = q.x; succ4.y = q.y+1; // SOUTH

        vector<A_Details_TeamOne> successors = {succ1, succ2, succ3, succ4};

        for (auto& succ : successors){

            if (!isValid_TeamOne(succ.x, succ.y)) continue;
            if (isWall_TeamOne(wallsM, succ.x, succ.y)) continue;

            // 1. GOAL CHECK FIRST
            if (succ.x == end.first && succ.y == end.second){
                succ.parent1 = q.x;
                succ.parent2 = q.y;
                closed.push_back(succ);

                A_Details_TeamOne current = succ;
                while (!(current.x == start.first && current.y == start.second)){
                    for (auto& node : closed){
                        if (node.x == current.parent1 && node.y == current.parent2){
                            int dx = current.x - node.x;
                            int dy = current.y - node.y;
                            if      (dx == 1)  finalDirection.push_back(EAST);
                            else if (dx == -1) finalDirection.push_back(WEST);
                            else if (dy == 1)  finalDirection.push_back(SOUTH);
                            else if (dy == -1) finalDirection.push_back(NORTH);
                            current = node;
                            break;
                        }
                    }
                }
                reverse(finalDirection.begin(), finalDirection.end());
                return finalDirection; // return for car!
            }

            // 2. SET COSTS
            succ.parent1 = q.x;
            succ.parent2 = q.y;
            succ.g = q.g + 1;
            succ.h = abs(succ.x - end.first) + abs(succ.y - end.second);
            succ.f = succ.g + succ.h;

            // 3. CHECKS FOR SKIPPING
            bool skip = false;
            for (auto& open_val : open){
                if (open_val.x == succ.x && open_val.y == succ.y){
                    if (succ.g >= open_val.g){
                        skip = true;
                    } else {
                        open_val.g = succ.g;
                        open_val.f = succ.f;
                        open_val.parent1 = q.x;
                        open_val.parent2 = q.y;
                        skip = true;
                    }
                    break;
                }
            }
            for (auto& closed_val : closed){
                if (closed_val.x == succ.x && closed_val.y == succ.y){
                    if (succ.g >= closed_val.g) skip = true;
                    break;
                }
            }

            // 4. ADD TO OPEN LAST
            if (!skip) open.push_back(succ);
        }
    }
    return {}; // no path found?
}

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
        case NORTH: currentLocation.second--; cout << "N" << endl; break;
        case SOUTH: currentLocation.second++; cout << "S" << endl; break;
        case EAST:  currentLocation.first++; cout << "E" << endl; break;
        case WEST:  currentLocation.first--; cout << "W" << endl; break;
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
                                                   pair<int, int> target,
                                                   map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap) {
//FIXME - indices to match the global ------------------------
    /*vector<DIRECTION> reversed;
    stack<DIRECTION> path;

    while (current != parentMap[current].first) {
        cout << " DIRECTION " << parentMap[current].second << endl;
        path.push(parentMap[current].second);
        current = parentMap[current].first;
    }

    /* Loop until we step back to the start node
    while (current != start) {
        // parentMap[current] contains {previous_node, direction_to_reach_current}
        auto entry = parentMap[current];
        pair<int, int> parent = entry.first;
        DIRECTION dirTaken = entry.second;

        // Push the direction to the stack
        path.push(dirTaken);

        // Move current to the parent to continue backtracking
        current = parent;
    }

    return path;

    // reverse so first move is on top of stack
    for (int i = reversed.size() - 1; i >= 0; i--) {
        path.push(reversed[i]);
    }*/

    stack<DIRECTION> backtrackToStart;
    queue<DIRECTION> forwardToTarget;
    stack<DIRECTION> finalPath;
    pair<int, int> current = end;

    //target == next in BFS

    // Leg 1: walk current → start, inverting directions as we go
    pair<int,int> node = current;
    while (node != parentMap.at(node).first) {
        backtrackToStart.push(invertDirection(parentMap.at(node).second));
        node = parentMap.at(node).first;
    }

    // Leg 2: walk start → target forward through parentMap
    //FIXME: Aubrey - Error here - attempting fix by using a queue to get FIFO behavior
    node = target;
    while (node != parentMap.at(node).first) {
        forwardToTarget.push(parentMap.at(node).second);
        node = parentMap.at(node).first;
    }



    // forwardToTarget is reversed (target→start), so it's already in the right
    // order to push onto finalPath after backtrackToStart

    // Build finalPath: backtrack first, then forward
    // forwardToTarget goes in first (it's the bottom of the stack)
    while (!forwardToTarget.empty()) {
        finalPath.push(forwardToTarget.front());
        forwardToTarget.pop();
    }
    // backtrackToStart goes on top (executes first)
    while (!backtrackToStart.empty()) {
        finalPath.push(backtrackToStart.top());
        backtrackToStart.pop();
    }

    return finalPath;
}

void exploreNeighbors_TeamOne(pair<int, int> currentLocation,
                              map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap,
                              queue<pair<int, int>>& pointQueue,
                              set<pair<int,int>>& walls,
                              Racer* car) {

    //FIXME - indices to match the global ------------------------

    const int NUM_DIRECTIONS = 4;
    DIRECTION directions[NUM_DIRECTIONS] = {NORTH, SOUTH, EAST, WEST}; // order of exploration: right, down, left, up

    /*for (int i = 0; i < NUM_DIRECTIONS; i++) {
        bool isWalll = car->look(directions[i]);
        pair<int, int> neighbor = currentLocation;
        updateCurrentLocation(neighbor, directions[i]);


        // case where there is a wall in the direction we are looking, so we add it to the walls set
        if (isWalll && neighbor.first >= 0 && neighbor.second >= 0) {
            cout << "Wall? " << neighbor.first << " " << neighbor.second << endl;
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
    }*/

    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        bool isWall = car->look(directions[i]);
        pair<int, int> neighbor = currentLocation;
        updateCurrentLocation(neighbor, directions[i]);

        if (isWall) {
            // wall — add to walls set, never touch parentMap
            walls.insert({neighbor.first, neighbor.second});
        }
        else if (parentMap.find(neighbor) == parentMap.end()) {
            // open path we haven't visited — add to parentMap and queue
            parentMap[neighbor] = {currentLocation, directions[i]};
            pointQueue.push(neighbor);
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
                              queue<pair<int, int>>& pointQueue,
                              Racer* car, map<pair<int,int>, pair<pair<int, int>, DIRECTION>>& parentMap) {
    // static variables declarations inside function

    // Note from TJ: I'm contemplating whether or not I should use color so I'm omitting for now
    static stack<DIRECTION> pathToTarget;
    static pair<int, int> targetLocation = {0, 0};
    // start and end location were moved to be local to the TeamOneNextMove()
    static bool isPathing = false;
    static bool isQueueInitialized = false;

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

    /* loop while the pointQueue is not empty and we are not currently pathing to a target
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
            exploreNeighbors_TeamOne(currentLocation, parentMap, pointQueue, walls, car);  //point queue is expree
            pathToTarget = reconstructPath_Backtrack_TeamOne(currentLocation, startLocation, parentMap);
            cout << "PATH SIZE " << pathToTarget.size() << endl;

            isPathing = true;
            DIRECTION nextMove = pathToTarget.top();
            pathToTarget.pop();
            updateCurrentLocation(currentLocation, nextMove);
            cout << "RETURNING " << nextMove << endl;
            return nextMove;
        }
    }*/

    while (!pointQueue.empty() && !isPathing) {
        targetLocation = pointQueue.front();

        if (!(currentLocation.first == targetLocation.first &&
              currentLocation.second == targetLocation.second)) {
            // path to the next unvisited node
            //pathToTarget = reconstructPath_TeamOne(currentLocation, targetLocation, parentMap);
            cout << "Building path from: " << currentLocation.first << "," << currentLocation.second
                 << " to target: " << targetLocation.first << "," << targetLocation.second << endl;
            //pathToTarget = reconstructPath_Backtrack_TeamOne(startLocation, currentLocation, targetLocation, parentMap);

            //Are we right next to the target location?
            if (parentMap.count(targetLocation) &&
                parentMap.at(targetLocation).first == currentLocation) {
                pathToTarget = stack<DIRECTION>();
                pathToTarget.push(parentMap.at(targetLocation).second);
            } else {
                pathToTarget = reconstructPath_Backtrack_TeamOne(startLocation, currentLocation, targetLocation, parentMap);
            }

            cout << "PATH SIZE " << pathToTarget.size() << endl;
            isPathing = true;
            DIRECTION nextMove = pathToTarget.top();
            pathToTarget.pop();
            updateCurrentLocation(currentLocation, nextMove);
            return nextMove;
        }
        else {
            // arrived at target, explore and move on
            pointQueue.pop();
            isPathing = false;
            exploreNeighbors_TeamOne(currentLocation, parentMap, pointQueue, walls, car);
            // loop back up - will now path toward next queue entry
        }
    }
    // if you are getting here, it means the queue is empty and you haven't found the target
    // which should never happen since the mazes are guaranteed to have a solution, but if it does
    // just return something
    assert(false); // should never reach here
}

#endif /* RACECARDRIVER_H_ */
