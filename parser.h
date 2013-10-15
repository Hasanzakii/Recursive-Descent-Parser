#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Parser
{
public:
	Parser(string str);
	~Parser() {}

private:
	bool error;
	int	nextWord;
	int	errorCount;
	//int line;
	string input;
	vector<string> wordList;

	void S();
	void NP();
	void VP();
	void NOM();
	bool Det();
	bool Noun();
	bool Verb();
	bool Aux();

	bool isFinished();
	void splitWords(string str);
};

#endif