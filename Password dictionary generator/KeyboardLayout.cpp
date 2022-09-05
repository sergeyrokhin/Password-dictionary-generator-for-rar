#include "KeyboardLayout.h"

extern KeyboardLayout KB;


KeyboardLayout::KeyboardLayout(
	const char* _l1,
	const char* _l2,
	const char* _l3,
	const char* _l4) {

	unsigned _length;
	//�������� ��� ��������� �� ����������� ������.
	length = strlen(_l1);
	_length = strlen(_l2);
	if (length > _length) length = _length;
	_length = strlen(_l3);
	if (length > _length) length = _length;
	_length = strlen(_l4);
	if (length > _length) length = _length;

	//�������� ������
	for(size_t i = 0; i < 4; ++i) l[i] = new char[length + 1];
	//l1 = new char[number + 1];
	//l2 = new char[number + 1];
	//lh1 = new char[number + 1];
	//lh2 = new char[number + 1];
	for (size_t i = 0; i < length; i++)
	{
		l[0][i] = _l1[i];
		l[1][i] = _l2[i];
		l[2][i] = _l3[i];
		l[3][i] = _l4[i];
	}
	//�������� �������� ����� ������
	for (size_t i = 0; i < 4; ++i) l[i][length]  = '\0';
}

KeyboardLayout::~KeyboardLayout()
{
	for (size_t i = 0; i < 4; ++i) delete l[i];
}

int KeyboardLayout::FindLayout(const char a) {
	int numLayout = -1;
	for (size_t j = 0; j < 4; ++j) {
		for (size_t i = 0; i < length; i++) {
			if (l[j][i] == a) {
				if (numLayout == -1)
				{
					numLayout = j;
					return numLayout; // �������� ������������� ���������. �� ����� ������ ������������ ����� ������� �����
				}
				else return -1;
			}
		}
	}
	return numLayout;
}

int KeyboardLayout::FindPosition(const unsigned layout, const char a) {
	for (size_t i = 0; i < length; i++) {
		if (l[layout][i] == a) {
			return i;
		}
	}
	return -1;
}

SingleWord::SingleWord()
{
	length = 0;
	Layout = -1; // ����� ���������
}


SingleWord::SingleWord(const char* word)
{
	length = 0;
	Layout = -1; // ����� ���������
	Assign(word);
}


SingleWord::~SingleWord()
{
	Clear();
}

void SingleWord::Clear()
{
	if (Layout != -1) {
		for (size_t i = 0; i < 2; ++i)
			for (size_t j = 0; j < 4; ++j) delete w[i][j];
	}
}

SingleWord& SingleWord::operator= (const char* s) {
	Assign(s);
	return *this;
}

void SingleWord::Assign(const char* s) {
	Clear();
	length = strlen(s);
	Layout = -1;
	for (size_t j = 0; j < length; ++j) {
		Layout = KB.FindLayout(s[j]);
		if (Layout != -1) break;
	}
	if (Layout == -1) return; //������������ �����

	int* Numbers = new int[length]; //������ ������� � �������� ��� ������ ����� �����

	//�������� ����� �� �������������� ������ ����� ���������
	for (size_t j = 0; j < length; ++j) {
		Numbers[j] = KB.FindPosition(Layout, s[j]);
		if (Numbers[j] == -1) {
			delete Numbers;
			return; //�� ��� ������� �� ����� ��������. //��� ������, ����� �� ������
		}
	}
	// ������ ������� �������� ����� �����
	for (size_t i = 0; i < 2; ++i) // ��������� ���������� 0 - ������ 0,1; 1 ������ 2,3  ��������
		for (size_t j = 0; j < 4; ++j) { //0,1 ������ �������� 2,3 ������ � ��������� ������ �����
			w[i][j] = new char[length + 1];
			for (size_t k = 0; k < length; ++k) {
				w[i][j][k] = KB.l[(i * 2) + (j % 2)][Numbers[k]];
			}
			w[i][j][length] = 0;

			if (j > 1) { //1 - ��������� �����������
				w[i][j][0] = KB.l[(i * 2) + ((j + 1) % 2)][Numbers[0]]; //0 => 2, 1 => 3, 2 => 0, 3 => 1,
			}
		}
	delete Numbers;
}