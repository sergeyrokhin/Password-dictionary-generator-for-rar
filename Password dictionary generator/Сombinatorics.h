#pragma once
#include "KeyboardLayout.h"


class WordOrder
{
public:
	unsigned number; //количество слов
	unsigned* order; //текущее положение
	bool NextSet();
	void GetStr(string& ss, const char* separator = NULL);
	WordOrder(unsigned num);
	~WordOrder();
};

class WordMap
{
public:
	unsigned number; //количество слов
	unsigned* placement; //расстановка
	bool NextSet();
	void GetStr(string& ss, const char* separator = NULL);
	WordMap();
	WordMap(unsigned num);
	~WordMap();
};

class KeyWords
{
public:
	unsigned lenght; //общая длина слов
	unsigned number; //количество слов
	SingleWord* words; //слова
	void SetWord(char* word, unsigned n);
	void Set(unsigned n);
	//char* GetStr(const WordOrder* order, const WordMap* map,  const char* separator = NULL);
	KeyWords();
	KeyWords(unsigned n);
	~KeyWords();
	void GetStr(char* s, const unsigned set, WordOrder* order, WordMap* map, char* separator = NULL);
};

class PasswordCounter
{
protected:
	WordMap* map;
	KeyWords* words;
	WordOrder* order;
	unsigned set;
	size_t size;
public:
	unsigned int count;
	wchar_t* wpassword;
	char* password;

	unsigned LenghtPassord() { return words->lenght; }
	bool NextPassword();
	PasswordCounter();
	PasswordCounter(KeyWords* _words, const unsigned _set, WordMap* _map, WordOrder* _order);
	~PasswordCounter();
};
