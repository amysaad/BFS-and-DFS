/* Comp 318 Spring 2023, programming assignment 2
 * Copyright (c) 2023
 * Wheaton College, Computer Science Department, Norton MA
 * J. Mndolwa and A. Saad
 */

#include <stdexcept>

/* STL libraries needed */
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

#include "maze.h"
#include "position.h"

using namespace std;

// Constructor for Maze class
Maze::Maze(int width, int height) {
    mazeHeight = height;    // Stores the maze height
    mazeWidth = width;      // Stores the maze width
    pathLength = 0;         // Initialize path length
    numVisitedNodes = 0;    // Initialize number of visited nodes

    // Allocate memory for the positions array
    positions = new Position **[mazeWidth]; // Use mazeWidth as the size for the first dimension

    // Loop to initialize each column
    for (int i = 0; i < mazeWidth; i++) {
        // Allocate memory for each row in the column
        positions[i] = new Position *[mazeHeight]; // Use mazeHeight as the size for the second dimension

        // Loop to initialize each row
        for (int j = 0; j < mazeHeight; j++) {
            // Create a new Position object and store it in the array
            positions[i][j] = new Position(i, j); // Pass the column and row indices to the Position constructor
        }
    }
}

// Destructor for Maze class
Maze::~Maze() {
    // Deletes the maze's position pointers
    for (int i = 0; i < mazeHeight; i++) {
        for (int n = 0; n < mazeWidth; n++) {
            delete positions[n][i]; // Deletes every single Position object.
        }
    }

    // The secondary arrays (inside other arrays) are deleted.
    for (int i = 0; i < mazeWidth; i++) {
        delete [] positions[i]; // Delete each secondary array
    }

    // Deletes the main array, which has arrays in it.
    delete [] positions; // Deletes the main array.

}

// Get the width of the maze
int Maze::getWidth() {
    return mazeWidth;
}

// Get the height of the maze
int Maze::getHeight() {
    return mazeHeight;
}

// Check if a position is a wall
bool Maze::isWall(int x, int y) {
    // To determine if a position is a wall, an If statement is used.
    if (positions[x][y]->isWall()) {
        return true; // If the position is a wall, returns true.
    }else{
        return false;   // If the position is not a wall, returns false.
    }
}

// Set a position as a wall
void Maze::setWall(int x, int y) {
    positions[x][y]->setWall();     // Sets a position as a wall
}

// Solve the maze using breadth-first search
vector<Position*> Maze::solveBreadthFirst() {
    // Unordered map to keep track of positions visited
    unordered_map <string, Position*> visited;

    // Vector to store the final path if it exists
    vector<Position*> path;

    // Empty vector to indicate no path exists
    vector<Position*> no_path;

    // Vector to store the neighbors of the current position
    vector<Position*> neighbors;

    // Queue for the BFS traversal
    queue<Position*> pathfinder;

    // Start position (top left corner of the maze)
    Position* start = positions[0][0];

    // Mark start as visited with nullptr as its predecessor
    visited[start->to_string()] = nullptr;

    // Destination position (bottom right corner of the maze)
    Position* destination = positions[mazeWidth - 1][mazeHeight - 1];

    // Push the start position into the queue
    pathfinder.push(start);

    // BFS traversal loop
    while (!pathfinder.empty()) {
        Position* current = pathfinder.front(); // Get the current position from the front of the queue
        pathfinder.pop(); // Remove the current position from the queue

        numVisitedNodes++;

        // If the destination is reached, reconstruct the path
        if (current == destination) {
            // Reconstruct the path by tracing back through the predecessors
            while (current != nullptr) {
                path.push_back(current); // Add the current position to the path
                current = visited[current->to_string()]; // Move to the predecessor position
            }
            reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            pathLength = path.size();
            return path; // Return the path
        } else {
            // Get the neighbors of the current position
            neighbors = getNeighbors(current);
            // Visit each unvisited neighbor
            for (Position* neighbor : neighbors) {
                // If the neighbor has not been visited yet
                if (visited.find(neighbor->to_string()) == visited.end()) {
                    visited[neighbor->to_string()] = current; // Mark the neighbor as visited with current as its predecessor
                    pathfinder.push(neighbor); // Add the neighbor to the queue for further exploration
                }
            }
        }
    }
    // If no path is found, return an empty vector
    return no_path;
}

