#include <string>
#include <iostream>
#include <sstream> 
#include "Сombinatorics.h"
#define NUM_OF_WORD 4 //число вариантов модификации слова шифт и заглавная

using namespace std;

KeyWords::KeyWords() {
	number = 0;
}
KeyWords::~KeyWords() {
		if(number > 0) delete[] words;
}

void KeyWords::SetWord(char* word, unsigned n) {
    if (n < number) {
        words[n].Assign(word);
        lenght += strlen(word);
    }
}

void KeyWords::GetStr(char* s, const unsigned set, WordOrder* order, WordMap* map, char* separator) {
    string ss;
        for (size_t i = 0; i < number; i++)
    {
        ss += words[order->order[i]].w[set][map->placement[i]] ;
        if (separator != NULL && i < (number - 1))    ss += separator;
    }
    ss.copy(s, lenght);
    s[lenght] = 0;
}

void KeyWords::Set(unsigned n) {
	if (number > 0) delete[] words;
    lenght = 0;
    number = n;
	words = new SingleWord[n];
}
KeyWords::KeyWords(unsigned n) {
	Set(n);
}

WordOrder::WordOrder(unsigned num) {
    number = num;
    order = new unsigned[num];
    for (size_t i = 0; i < number; i++)
    {
        order[i] = i; //это начальное заполнение
    }
}

WordOrder::~WordOrder() {
    if (number > 0) delete order;
}

void WordOrder::GetStr(string& ss, const char* separator) {

    for (size_t i = 0; i < number; i++)
    {
        ss += to_string(order[i]);
        if(separator != NULL && i < number - 1)    ss += separator ;
    }
}

void swap(unsigned* a, int i, int j)
{
    int s = a[i];
    a[i] = a[j];
    a[j] = s;
}
bool WordOrder::NextSet()
{
    int j = number - 2;
    while (j != -1 && order[j] >= order[j + 1]) j--;
    if (j == -1)
        return false; // больше перестановок нет
    int k = number - 1;
    while (order[j] >= order[k]) k--;
    swap(order, j, k);
    int l = j + 1, r = number - 1; // сортируем оставшуюся часть последовательности
    while (l < r)
        swap(order, l++, r--);
    return true;
}

void WordMap::GetStr(string& ss, const char* separator) {
    
    for (size_t i = 0; i < number; i++)
    {
        ss += to_string(placement[i]);
        if (separator != NULL && i < number - 1)    ss += separator;
    }
}

WordMap::WordMap() {
    number = 0;
}

WordMap::~WordMap() {
    if (number != 0)
    {
        delete placement;
    }
}
WordMap::WordMap(unsigned num) {
    number = num;
    placement = new unsigned[num];
    for (size_t i = 0; i < number; i++)
    {
        placement[i] = 0; //это начальное заполнение
    }
}
bool WordMap::NextSet() {
    for (size_t i = 0; i < number; i++)
    {
        ++ placement[i] %= NUM_OF_WORD; //увеличим значение в этом разряде
        if (placement[i] != 0) //, если переполнился, то обнулим
        {
            return true; //не переполнился, значит следующий разряд увеличивать не нужно, выход
        }
        if (i == number - 1)
        {
            return false;
        }
        //требуется увеличить следующий разряд, следующий цикл
    }
    return false;
}

bool PasswordCounter::NextPassword() {
    size_t convertedChars = 0;
    size_t size = words->lenght + 1;
    bool not_end = true;
    if(count != 0) //если это первый шаг, то сдвигаться не будем
        if(! map->NextSet()) not_end = order->NextSet(); //если карта пролистана, переходим к следующей перестановке
    if (not_end) {
        words->GetStr(password, set, order, map);
        mbstowcs_s(&convertedChars, wpassword, size, password, _TRUNCATE);
    }
    ++count;
    return not_end;
}
PasswordCounter::PasswordCounter(KeyWords* _words, const unsigned _set, WordMap* _map, WordOrder* _order) {
    //size_t convertedChars = 0;
    count = 0;
    set = _set;
    map = _map;
    words = _words;
    order = _order;
    size = words->lenght + 1;
    password = new char[size];
    //password[0] = 0;
    wpassword = new wchar_t[size];
    //wpassword[0] = 0;
    //words->GetStr(password, set, order, map);
    //mbstowcs_s(&convertedChars, wpassword, size, password, _TRUNCATE);
}
PasswordCounter::~PasswordCounter() {
    if (size > 0) {
        delete password;
        delete wpassword;
    }
}

