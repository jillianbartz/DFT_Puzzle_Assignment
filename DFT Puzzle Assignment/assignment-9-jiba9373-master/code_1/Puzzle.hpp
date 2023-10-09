#ifndef PUZZLE_H
#define PUZZLE_H
#include<vector>
#include<iostream>
using namespace std;

struct vertex;
struct adjVertex{
    vertex *v;
};

struct vertex{
    int vertexNum;
    bool visited = false;
    vector<adjVertex> adj;
};

class Puzzle
{
    public:
        Puzzle(int n = 0); 
        ~Puzzle(); 
        void createDefaultPuzzle();
        void createPath(int i, int j);
        void printPuzzle(); 
        int findVertexNumFromPosition(int x, int y);
        void addVertex(int num);
        void addEdge(int v1, int v2);
        void displayEdges();
        vector<int> findOpenAdjacentPaths(int x, int y);
        void convertPuzzleToAdjacencyListGraph(); 
        bool checkIfValidPath();
        bool findPathThroughPuzzle(); 

    private:
        int n;
        int ** puzzle; 
        vector<int> path; 
        vector<vertex*> vertices; //Graph of Vertices from Puzzle
};

#endif // PUZZLE_H
