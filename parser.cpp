#include "parser.h"

#define NOM_ERROR "There is an error in 'NOM'\n"
#define VP_ERROR "There is an error in 'VP'\n"
#define NP_ERROR "There is an error in 'NP'\n"
#define SUCCESSFULLY "Successfully parsed!\n\n"
#define UNSUCCESSFULLY "Parsing failed!\n\n"

Parser::Parser(string str)
{
	error = false;
	errorCount = 0;
	//line = 0; SHOW LINE OF ERROR

	splitWords(str);
	
	if(wordList.size() >= 2)
		nextWord = 1;
	else 
		nextWord = 0;

	S(); //start
	
	if(!error && errorCount == 0)
		cout << SUCCESSFULLY;
	else
		cout << " " << errorCount << " ERROR found, " << UNSUCCESSFULLY;
}

void Parser::S()
{
	NP();
	if(!error)
	{
		if(isFinished())
		{
			error = true;
			errorCount++;
			return;
		}
			
		nextWord++;
		VP();
	}
	else
	{
		if(Aux())
		{
			error = false;
			errorCount--;

			if(isFinished())
			{
				error = true;
				errorCount++;
				return;
			}

			nextWord++;
			NP();
			if(!error)
			{
				if(isFinished())
				{
					error = true;
					errorCount++;
					return;
				}

				nextWord++;
				VP();
				if(error)
					cout << VP_ERROR; //VP_ERROR
			}
			else
				cout << NP_ERROR; //NP_EEROR
		}
		else
		{
			error = false;
			errorCount--;

			VP();
			if(error)
				cout << VP_ERROR; //VP_ERROR
			else
				return;
		}
	}
}

void Parser::NP()
{
	if(Det())
	{
		if(isFinished())
		{
			error = true;
			errorCount++;
			return;
		}	

		nextWord++;
		NOM();
		if(error)
			cout << NOM_ERROR; //NOM_ERROR
	}
	else
		errorCount++;
}

void Parser::VP()
{
	if(Verb())
	{
		if(isFinished())
			return;
			
		nextWord++;
		NP();
		if(error)
			return;
	}
	else
		errorCount++;
}

void Parser::NOM()
{
	if(Noun())
	{
		if(isFinished())
			return;
			
		while(Noun())
		{
			if(isFinished())
				return;
				
			nextWord++;
		}

		error = false;
		nextWord--;
	}
	else
		errorCount++;
}

bool Parser::Det()
{
	if(wordList.size() >= 2)
	{
		if(wordList[nextWord - 1] == "that" || wordList[nextWord - 1] == "this" || wordList[nextWord - 1] == "a" || wordList[nextWord - 1] == "the")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
	else
	{
		if(wordList[nextWord] == "that" || wordList[nextWord] == "this" || wordList[nextWord] == "a" || wordList[nextWord] == "the")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
}

bool Parser::Noun()
{
	if(wordList.size() >= 2)
	{
		if(wordList[nextWord - 1] == "book" || wordList[nextWord - 1] == "flight" || wordList[nextWord - 1] == "meal" || wordList[nextWord - 1] == "man")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
	else
	{
		if(wordList[nextWord] == "book" || wordList[nextWord] == "flight" || wordList[nextWord] == "meal" || wordList[nextWord] == "man")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
}

bool Parser::Verb()
{
	if(wordList.size() >= 2)
	{
		if(wordList[nextWord - 1] == "book" || wordList[nextWord - 1] == "include" || wordList[nextWord - 1] == "read")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
	else
	{
		if(wordList[nextWord] == "book" || wordList[nextWord] == "include" || wordList[nextWord] == "read")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
}

bool Parser::Aux()
{
	if(wordList.size() >= 2)
	{
		if(wordList[nextWord - 1] == "does")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
	else
	{
		if(wordList[nextWord] == "does")
			return true;
		else
		{
			error = true;
			return false;
		}
	}
}

bool Parser::isFinished()
{
	if(wordList.size() >= 2)
		if(nextWord == wordList.size())
			return true;
		else
			return false;
	else
		return true;
}

void Parser::splitWords(string str)
{
	input = str;
	string temp = "";
	for(int j = 0; j < input.size(); j++)
	{
		if(input[j] != ' ')
		{
			temp += input[j];
		}
		else
		{
			wordList.push_back(temp);
			temp = "";
		}
	}
	wordList.push_back(temp);
}