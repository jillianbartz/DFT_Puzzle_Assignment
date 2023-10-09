#ifndef TEST_H__
#define TEST_H__
#include <string>
#include <iostream>
#include <fstream>
#include <array>

#include "../code_1/Puzzle.hpp"

using namespace std;

// TODO add detailed explanation on what the function should do
std::string exec(const char* cmd);
std::string readFileIntoString(std::string fileName);
string test_createDefaultPuzzle(int);
string test_createPath (Puzzle&, int, int);
string test_printPuzzle (Puzzle&);
string test_convertPuzzleToAdjacencyListGraph(Puzzle&);
string test_findPathThroughPuzzle(Puzzle&);
#endif // TEST_H__