#include "globals.h"

int main() 
{
	string fileName;

	cout << "Enter file name with extension .txt : "; cin >> fileName;
	
	bool cont = true;
	ReadFromFile read(fileName);

	do {
		graph board(read);
		puts("Enter operation you want to do\n1\\ Output one soloution\n2\\ Output all soloutions\n");
		int operation;
		cin >> operation;
		if (operation < 1 or operation > 2) {
			puts("Please enter a valid operation!!!!");
			continue;
		}
		if (operation == 1) {
			board.greedyColoring();
		}
		else if (operation == 2) {
			board.getAll();
		}
		bool flag = true;
		do {
			puts("Do you want to continue?\nyes\nno");
			string s; cin >> s;
			int size = s.size();
			for (int i = 0; i < size; ++i) {
				s[i] = tolower(s[i]);
			}
			if (s == "no") {
				cont = false;
				puts("Bye Bye!!");
				break;
			}
			else if (s == "yes") {
				break;
			}
			else {
				puts("Please Enter a valid operation!!!");
			}
		} while (flag);
	} while (cont);

	system("pause");
	return 0;
}