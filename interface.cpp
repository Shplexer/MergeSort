#include "interface.h"
#include "sort.h"
#include "files.h"
#include "main.h"

//������ ��� �������� ���� �����
template<typename T>
T checkInput() {
	T userInput{};
	while (!(cin >> userInput)) {
		cin.clear();											//����� ����� ������
		cin.ignore(INT_MAX, '\n');								//������� ������� �� ����������� ��������, ������ INT_MAX, ��� �� '\n'
		cout << "������. ������ ������������ ��������, ���������� �����" << endl;
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

//������� ��� ����� �����
int inputInt() {
	return checkInput<int>();
}

//������� ��� ����� ������� �����
double inputDouble() {
	return checkInput<double>();
}

//�������������� ����
void giveWelcomeMenu() {
	cout	<< "����� ���������� � ���������! " << endl
				<< "��������: ����������� N� 2" << endl
				<< "���������: ������� ����, ������ ������, ������� ������" << endl
				<< "����������, �������� ���� ���������, �������������� ����, � �������� ��������������� �����:" << endl;
	cout	<< "1. ������ ������" << endl
				<< "2. ��������� ���� ���������" << endl
				<< "3. ����� �� ���������" << endl
				<< "> ";
}

std::vector<double>fillArrayManual() {
	std::vector<double>arr;
	cout << "������� ������: " << endl
		 << "> ";
	int	size = inputInt();
	for (int i = 0; i < size; i++) {
		cout << "������� " << i+1 << "-�� ������� �������" << endl
			 << "> ";
		double input = inputDouble();
		arr.push_back(input);
	}

	return arr;
}

std::vector<double>fillArrayRandom() {
	std::vector<double>arr;
	double lowestRandomNumber = 0;
	double highestRandomNumber = 0;
	cout << "������� ������: " << endl
		 << "> ";
	int	size = inputInt();
	cout << "������� ���������� ���������� �����: " << endl
		 << "> ";
	lowestRandomNumber = inputDouble();
	do {
		cout << "������� ����������� ���������� �����: " << endl
			 << "> ";
		highestRandomNumber = inputDouble();
	} while (highestRandomNumber < lowestRandomNumber);
	
	std::uniform_real_distribution<double>unif(lowestRandomNumber, highestRandomNumber);
	std::default_random_engine re;

	for (int i = 0; i < size; i++) {
		arr.push_back(unif(re));
	}

	return arr;
}

//����� �������
void giveArrayToUser(std::vector<double> array) {
	cout << "��������������� ������: [";
	for (int i = 0; i < array.size(); i++) {
		cout << array[i];
		if (i != array.size() - 1) {
			cout << ", ";
		}
		else {
			cout << "]" << endl;
		}
	}
}


void saveToFile(vector<double> arr) {
	bool exitFlag = false;
	cout << "������ ��������� ������ � ����? �������� ���� �� ���������:" << endl
		<< "1. ��" << endl
		<< "2. ���" << endl;
	cout << "> ";
	saveChoice choice = static_cast<saveChoice>(inputInt());
	while (!exitFlag) {
		switch (choice) {
		case saveChoice::yes:
			outputToFile(arr);
			exitFlag = true;
			break;
		case saveChoice::no:
			cout << "���� �� ����� �������" << endl;
			exitFlag = true;
			break;


		default:
			cout << "������ �������� ���, �������� ������������" << endl;
			exitFlag = false;
			break;

		}

	}


}


//���� ������ ���������� �������
std::vector<double> arrayFillMethodMenu() {
	std::vector<double>temp;
	bool exitFlag = false;
	cout << "������� ���� �� �������������� �������� ���������� �������: " << endl;
	cout << "1. �������" << endl
		 << "2. ����������� �������" << endl
		 << "3. �� �����"
		<< "> ";

	arrayFillMethodChoice choice = static_cast<arrayFillMethodChoice>(inputInt());
	while (!exitFlag) {
		switch (choice) {
		case arrayFillMethodChoice::manual:
			temp = fillArrayManual();
			exitFlag = true;
			break;
		case arrayFillMethodChoice::random:
			temp = fillArrayRandom();
			exitFlag = true;
			break;
		case arrayFillMethodChoice::file:
			cout << "������� ��� ����� � �������:" << endl
				 << "> ";
			temp = inputFromFile();
			exitFlag = true;
			break;

		default:
			cout << "������ �������� ���, �������� ������������" << endl;
			exitFlag = false;
			break;
		}
	}
	return temp;
}