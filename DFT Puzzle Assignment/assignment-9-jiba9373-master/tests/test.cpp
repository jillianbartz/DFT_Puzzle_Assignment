// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"
#include "../code_1/Puzzle.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;

/////////////////////////////////////////
// Tests start here for Assn-9
/////////////////////////////////////////

TEST_F(test_x, testCreateDefaultPuzzle) {
    string result, expected;

    // Puzzle size 1
    int puzzleSize = 1;
    result = test_createDefaultPuzzle (puzzleSize);
    expected = "| 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2.5);

    // Puzzle size 3
    puzzleSize = 3;
    result = test_createDefaultPuzzle (puzzleSize);
    expected = "| 0 | 1 | 1 |\n| 1 | 1 | 1 |\n| 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2.5);

    // Puzzle size 5
    puzzleSize = 5;
    result = test_createDefaultPuzzle (puzzleSize);
    expected = "| 0 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
}

TEST_F(test_x, testCreatePath) {
    string result, expected;

    // Test 1
    int puzzleSize = 3;
    Puzzle pz (puzzleSize);
    pz.createDefaultPuzzle();

    result = test_createPath (pz, 1, 1);
    expected = "| 0 | 1 | 1 |\n| 1 | 0 | 1 |\n| 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2.5);

    // Test 2
    pz.createDefaultPuzzle();

    result = test_createPath (pz, 1, 2);
    expected = "| 0 | 1 | 1 |\n| 1 | 1 | 0 |\n| 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(2.5);

    // Test 3
    Puzzle pz1 (5);
    pz1.createDefaultPuzzle();

    result = test_createPath (pz1, 3, 4);
    expected = "| 0 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 0 |\n| 1 | 1 | 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);
    
}

TEST_F(test_x, testPrintPuzzle) {
    string result, expected;

    // Test 1
    int puzzleSize = 3;
    Puzzle pz (puzzleSize);
    pz.createDefaultPuzzle();
    pz.createPath(0, 1);
    pz.createPath(0, 2);
    pz.createPath(2, 2);
    pz.createPath(1, 2);

    result = test_printPuzzle (pz);
    expected = "| 0 | 0 | 0 |\n| 1 | 1 | 0 |\n| 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

    // Test 2
    puzzleSize = 5;
    Puzzle pz1 (puzzleSize);
    pz1.createDefaultPuzzle();
    pz1.createPath(0, 1);
    pz1.createPath(0, 2);
    pz1.createPath(2, 2);
    pz1.createPath(1, 2);

    result = test_printPuzzle (pz1);
    expected = "| 0 | 0 | 0 | 1 | 1 |\n| 1 | 1 | 0 | 1 | 1 |\n| 1 | 1 | 0 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 1 |\n| 1 | 1 | 1 | 1 | 0 |\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(4);

}

TEST_F(test_x, TestFindVertexNumFromPosition){
    
    int output = -1, expected;
    // int puzzleSize = 5;
    Puzzle p(10);
    p.createDefaultPuzzle();
    // Puzzle p(10);
    
    //general case
    expected = 52;
    output = p.findVertexNumFromPosition(5,2);
    ASSERT_EQ(expected,output);
    add_points_to_grade(2);
    
    // index out of bounds
    expected = -1;
    output = p.findVertexNumFromPosition(2,-3);
    ASSERT_EQ(expected,output);
    add_points_to_grade(2);
    
    //index out of bounds
    output = p.findVertexNumFromPosition(25,11);
    ASSERT_EQ(expected,output);
    add_points_to_grade(2);
    
    //index out of bounds
    output = p.findVertexNumFromPosition(-1,2000);
    ASSERT_EQ(expected,output);
    add_points_to_grade(2);
}

