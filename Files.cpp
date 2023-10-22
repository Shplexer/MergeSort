#include "Files.h"
#include "interface.h"

using namespace std;
using namespace filesystem;

void inputFromFile(vector<double>& vec) {
	bool isCorrect = false;
	string fileName;
	cout << "��� ����� ����� ���� ������������ � ������� ***.txt" << endl
		 << "������ � ����� ������ ���� ������������ � ����, ��������: '-5 34 7 18' " << endl;

	// ����������� ������� ��������� ������ �� ����� ��� ���������� ��������� ������
	while (true) {
		fileName = OpenFile();
		//size = CalculateSize(fileName);
		isCorrect = GetValueFromFile(vec, fileName);
		if (isCorrect) break;
		else {
			cout << "������ � ����� �����������, �������� ������ ���� ��� �������� ���������� �������� � ���������� �����" << endl;
		}
	}
	cout << "������ �������� � �������� � ������!" << endl;
}

void outputToFile(vector<double>& vec) {
	bool isCorrect = false;
	string fileName;
	fstream fileStream;
	cout << "��� ����� ����� ���� ������������ � ������� ***.txt" << endl;
	fileName = OpenFile();
	fileStream.open(fileName);
	for (int i = 0; i < vec.size(); i++) {
		fileStream << vec[i] << " ";
	}
	cout << "������ ��������!" << endl;
}

string OpenFile() {
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
			cout << "���� ������!" << endl;
			isExit = true;
		}
	} while (!isExit);
	fileStream.close();
	return fileName;
}

string FileNameCheck(string inputName) {
	error_code ec{};
	bool exitFlag;

	//���� �� ��������� ����������� ����� �����
	do {
		exitFlag = true;
		if (!ifstream(inputName)) continue;
		if (!is_regular_file(inputName, ec)) {
			cout << "������! ��������� �������� ����� � ���������� �����:" << endl;
			getline(cin >> ws, inputName);
			exitFlag = false;
			break;
		}
	} while (!exitFlag);
	return inputName;
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
