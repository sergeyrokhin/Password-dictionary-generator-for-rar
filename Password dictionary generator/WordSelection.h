#pragma once
class WordSelection
{
protected:
	unsigned int n; //всего слов
	unsigned int m; //слов в выборке
	unsigned int k; //слов последних обязательных
	unsigned long long selection; //текущая выборка
	unsigned long long selectionStop;
	unsigned long long selectionStart; //последние обязательные
	char** word;

public:
	~WordSelection();
	WordSelection(unsigned int _n, unsigned int _k, char* _word[]);
	void Start(unsigned int _m);
	void Start();
	void PrintOut();
	void PrintOutAll();
	bool Next();
	void FillSelection(char** lot_word);
};