TEST_F(test_x, TestConvertPuzzleToAdjacencyListGraph){
    
    // CASE 1
    
    Puzzle p1(3);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p1.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p1.createPath(0, 2); 
    p1.createPath(1, 1); 
    p1.createPath(1, 2);
    p1.createPath(1, 0);
    p1.createPath(2, 1);
    
    string expected = "0 --> 3 4 \n2 --> 4 5 \n3 --> 0 4 7 \n4 --> 0 2 3 5 7 8 \n5 --> 2 4 7 8 \n7 --> 3 4 5 8 \n8 --> 4 5 7 \n";
    string output = test_convertPuzzleToAdjacencyListGraph(p1);
    ASSERT_EQ(expected,output);
    add_points_to_grade(10);
    
    // CASE 2
    
    Puzzle p2(5);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p2.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p2.createPath(0, 2); 
    p2.createPath(0, 2); 
    p2.createPath(0, 2);
    
    expected = "0 --> \n2 --> \n24 --> \n";;
    output = test_convertPuzzleToAdjacencyListGraph(p2);
    ASSERT_EQ(expected,output);
    add_points_to_grade(10);
    
    //CASE 3
    
    Puzzle p3(3);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p3.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p3.createPath(0, 200); 
    p3.createPath(100, 1); 
    
    expected = "0 --> \n8 --> \n";
    output = test_convertPuzzleToAdjacencyListGraph(p3);
    ASSERT_EQ(expected,output);
    add_points_to_grade(10);
}

TEST_F(test_x, TestFindPathThroughPuzzle){
    
    string output="", expected="";
    
    Puzzle p1(5);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p1.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p1.createPath(0, 0);
    p1.createPath(0, 1); 
    p1.createPath(1, 1); 
    p1.createPath(0, 2); 
    p1.createPath(1, 3);
    p1.createPath(2, 2); 
    p1.createPath(3, 1); 
    p1.createPath(4, 1); 
    p1.createPath(4, 2);
    p1.createPath(4, 3);
    p1.createPath(4, 4);
    cout << "[GRADER] Building Adjacency List..."<< endl;
    p1.convertPuzzleToAdjacencyListGraph();
    output = test_findPathThroughPuzzle(p1);
    expected = "Starting at vertex: 0\nReached vertex: 0\nReached vertex: 1\nReached vertex: 2\nReached vertex: 6\nReached vertex: 12\nReached vertex: 8\nBacktracked to vertex: 12\nReached vertex: 16\nReached vertex: 21\nReached vertex: 22\nReached vertex: 23\nReached vertex: 24\n1\n";
    ASSERT_EQ(expected,output);
    add_points_to_grade(15);
    
    Puzzle p2(5);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p2.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p2.createPath(0, 0);
    p2.createPath(0, 1); 
    p2.createPath(1, 1); 
    p2.createPath(0, 2); 
    p2.createPath(1, 3);
    p2.createPath(3, 1); 
    p2.createPath(4, 1); 
    p2.createPath(4, 2);
    p2.createPath(4, 3);
    p2.createPath(4, 4);
    cout << "[GRADER] Building Adjacency List..."<< endl;
    p2.convertPuzzleToAdjacencyListGraph();
    output = test_findPathThroughPuzzle(p2);
    expected = "Starting at vertex: 0\nReached vertex: 0\nReached vertex: 1\nReached vertex: 2\nReached vertex: 6\nBacktracked to vertex: 2\nReached vertex: 8\nBacktracked to vertex: 2\nBacktracked to vertex: 1\nBacktracked to vertex: 0\n0\n";
    ASSERT_EQ(expected,output);
    add_points_to_grade(15);
    
}

TEST_F(test_x, TestCheckIfValidPath){
    
    int output,expected;
    
    Puzzle p1(3);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p1.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p1.createPath(0, 2);
    p1.createPath(2, 0); 
    cout << "[GRADER] Building Adjacency List..."<< endl;
    p1.convertPuzzleToAdjacencyListGraph();
    cout << "[GRADER] Finding Path..."<< endl;
    p1.findPathThroughPuzzle();
    output = p1.checkIfValidPath();
    expected = 0;
    ASSERT_EQ(expected,output);
    add_points_to_grade(4);
    
    Puzzle p(5);
    cout << "[GRADER] Creating Default Puzzle..."<< endl;
    p.createDefaultPuzzle();
    cout << "[GRADER] Creating Path..."<< endl;
    p.createPath(0, 0);
    p.createPath(0, 1); 
    p.createPath(1, 1); 
    p.createPath(0, 2); 
    p.createPath(1, 3);
    p.createPath(2, 2); 
    p.createPath(3, 1); 
    p.createPath(4, 1); 
    p.createPath(4, 2);
    p.createPath(4, 3);
    p.createPath(4, 4);
    cout << "[GRADER] Building Adjacency List..."<< endl;
    p.convertPuzzleToAdjacencyListGraph();
    cout << "[GRADER] Finding Path..."<< endl;
    p.findPathThroughPuzzle();
    output = p.checkIfValidPath();
    expected = 1;
    ASSERT_EQ(expected,output);
    add_points_to_grade(4);
    
}