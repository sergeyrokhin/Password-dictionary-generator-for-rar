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
		const char* _l1, // ���� - 1
		const char* _l2, // ���� - 2
		const char* _l3, //���� � ������
		const char* _l4);
	~KeyboardLayout();
//private:
};

	

class SingleWord 
{
public:
	
	//char* w; //�������� �����
	char* w[2][4]; //[������ ���������][������ �������, ������ � ������];

	SingleWord (const char* s);
	SingleWord();
	~SingleWord ();
	SingleWord& operator= (const char* s);
	void SetLayout(const char* s);
	//��� ����� ��������, ��� ����� �������� � ����� ��������� � ��� ������
	void Assign(const char* s);

private:
	void Clear();
	unsigned length; //����� �����
	int Layout; //����� ���������
};


