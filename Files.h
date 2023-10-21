#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "interface.h"

using namespace std;
using namespace filesystem;

enum class fileNameChoice { change = 1, exit };
enum class errChoice { change = 1, add, keep };
enum class saveDialogChoice { yes = 1, no };
vector<double>& inputFromFile(vector<double>& vec);
string OpenFile();								 //проверка возможности открытия файла
string FileNameCheck(string inputName);						 //проверка корректности имени файла
bool GetValueFromFile(vector<double>& vec, string fileName);
//int CalculateSize(string fileName);