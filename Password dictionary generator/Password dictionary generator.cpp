// Password dictionary generator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "WordSelection.h"
#include "KeyboardLayout.h"
#include "Сombinatorics.h"
//#include "ConsoleFrame.h"
#include "StackOfWords.h"
#include "SimpleTimer.h"


void ExtractArchive(char* ArcName, KeyWords* words, WordMap* map);

//ConsoleFrame <unsigned> Console; 
StackOfWords stack_of_words;

using namespace std;
KeyboardLayout KB(
	"`1234567890-=qwertyuiop[]asdfghjkl;'\\zxcvbnm,./",
	"~!@#$%^&*()_+QWERTYUIOP{}ASDFGHJKL:\"|ZXCVBNM<>?",
	"ё1234567890-=йцукенгшщзхъфывапролджэ\\ячсмитьбю.",
	"Ё!\"№;%:?*()_+ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭ/ЯЧСМИТЬБЮ,"
);
bool password_found = false;


void PrintHelp() {
	std::string arh_name = "arhive001.rar";
	std::cout << "параметры: <файл-архив>\n";
	std::cout << "пример параметров:" << arh_name << std::endl;
	std::cout << "Набор слов для комбинации в файле: " << arh_name << suffix << std::endl << "пример файла слов подбора\n";
	std::cout << "3 2\nd\nc\nb\na\n\n";
	std::cout << "В случае успеха пароль будет на экране и в файле: " << arh_name << suffix_psw << std::endl;
}


int main(int argc, char* argv[])
{
	SimpleTimer st(" Итоговое время:");

	setlocale(LC_ALL, "Russian");

	if (argc < 2)
	{
		PrintHelp();
		return(0);
	};

	//Console.AddPoint(0, 0, 1); //000010001111
	//Console.AddPoint(1, 33, 1); //password
	//Console.AddPoint(2, 0, 2); //1
	//Console.AddPoint(3, 3, 2); //temp


	stack_of_words.SetFileName(argv[1]);
	if (stack_of_words.OpenFile())
	{
		PrintHelp();
		stack_of_words.SaveFile();
		return(0);
	};

	while (stack_of_words.Next())
	{
		SimpleTimer st1(" время:");
		//создаем набор слов
		WordSelection ws(stack_of_words);
		//std::cout << "\n=========\n";
		ws.PrintOutAll();

		//Console.Slide(2); //сдвинем консоль на следующую строку
		//перебор количество слов от к+1 до m, к - обязательные присутствующие слова
		unsigned short number_max = stack_of_words.number_max < ws.GetNumberOfWord() ? stack_of_words.number_max : ws.GetNumberOfWord();
		for (size_t s_w_q = stack_of_words.number_min; s_w_q <= number_max; s_w_q++) // s_w_q - количество слов в выборке
		{
			//перебор слов
			WordMap map(s_w_q); //После полного перебора, он встает в начальное состояние, поэтому можно не сбрасывать в начальное состояние
			ws.Start(s_w_q); //определяем количество в выборке
			char** lot_word = new char* [s_w_q]; //ссылки на слова.
			do
			{
				//std::cout << "\n-----\n";
				//Console.Slide(1);
				//Console.SetCursor(0);
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
		//std::cout << "Конец\n";
		stack_of_words.SaveFile();
	}
	stack_of_words.SaveFile();
	return 0;
}
