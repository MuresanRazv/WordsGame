#pragma once
#include "Tests.h"

void AdjacencyListTests::runAllTests()
{
	creationTest();
	insertTest();
}

int AdjacencyListTests::creationTest()
{
	Graph<int> list = Graph<int>();


	return 0;
}

int AdjacencyListTests::insertTest()
{
	Graph<int> list = Graph<int>();
	
	Node<int>* newNode1, *newNode2, *newNode3, *newNode4, *newNode5, *newNode6;
	

	return 0;
}

void WordMapTests::runAllTests()
{
	creationTest();
}

int WordMapTests::creationTest()
{
	map<string, vector<string>> wordsMap;
	string filePath = "C:/Users/seNNNz0rel/Documents/Lab Sem II/ExtraCredit/ExtraCredit/words_alpha.txt";

	wordsMap = getWords(filePath, 4);

	Graph<string> graph = createPatternGraph(wordsMap);

	map<string, vector<string>> words = graph.getVertices();
	
	map<string, vector<string>>::iterator it = words.begin();

	for (it; it != words.end(); it++)
	{
		cout << it->first << ": ";
		for (int i = 0; i < it->second.size(); i++)
			cout << it->second[i] << " ";
		cout << '\n';
	}
	

	return 0;
}

void GameTests::runAllTests()
{
	pathTest();
}

int GameTests::pathTest()
{
	map<string, vector<string>> wordsMap;
	string filePath = "C:/Users/seNNNz0rel/Documents/Lab Sem II/ExtraCredit/ExtraCredit/words_alpha.txt";

	wordsMap = getWords(filePath, 5);

	Graph<string> graph = createPatternGraph(wordsMap);

	Game game = Game(graph);

	game.getWordsPath("paper", "lamer");

	return 0;
}
