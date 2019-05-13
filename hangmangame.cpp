//Hangman code
#include <iostream>
using namespace std;
class hangman{
	public:
	void startGame();
	hangman(string _word){
		word = _word;
		wordlength = _word.length();
		*correctletters = new bool[wordlength];
		for(int i = 0; i < wordlength; i++)
			correctletters[i] = 0;
		chances = 10;
		hintstate = 0;
		/*cout<<"Do you want to add a hint? (Type 'y' for yes.)"<<endl;
		char confirmation;
		cin>>confirmation;
		cout<<endl;
		if(confirmation == 'y')
			getHint();*/ //hint functionality does not work yet.
	}
	private:
	string word;
	int wordlength;
	bool correctletters[];
	int chances;
	string hint = "\0";
	int hintstate;
	void getHint();
	bool hasWon();
	void guess(string x);
	void victory();
	void printHint();
};
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
					cout<<"You had already guessed this letter."<<endl<<"Chances: "<<chances<<endl;
					improvement = -1;
					break;
				}
				else{
					correctletters[i] = 1;
					improvement = 1;
					while(i<wordlength){
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
			cout<<"Oops, you guessed the wrong letter"<<endl<<"Chances: "<<chances;
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
	cin>>hint; //need to make multi word supported hint.
}
void hangman::printHint(){
	if(hintstate == 1)
		cout<<"HINT: "<<endl<<hint<<endl;
	else
		cout<<"There's no hint."<<endl;
}
void hangman::startGame(){
	while(!hasWon()){
		if(chances == 0)
		{
			cout<<"You lost the game as 0 chances left."<<endl;
			return;
		}
		cout<<"Enter your guess: "<<endl;
		string guess_argument;
		cin>>guess_argument;
		guess(guess_argument);
		/*if(chances == 5)
		{
			cout<<"Would you like to opt for the hint your opponent might have left? (Type 'y' for yes.)"<<endl;
			char x;
			cin>>x;
			if(x == 'y')
			{
				printHint();
			}
		}*/ //hint functionality does not work.
	}
	cout<<"You won the game! The correct word was: "<<word<<endl;
	return;
	
}
int main(){
	cout<<"Welcome to the Hangman game."<<endl;
	cout<<"Enter the word you would like your opponent to guess:"<<endl;
	string word;
	cin>>word;
	hangman game(word);
	game.startGame();
	return 0;
}
