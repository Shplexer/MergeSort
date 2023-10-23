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

//��� ������ �� ������ ������ ���������:
vector<double> inputFromFile();	//��������� ������ �� ����� � ������. �������� ��������� �� ������ ��� ������ ������.
void outputToFile(vector<double>& vec);		//����� ������� � ����. �������� ��������� �� ������, ������� ����� ������� � ����.

std::string OpenFile();		//�������� ����������� �������� �����. ���������, ������ �� ���� � ���������� �� ����. ���������� ��� �����, ���� �� �������� ��� ��������� ����������.
string FileNameCheck(string inputName);		//�������� ������������ ����� �����. ��������� ����������� ����� ������������ �������� � ����������������� ����. ���������� ��� �����, ���� ��� �������� �� �������� ������������ ��������
bool GetValueFromFile(vector<double>& vec, string fileName);	//��������� ������ �� ����� � ������ � ������. �� ���� �������� ��������� �� ������ ��� ������ ������ � ��� �����. ���������� ������, ���� ������ ��������.