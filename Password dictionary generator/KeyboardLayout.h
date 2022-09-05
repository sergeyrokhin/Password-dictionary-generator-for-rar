#pragma once
#include <iostream>
#include <string>

using namespace std;

class KeyboardLayout
{
public:
	unsigned length;
	char* l[4];
	int FindLayout(const char a);
	int FindPosition(const unsigned layout, const char a);
	KeyboardLayout(
		const char* _l1, // язык - 1
		const char* _l2, // язык - 2
		const char* _l3, //тоже с шифтом
		const char* _l4);
	~KeyboardLayout();
//private:
};

	

class SingleWord 
{
public:
	
	//char* w; //исходное слово
	char* w[2][4]; //[каждая раскладка][первая обычная, первая с шифтом];

	SingleWord (const char* s);
	SingleWord();
	~SingleWord ();
	SingleWord& operator= (const char* s);
	void SetLayout(const char* s);
	//еще нужна проверка, что слово написано в одной раскладке и без шифтов
	void Assign(const char* s);

private:
	void Clear();
	unsigned length; //длина слова
	int Layout; //какая раскладка
};


