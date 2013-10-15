#include "parser.h"

int main()
{
	cout << "*********************\n";
	cout << "* RECURSIVE DESCENT *\n";
	cout << "*********************\n\n";

	string str;
	cout << "> ";
	getline(cin, str);
	while(str != "#")
	{
		Parser exampleInput(str);
		cout << "> ";
		getline(cin, str);
	}

	return 0;
}