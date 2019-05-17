//Hangman code
/* TODO list:
* Make a single player mode and take string at random from a file of similar things.
* Have multiple files like that and pick one file at random.
* Don't need to implement hint for them but we can if we want slowly. 
* Make the whole implementation bugless before 15th.
*credentials for admin login are:
*login id:hangman
*password:nhibataunga
*/
#include<stdlib.h>
#include<process.h>
#include <iostream>
#include <conio.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
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
void initialize_game()
{
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
}
///FILE WORK
struct word
{
	string genre;
	string word;
	string hint;		
};
void addword()
{
	word w;
	cout<<"\nEnter genre:";
	cin>>w.genre;
	cout<<"Enter Word:";
	cin>>w.word;
	cout<<"Enter hint:";
	cin>>w.hint;
	ofstream fout("hang1.dat",ios::binary | ios::app);
	fout.write(w.genre.c_str(),w.genre.size());
	fout.write("\0" , sizeof(char));
	fout.write(w.word.c_str(),w.word.size());
	fout.write("\0" , sizeof(char));
	fout.write(w.hint.c_str(),w.hint.size());
	fout.write("\0" , sizeof(char));
	fout.close();
	string s;
	s = w.genre;
	int flag =0;
	ifstream fin;
	string genre = "";
	fin.open("genre.dat" , ios::binary);
	if(!fin.fail())
	{
		while(!fin.eof())
		{
			getline(fin,genre,'\0');
			if(genre == s)
				flag = 1;
		}
	}
	fin.close();
	ofstream fout1("genre.dat" , ios::binary | ios::app);
	if(flag == 0)
	{
		fout1.write(s.c_str(),s.size());
		fout1.write("\0" , sizeof(char));
	}
	fout1.close();
}
void showall()
{
	int i=1;
	ifstream fin;
	fin.open("hang1.dat",ios::binary);	
	string genre = "";
	string word = "";
	string hint = "";
	if(!fin.fail())
	{
		while(!fin.eof())
		{
			getline(fin,genre,'\0');
			getline(fin,word,'\0');
			getline(fin,hint,'\0');
			if(!fin.eof())
			{
				cout<<endl<<i<<".\n";
				cout<<"Genre:"<<genre;
				cout<<"\nWord"<<word;
				cout<<"\nHint"<<hint;
			}
			i++;
		}
	}
	cout<<"\nCompleted";
	fin.close();
}
void deleteword()
{
	string s;
	cout<<"\nEnter the word you want to delete";
	cin>>s;
	ifstream fin;
	fin.open("hang1.dat" , ios::binary);
	ofstream fout;
	fout.open("temp.dat" , ios::binary);
	string genre = "";
	string word = "";
	string hint = "";
	while(!fin.eof())
	{
		getline(fin,genre,'\0');
		getline(fin,word,'\0');
		getline(fin,hint,'\0');
		if(word != s)
		{
			fout.write(genre.c_str(),genre.size());
			fout.write("\0" , sizeof(char));
			fout.write(word.c_str(),word.size());
			fout.write("\0" , sizeof(char));
			fout.write(hint.c_str(),hint.size());
			fout.write("\0" , sizeof(char));
			continue;
		}
	}
	fin.close();
	fout.close();
	remove("hang1.dat");
	rename("temp.dat" , "hang1.dat");
	
}
void genreshow()
{
	string s;
	int i=1;
	ifstream fin("genre.dat",ios::binary);
	while(!fin.eof())
	{
		getline(fin,s,'\0');
		if(!fin.eof())
		{
			cout<<i<<"."<<s;
			cout<<endl;
			i++;
		}
	}
	cout<<"\nCompleted";
	fin.close();
}
////USER
class user
{
	char name[50];
	char login[50];
	char pass[50];
	long long int phno;
	int points;
	public:
	char* retpass()
	{
		return pass;
	}
	char* retlogin()
	{
		return login;
	}
	user()
	{
		points = 0;
	}
	void createuser();
};
int login(int i,string strlogin)//i = 1 for admin 0 for normal user
{
	char pass[50];
	cout<<"\nPassword";
	cin>>pass;	
	if(i==1)
	{
		if(strlogin == "hangman" && !strcmp(pass,"nhibataunga"))
		{
			return 0;
		}
		return 1;
	}
	if(i==0)
	{
		char log[50];
		strcpy(log,strlogin.c_str());
		int flag = 0;
		fstream f;
		f.open("login.dat",ios::binary | ios::in | ios::out | ios::app);
		user u;
		while(f.read((char *)&u,sizeof(u)))
		{
			if(!strcmp(u.retlogin(),log))
			{
				flag = 1;
				if(!strcmp(u.retpass() , pass))
				{
					return 1;
				}
				else
					flag = 2;
			}
		}
		if(flag == 1)
			cout<<"\nInvalid Login id";
		if(flag == 2)
			cout<<"\nInvalid password";
		return 0;
	}
}
void admin()
{
	string strlogin ;
	cout<<"\nEnter login id";
	cin>>strlogin;
	int flag = login(1,strlogin);
	if(flag == 0)
	{
		int choice;
		do
		{
			cout<<"\nEnter your choice";
			cout<<"\n1.Show LeaderBoard";
			cout<<"\n2.Add words in file";
			cout<<"\n3.Delete word from file";
			cout<<"\n4.Show all genre";
			cout<<"\n5.Show All words";
			cout<<"\n6.Go back to main menu";
			cin>>choice;
			switch(choice)
			{
				case 1://leaderboard();
					break;
				case 2:addword();
					break;
				case 3:deleteword();
					break;
				case 4:genreshow();
					break;
				case 5:showall();
					break;
				case 6:	return;
				default:
					cout<<"Wrong key entered..please try again";
			}
		}while(1);
	}
	else
	{
		if(flag == 1)
			cout<<"\nInvalid id Entered";
		if(flag == 2)
			cout<<"\nInvalid Password entered";
		admin();
	}
}
void user::createuser()
{
	fstream f;
	f.open("login.dat",ios::binary | ios::in | ios::out | ios::app);
	user u;
	int flag = 0;
	cout<<"\nEnter Name";
	cin>>u.name;
	cout<<"\nEnter phone number";
	cin>>u.phno;
	do
	{
		flag = 0;
		cout<<"\nEnter login id";
		cin>>u.login;
		while(f.read((char *)&u,sizeof(u)))
		{
			if(!strcmp(u.retlogin() , this->login))
				flag = 1;
		}
		if(flag == 1)
			cout<<"\nSorry login id already exist please choose a new one";
	}while(flag == 1);
	flag = 0;
	char pass2[50];
	do
	{
		flag = 0;
		cout<<"\nEnter Password:  ";
		cin>>u.pass;
		cout<<"\nReenter password:";
		cin>>pass2;
		if(strcmp(u.retpass(),pass2))
		{
			cout<<"\nSorry! password didnot match. Please reenter password";
			flag = 1;
		}
	}while(flag ==1);
	f.write((char *)&u,sizeof(u));
	f.close();
}
void singleplayer()
{
	word w;
	int n;
	char ch;
	user u;
	cout<<"Does User exist?(y/n)";
	cin>>ch;
	if(ch == 'n')
		u.createuser();
	string strlogin ;
	cout<<"Enter credentials to login:";
	cout<<"\nEnter login id";
	cin>>strlogin;
	int flag = login(0,strlogin);
	if(flag == 0)
	{
		cout<<"Welcome to the Hangman game."<<endl;
		cout<<"Enter the word you would like your opponent to guess:"<<endl;
		string word = "";
		int i=1;
		ifstream fin;
		fin.open("hang1.dat",ios::binary);	
		string genre = "";
		string _word = "";
		string hint = "";
		if(!fin.fail())
		{
			while(!fin.eof())
			{
				getline(fin,genre,'\0');
				getline(fin,_word,'\0');
				getline(fin,hint,'\0');
				if(!fin.eof())
				{
					i++;
				}
			}
		}
		cout<<"\nCompleted";
		fin.close();
		n = rand() % i;
		ifstream fin1;
		fin1.open("hang1.dat",ios::binary);	
		if(!fin.fail())
		{
			while(--i)
			{
				getline(fin1,genre,'\0');
				getline(fin1,_word,'\0');
				getline(fin1,hint,'\0');
			}
		}
		fin1.close();
		cout << "Great!, Let's start!" << endl;
		hangman game(_word);
		game.startGame();
	}
	else
	{
		if(flag == 1)
			cout<<"\nInvalid id Entered";
		if(flag == 2)
			cout<<"\nInvalid Password entered";
		singleplayer();
	}
}
void guest()
{
	word w;
	cout<<"Welcome to the Hangman game."<<endl;
	cout<<"Enter the word you would like your opponent to guess:"<<endl;
	string _word = "";
	//int n = rand() % w.count;
	ifstream fin;
	fin.open("hangman.dat",ios::binary);
	//while(n--)
	//{
//		fin.read((char *)&w , sizeof(w));
	//}
	_word = w.word;
	cout << "Great!, Let's start!" << endl;
	hangman game(_word);
	game.startGame();
}
int main()
{
	int choice;
	do
	{
		cout<<"\t\t\tHello User..";
		cout<<"\n1.Admin mode";
		cout<<"\n2.Single Player";
		cout<<"\n3.Multiplayer";
		cout<<"\n4.Guest";
		cout<<"\n5.Exit";
		cin>>choice;
		switch(choice)
		{
			case 1:admin();
				break;
			case 2:singleplayer();
				break;
			case 3://multiplayer();
				initialize_game();
				break;
			case 4:guest();
				break;
			case 5:exit(0);
				break;
			default:
				cout<<"Wrong key entered..please try again";
		}
	}while(1);
	return 0;
}
