# Password dictionary generator for rar
# Программа для подбора пароля к архиву rar выборкой из указанных слов

Перебор всех возможных вариантов перестановок символов бесконечен. Но если автор пароля может вспомнить слова, которые использовал, то перебор всех вариантов сочетаний этих слов не кажется недостижимым.

Если известны какие слова могут быть в составе пароля, но не известно какие из них использованы, и не известно в какой раскладке, не известно, был ли нажат Caps Lock, вводились ли некоторые слова с заглавной буквы.
Программа подберет выбирая все возможные варианты.
Считаем, что при вводе пароля не переключалась раскладка (EN-RU)

При компиляции используется библиотека, при выполнении динамическая из состава.
Используется библиотека с ресурса
https://www.rarlab.com/rar_add.htm
UnRAR.dll	- UnRAR dynamic library for Windows software developers.

Задача родилась с целью восстановить запароленный семейный архив в котором запечетлен важный момент.
Когда проект был закончен, я еще не знал, что поступлю на курс Яндекс.Практикум "Разработчик С++".
Как только появится свободное время нужно будет сделать рефакторинг.
Кроме того нужно добавить библиотеку rar, которая бы позволила добавить режим работы для небольших файлов. Единожды загрузить файл в память, проверять пароль без частой загрузки файла.
