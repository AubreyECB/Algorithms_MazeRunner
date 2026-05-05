#ifndef RACECARDRIVER_H_
#define RACECARDRIVER_H_

#include "Racer.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cassert>

using namespace std;

// Needs to be moved INSIDE the function or he wont count it
struct Point {
	int x;
	int y;
};

class RaceCarDriver{
private:
	Racer* car;

	// Starting point of the maze
	Point startPos = {0, 0}; // Need to replace getLocation.

	// Using a set to track visited locations
	set<pair<int,int>> visited;

	// Current direction of the car
	DIRECTION currDir = EAST;

	    }

	// BFS variables
	queue<Point> pointQueue;

	// used to map the points to the path
	// point doesn't have a comparison operator, so we have to use a pair of ints to represent the point
	// the point is the parent point 
	map<pair<int,int>, pair<Point, DIRECTION>> parentMap;
	bool isQueueInitialized = false;

	// direction array for BFS
	const DIRECTION directions[4] = {EAST, SOUTH, NORTH, WEST};


public:
	RaceCarDriver(Racer* p = nullptr): car{p}{}

	// // Emeka's DFS Next Move Implementation
	// DIRECTION DFSNextMove() {

	// 	// Retrive the current location of the car
	// 	point currLoc = startPos; // car->getLocation();

	// 	// Utilized to track that if all directions have been iterated through
	// 	int directionsTried = 0;

	// 	while (!iterationDone(directionsTried)) {
	// 		// Getting the neighboring point in the current direction
	// 		point neighbor = iterationCurrent(currLoc);

	// 		// Check if the neighboring point is open and unvisited
	// 		if (!car->look(currDir) && visited.find({neighbor.x, neighbor.y}) == visited.end()) {
	// 			 DIRECTION moveDir = currDir; // Store the direction to move before modifying currDir

	// 			// If it is, push the current direction to the stack and return it
	// 			iterationBegin(); // Reset the current direction to EAST for the next iteration

	// 			// Mark the current location as visited
	// 			visited.insert({neighbor.x, neighbor.y});
				
	// 			dfsPath.push(moveDir); // Push the direction to the stack before returning
	// 			return moveDir;
	// 		} 
			
	// 		else {
	// 			// If it isn't, advance to the next direction and increment the directionsTried counter
	// 			iterationAdvance();
	// 			directionsTried++;
	// 		}
	// 	}

	// }
	
	// TJ's BFS Next Move Implementation
    //TODO: Hannah - the BFS continues, even after finding the end and printing a time. how come?
	void initializeBFS() {
		Point start = startPos;
		pointQueue.push(start);
		parentMap[{start.x, start.y}] = {start, NORTH}; // dummy value to represent the start point
		isQueueInitialized = true;
	}

	DIRECTION BFSNextMove() {
		// initialize the point queue if this is the first BFS Run
		if (!isQueueInitialized) {
			initializeBFS();
		}

		// case where queue is empty before looking for next move

		// this case should never happen because the mazes have guaranteed solutions
        //FIXME: I commented out bc it threw assert before end - H
		/*if (pointQueue.empty()) {
			assert(false);
			return EAST;
		}*/

		// take note of the real location of the car
		Point realLocation = startPos;

		Point currentPoint = pointQueue.front();
		pointQueue.pop();

		// car is set to the current point so we can look around it and find its neighbors
        cout << "about to teleport to: " << currentPoint.x << "," << currentPoint.y << endl; // cheking a print
        car->setLocation(currentPoint);

        //FIXME: H - the code is segfaulting for pixeling, think its looking too far (out of bounds) - check here:
        if(currentPoint.x < 0 || currentPoint.y < 0 ||
           currentPoint.x >= col || currentPoint.y >= row) {
            cout << "within bounds!" << endl;
            car->setLocation(realLocation);

            cout << "realLocation: " << realLocation.x << "," << realLocation.y << endl;
            cout << "queue size: " << pointQueue.size() << endl;
        }

		const int DIRECTIONS = 4;

		for (int i = 0; i < DIRECTIONS; i++) {
			// case where the move is open
			if (!car->look(directions[i])) {
				// set nextPoint to currentPoint so we have a reference

                cout << "looking direction: " << directions[i] << endl; // print for checking

                Point neighbor = currentPoint;
				if (directions[i] == EAST) {
					neighbor.x++;
				} else if (directions[i] == SOUTH) {
					neighbor.y++;
				} else if (directions[i] == WEST) {
					neighbor.x--;
				} else if (directions[i] == NORTH) {
					neighbor.y--;
				}

				// make sure we haven't already been to nextPoint
				pair<int, int> neighborPair = make_pair(neighbor.x, neighbor.y);
				// case where we haven't been to neighbor
				if (parentMap.find(neighborPair) == parentMap.end()) {
					parentMap[neighborPair] = {currentPoint, directions[i]};

                    //FIXME: H - ensuring it doesnt push junk
                    cout << "pushing neighbor: " << neighbor.x << "," << neighbor.y << endl;
					pointQueue.push(neighbor);
				}
			}
		}

		// set back to the real location of the car before returning the next move
		car->setLocation(realLocation);

		// this case should never happen because the mazes have guaranteed solutions
		if (pointQueue.empty()) {
			//assert(false); // H - remove assert? whys that there
			return EAST;
		}

		Point nextPoint = pointQueue.front();
		//int displacementX = nextPoint.x - realLocation.x;
		//int displacementY = nextPoint.y - realLocation.y;
		//based on the displacement, determine the direction to move
		// if there are no points, skip it
		/*if (displacementX == 1 && displacementY == 0) {
			return EAST;
		}
		else if (displacementX == -1 && displacementY == 0) {
			return WEST;
		}
		else if (displacementX == 0 && displacementY == 1) {
			return SOUTH;
		}
		else if (displacementX == 0 && displacementY == -1) {
			return NORTH;
		}
		else {
			pointQueue.pop();
			return BFSNextMove();
		} */

        /**TODO: H - this loop is the same as your code above, just w/o the recursion piece:
         * The recursive piece was causing a seg fault since bfs was trying to access and look
         * at points too far in advance, and trying to call on those points - but they're null/out of bounds
         * the for loop allows for checking, but only the adjacent points, that can be accessed w data
         * are called on and used- or else skipped
         * */

        while (!pointQueue.empty()) {
            Point nextPoint = pointQueue.front();
            int displacementX = nextPoint.x - realLocation.x;
            int displacementY = nextPoint.y - realLocation.y;

            if (displacementX == 1 && displacementY == 0) return EAST;
            else if (displacementX == -1 && displacementY == 0) return WEST;
            else if (displacementX == 0 && displacementY == 1) return SOUTH;
            else if (displacementX == 0 && displacementY == -1) return NORTH;
            else pointQueue.pop();
        }

        //assert(false); // should never reach here - so why is itt here
        return EAST;
	}



	// this is gievn that we keep track of the start and end points of the maze
	vector<DIRECTION> reconstructPath(Point start, Point end) {
		vector<DIRECTION> path;
		Point current = end;

		while (!(current.x == start.x && current.y == start.y)) {
			pair<Point, DIRECTION> parent = parentMap[{current.x, current.y}];
			path.push_back(parent.second);
			current = parent.first;
		}

		reverse(path.begin(), path.end());
		return path;
	}


	DIRECTION nextMoveTeamOne() {
		
	}

};


#endif /* RACECARDRIVER_H_ */
