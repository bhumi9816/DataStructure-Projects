#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
	// Your data structure goes here
	Node* sData[26] = {};    //creating a Node which is an array of 26 pointers
	bool isValid;           //return bool if the given Node is a word or not
	//Node *branch;
	Node* next;

};


class Dictionary
{
public:
	Dictionary();
	~Dictionary();
	Dictionary(string file);
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	//void PrintWords(string prefix);
	int wordCount();

private:
	Node* root;
	int numWords;
	//void destroy(Node*);
	// Any private methods you need/want
};


