#include<string.h>
#include<map>
#include "game.h"
#include "File.h"
using namespace std;
class user{
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
	int retpoint()
	{
		return points;
	}
	user()
	{
		points = 0;
	}
	void update_point(int point)
	{
		points += point;
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
		if(strlogin == "a" && !strcmp(pass,"a"))
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
	return -1;
}
void leaderboard()
{
	fstream f;
	f.open("login.dat",ios::binary | ios::in);
	user u;
	map< char* , int> m;
	if(!f.fail())
	{
		cout<<1;
		while(f.read((char *)&u,sizeof(u)))
		{
			cout<<u.retlogin()<<" "<<*u.retlogin();
			m[u.retlogin()] = u.retpoint();
		}
	}
	f.close();
	int i= 0;
	map<char* , int>::iterator it;
	for(it = m.begin() ; it!= m.end();it++)
	{
		cout<<++i<<"   "<<*it->first<<"   "<<it->second<<endl;
	}
}
void admin(){
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
				case 1:leaderboard();
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
void user::createuser(){
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
void singleplayer(){
	int point;
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
		if(!fin.fail())
		{
			while(!fin.eof())
			{
				getline(fin,genre,'\n');
				getline(fin,_word,'\n');
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
			}
		}
		fin1.close();
		cout << "Great!, Let's start!" << endl;
		hangman game(_word);
		point = game.startGame();
		fstream f;
		f.open("login.dat",ios::binary | ios::in | ios::out | ios::app);
		user u;
		while(f.read((char *)&u,sizeof(u)))
		{
			if(!strcmp(u.retlogin(),strlogin.c_str()))
			{
				f.seekg(-sizeof(u));
				u.update_point(point);
				f.write((char *)&u,sizeof(u));
			}
		}
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
void guest(){
	word w;
	cout<<"Welcome to the Hangman game."<<endl;
	int i=1;
	ifstream fin;
	fin.open("hang1.dat",ios::binary);	
	string genre = "";
	string _word = "";
	if(!fin.fail())
	{
		while(!fin.eof())
		{
			getline(fin,genre,'\n');
			getline(fin,_word,'\n');
			if(!fin.eof())
			{
				i++;
			}
		}
	}
	cout<<"\nCompleted";
	fin.close();
	int n = rand() % i;
	ifstream fin1;
	fin1.open("hang1.dat",ios::binary);	
	if(!fin.fail())
	{
		while(--i)
		{
			getline(fin1,genre,'\0');
			getline(fin1,_word,'\0');
		}
	}
	fin1.close();
	cout << "Great!, Let's start!" << endl;
	hangman game(_word);
	game.startGame();
}
void multiplayer()
{
	cout<<"Welcome to the Hangman game."<<endl;
	cout<<"Enter the word you would like your opponent to guess:"<<endl << endl;
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

