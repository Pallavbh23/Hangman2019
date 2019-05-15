//Hangman code
/* TODO list:
* Make a single player mode and take string at random from a file of similar things.
* Have multiple files like that and pick one file at random.
* Don't need to implement hint for them but we can if we want slowly. 
* Make the whole implementation bugless before 15th.
*/
#include <iostream>
#include <conio.h>
#include<stdio.h>
using namespace std;
class hangman{
	public:
	void startGame();
	hangman(string _word){
		word = _word;
		wordlength = _word.length();
		correctletters = makeArray(wordlength);
		chances = 10;
		hintstate = 0;
		hint = "\0";
		cout<<"Do you want to add a hint? (Type 'y' for yes.)"<<endl;
		char confirmation;
		cin>>confirmation;
		cout<<endl;
		if(confirmation == 'y')
			getHint();
	}
	private:
	string word;
	int wordlength;
	bool* correctletters;
	int chances;
	string hint;
	int hintstate;
	void getHint();
	bool hasWon();
	bool* makeArray(int length);
	void guess(string x);
	void victory();
	void printHint();
	void printState();
};
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
					cout<<"You had already guessed this letter."<<endl<<"Chances: "<<chances<<endl;
					improvement = -1;
					break;
				}
				else{
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
			cout<<"Oops, you guessed the wrong letter"<<endl<<"Chances: "<<chances<<endl;
		}
	}
	else {
		if(word == x)
			victory();
		else{
			cout<<"Wrong!"<<endl<<"Chances: "<<chances<<endl;
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

	cout<<"Please enter your hint:"<<endl;
	hintstate = 1;
	while(1) {
		char x;
		x = getch();
		if(x == '\r')
		break;
		hint+=x;
	}
}
void hangman::printHint(){
	if(hintstate == 1)
		cout<<"HINT: "<<endl<<hint<<endl;
	else
		cout<<"There's no hint."<<endl;
}
void hangman::startGame(){
	int shownstate = 0;
	while(!hasWon()){
		if(chances == 0)
		{
			cout<<"You lost the game as 0 chances left."<<endl;
			return;
		}
		printState();
		cout<<"Enter your guess: "<<endl;
		string guess_argument;
		cin>>guess_argument;
		guess(guess_argument);
		if(chances == 5 && shownstate == 0)
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
	cout << "Great!, Let's start!" << endl;
	hangman game(word);
	game.startGame();
	cout<<"press any key to exit.";
	_getch();
	return 0;
}

