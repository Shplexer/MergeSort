#include "Files.h"
#include "interface.h"

using namespace std;
using namespace filesystem;

vector<double>& inputFromFile() {
	vector<double> vec;
	bool isCorrect = false;
	string fileName;
	cout << "��� ����� ����� ���� ������������ � ������� ***.txt" << endl
		 << "������ � ����� ������ ���� ������������ � ����, ��������: '-5 34 7 18' " << endl;

	// ����������� ������� ��������� ������ �� ����� ��� ���������� ��������� ������
	while (true) {
		fileName = InputFileCheck();
		//size = CalculateSize(fileName);
		isCorrect = GetValueFromFile(vec, fileName);
		if (isCorrect) break;
		else {
			cout << "������ � ����� �����������, �������� ������ ���� ��� �������� ���������� �������� � ���������� �����" << endl;
		}
	}
	cout << "������ �������� � �������� � ������!" << endl;
	return vec;
}

void outputToFile(vector<double>& vec) {
	bool isCorrect = false;
	string fileName;
	fstream fileStream;
	cout << "��� ����� ����� ���� ������������ � ������� ***.txt" << endl;
	fileName = OutputFileCheck();
	fileStream.open(fileName);
	for (int i = 0; i < vec.size(); i++) {
		fileStream << vec[i] << " ";
	}
	cout << "������ ��������!" << endl;
}

string OutputFileCheck() {
	bool isExit = false;
	string fileName;
	fstream fileStream;

	cout << "������� ��� �����: ";
	getline(cin >> ws, fileName);
	do {
		isExit = false;
		fileName = FileNameCheck(fileName);
		fileStream.open(fileName);

		if (!fileStream.is_open()) {
			cout << endl << "���� � ����� ������ �� ����������! �������� ��� �����:" << endl;
			getline(cin >> ws, fileName);
			fileName = FileNameCheck(fileName);
			isExit = false;
		}
		else if (fileStream.is_open()) {
			isExit = true;
		}
	}while (!isExit);
	fileStream.close();
	return fileName;
}

string InputFileCheck() {
	bool isExit = false;
	bool isEmpty = false;
	string fileName;
	fstream fileStream;

	cout << "������� ��� �����: ";
	getline(cin >> ws, fileName);
	// ���� �� ����� ����������� �����
	do {
		isExit = false;
		isEmpty = false;
		fileName = FileNameCheck(fileName);
		fileStream.open(fileName);
		// �������� �� ������� ������ � �����
		if (fileStream.is_open() && fileStream.peek() == EOF) {
			cout << "���� ����! ���������� �����." << endl;
			fileStream.close();
			isExit = false;
			isEmpty = true;
		}
		//�������� ����� �� �������������
		else if (!fileStream.is_open()) {
			cout << endl << "���� � ����� ������ �� ����������! �������� ��� �����:" << endl;	
			getline(cin >> ws, fileName);
			fileName = FileNameCheck(fileName);
		}
		//���������� �������� �����
		else if (fileStream.is_open() && !isEmpty) {
			isExit = true;
		}
	} while (!isExit);
	fileStream.close();
	return fileName;
}

string SaveFileCheck1(string saveFileName) {
	fstream checkStream;
	bool isExit;
	bool isAllExit;
	do {
		isAllExit = false;
		checkStream.open(saveFileName);
		//error_code ec{};
		if (!checkStream.is_open()) {
			cout << "������� ��� �����: ";
			saveFileName = FileNameCheck(StringInput());
		}
		else {
			cout << "��� ��������� �����: " << saveFileName << endl <<
				"������ ���� ��� ������������! �������� �� �������������� �������:" << endl <<
				"1. ��������� � ������ ����" << endl <<
				"2. ������������ ������ ����" << endl;
			do {
				isExit = true;
				errChoice choice = static_cast<errChoice>(CheckInputInt());
				switch (choice)
				{
				case errChoice::change:
					cout << "������� ��� �����: ";
					saveFileName = FileNameCheck(StringInput());
					break;
				case errChoice::keep:
					isAllExit = true;
					break;
				default:
					isExit = false;
					break;
				}
			} while (!isExit);
		}
		checkStream.close();
		checkStream.open(saveFileName);
		if (!checkStream.is_open() || isAllExit)
			break;
		checkStream.close();
	} while (true);
	return saveFileName;
}

string FileNameCheck(string fileName) {
	error_code ec{};
	bool exitFlag;

	//���� �� ��������� ����������� ����� �����
	do {
		exitFlag = true;
		if (!ifstream(fileName)) continue;
		if (!is_regular_file(fileName, ec)) {
			cout << "������! ��������� �������� ����� � ���������� �����:" << endl;
			getline(cin >> ws, fileName);
			exitFlag = false;
		}
	} while (!exitFlag);
	return fileName;
}

bool GetValueFromFile(vector<double>& vec, string fileName) {
	double tempDouble;
	bool isCorrect = true;
	fstream fileStream;

	fileStream.open(fileName);
	// ���� �� ��������� ������ �� ����� � �� ������ � ������
	while (true) {
		fileStream >> tempDouble;
		// ���� ����� �����
		if (fileStream.eof()) {
			vec.push_back(tempDouble);
			break;
		};
		// ���� �� ��������� ����� ������
		if (fileStream.fail())
		{
			cout << "������ �������� �����������." << endl;
			isCorrect = false;
			break;
		}
		vec.push_back(tempDouble);
	}
	fileStream.close();
	return isCorrect;
}
