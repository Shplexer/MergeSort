#include "Files.h"
#include "interface.h"

using namespace std;
using namespace filesystem;

vector<double> inputFromFile() {
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
	ofstream fileStream;
	cout << "��� ����� ����� ���� ������������ � ������� ***.txt" << endl;
	cout << "������� ��� �����: ";
	getline(cin >> ws, fileName);
	fileName = FileNameCheck(fileName);

	fileStream.open(fileName);
	if (fileStream.is_open())
		cout << "KEK" << endl;

	for (int i = 0; i < vec.size(); i++) {
		fileStream << vec[i] << " ";
	}
	cout << "������ ��������!" << endl;
	fileStream.close();
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
	string temp = "";
	for (auto i = fileName.size() - 4; i < fileName.size(); i++) {
		temp = temp + fileName[i];
	}
	if (temp != ".txt") {
		fileName = fileName + ".txt";
	}
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
