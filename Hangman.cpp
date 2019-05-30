
//Hangman code
/*credentials for admin login are:
*login id:a
*password:a
*/

#include "Login.h"
using namespace std;
int main(){
	cout<<"\t\t\t\t\t\tWelcome, Player!";
	int choice;
	do
	{
		cout<<"\n1.Admin mode";
		cout<<"\n2.Single Player";
		cout<<"\n3.Multiplayer";
		cout<<"\n4.Guest";
		cout<<"\n5.Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1:admin();
				break;
			case 2:singleplayer();
				break;
			case 3:multiplayer();
				break;
			case 4:guest();
				break;
			case 5:exit(0);
				break;
			default:
				cout<<"That's an incorrect choice! Please select a valid option:";
		}
	}
	while(1);

	return 0;
}

