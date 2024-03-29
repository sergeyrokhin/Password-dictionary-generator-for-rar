﻿#include <iostream>
#include <bitset>
#include "WordSelection.h"
#include "StackOfWords.h"

extern StackOfWords stack_of_words;

using namespace std;

void WordSelection::PrintOutAll()
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << i << " " << word[i] << " ";
    }
}

void WordSelection::PrintOut()
{
    std::cout << std::bitset<32>(selection);
    for (size_t i = 0; i < n; i++) {
        if (selection & ((unsigned long long) 1) << i)
        {
            std::cout << word[i] << " ";
        }
    }
    //std::cout << endl;
}


void WordSelection::FillSelection(char** lot_word)
{
    unsigned k = 0;

    std::cout << std::bitset<32>(selection);
    for (size_t i = 0; i < n; i++) {
        if (selection & ((unsigned long long) 1) << i)
        {
            std::cout << " " << word[i];
            lot_word[k++] = word[i];
        }
    }
    //std::cout << endl;
}

void WordSelection::Start()
{
    unsigned long long selectionUp = (unsigned long long)1 << (m - k); //000100  m = 5 k = 3
    --selectionUp;                            //000011

    selection = selectionStart | selectionUp;
}

void WordSelection::Start(unsigned int _m)
{
    m = _m;
    Start();
}


bool WordSelection::Next()
{
    unsigned long long position = 1;
    while (++selection < selectionStop)
    {
        unsigned k = 0;
        //std::cout << "проверка на количество единиц " << std::bitset<16>(selection) << endl;
        // сколько единиц?
        for (size_t i = 0; i < n; i++) {
            if (selection & ((unsigned long long) 1) << i)
            {
                ++k;
            }
        }
        if (k == m)
        {
            return true;
        }
    }
    return false;
}

WordSelection::~WordSelection() {
    for (size_t i = 0; i < n; i++)
    {
        delete word[i];
    }
}
WordSelection::WordSelection(unsigned int _n, unsigned int _k, char* _word[]) {
    n = _n;
    k = _k;
    m = 0;
    size_t s_o;
    word = new char* [n];
    for (size_t i = 0; i < n; i++)
    {
        s_o = strlen(_word[i]) + 1;
        word[i] = new char[s_o];
        strcpy_s(word[i], s_o, _word[i]);
    }

    selectionStop = (unsigned long long)1 << n; //00010000  n = 4


    selectionStart = (unsigned long long)1 << k; //0001000  k = 3
    --selectionStart;                            //0000111
    selectionStart = selectionStart << (n - k); //00011100  n = 5 
    //    Start();
}

WordSelection::WordSelection(StackOfWords & stack) {
    n = stack.word.size();
    k = (n <= 1) ? 0 : 1;
    m = 0;
    size_t s_o;
    word = new char* [n];
    size_t i = 0;
    for (auto &addword : stack.word)
    {
        s_o = addword.size() + 1;
        word[i] = new char[s_o];
        strcpy_s(word[i], s_o, addword.c_str());
        //strcpy(word[i], addword.c_str());
        ++i;
    }

    selectionStop = (unsigned long long)1 << n; //00010000  n = 4


    selectionStart = (unsigned long long)1 << k; //0001000  k = 3
    --selectionStart;                            //0000111
    selectionStart = selectionStart << (n - k); //00011100  n = 5 
    //    Start();
}

