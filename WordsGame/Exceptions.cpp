#include "Exceptions.h"

bool validWord(string originalWord, string newWord)
{
	int c = 0;
	for (int i = 0; i < originalWord.size() && c < 2; i++)
		if (originalWord[i] != newWord[i])
			c++;
	return c < 2;
}

wordExceptions::wordExceptions()
{
}

wordExceptions::wordExceptions(string word)
{
	invalidWord = word;
}

const char* wordExceptions::what() const throw()
{
	return invalidWord.c_str();
}
