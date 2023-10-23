#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using std::vector;
using std::string;

enum class errChoice { change = 1, add, keep };
enum class saveDialogChoice { yes = 1, no };

//Для вызова из других частей программы:
vector<double> inputFromFile();	//Получение данных из файла в массив. Получает указатель на массив для записи данных.
void outputToFile(vector<double>& vec);		//Вывод массива в файл. Получает указатель на массив, который нужно вывести в файл.



std::string OpenFile();		//Проверка возможности открытия файла. Проверяет, пустой ли файл и существует ли файл. Возвращает имя файла, если он подходит для получения информации.
string FileNameCheck(string inputName);		//Проверка корректности имени файла. Исключает возможность ввода некорректных символов и зарезервированных имен. Возвращает имя файла, если его название не содержит неподходящих символов
bool GetValueFromFile(vector<double>& vec, string fileName);	//Получение данных из файла и запись в вектор. На вход получает указатель на вектор для записи данных и имя файла. Возвращает истину, если данные получены.