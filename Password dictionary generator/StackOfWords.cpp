#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "StackOfWords.h"

const string suffix = "$.txt"s;
const string separator = "##########################"s;
const string suffix_psw = "$psw.txt"s;

StackOfWords::StackOfWords()
{
	number_max = 1;
	number_min = 1;
}

int StackOfWords::OpenFile()
{
	ifstream myfile;
	myfile.open(this->filename + suffix);
	if (myfile.is_open())
	{
		string tempword;
		myfile >> number_max >> number_min;

		if (number_min == 0) number_min = 1; //не должны быть нулевыми
		if (number_min > number_max) number_max = number_min; // должны быть ранжированы
		if (number_max >= 32) number_max = 32; //не должны быть нереально большими; на практике не больше 10 слов в выборке
		if (number_min > number_max) number_min = number_max; // должны быть ранжированы

		while (true) //считываем проверенные слова
		{
			if (myfile.eof()) break;
			myfile >> tempword;
			if (tempword.empty()) continue;
			if (tempword == separator)	break; //пока не наткнемс€ на сепаратор
			word.emplace_back(tempword);
		}
		while (true) //считываем новые слова дл€ их проверки
		{
			if (myfile.eof()) break;
			myfile >> tempword;
			if (tempword.empty()) continue; //пустого слова не может быть, только в конце.
			if (tempword == separator)	continue; // сепаратора второй раз тоже не дложно быть
			word_new.emplace_back(tempword);
		}

		myfile.close();
		return 0;
	}
	else
	{
		cout << "Unable to open file " << filename << suffix << endl;;
		return -1;
	}
}

int StackOfWords::SaveFile()
{
	ofstream myfile;
	myfile.open(this->filename + suffix);
	if (myfile.is_open())
	{
		myfile << number_max << " " << number_min << endl;

		for (const auto &tempword : word) {
			myfile << tempword << endl;
		}
		myfile << separator << endl;
		for (const auto &tempword : word_new) {
			myfile << tempword << endl;
		}
		myfile.close();
	}
	else 
	{
		cout << "Unable to open file " << filename << suffix << endl;
		return -1;
	}
	if (word.size() == 0) {
		if (Next())
		{
			return 0;
		}
	}
	if (word_new.size() == 0) {
		cout << "Nothing to do: " << filename << suffix << endl;
		return -1;
	}
	return 0;
}

void StackOfWords::PasswordFound(const char* pwd) {
	ofstream myfile;
	myfile.open(this->filename + suffix_psw);
	if (myfile.is_open())
	{
		myfile << "Password:" << endl << pwd << endl;
		myfile.close();
		return;
	}
	else
	{
		cout << "Unable to open file " << filename << suffix_psw << endl;
		return;
	}
}

void StackOfWords::SetFileName(const char* filename)
{
	this->filename = filename;
}

bool StackOfWords::Next()
{
	while (true)
	{
		if (word_new.size() == 0)
		{
			return false;
		}
		if (std::find(word.begin(), word.end(), word_new.back()) == word.end())
		{
			//Ќе найден в уже имеющихс€
			word.emplace_back(word_new.back());
			word_new.pop_back();
			return true;
		}
		else {
			//Ќайден в уже имеющихс€, просто удалим
			word_new.pop_back();
		}
	}
}
