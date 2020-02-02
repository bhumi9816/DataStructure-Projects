
#include "FamilySet.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include<ctime>

using namespace std;

//bool debug;
FamilySet::FamilySet()
{
	vector<string> masterList = {};   //initializing the vecotr to empty
	dictionaries[""] = {};         //initialze the dictionary...

	// Your code here
}

FamilySet::FamilySet(string file)
{
	ifstream myFile(file);

	// Your code here
	string r;

	while (myFile >> r)
	{
		masterList.push_back(r);

	}
	//cout << "put in the masterList\n";

	myFile.close();
}

FamilySet::FamilySet(string file, int len)
{

	ifstream myFile(file);

	// Your code here
	string r;

	while (myFile >> r)
	{
		if (len == r.size())               //we would check if the len is equal to the size of the word
		{
			masterList.push_back(r);       //if yes, then add to the masterList
			//cout << r << endl;
			//cout << "put the words with length in the master list " << r.size() << endl;
		}
		//do i have to add the words to my unordered map dictionaries as well??
	}

	myFile.close();
}

FamilySet::~FamilySet()
{
	// Optional for this assignment
	auto it = dictionaries.begin();

}

void FamilySet::filterFamilies(string letter, string guessPattern, bool debug)
{
	// The first step is to clear dictionaries to prepare
	// for the new filter based on the letter and pattern
	dictionaries.clear();

	string wordFam = "";   //a copy of guessPattern

	for (unsigned i = 0; i < masterList.size(); i++)
	{
		wordFam = guessPattern;
		string word = masterList.at(i);  //put the word at that position in another string
		//cout << "size of the word is" << word << word.size() << endl;
		for (unsigned i = 0; i < word.size(); i++)
		{
			//cout << "entering the for loop \n";
			if (letter[0] == word[i])
			{

				wordFam[i] = letter[0];
			}

		}
		dictionaries[wordFam].push_back(word);


	}

	if (debug)
	{
		auto it = dictionaries.begin();
		while (it != dictionaries.end())
		{
			cout << it->first << "  " << it->second.size() << endl;
			it++;
		}
	}


	// For each word in the master list, you need to classify
	// what family is part of based on the letter and pattern.
	// If you can find letter in the word, then we need to
	// create the new family.
	// Otherwise, if the letter does not exist in the word, then
	// the family is simply the guessPattern.
	// Example 1:Suppose letter is "a", word is "ally", and 
	//           guessPattern is ***y.
	//           In this case, the family is a**y. Once this
	//           is determined, then "ally" can be added to
	//           the "a**y" dictionary.
	// Example 2:Suppose letter is "a", word is "cool", and 
	//           guessPattern is ***y.
	//           In this case, the family is ***y and "cool"
	//           would be added to the ***y dictionary.	
}

void FamilySet::setFamily(string family)
{
	// This updates the master list.  The new master list
	// should contain the words within the dictionary for family.


	// dictionaries should be cleared after updating the master list.
	masterList.clear();
	masterList = dictionaries[family];
	//dictionaries.clear();


	// Your code here
}

vector<string> FamilySet::getFamily(string family)
{
	//vector<string> s;
	// Returns the dictionary associated with family.

	// Your code here
	return dictionaries[family];

}

string FamilySet::getRandomWord()
{

	// Returns random word from master list
	srand(time(0));
	int index = rand() % numWords();
	return masterList[index];
	//return string();
}

int FamilySet::numWords()
{
	//since masterList is a vector<strings>
	// This should return the number of words in the master list
	return masterList.size();
}

int FamilySet::numFamilies()
{
	// This should return how many families are in dictionaries
	// (Note FAMILIES, not words)

	//unordered_map has member function .size()
	return dictionaries.size();
}

void FamilySet::resetFamilyIter()
{
	// The iterator should return each family from
	// dictionaries (Note, it should returns the family,
	// not the words).
	// The resetFamilyIter function should be starting
	// iterator for dictionaries.

	count = dictionaries.begin();


	// Your code here
}

bool FamilySet::hasNext()
{
	//if(count !=nullptr)
	// Returns true as long as there is another family to return
	return true;
}

string FamilySet::getNextFamily()
{
	// Returns the next family using the unordered_map iterator.
	//dictionaries::iterator newCount = count;
	//count++;

	// Your code here
	//resetFamilyIter();

	string j = "";


	j = count->first;
	//cout << "String..."<< j << endl;
	count++;

	return j;
}

int FamilySet::familySize(string family)
{
	// Returns the size of the dictionary of family.

	return (int)dictionaries[family].size();
}