// Solve the maze using depth-first search
vector<Position*> Maze::solveDepthFirst() {
    // Unordered map to store visited positions with their predecessors
    unordered_map<string, Position*> visited;

    // Vector to store the final path if it exists
    vector<Position*> path;

    // Empty vector to indicate no path exists
    vector<Position*> no_path;

    // Vector to store the neighbors of the current position
    vector<Position*> neighbors;

    // Stack for the DFS traversal
    stack<Position*> pathfinder;

    // Start position (top left corner of the maze)
    Position* start = positions[0][0];

    // Mark start as visited with nullptr as its predecessor
    visited[start->to_string()] = nullptr;

    // Destination position (bottom right corner of the maze)
    Position* destination = positions[mazeWidth - 1][mazeHeight - 1];

    // Push the start position into the stack
    pathfinder.push(start);

    // DFS traversal loop
    while (!pathfinder.empty()) {
        Position* current = pathfinder.top(); // Get the current position from the top of the stack
        pathfinder.pop(); // Remove the current position from the stack

        numVisitedNodes++;

        // If the destination is reached, reconstruct the path
        if (current == destination) {
            // Reconstruct the path by tracing back through the predecessors
            while (current != nullptr) {
                path.push_back(current); // Add the current position to the path
                current = visited[current->to_string()]; // Move to the predecessor position
            }
            reverse(path.begin(), path.end()); // Reverse the path to get the correct order
            pathLength = path.size();
            return path; // Return the path
        } else {
            // Get the neighbors of the current position
            neighbors = getNeighbors(current);
            // Visit each unvisited neighbor
            for (Position* neighbor : neighbors) {
                // If the neighbor has not been visited yet
                if (visited.find(neighbor->to_string()) == visited.end()) {
                    visited[neighbor->to_string()] = current; // Mark the neighbor as visited with current as its predecessor
                    pathfinder.push(neighbor); // Add the neighbor to the stack for further exploration
                }
            }
        }
    }
    // If no path is found, return an empty vector
    return no_path;

}

vector<Position*> Maze::getNeighbors(Position* position) {
    int xPos = position->getX(); // Get the x position of the current position
    int yPos = position->getY(); // Get the y position of the current position

    vector<Position*> neighbors; // Vector to store the neighboring positions

    // Check if the position above is within bounds and not a wall
    if (yPos - 1 >= 0 && !(positions[xPos][yPos - 1]->isWall())) {
        Position* position_top = positions[xPos][yPos - 1];
        neighbors.push_back(position_top); // Add the top neighbor to the vector
    }

    // Check if the position to the left is within bounds and not a wall
    if (xPos - 1 >= 0 && !(positions[xPos - 1][yPos]->isWall())) {
        Position* position_left = positions[xPos - 1][yPos];
        neighbors.push_back(position_left); // Add the left neighbor to the vector
    }

    // Check if the position to the right is within bounds and not a wall
    if (xPos + 1 < getWidth() && !(positions[xPos + 1][yPos]->isWall())) {
        Position* position_right = positions[xPos + 1][yPos];
        neighbors.push_back(position_right); // Add the right neighbor to the vector
    }

    // Check if the position below is within bounds and not a wall
    if (yPos + 1 < getHeight() && !(positions[xPos][yPos + 1]->isWall())) {
        Position* position_bottom = positions[xPos][yPos + 1];
        neighbors.push_back(position_bottom); // Add the bottom neighbor to the vector
    }

    return neighbors; // Return the vector containing the neighboring positions
}

int Maze::getPathLength() const {
    return pathLength;
}

int Maze::getNumVisitedNodes() const {
    return numVisitedNodes;
}

