#pragma once
class WordSelection
{
protected:
	unsigned int n; //����� ����
	unsigned int m; //���� � �������
	unsigned int k; //���� ��������� ������������
	unsigned long long selection; //������� �������
	unsigned long long selectionStop;
	unsigned long long selectionStart; //��������� ������������
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

