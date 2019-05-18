//For implementing hintv1
Constructor:
	hintstate = 0;
	cout<<"Do you want to add a hint? (Type 'y' for yes.)"<<endl;
	char confirmation;
	cin>>confirmation;
	cout<<endl;
	if(confirmation == 'y')
		getHint();
Class:
	private:
		int hintstate;
		void getHint();
		void printHint();
		
functions:
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
	
in startGame() function:
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
			
hint prompt at every wrong guess:
	in the guess():
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
