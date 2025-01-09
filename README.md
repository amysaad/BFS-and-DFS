# Project Title

Title: Pathfinding using Breadth-First Search (BFS) or Depth-First Search (DFS)

Use/purpose of project: The purpose of this project is to find a path through a given maze using breadth-first search (BFS) and depth-first search (DFS) algorithms.

## Description

Overview of use: This project provides a C++ implementation to solve mazes using both breadth-first search (BFS) and depth-first search (DFS) algorithms. It consists of classes representing a maze, positions within the maze, and utility functions for loading maps, solving mazes, and searching for solutions.

### Directories and Files

- main.cpp: This file contains the main logic of the maze solver program, along with test cases to verify the functionality of various components

- maze.cpp: This file encapsulates the implementation of the `Maze` class, which represents a maze and provides methods for solving it using breadth-first search (BFS) and depth-first search (DFS) algorithms

- maze.h: This file is a header file defining the `Maze` class, including its member functions and data members. It serves as a way to interact with the `Maze` class from other parts of the program

- positions.cpp: This file implements the `Position` class, which represents individual positions within a maze. This file contains the functionality to set positions as walls, check if positions are walls, and to obtain the coordinates of positions

- positions.h: This file is a header file defining the `Position` class, including its member functions and data members. It serves as a way to interact with the `Position` class from other parts of the program

- mazeUtils.cpp: This file provides utility functions for the maze solver program, including functions for loading maze maps from files and rendering solutions. It implements the `loadMap` function for loading maps and the `renderAnswer` function for rendering solutions.

- mazeUtils.h: This file is a header file defining utility functions for the maze solver program. It includes declarations for the `loadMap` and `renderAnswer` functions, allowing other parts of the program to utilize these utilities.


## Getting Started 

### Dependencies

- C++ compiler: C++ compiler installed on system to compile the source code

- Standard Template Library (STL): The program utilizes standard C++ libraries such as <vector>, <queue>, <stack>, and <unordered_map> (included with most C++ compilers)

- Compatible with various operating systems (Windows, macOS, Linux, etc)


### Installing / Compiling

- Download the project from the repository to your computer

- Open the project in JetBrains CLion IDE

- Make sure that CLion and CMake build are updated to the most recent version

- Ensure that you have a C++ compiler and Standard Template Library (STL) installed

- Build the project using the CMakeLists.txt file

- Ensure the test.cpp file is NOT included in the CMakeLists.txt file. Due to duplicate _main, including test.cpp will result in the program crashing


### Executing Program

- Enter the name of the maze (.map) file you want to use to BFS of DFS

- Enter BFS or DFS depending on which search algorithm you want (caps-LOCK on)

- Enter a name for the output file (.txt) to display the path

- The program will load the maze, execute the chosen search algorithm, and create the .txt file containing the path for the map

Sample input: 

Welcome to the A-maze-ing Race.

Please enter your maze file: 
map_file_name.map

Which search algorithm to use (BFS or DFS)? 
DFS

Sample output: 

Loading cycle.map...
@@###
#@@@#
#@#@#
#@@@@
####@

DFS Searching...
@@###
#@..#
#@#.#
#@@@@
####@

Path length: 9
# of visited nodes: 9
What is the name of the output file? output_file_name_choice.txt

## Help

- Make sure that CLion and CMake build are updated to the most recent version, or the program will not run

- Ensure the test.cpp file is NOT included in the CMakeLists.txt file. Due to duplicate _main, including test.cpp in the CMakeLists.txt will result in the program crashing


## Version

CLion Info: CLion 2023.3.4, build CL-233.14475.31. Copyright JetBrains s.r.o., (c) 2000-2024

CMake Info: Version 3.29.0

## License

## Acknowledgements 

// To implement
void Graph::BFS(){
    queue <int> myQueue;
    bool * visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
    
    if (visited[0] == false) {
        
        myQueue.push(0);
        visited[0] = true;
        while (!myQueue.empty()) {
            list<int>::iterator i;
            int node = myQueue.front();
            for (i = adj[node].begin(); i != adj[node].end(); i++) {
                if (!visited[*i]) {
                    cout << *i <<endl;
                    visited[*i] = true;
                    myQueue.push(*i);
                }

            }
            myQueue.pop();
        }

    void BFS(int s)
    {
        for(auto i : visited) i = false;
        list<int> q;
        visited[s] = true;
        q.push_back(s);
        while (!q.empty())
        {
            s = q.front();
            cout<<s<<" ";
            q.pop_front();
            for(auto i : Edge[s])
            {
                if(!visited[i])
                {
                    visited[i] = true;
                    q.push_back(i);
                }
            }
        }

    }
//returns path from->to
list<string> SearchingProblem::BFS(string start, string goal)
{
    list<string> path;
    map<string,string> parent;
    deque<string> frontier;     //treat like queue and push at back and pop from front
    set<string> explored;
    string current;
    if(start == goal)
        return path;

    frontier.push_back(start);

    while(!frontier.empty())
    {
        current = frontier.front();
        frontier.pop_front();
        explored.insert(current);
        list<string> neighbours = getNeighbours(current);
        neighbours.reverse();
        for(list<string>::iterator it = neighbours.begin(); it!=neighbours.end(); ++it )
        {
            string child = *it;
            if(explored.find(child) == explored.end() && find(frontier.begin(),frontier.end(),child)==frontier.end())
            {
                parent[child] = current;
                if(child==goal)
                {
                    //construct path
                    while(child!=start)
                    {
                        path.push_back(child);
                        child = parent[child];
                    }
                    path.push_back(start);
                    cout<<"Size of explored set= "<<explored.size()<<endl;
                    path.reverse();
                    return path;
                }
                frontier.push_back(child);
            }
        }
    }
    return path;
}
