// FinalAssign6EvilHangman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "FamilySet.h"

using namespace std;

bool debug;	// Global variable to indicate debugging

bool PromptYesNoMessage(string msg)
{
	while (true) {
		cout << msg << "(y/n) ";
		string response;
		cin >> response;
		if (response == "y")
			return true;
		if (response == "n")
			return false;
		cout << "Please enter y or n..." << endl;
	}
}

int PromptGuesses()
{
	while (true)
	{
		int len;
		cout << "Please enter how many guesses: ";
		cin >> len;
		if (len > 0)
			return len;
	}
}

int PromptWordLength()
{
	while (true)
	{
		int len;
		// Your code here...

		cout << "Please enter the length of the word: ";
		cin >> len;
		if (len > 0)
			return len;
	}
}

string PromptGuess(string& guessedLetters)
{
	string guess = "";

	//int guessSize = PromptGuesses();

	// Your code here...
	bool isIn = true;
	while (isIn)
	{
		cout << "Enter the guess word: ";
		cin >> guess;
		isIn = false;

		for (unsigned i = 0; i < guessedLetters.size(); i++)
		{
			if (guess[0] == guessedLetters.at(i) || guess.size() == 2 || !(isalpha(guess[0])))
			{
				isIn = true;
				//i = 9999;
			}

			//continue;		
		}
	}

	guessedLetters += guess;
	//isIn = false;


	return guess;
}

string ChooseFamily(string guess, string guessProgress, FamilySet& set)
{
	// filter families by guess and guessProgress/guessPattern

	set.filterFamilies(guess, guessProgress, debug);

	set.resetFamilyIter();

	string maxFamily = "";   //family with maxSize
	int maxSize = 0;    //keeping the temporary size 
	int s_ize = 0;
	string f = "";

	/*
	 * Use the iterator to loop through each family and
	 * figure out the biggest family size.
	 * Return this family
	 */

	 //pointing to the family of the guessPattern
	for (int i = 0; i < set.numFamilies(); i++)
	{
		f = set.getNextFamily();		//pointing to the family of the guessPattern               
		s_ize = set.familySize(f);		//storing the size of the words in the guessProgressed family
									//cout << "size for every family..." << s_ize << endl;
		if (s_ize > maxSize)        //comparing the sizes to find the maximum size
		{
			maxSize = s_ize;
			maxFamily = f;
		}
	}



	return maxFamily;
}

bool isWin(string guessedProgress)
{
	//here, the function returns true if it's not a string... 
	return guessedProgress.find("*") == string::npos;
}

void PlayEvilHangman(string file)
{
	// Prompt user for word length and number of guesses
	int len = PromptWordLength();
	int guessesLeft = PromptGuesses();
	string guessProgress = "";

	// Load dictionary based on word length
	cout << "Loading dictionary..." << endl;
	FamilySet families(file, len);

	string guessedLetters = "";
	string correctlyGuessed = "";	            // correctly guessed positions
	for (int i = 0; i < len; i++)
		guessProgress += "*";


	// Actual game loop...
	int l_size = families.numWords();

	while (true) {

		// Your code here...

		cout << guessProgress << endl;
		cout << "Guesses Left: " << guessesLeft << endl;
		cout << "Guessed Letter: " << guessedLetters << endl;
		cout << "Candidate Words: " << l_size << endl;

		//prompt the user for guess to guess the letter
		string g = PromptGuess(guessedLetters);

		//guessProgress = ChooseFamily(g, guessProgress, families);
		guessProgress = ChooseFamily(g, guessProgress, families);
		families.setFamily(guessProgress);

		//decrementing the guessesLeft
		guessesLeft--;

		/*else
		{
			correctlyGuessed = gueguessProgress;
		}*/


		//Candidate words with my maxFamily words 
		int Fam_size = families.familySize(guessProgress);
		cout << "Max family size is" << " " << Fam_size << " " << "for " << guessProgress << endl;
		l_size = Fam_size;

		/*
				else if (!debug)
				{
					cout << guessProgress << endl;
					cout << "Guesses Left: " << guessesLeft << endl;
					cout << "Guessed Letter: " << guessedLetters << endl;

					string g = PromptGuess(guessedLetters);


					guessesLeft--;

				}*/


		if (isWin(guessProgress)) {
			cout << "Wow! You won!" << endl;
			break;
		}

		if (guessesLeft <= 0) {
			cout << "Wow... you are a really bad guesser..." << endl;
			cout << "The mystery word was " << families.getRandomWord() << endl;
			break;
		}
	}
}



int main()
{
	string file;
	cout << "Enter file: ";
	cin >> file;				// Can comment out this line and include the following while developing
	//file = "dictionary.txt";  // Convenient to hard code while developing

	while (true)
	{
		debug = PromptYesNoMessage("Turn debugging on?");
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again ?"))
			break;
	}

}


/*FamilySet s("dictionary.txt", 3);
	int length = s.numWords();
	cout << "Total number of words are " << length << endl;
	s.filterFamilies("e", "***");*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
