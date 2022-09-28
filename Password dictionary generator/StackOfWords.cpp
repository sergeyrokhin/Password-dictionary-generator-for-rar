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

		if (number_min == 0) number_min = 1; //�� ������ ���� ��������
		if (number_min > number_max) number_max = number_min; // ������ ���� �����������
		if (number_max >= 32) number_max = 32; //�� ������ ���� ��������� ��������; �� �������� �� ������ 10 ���� � �������
		if (number_min > number_max) number_min = number_max; // ������ ���� �����������

		while (true) //��������� ����������� �����
		{
			if (myfile.eof()) break;
			myfile >> tempword;
			if (tempword.empty()) continue;
			if (tempword == separator)	break; //���� �� ��������� �� ���������
			word.emplace_back(tempword);
		}
		while (true) //��������� ����� ����� ��� �� ��������
		{
			if (myfile.eof()) break;
			myfile >> tempword;
			if (tempword.empty()) continue; //������� ����� �� ����� ����, ������ � �����.
			if (tempword == separator)	continue; // ���������� ������ ��� ���� �� ������ ����
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
			//�� ������ � ��� ���������
			word.emplace_back(word_new.back());
			word_new.pop_back();
			return true;
		}
		else {
			//������ � ��� ���������, ������ ������
			word_new.pop_back();
		}
	}
}
