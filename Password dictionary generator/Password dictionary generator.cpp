// Password dictionary generator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//#include <windows.h>
#include "WordSelection.h"
#include "KeyboardLayout.h"
#include "Сombinatorics.h"

void ExtractArchive(char* ArcName, KeyWords* words, WordMap* map);

using namespace std;
KeyboardLayout KB(
	"`1234567890-=qwertyuiop[]asdfghjkl;'\\zxcvbnm,./",
	"~!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKL:\"|ZXCVBNM<>?",
	"ё1234567890-=йцукенгшщзхъфывапролджэ\\ячсмитьбю.",
	"Ё!\"№;%:?*()_+ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭ/ЯЧСМИТЬБЮ,"
);
bool password_found = false;


void PrintHelp() {
	std::cout << "параметры: <файл-архив> <максимальное количество слов в выборке (m)> <количество обязательных они в конце> <Слово1> <Слово2> ... <Слово(n)>\n";
	std::cout << "пример параметров: arhive001.rar 3 1 win cool 007\n";
}


//    TCHAR szPath[] = L"\"C:\\Program Files\\WinRAR\\RAR.exe\" t -phj[by1 C:\\Users\\User\\pi2.rar";
int main(int argc, char* argv[])
{
	unsigned int k,m, n = (unsigned)argc - 4;  // если передаем аргументы, то argc будет больше 1(в зависимости от кол-ва аргументов)

	setlocale(LC_ALL, "Russian");

	m = atoi(argv[2]);
	k = atoi(argv[3]);
	if (n < 1 || m < 1 || m > n || k >= m)
	{
		PrintHelp();
		return(0);
	}


	//из командной строки считываем слова и создаем набор слов
	WordSelection ws(n, k, &argv[4]);
	std::cout << "\n=========\n";
	ws.PrintOutAll();
	std::cout << "\n";

	//перебор количество слов от 1 до m 
	for (size_t s_w_q = k + 1; s_w_q <= m; s_w_q++) // s_w_q - количество слов в выборке
	{
		//перебор слов
		WordMap map(s_w_q); //После полного перебора, он встает в начальное состояние, поэтому можно не сбрасывать в начальное состояние
		ws.Start(s_w_q); //определяем количество в выборке
		char** lot_word = new char* [s_w_q]; //ссылки на слова
		do
		{
			std::cout << "\n-----\n";
			ws.FillSelection(lot_word); //заполняем выборкой

			//Заполним
			KeyWords words(s_w_q);

			for (size_t k = 0; k < s_w_q; k++)
			{
				words.SetWord(lot_word[k], k);
			}
			ExtractArchive(argv[1], &words, &map);
			if (password_found)
			{
				return 0;
			}
		} while (ws.Next());
		delete[] lot_word;
	}
	std::cout << "Конец\n";
	return 0;

}
