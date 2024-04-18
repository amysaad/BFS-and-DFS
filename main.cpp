/* Comp 318 Spring 2023, programming assignment 2
 * Copyright (c) 2023
 * Wheaton College, Computer Science Department, Norton MA
 * M. Gagne
 */

#include <iostream>
#include <fstream>
#include <string>
#include <utility>

#include "maze.h"
#include "mazeUtils.h"

using namespace std;

int main() {
    // Initial code to read input from cin.
    // You shouldn't need to modify this portion of code
    cout << "Welcome to The A-Maze-ing Race.\n";
    string map;
    cout << "Please enter your maze file: \n";
    cin >> map;

    string search;
    cout << "Which search algorithm to use (BFS or DFS)? \n";
    cin >> search;

    // Creates vector of position pointers to store maze solution and loads chosen map into "labyrinth"
    vector<Position*> solution;
    Maze* labyrinth = loadMap(map);

    // Validate the search algorithm chosen by the user
    if (search == "BFS") {
        // Solve the maze using Breadth-First Search algorithm
        solution = labyrinth->solveBreadthFirst();
    } else if (search == "DFS") {
        // Solve the maze using Depth-First Search algorithm
        solution = labyrinth->solveDepthFirst();
    } else {
        // Print an error message for invalid algorithm choice
        cerr << "ERROR: Invalid Algorithm. Please choose either 'BFS' or 'DFS'.\n";
        delete labyrinth; // Free memory allocated for the maze
        return 1; // Exit the program with an error code
    }

    // Check if solution is empty indicating an invalid maze file
    if (solution.empty()) {
        cerr << "ERROR: Invalid Maze File.\n";
        delete labyrinth; // Free memory allocated for the maze
        return 1; // Exit the program with an error code
    }

    // Prompt user to input name of output file
    string filename; // Stores name of output file
    cout << "What is the name of the output file? ";
    cin >> filename;

    // Open the maze file and prints
    cout << "\nLoading " << map << "..." << endl;
    ifstream mazeFile(map);
    if (mazeFile.is_open()) {
        string line;
        while (getline(mazeFile, line)) {
            cout << line << endl;
        }
        mazeFile.close();
        cout << endl;

    } else {
        cerr << "ERROR: Unable to open maze file.\n";
        return 1; // Exit the program with an error code
    }

    // Render the solution and output it to the console
    cout << "Searching " << search << "..." << endl;
    string solutionString = renderAnswer(labyrinth, solution);
    cout << solutionString << endl;
    cout << "Path Length: " << labyrinth->getPathLength() << endl;
    cout << "Number of Visited Nodes: " << labyrinth->getNumVisitedNodes() << endl;

    // Opens output file and renders the output to said file then closes the file
    ofstream outfile;
    outfile.open(filename);
    outfile << solutionString; // Use the rendered solution string obtained earlier
    outfile.close();

    // Free memory allocated for the maze
    delete labyrinth;

    return 0;
}
