#include "UI.h"

UI::UI()
{
	running = true;
}

UI::~UI()
{
}

void UI::doOperation(string key)
{
	// Automatic Mode
	if (key == "A" || key == "a") {
		bool valid = false;
		string startWord, goalWord;
		int length = 0;

		// Input for length of words
		cout << setw(5) << "Please input length of words: "; cin >> length; cout << endl;
		
		// Validate input
		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << setw(5) << "Invalid input type! Please input a number." << endl;
			cin >> length;
		}

		// Create game pattern graph
		map<string, vector<string>> wordsMap;
		string filePath = "C:/Users/seNNNz0rel/Documents/Lab Sem II/ExtraCredit/ExtraCredit/words_alpha.txt";

		wordsMap = getWords(filePath, length);

		Graph<string> graph = createPatternGraph(wordsMap);

		Game game = Game(graph);

		// Input for starting word with validation
		cout << setw(5) << "Please input starting word: ";
		while (!valid) {
			try {
				cin >> startWord; cout << endl;
				if (game.graph.getVertices().find(startWord) == game.graph.getVertices().end())
					throw wordExceptions("Invalid Word!");
				else
				{
					valid = true;
				}
			}
			catch (wordExceptions& e) {
				cout << e.what() << endl;
			}
		}
		
		// Input for goal word with validation
		valid = false;
		cout << setw(5) << "Please input goal word: ";
		while (!valid) {
			try {
				cin >> goalWord; cout << endl;
				if (game.graph.getVertices().find(goalWord) == game.graph.getVertices().end())
					throw wordExceptions("Invalid Word!");
				else
				{
					valid = true;
				}
			}
			catch (wordExceptions& e) {
				cout << e.what() << endl;
			}
		}

		// Get the optimal path between start word and goal word
		vector<string> path = game.getWordsPath(startWord, goalWord);

		vector<string>::iterator it = path.begin();

		// Output the optimal path
		cout << setw(5) << "Path is: " << endl;
		for (it; it != path.end(); ++it)
			cout << *it << " ";
		cout << endl;
	}

	// Playing Mode
	if (key == "P" || key == "p") {
		// Input user name
		string userName;
		cout << setw(5) << "Please input your name: "; cin >> userName; cout << endl;

		// Input for length of words
		int length = 0;
		cout << setw(5) << "If you want a hint press H/h" << endl;
		cout << setw(5) << "Please input length of words: "; cin >> length; cout << endl;

		// Validate input
		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << setw(5) << "Invalid input type! Please input a number." << endl;
			cin >> length;
		}

		// Create graph data structure for words
		map<string, vector<string>> wordsMap;
		string filePath = "C:/Users/seNNNz0rel/Documents/Lab Sem II/ExtraCredit/ExtraCredit/words_alpha.txt";

		wordsMap = getWords(filePath, length);
		Graph<string> graph = createPatternGraph(wordsMap);

		// Create game object 
		Game game = Game(graph);

		// Get two random words from the map
		map<string, vector<string>>::iterator secondWord = graph.getVertices().begin();
		map<string, vector<string>>::iterator firstWord = graph.getVertices().begin();
		vector<string> optimalPath;

		while (optimalPath.size() <= 1) {
			srand(time(NULL));
			std::advance(firstWord, rand() % graph.getVertices().size() + 1);
			std::advance(secondWord, rand() % graph.getVertices().size() + 1);

			// Get original (shortest) path to the other word
			optimalPath = game.getWordsPath(firstWord->first, secondWord->first);

			if (optimalPath.size() > 1)
				break;

			firstWord = graph.getVertices().begin();
			secondWord = graph.getVertices().begin();
		}
		// Keep track of user's path
		vector<string> userPath;

		// Now we deal with user input
		string currentWord = firstWord->first;
		int hintCount = 0;
		int nrOfMoves = 0;
		int optimalNr = optimalPath.size();
		string timeAndDate = returnTimeAndDate();

		while (currentWord != secondWord->first) {
			cout << setw(5) << "Current word: " << currentWord << endl << "Goal word: " << secondWord->first << endl;
			try {
				// Create a new variable and read it
				string newWord;
				cout << setw(5) << "Please input a word (Must be different by 1 letter!) or H/h for hint ";
				cin >> newWord; cout << endl;

				// If the user wants a hint, we will display the hinted letter with green
				// and then set the current word to the hinted word
				if (newWord == "H" || newWord == "h") {
					nrOfMoves++;
					hintCount++;
					vector<string>::iterator it = optimalPath.begin();

					while (it != optimalPath.end()) {
						if (&it != nullptr && *it == currentWord)
							break;
						it++;
					}
					it--;
					for (int i = 0; i < currentWord.size(); ++i) {
						if (currentWord[i] != (*it)[i]) {
							// cout the hinted letter with a different color
							cout << "\033[32m" << (*it)[i] << "\033[m";
						}
						else
							cout << (*it)[i];
					}
					cout << endl;

					currentWord = *it;
					userPath.push_back(currentWord);
				}

				// The user typed a word, we check if it's valid
				else {

					// If the input is invalid, we will throw an error
					if (!validWord(currentWord, newWord) || game.graph.getVertices().find(newWord) == game.graph.getVertices().end()
						|| newWord.size() < length) {
						throw wordExceptions("Invalid word!");
					}

					// If the input is valid, we first check if it's corresponding to the optimal path
					// Otherwise, we need to get a new optimal path from the new word added by the user
					else {
						// Check if the new word is located in optimal path
						vector<string>::iterator it = optimalPath.begin();
						for (it; it != optimalPath.end(); ++it) {
							if (*it == newWord)
								break;
						}

						// The word is in optimal path, we don't need to create a new optimal path
						if (it != optimalPath.end()) {
							userPath.push_back(newWord);
							currentWord = newWord;
						}
						// The word is not in the optimal path, we need to search for another one
						else {
							optimalPath.clear();
							optimalPath = game.getWordsPath(newWord, secondWord->first);
							userPath.push_back(newWord);
							currentWord = newWord;
						}
						nrOfMoves++;
					}
				}
			}
			catch (wordExceptions& e) {
				cout << e.what() << '\n';
			}
		}

		// When the round is over, we save our data into a csv file
		game.saveCsv("C:/Users/seNNNz0rel/Documents/Lab Sem II/ExtraCredit/ExtraCredit/statistics.csv",
			userName, firstWord->first, secondWord->first, timeAndDate, hintCount, userPath, nrOfMoves);
	}

	// Analytics Module
	if (key == "AL" || key == "al") {
		
		// Ask the user to input the name
		string userName;

		cout << setw(5) << "Please input user name: "; cin >> userName; cout << endl;

		// Extract the necessary data from statistics file and return it to the user
		Game game = Game();
		
		int nrOfWords = game.loadFromCsv("C:/Users/seNNNz0rel/Documents/Lab Sem II/ExtraCredit/ExtraCredit/statistics.csv",
			userName);

		cout << setw(5) << userName << " has used " << nrOfWords << " unique words." << endl;
	}

	if (key == "Q" || key == "q")
		running = false;
}

void UI::displayMenu()
{
	char prev = cout.fill();
	cout << setw(32) << setfill('-') << "" << endl;
	cout.fill(prev);
	cout << "|" << left << setw(30) << " Menu" << "|" << endl;
	cout << setw(32) << setfill('-') << "" << endl;
	cout.fill(prev);
	cout << "|" << setw(30) << "  Automatic Mode (A/a)" << "|" << endl;
	cout << "|" << setw(30) << "  Playing Mode (P/p)" << "|" << endl;
	cout << "|" << setw(30) << "  Analytics Module (AL/al)" << "|" << endl;
	cout << "|" << setw(30) << "  Quit (Q/q)" << "|" << endl;
	cout << setw(32) << setfill('-') << "" << endl;
	cout.fill(prev);

	string key;
	cout << setw(5) << "Waiting for input..." << endl;
	cin >> key; cout << endl;

	doOperation(key);

}

void UI::run()
{
	while (running)
		this->displayMenu();
}

string returnTimeAndDate()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}
