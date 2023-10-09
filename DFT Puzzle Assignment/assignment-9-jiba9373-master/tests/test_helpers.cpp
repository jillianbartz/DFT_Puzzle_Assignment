#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/Puzzle.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_createDefaultPuzzle (int n) {
    testing::internal::CaptureStdout();
    Puzzle pz(n);

    pz.createDefaultPuzzle();
    pz.printPuzzle();
    
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_createPath (Puzzle &pz, int x, int y) {
    testing::internal::CaptureStdout();

    pz.createPath(x, y);
    pz.printPuzzle();

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_printPuzzle (Puzzle &pz) {
    testing::internal::CaptureStdout();

    pz.printPuzzle();

    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_convertPuzzleToAdjacencyListGraph(Puzzle &p){
    testing::internal::CaptureStdout();
    
    p.convertPuzzleToAdjacencyListGraph();
    p.displayEdges();
    
    string output = testing::internal::GetCapturedStdout();
    
    return output;
    
}

string test_findPathThroughPuzzle(Puzzle &p){
    testing::internal::CaptureStdout();
    
    p.convertPuzzleToAdjacencyListGraph();
    cout<<p.findPathThroughPuzzle()<<endl;
    
    string output = testing::internal::GetCapturedStdout();
    
    return output;
}
    