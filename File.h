#include<fstream>
#include<string.h>
#include<iostream>
using namespace std;

struct word{
	string genre;
	string word;		
};
void addword(){
	word w;
	cout<<"\nEnter genre:";
	cin>>w.genre;
	cout<<"Enter Word:";
	cin>>w.word;
	ofstream fout("hang1.dat",ios::binary | ios::app);
	fout.write(w.genre.c_str(),w.genre.size());
	fout.write("\n" , sizeof(char));
	fout.write(w.word.c_str(),w.word.size());
	fout.write("\n" , sizeof(char));
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
			getline(fin,genre,'\n');
			if(genre == s)
				flag = 1;
		}
	}
	fin.close();
	ofstream fout1("genre.dat" , ios::binary | ios::app);
	if(flag == 0)
	{
		fout1.write(s.c_str(),s.size());
		fout1.write("\n" , sizeof(char));
	}
	fout1.close();
}

void showall(){
	int i=1;
	ifstream fin;
	fin.open("hang1.dat",ios::binary);	
	string genre = "";
	string word = "";
	if(!fin.fail())
	{
		while(!fin.eof())
		{
			getline(fin,genre,'\n');
			getline(fin,word,'\n');
			if(!fin.eof())
			{
				cout<<endl<<i<<".\n";
				cout<<"Genre:"<<genre;
				cout<<"\nWord"<<word;
			}
			i++;
		}
	}
	cout<<"\nCompleted";
	fin.close();
}
void deleteword(){
	string s;
	cout<<"\nEnter the word you want to delete";
	cin>>s;
	ifstream fin;
	fin.open("hang1.dat" , ios::binary);
	ofstream fout;
	fout.open("temp.dat" , ios::binary);
	string genre = "";
	string word = "";
	while(!fin.eof())
	{
		getline(fin,genre,'\n');
		getline(fin,word,'\n');
		if(word != s)
		{
			fout.write(genre.c_str(),genre.size());
			fout.write("\n" , sizeof(char));
			fout.write(word.c_str(),word.size());
			fout.write("\n" , sizeof(char));
			continue;
		}
	}
	fin.close();
	fout.close();
	remove("hang1.dat");
	rename("temp.dat" , "hang1.dat");
	
}
void genreshow(){
	string s;
	int i=1;
	ifstream fin("genre.dat",ios::binary);
	while(!fin.eof())
	{
		getline(fin,s,'\n');
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
