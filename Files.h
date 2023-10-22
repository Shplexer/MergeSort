#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include "interface.h"


enum class fileNameChoice { change = 1, exit };
enum class errChoice { change = 1, add, keep };
enum class saveDialogChoice { yes = 1, no };

//��� ������ �� ������ ������ ���������:
void inputFromFile(vector<double>& vec);	//��������� ������ �� ����� � ������. �������� ��������� �� ������ ��� ������ ������.
void outputToFile(vector<double>& vec);		//����� ������� � ����. �������� ��������� �� ������, ������� ����� ������� � ����.
//


std::string OpenFile();		//�������� ����������� �������� �����. ���������, ������ �� ���� � ���������� �� ����. ���������� ��� �����, ���� �� �������� ��� ��������� ����������.
string FileNameCheck(string inputName);		//�������� ������������ ����� �����. ��������� ����������� ����� ������������ �������� � ����������������� ����. ���������� ��� �����, ���� ��� �������� �� �������� ������������ ��������
bool GetValueFromFile(vector<double>& vec, string fileName);	//��������� ������ �� ����� � ������ � ������. �� ���� �������� ��������� �� ������ ��� ������ ������ � ��� �����. ���������� ������, ���� ������ ��������.
