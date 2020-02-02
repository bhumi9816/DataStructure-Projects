// BogglerSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <fstream>
#include "Dictionary.h"

const int MAX_ROW = 4;
const int MAX_COL = 4;

using namespace std;
string choice = "y";
map<string, int>m;

//clear functions initialize the visited step matrix to 0
void clear(int temp[MAX_ROW][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			temp[i][j] = 0;
			//cout << setw(2) << temp[i][j] << " ";
		}
		cout << endl;
	}
}

//board function, allows the user to enter letter matrix for Boggle Solver
void board(string letter[MAX_ROW][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++) {
		cout << "Row " << i << ":";
		for (int j = 0; j < MAX_COL; j++) {
			cin >> letter[i][j];
		}
	}
}


//SearchForWord function does the heavy lifting of solving the board and find the words
void SearchForWord(int row, int col, int temp[MAX_ROW][MAX_COL], string path, Dictionary wordsSeen, string letter[MAX_ROW][MAX_COL], Dictionary tree, int currValue)
{
	//base case:
	if (row < 0 || col < 0 || row >= MAX_ROW || col >= MAX_COL)
		return;

	if (temp[row][col] >= 1)    //make sure to check it's visited the letter only once
		return;

	path = path + letter[row][col];    // appends/add the next letter to the path

	bool find_prefix = tree.isPrefix(path);    //check if the path isPrefix or not

	if (find_prefix)
	{
		bool is_word = tree.isWord(path);      //if it's a prefix, check if it's a word or not
		temp[row][col] = currValue + 1;
		if (is_word)
		{
			if (m[path] == 0) {

				m[path] = 1;


				cout << "Number of Words: " << m.size() << endl;
				cout << "Word:  " << path << endl;
				if (choice == "y")
				{
					for (int i = 0; i < MAX_ROW; i++) {
						for (int j = 0; j < MAX_COL; j++) {
							if (temp[i][j] >= 1)     //check based on the step matrix, if >0, print the board
							{
								cout << "'" << letter[i][j] << "'" << "\t";
							}
							else {
								cout << letter[i][j] << "\t";
							}
						}
						cout << "\t\t";    //spaces between two matrix

						//Now printing the visited step-matrix
						for (int j = 0; j < MAX_COL; j++) {
							if (temp[i][j] >= 1) {
								cout << temp[i][j] << "\t";
							}
							else
								cout << temp[i][j] << "\t";
						}
						cout << endl;    //moving to the next line, after the first row is printed
					}
					//return;
				}
			}
		}

		//MAKING 8 Recursive calls, in clock-wise manner

		SearchForWord(row, col + 1, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row + 1, col + 1, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row + 1, col, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row + 1, col - 1, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row, col - 1, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row - 1, col - 1, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row - 1, col, temp, path, wordsSeen, letter, tree, currValue + 1);
		SearchForWord(row - 1, col + 1, temp, path, wordsSeen, letter, tree, currValue + 1);
		temp[row][col] = 0;
	}

	else {
		return;
	}

}

//WordSolver serves as rappper and call the searchforWord function.
void WordSolver(int temp[MAX_ROW][MAX_COL], Dictionary wordsSeen, string letter[MAX_ROW][MAX_COL], Dictionary tree)
{
	clear(temp);
	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			//clear(temp);
			SearchForWord(i, j, temp, "", wordsSeen, letter, tree, 0);
		}
	}
}


int main()
{
	Dictionary tree("Dictionary.txt");       //("newdictionary.txt");   //loads the words

	//testing words
	/*
	tree.addWord("hell");
	tree.addWord("hello");
	tree.addWord("aa");
	tree.addWord("aal");
	tree.addWord("aals");
	tree.addWord("cat");
	tree.addWord("dog");
	*/

	Dictionary wordsSeen;    //wordsSeen is an empty dictionary that checks whether the formed word is added to the
							//dictionary or not. If not then it adds it.
	//ofstream ofile;

	string letter[MAX_ROW][MAX_COL];
	int temp[MAX_ROW][MAX_COL];


	cout << "Words loaded " << tree.wordCount() << endl;

	cout << "Enter Board \n";
	cout << "------------\n";

	board(letter);

	//string choice;
	cout << "Show Board (y/n): ";
	cin >> choice;

	//creating a two-dimensional matrix for the letter board

	WordSolver(temp, wordsSeen, letter, tree);


}


/*	tree.addWord("hello");
		if (tree.isWord("hello")) {
			cout << "is a Word \n";
		}
		else {
			cout << "not a word \n";
		}
		if (tree.isPrefix("he")) {
			cout << "is a Prefix \n";
		}
		else {
			cout << "is not a Prefix \n";
		}
		cout << tree.wordCount() << endl; */

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
