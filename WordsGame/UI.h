#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Game.h"
#include <random>
#include <chrono>
#include "Exceptions.h"
#include <conio.h>

using namespace std;

class UI : public Game {
private:
	bool running;
	friend class Game;

public:
	// Constructors
	UI();

	// Destructor
	~UI();

	// Operations
	void doOperation(string key);

	// Display
	void displayMenu();

	// Run App
	void run();

};

string returnTimeAndDate();