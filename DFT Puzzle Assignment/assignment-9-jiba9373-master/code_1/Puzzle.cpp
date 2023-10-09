#include "Puzzle.hpp"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

Puzzle::Puzzle(int n){
    this->n = n;
}

void Puzzle::addEdge(int v1, int v2){
    //TODO
    for(long unsigned int i = 0; i < vertices.size(); i++){
        if(vertices[i]->vertexNum == v1){
            for(long unsigned int j = 0; j < vertices.size(); j++){
                if(vertices[j]->vertexNum == v2 && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);
                }
            }
        }
    }

}

void Puzzle::addVertex(int num){
    //TODO
    bool visited = false;
    for(long unsigned int i = 0; i < vertices.size(); i++){
        if(vertices[i]->vertexNum == num){
            visited = true;
        }
    }
    if(visited == false){
        vertex * v = new vertex;
        v->vertexNum = num;
        vertices.push_back(v);
    }
}

void Puzzle::displayEdges(){
    //TODO
    for(long unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->vertexNum<<" --> ";
        for(long unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout << vertices[i]->adj[j].v->vertexNum << " ";
        }
        cout<<endl;
    }
}

// Finds the vertex number from the position of the open path in the maze
int Puzzle::findVertexNumFromPosition(int x, int y){
    //TODO
    if (x < n && x >= 0 && y < n && y >= 0)
    {
        return (y + n * x);
    }
    return -1;
}

// Creates a default maze of all 1s of size n x n, except for positions (0,0) and (n-1, n-1)
void Puzzle::createDefaultPuzzle(){
    //TODO
    puzzle = new int*[n];  // i dont understand this part at all, like what is the point of a double pointer if a double array exists
    
    for (int i = 0; i < n; i++)
    {
        puzzle[i] = new int[n];
    }
    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            puzzle[k][l] = 1;
        }
    }
    puzzle[0][0] = 0;
    puzzle[n-1][n-1] = 0;
}

void Puzzle::createPath(int i, int j){
    //TODO
    if (i < n && i >= 0 && j < n && j >= 0)
    {
        puzzle[i][j] = 0;
    }
    
}

void Puzzle::printPuzzle(){
    //TODO
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n-1)
            {
                cout << "| " << puzzle[i][j] << " |" << endl;
            }
            else
            {
                cout << "| " << puzzle[i][j] << " ";
            }
        }
    }
}

vector<int> Puzzle::findOpenAdjacentPaths(int x, int y){
    vector<int> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= n){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= n){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && puzzle[i][j] == 0){
                neighbors.push_back(findVertexNumFromPosition(i, j));
            }
        }
    }
    return neighbors;
}

void Puzzle::convertPuzzleToAdjacencyListGraph(){
    //TODO
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (puzzle[i][j] == 0)
            {
                int v = 0;
                vector<int> local;
                v = findVertexNumFromPosition(i, j);
                addVertex(v);
                local = findOpenAdjacentPaths(i, j);
                for (long unsigned int w = 0; w < local.size(); w++)
                {
                    addEdge(v, local[w]);
                }
            }
        }
    }
}

bool isChecked (vertex *m)
{
    for (int i = 0; i < m->adj.size(); i++)
    {
        if (m->adj[i].v->visited != true)
        {
            return false;
        }
    }
    return true;
}

void DFTraversal(vertex *n, vertex *start, vertex *end)
{
    if (n->vertexNum == 0)
    {
        cout << "Starting at vertex: 0" << endl;
    }
    cout << "Reached vertex: " << n->vertexNum << endl;
    n->visited = true;
    
    for(int x = 0; x < n->adj.size(); x++ )
    {
        // TODO
        if (n->adj[x].v->visited != true)
        {
            DFTraversal(n->adj[x].v, start, end);
            if (!isChecked(n) || end->visited == false)
            {
                cout << "Backtracked to vertex: " << n->vertexNum << endl;
            }
        }
    }
}

bool Puzzle::findPathThroughPuzzle(){
    DFTraversal(vertices[0], vertices[0], vertices[n]);
    if (vertices[n]->visited == false)
    {
        return false;
    }
    return true;
}

bool Puzzle::checkIfValidPath(){
    //TODO
    if (findPathThroughPuzzle() == true)
    {
        return true;
    }
    return false;
}

Puzzle::~Puzzle(){
    if (n > 0){
        for(int i = 0; i < n; i++){
            delete[] puzzle[i];
        }
        delete[] puzzle;
    }
    for (unsigned int i = 0; i< vertices.size(); i++){
        delete vertices[i]; 
    }
}
