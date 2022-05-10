#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <set>
#include "AdjacencyLists.h"

using std::map;
using std::vector;
using std::list;
using std::string;
using std::cout;
using std::fstream;
using std::pair;
using std::set;

// Function for finding all words of a given length and creates elements of a map container
// which has as key a pattern and as values a list of words which correspond to that pattern
map<string, vector<string>> getWords(string filePath, int length);

// Function for getting all possible patterns of a word and adding them to a map
void addPattern(map<string, vector<string>>& wordMap, string word);

// Function for creating graph of words that follow a pattern
Graph<string> createPatternGraph(map<string, vector<string>> wordsMap);

// Class for managing game

class Game {
public:
	// Constructors
	Game();
	Game(Graph<string> graph);

	// Operations
	vector<string> getWordsPath(string root, string goal);
	
	// CSV file management
	std::vector<string> tokenize(string str, char delimiter);
	int loadFromCsv(string csvPath, string userName);
	bool saveCsv(string csvPath, string name, string startingWord, string targetWord, string dateTime, int nrOfHints, vector<string> usedWords, int nrOfMoves);

private:
	Graph<string> graph;
	friend class Graph<string>;
	friend class UI;
};