#pragma once
#include <vector>
#include <string>
#include <chrono>


using namespace std;

class StackOfWords
{
public: 
	vector <string> word;
	StackOfWords();
	~StackOfWords() {}
	int OpenFile();
	int SaveFile();
	void SetFileName(const char* filename);
	bool Next();
	void PasswordFound(const char * pwd);
	unsigned number_max, number_min;
private :
	string filename;
	vector <string> word_new;
};

