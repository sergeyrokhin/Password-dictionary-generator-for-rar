#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "StackOfWords.h"

StackOfWords::StackOfWords()
{
	number_max = 1;
	number_min = 1;
}

int StackOfWords::OpenFile()
{
	auto set_file = filename + suffix;
	std::ifstream myfile(set_file);

	if (myfile.bad())
	{
		std::cout << "Unable to open init file " << set_file << std::endl;;
		return -1;
	}
	else
	{
		std::string tempword;
		myfile >> number_max >> number_min;

		if (number_min == 0) number_min = 1; //не должны быть нулевыми
		if (number_min > number_max) number_max = number_min; // должны быть ранжированы
		if (number_max >= 32) number_max = 32; //не должны быть нереально большими; на практике не больше 10 слов в выборке
		if (number_min > number_max) number_min = number_max; // должны быть ранжированы

		std::cout << "\nВыборка из слов, количество в выборке от " << number_min << " максимально " << number_max << std::endl;
		std::cout << "Слова для перебора: \n";

		while (true) //считываем новые слова для их проверки
		{
			myfile >> tempword;
			if (myfile.eof()) break; //если конец файла, то нужно проверять, т.к. tempword не затирается
			if (tempword.empty()) continue;// continue;
			if (tempword == separator)	break; //пока не наткнемся на сепаратор
			word_new.emplace_back(tempword);
			std::cout << tempword << std::endl;
		}
		std::cout << "Отработанные комбинации слов: \n";
		while (true) //считываем проверенные слова
		{
			myfile >> tempword;
			if (myfile.eof()) break; //если конец файла, то нужно проверять, т.к. tempword не затирается
			if (tempword.empty()) break; //пустого слова не может быть, только в конце.
			if (tempword == separator)	continue; // сепаратора второй раз тоже не дложно быть
			word.emplace_back(tempword);
			std::cout << tempword << std::endl;
		}

		myfile.close();
		return 0;
	}
}

StackOfWords::~StackOfWords() { }

int StackOfWords::SaveFile()
{
	std::ofstream myfile;
	myfile.open(this->filename + suffix);
	if (myfile.is_open())
	{
		myfile << number_max << " " << number_min << std::endl;

		for (const auto& tempword : word_new) {
			myfile << tempword << std::endl;
		}
		myfile << separator << std::endl;
		for (const auto& tempword : word) {
			myfile << tempword << std::endl;
		}
		myfile.close();
	}
	else 
	{
		std::cout << "Unable to open file " << filename << suffix << std::endl;
		return -1;
	}
	if (word.size() == 0) {
		if (Next())
		{
			return 0;
		}
	}
	if (word_new.size() == 0) {
		std::cout << "Nothing to do: " << filename << suffix << std::endl;
		return -1;
	}
	return 0;
}

void StackOfWords::PasswordFound(const char* pwd) {
	std::ofstream myfile(filename + suffix_psw);
	if (myfile.is_open())
	{
		myfile << "Password:" << std::endl << pwd << std::endl;
		myfile.close();
		return;
	}
	else
	{
		std::cout << "Unable to open file " << filename << suffix_psw << std::endl;
		return;
	}
}

void StackOfWords::SetFileName(const char* _filename)
{
	filename = _filename;
}

bool StackOfWords::Next()
{
	while (true)
	{
		if (word_new.size() == 0)
		{
			return false;
		}
		//if (std::find(word.begin(), word.end(), word_new.back()) == word.end())
		//{
			//Не найден в уже имеющихся
			word.emplace_back(word_new.back());
			std::cout << "\nПроверяем комбинации слов:\n";
			for(const auto &word_prnt : word) {
				std::cout << word_prnt << std::endl;
			}
			word_new.pop_back();
			return true;
		//}
		//else {
		//	//Найден в уже имеющихся, просто удалим
		//	word_new.pop_back();
		//}
	}
}

using namespace std;
const std::string suffix = "$.txt"s;
const std::string separator = "##########################"s;
const std::string suffix_psw = "$psw.txt"s;
