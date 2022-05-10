#pragma once
#include <exception>
#include <string>

using std::exception;
using std::string;

bool validWord(string originalWord, string newWord);

class wordExceptions : public exception {
public:
	wordExceptions();
	wordExceptions(string word);

	const char* what() const throw ();
private:
	string invalidWord;
};