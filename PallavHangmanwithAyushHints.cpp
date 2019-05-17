//Hangman code
/* TODO list:
* Make a single player mode and take string at random from a file of similar things.
* Have multiple files like that and pick one file at random.
* Don't need to implement hint for them but we can if we want slowly. 
* Implement Score and Leaderboard for both Single Player and Multiplayer.
* Implement Single Player mode and Difficulties and File Selection.
*/
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <unordered_map>
using namespace std;

class node{
	public:
		string data;
		node* next;
};
class hangman{
	public:
	void startGame();
	hangman(string _word){
		word = _word;
		usedwords = new node();
		usedwords->next = NULL;
		cursor = usedwords;
		wordlength = _word.length();
		correctletters = makeArray(wordlength);
		chances = 10;
		hints = 3;
		//hintstate = 0 for hint v1
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
	void getHint();
	//int hintstate;
	//void printhint(); for hint v1
	bool hasWon();
	bool* makeArray(int length);
	void guess(string x);
	void victory();
	void printUsedWords(node* used);
	void printState();
};

void hangman::printUsedWords(node* used){
	cout<<"\nYou have already tried:"<<endl;
	while(used != NULL)
	{
		cout<<used->data<<' ';
		used = used->next;
	}
	cout<<endl<<endl;
}
bool* hangman::makeArray(int length){
	bool* arr = new bool[length];
	for(int i = 0; i < length; i++)
		arr[i] = 0;
	return arr;
}

void hangman::printState(){
	cout<<"Current state of your characters is: "<<endl;
	for(int i = 0; i < wordlength; i++)
	{
		if(correctletters[i] == 1)
			cout<<word[i];
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
			if(word[i] == x[0])
			{
				if(correctletters[i] == 1){
					chances--;
					cout<<endl<<"You had already guessed this letter."<<endl<<"Chances: "<<chances<<endl<<endl;
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
			/*if(hints != 0) {
				cout << "Would you like a hint? (y/n)" << endl;
				char c;
				cin >> c;
				if(c == 'n') {
					return;
				} 
				else {
					getHint();
				}
			}*/
			
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
	/*
	cout<<"Please enter your hint:"<<endl;
	hintstate = 1;
	while(1) {
		char x;
		x = getch();
		if(x == '\r')
		break;
		hint+=x;
	}*/ //for hint v1
	
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
		cout << "There are " << count << " vowels left in the remaining word." << endl;
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
		cout << "There are " << count << " set repeated letters in the remaining word" << endl;
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
		cout << "In the remaining word, there are " << mymap[maxIndex] << " letters between " << char(maxIndex) << " and " << char(maxIndex + 3) << " (both included)." << endl;	
		for(int i = 0; i < 7; i++) {
			mymap[97 + 4*i] = 0;
		}
	}
	hints --;
	return;
}

void hangman::startGame(){
	int shownstate = 0;
	while(!hasWon()){
		if(chances == 0)
		{
			cout<<"You lost the game as 0 chances left."<<endl << "The correct word was " << word << endl;
			return;
		}
		printState();
		printUsedWords(usedwords);
		cout<<"Enter your guess: "<<endl;
		string guess_argument;
		cin>>guess_argument;
		cursor->data = guess_argument;
		cursor->next = new node();
		cursor = cursor->next;
		cursor->next = NULL;
		guess(guess_argument);
		if(chances == 5 && shownstate == 0){
			shownstate = 1;
			if(hints != 0) {
				cout << "Would you like a hint? (y/n)" << endl;
				char c;
				cin >> c;
				if(c == 'n') {
					return;
				} 
				else {
				
					getHint();
				}
			}
		}
		/*if(chances == 5 && shownstate == 0)
		{
			shownstate = 1;
			cout<<"Would you like to opt for the hint your opponent might have left? (Type 'y' for yes.)"<<endl;
			char x;
			cin>>x;
			if(x == 'y')
			{
				printHint();
			}
		}
		}*/ //hint v1
	}
	cout<<"You won the game! The correct word was: "<<word<<endl;
	return;
	
}

int main(){
	cout<<"Welcome to the Hangman game."<<endl;
	cout<<"Enter the word you would like your opponent to guess:"<<endl;
	string word = "";
	while(1) {
		char x;
		x = getch();
		if(x == '\r')
		break;
		word+=x;
	}
	cout<<endl<<"Great!, Let's start!"<<endl<<endl;
	hangman game(word);
	game.startGame();
	cout<<"press any key to exit.";
	_getch();
	return 0;
}
