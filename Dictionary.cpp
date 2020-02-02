#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Dictionary::Dictionary()
{
	root = new Node;    //initializing the root to nulllptr
	for (int i = 0; i < 26; i++)
	{
		root->sData[i] = nullptr;
	}
	root->isValid = false;
	numWords = 0;     //initializing the words to 0 in the beginning
	//numWords = 0;
}


Dictionary::~Dictionary()
{
}

Dictionary::Dictionary(string file)
{
	root = new Node;    //initializing the root to nulllptr
	for (int i = 0; i < 26; i++)
	{
		root->sData[i] = nullptr;
	}
	root->isValid = false;
	numWords = 0;     //initializing the words to 0 in the beginning
	//numWords = 0;
	ifstream infile;    //creating a file object

	infile.open(file);

	if (!infile) {
		cout << "Error! opening the file \n";
		return;
	}

	string read;

	while (infile >> read) {
		addWord(read);
	}

	//cout << "Words are added to the dictionary \n";
	//string read;
	//mydict.addWord(read);
	infile.close();
}

void Dictionary::addWord(string word)
{
	Node* currNode = root;

	//create a newNode

	for (int i = 0;i < word.size();i++)
	{
		//cout<<(word.at(i) - 'a')<<endl;
		if (currNode->sData[word[i] - 'a'] == nullptr)    //branch of char c... //
		{
			Node* newNode = new Node;    //creating a newNode
			for (int i = 0; i < 26; i++)
			{
				newNode->sData[i] = nullptr;      //initializing the letters to null
			}
			currNode->sData[word.at(i) - 'a'] = newNode;      //setting the newNode to the particular data
			newNode->isValid = false;                        //setting the bool value to false
		}
		currNode = currNode->sData[word.at(i) - 'a'];       //moving to the nextNode
	}
	currNode->isValid = true;                              //setting the bool value to true
	numWords++;
}

bool Dictionary::isWord(string word)
{
	Node* currNode = root;
	for (int i = 0; i < word.size(); i++)                //traversing through each letter of the word
	{
		if (currNode->sData[word.at(i) - 'a'] == nullptr)
		{
			return false;                                //if the data hits null returns false
		}
		currNode = currNode->sData[word.at(i) - 'a'];
	}

	return currNode->isValid;                           //else return whatever the bool value for that Node
}

bool Dictionary::isPrefix(string word)
{
	Node* currNode = root;
	for (int i = 0; i < word.size(); i++)            //traversing through each letter of the word
	{
		if (currNode->sData[word.at(i) - 'a'] == nullptr)
		{
			return false;                            //if the data hits null returns false
		}
		currNode = currNode->sData[word.at(i) - 'a'];
	}
	return true;                                    //else it returns true if the loops successfully reaches the end
												   // without hitting NULL
}

int Dictionary::wordCount()
{
	//numWords = numWords + 1;
	return numWords++;
}
