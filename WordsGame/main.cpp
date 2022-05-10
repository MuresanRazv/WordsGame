#include <iostream>
#include "Tests.h"
#include "UI.h"

int main() {
	// TODO: Store information on csv and finish analytics module
	srand(time(NULL));

	//Tests* testAdjacencyList = new AdjacencyListTests;
	//Tests* testWordMap = new WordMapTests;
	//Tests* testGame = new GameTests;
	//testAdjacencyList->runAllTests();
	//testWordMap->runAllTests();
	//testGame->runAllTests();
	//delete testAdjacencyList;
	//delete testWordMap;
	//delete testGame;

	UI ui = UI();
	ui.run();

	return 0;
}