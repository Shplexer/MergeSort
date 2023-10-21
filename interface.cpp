#include "interface.h"



//������ ��� �������� ���� �����
template<typename T>
T checkInput() {
	T userInput{};
	while (!(cin >> userInput)) {
		cin.clear();											//discard err flag
		cin.ignore(INT_MAX, '\n');								//clear buffer for INT_MAX characters or until '\n'
		cout << "ERR. Wrong input, try again" << endl;
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
//TODO: ��������������
void giveWelcomeMenu() {
	std::cout	<< "Welcome temporary msg" << std::endl; //�������� �����
	std::cout	<< "1. Start" << std::endl
				<< "2. Test" << std::endl
				<< "3. Exit" << std::endl
				<< "> ";
}

std::vector<double> fillArr() {
	std::vector<double>arr;
	std::cout << "size: " << std::endl << "> ";
	int	size = inputInt();
	for (int i = 0; i < size; i++) {
		double input = inputDouble();
		arr.push_back(input);
	}
	return arr;
}
