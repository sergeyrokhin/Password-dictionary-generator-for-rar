#pragma once
#include <vector>
#include <string>
#include <chrono>

extern const std::string suffix;
extern const std::string separator;
extern const std::string suffix_psw;

class StackOfWords
{
public: 
	std::vector <std::string> word;
	StackOfWords();
	~StackOfWords();
	int OpenFile();
	int SaveFile();
	void SetFileName(const char* filename);
	bool Next();
	void PasswordFound(const char * pwd);
	unsigned number_max, number_min;
private :
	std::string filename;
	std::vector <std::string> word_new;
};

