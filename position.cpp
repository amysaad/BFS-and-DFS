/* Comp 318 Spring 2023, programming assignment 2
 * Copyright (c) 2023
 * Wheaton College, Computer Science Department, Norton MA
 * M. Gagne
 */

#include "position.h"
#include <stdexcept>
#include <string>

using namespace std;

Position::Position(int x, int y) {
    xPos = x; //Set the x coordinate of the position
    yPos = y; //Set the y coordinate of the position
    wall = false; //Initialize the position as not being a wall
}

// Return the x coordinate of the position
int Position::getX()  {
    return xPos;
}

// Return the y coordinate of the position
int Position::getY() {
    return yPos;
}

// Set the position as a wall
void Position::setWall()  {
    wall = true;
}

// Check if the position is a wall
bool Position::isWall()  {
    if (wall) {
        return true; // Return true if the position is a wall
    } else {
        return false; // Return false if the position is not a wall
    }}

// Convert the position coordinates to a string representation
string Position::to_string()  {
    string position = "(" + ::to_string(xPos) + "," + ::to_string(yPos) + ")";
    return position; // Returns position string
}
