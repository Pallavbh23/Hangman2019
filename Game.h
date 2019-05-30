#include <ios>
#include <limits>
#include<stdlib.h>
#include<process.h>
#include <iostream>
#include <conio.h>
#include<stdio.h>
#include<string.h>
#include <cctype>
#include <unordered_map>
using namespace std;

class node{
	public:
		string data;
		node* next;
};

class hangman{
	public:
	int startGame();
	hangman(string _word){
		word = _word;
		usedwords = new node();
		usedwords->next = NULL;
		cursor = usedwords;
		wordlength = _word.length();
		correctletters = makeArray(wordlength);
		chances = 10;
		hints = 3;
		for(int i = 0; i < 7; i++) {
			mymap[97 + 4*i] = 0;
		}
	}
	private:
	node* usedwords;
	node* cursor;
	string word;
	int wordlength;
	bool* correctletters;
	int chances;
	int hints;
	int level;
	unordered_map <int, int> mymap;
	bool hasWon();
	void getHint();
	bool* makeArray(int length);
	void guess(string x);
	void victory();
	void printUsedWords(node* used);
	void printState();
};
/*string allSmall(string input) {
	string output = "";
	for(int i = 0; i < input.length(); i++) {
		if(input[i] < 97 && input[i] != 32) {
			output += input[i] + 32;
		} else {
			output += input[i];
		}
	}
	return output;
}*/ //Had to remove this function cause it was leading to a lot of bugs.

void hangman::printUsedWords(node* used){
	cout<<"\nYou have already tried:"<<endl;
	while(used != NULL) //Traverses the linkedlist and prints all the nodes that are present
	{
		cout<<used->data<<' ';
		used = used->next;
	}
	cout<<endl<<endl;
}

bool* hangman::makeArray(int length){ //Helper function 
	bool* arr = new bool[length];
	for(int i = 0; i < length; i++)
		arr[i] = 0;
	return arr;
}

void hangman::printState(){
	cout<<"Current state of your characters is: "<<endl;
	for(int i = 0; i < wordlength; i++)
	{
		if(correctletters[i] == 1 && word[i] != 32)
			cout<<word[i];
		else if(word[i] == 32) {
			cout << word[i] << word[i];
			correctletters[i] = 1;
		}
			
		else
			cout<<" _ ";
	}
	cout<<endl;
}

bool hangman::hasWon(){
	for(int i = 0; i < wordlength; i++){
		if(correctletters[i] == 0)
			return 0;
	}
	return 1;
}

void hangman::guess(string x){
	if(x.length() == 1){
		bool improvement = 0;
		for(int i = 0; i < wordlength; i++){
			if(tolower(word[i]) == tolower(x[0]))
			{
				if(correctletters[i] == 1){
					cout<<endl<<"You had already guessed this letter."<<endl;//<<"Chances: "<<chances<<endl<<endl;
					improvement = -1;
					break;
				}
				else{
					cout<<endl<<"You guessed correct!"<<endl<<endl;
					correctletters[i] = 1;
					improvement = 1;
					while(i < wordlength){
						i++;
						if(word[i] == x[0])
						{
							correctletters[i] = 1;
						}
					}
					break;
				}
			} 
		}
		if(improvement == 0){
			chances--;
			cout<<endl<<"Oops, you guessed the wrong letter."<<endl<<"Chances: "<<chances<<endl<<endl;
		}
	}
	else {
		if(word == x)
			victory();
		else{
			chances--;
			cout<<endl<<"Wrong!"<<endl<<"Chances: "<<chances<<endl<<endl;
		}
	}
}

void hangman::victory(){
	for(int i = 0; i < wordlength; i++)
	{
		correctletters[i] = 1;
	}
	cout<<"Congratulations, you guessed the whole word!"<<endl;
}

