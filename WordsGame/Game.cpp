#include "Game.h"

map<string, vector<string>> getWords(string filePath, int length)
{
	fstream fin(filePath);
	string currentWord;
	map<string, vector<string>> wordsMap;
	int nr = 0;

	while (!fin.eof()) {
		fin >> currentWord;

		// found a number of given length
		if (currentWord.size() == length) {
			nr++;
			// add as many patterns to the map as possible and if the pattern already exists, we add
			// the word corresponding to that pattern to its array of words
			addPattern(wordsMap, currentWord);
		}
	}
	return wordsMap;
}

void addPattern(map<string, vector<string>>& wordsMap, string word)
{
	for (int i = 0; i < word.size(); i++)
	{
		// Create wildcard and initialize an array of words for that wildcard in case we add it to the map
		string newPattern = word;
		vector<string> newPatternWords;
		newPatternWords.push_back(word);
		newPattern[i] = '*';

		// try to insert new pattern to the map
		pair<map<string, vector<string>>::iterator, bool> check;
		check = wordsMap.insert(pair<string, vector<string>>(newPattern, newPatternWords));

		// if the pattern already exists, we add the word for that pattern and move on to the next
		// possible pattern
		if (check.second == false)
			check.first->second.push_back(word);
	}
}

Graph<string> createPatternGraph(map<string, vector<string>> wordsMap) {
	// Initialize a graph
	Graph<string> patternGraph = Graph<string>();
	
	// Iterate through all patterns of the map and add them to the graph
	map<string, vector<string>>::iterator it = wordsMap.begin();

	// Add all nodes
	for (it; it != wordsMap.end(); ++it) {
			for (int i = 0; i < it->second.size(); i++)
				patternGraph.addNode(it->second[i]);
	}

	// Put an edge between all required nodes
	for (it = wordsMap.begin(); it != wordsMap.end(); ++it)
	{
		for (int i = 0; i < it->second.size(); i++)
			for (int j = 0; j < it->second.size(); j++)
				if (i != j) {
					patternGraph.connect(it->second[i], it->second[j]);
				}
	}
	return patternGraph;
}

Game::Game()
{
	graph = Graph<string>();
}

Game::Game(Graph<string> graph)
{
	this->graph = graph;
}

vector<string> Game::getWordsPath(string root, string goal)
{
	// Create queue
	list<string> queue;

	// Create maps which keep track of visited nodes and their distance from the root
	map<string, bool> visitedm;
	map<string, int> distm;
	map<string, string> predm;

	map < string, vector<string>>::iterator it = graph.vertices.begin();
	for (it; it != graph.vertices.end(); ++it) {
		visitedm.insert(std::pair<string, bool>(it->first, false));
		predm.insert(std::pair<string, string>(it->first, ""));
		distm.insert(std::pair<string, int>(it->first, INT_MAX));
	}

	visitedm.find(root)->second = true;
	distm.find(root)->second = 0;
	queue.push_back(root);
	bool done = false;
	while (!queue.empty()) {
		string current = queue.front();
		queue.pop_front();

		// Go through all neighbours of current node and search

		map<string, vector<string>>::iterator currentNeigh = graph.vertices.find(current);

		for (int i = 0; i < currentNeigh->second.size(); i++) {
			string currentNode = currentNeigh->second[i];
			if (!visitedm.find(currentNode)->second) {
				visitedm.find(currentNode)->second = true;
				distm.find(currentNode)->second = distm.find(current)->second + 1;
				predm.find(currentNode)->second = current;
				queue.push_back(currentNeigh->second[i]);

				if (currentNeigh->second[i] == goal) {
					done = true;
					break;
				}
			}
				
		}

		if (done)
			break;
	}

	// We have the shortest path stored in dist, we now place it in a vector and return it
	vector<string> path;
	string crawl = goal;
	path.push_back(goal);
	while (predm[crawl] != "") {
		path.push_back(predm[crawl]);
		crawl = predm[crawl];
	}

	return path;
}

std::vector<string> Game::tokenize(string str, char delimiter)
{
	vector <string> result;
	std::stringstream ss(str);
	string token;
	while (std::getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

int Game::loadFromCsv(string csvPath, string userName)
{
	// Create a set container to store every unique word a user has used
	set<string> uniqueWords;

	// Open csv file
	std::ifstream csv(csvPath);

	// If we managed to open the file, we go through each line and search for the username to compute statistics
	if (csv.is_open())
	{
		while (csv) {
			string line;
			std::getline(csv, line);

			vector<string> tokens = tokenize(line, ',');

			// Found the user name we are looking for, we add it's used words to the set
			if (tokens.size() == 7 && tokens[0] == userName) {
				string word;
				std::stringstream ss(tokens[5]);
				while (std::getline(ss, word, ' '))
					uniqueWords.insert(word);
			}
		}

		csv.close();
	}

	// return number of unique user words by the user
	return uniqueWords.size();
}

bool Game::saveCsv(string csvPath, string name, string startingWord, string targetWord, string dateTime, int nrOfHints, vector<string> usedWords, int nrOfMoves)
{
	// Open csv file in append mode
	std::ofstream csv;
	csv.open(csvPath, std::ios_base::app);

	if (!csv.is_open())
		return false;

	// Append data to the file
	csv << name << "," << startingWord << "," << targetWord << "," << dateTime << "," << nrOfHints << ",";
	for (int i = 0; i < usedWords.size(); i++)
		csv << usedWords[i] << " ";
	csv << "," << nrOfMoves << '\n';

	csv.close();

	return true;
}
