#pragma once
#include <cassert>
#include "AdjacencyLists.h"
#include "Game.h"

class Tests {
public:
	virtual void runAllTests() = 0;
};

class AdjacencyListTests : public Tests {
public:
	void runAllTests();
	static int creationTest();
	static int insertTest();
};

class WordMapTests : public Tests {
public:
	void runAllTests();
	static int creationTest();
};

class GameTests : public Tests {
public:
	void runAllTests();
	static int pathTest();
};