void hangman::getHint(){
	if(hints <= 0) {
		cout << "Sorry, you do not have any hints left!" << endl;
		return;
	}
	
	cout << "Press 'v' to know the number of vowels and 'r' to know the number of repeated letters and 'o' for a different hint." << endl;
	char c;
	cin >> c;
	if(c == 'v') {
		int count = 0;
		for(int i = 0; i < wordlength; i++) {
			if(correctletters[i] == 1)
				continue;
			if(word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')	
				count++;				
		}
		cout << endl << "HINT:   There are " << count << " vowels left in the remaining word." << endl << endl;
	} else if(c == 'r') {
		unordered_map<char, int> map;
		for(int i = 0; i < wordlength; i++) {
			if(correctletters[i] == 1)
			continue;
			map[word[i]] ++;
		}
		int count = 0;
		for(int i = 0; i < wordlength; i++) {
			if(correctletters[i] == 1)
			continue;
			if(map[word[i]] > 1) {
				count++;
				map[word[i]] -= 2;
			}
			
		}
		cout << endl <<"HINT:  There are " << count << " set repeated letters in the remaining word" << endl << endl;
	} else {
		for(int i = 0; i < wordlength; i++) {
			if(correctletters[i] == 1)
			continue;
			for(int j = 0; j < 7; j++) {
				if(word[i] >= 97 + 4*j && word[i] < 101 + 4*j ) {
					mymap[97 + 4*j]++;
				}
			}		
		}
		int max = 0;
		int maxIndex = 0;
		for(int j = 0; j < 7; j++) {
			if(mymap[97 + 4*j] > max) {
				maxIndex = 97 + 4*j;
			}
		}
		cout << endl << "HINT:  In the remaining word, there are " << mymap[maxIndex] << " letters between " << char(maxIndex) << " and " << char(maxIndex + 3) << " (both included)." << endl << endl;	
		for(int i = 0; i < 7; i++) {
			mymap[97 + 4*i] = 0;
		}
	}
	hints --;
	return;
}

int hangman::startGame(){
	bool shownstate = 0; //Hint usage block has not been shown yet.
	int ch;
	while(!hasWon()){
		if(chances == 0)
		{
			cout<<"You lost the game as 0 chances left."<<endl << "The correct answer was \"" << word <<"\""<< endl;
			return 0;
		}
		printState(); //Prints the current state of the word depecting the letters that have been guessed and the letters that haven't.
		printUsedWords(usedwords); //Prints the letters/words that the user has already tried.
		if(chances == 5 && shownstate == 0){
			shownstate = 1; //Shownstate = 1 ensures that this block is executed only once.
			cout << "You are now eligible for hints! Enter #h during any chance to get one." << endl;
			cout << "You have " << hints << " hints left." << endl;
		}
		cout<<"Enter your guess: "<<endl;
		string guess_argument; 
		getline(cin, guess_argument); //Takes the guess from user (word/letter).
		if(chances <= 5) { //Only executes when chances are less than 5.
			if(guess_argument == "#h") { // Checks if the guess_argument is #h.
				if(hints == 0) { //Exhausted all hints.
					cout << "Sorry, you have no hints left!" << endl;
				} 
				else {
					getHint(); //Function to get hint is called.
					cout << "You have " << hints << " hints left." << endl;
				}
			}
		}

		cursor->data = guess_argument;
		cursor->next = new node();
		cursor = cursor->next;
		cursor->next = NULL;		

		guess(guess_argument); // Function to check if the argument is correct and updating it in the context of the game.
	}
	ch = chances;
	cout<<"You won the game! The correct word was: "<<word<<endl;
	return ch;
}

void initialize_game(){
	cout<<"Welcome to the Hangman game."<<endl;
	cout<<"Enter the word you would like your opponent to guess:"<<endl;
	string word = "";
	while(1) {
		char x;
		x = getch();
		if(x == '\b') {
			word = word.substr(0, word.length() - 1);
			continue;
		}
		if(x == '\r')
		break;
		word+=x;
	}
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
		//word = allSmall(word); // This is so wrong.
	cout << "Great!, Let's start!" << endl;
	hangman game(word);
	game.startGame();
}
