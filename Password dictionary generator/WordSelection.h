#pragma once
#include "StackOfWords.h"
class WordSelection
{
protected:
	unsigned int n; //всего слов
	unsigned int m; //слов в выборке
	unsigned int k; //слов последних обязательных
	unsigned long long selection; //текущая выборка
	unsigned long long selectionStop;  // болше этого числа selection никогда не будет
	unsigned long long selectionStart; //последние обязательные. Заполнены старшие разряды для обязательных слов
	char** word; //полный набор слов для перебора

public:
	~WordSelection();
	WordSelection(unsigned int _n, unsigned int _k, char* _word[]);
	WordSelection(StackOfWords& stack);
	void Start(unsigned int _m); //инициализировать начальное состояние выборки selection 
	void Start();
	void PrintOut();
	unsigned GetNumberOfWord() { return n; };
	void PrintOutAll();
	bool Next(); //подготовить следующую выборку m слов (selection ++)
	void FillSelection(char** lot_word); //Заполнить lot выборкой слов в соответствии с selection 
};

