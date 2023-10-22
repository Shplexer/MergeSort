#include "interface.h"
#include "sort.h"
#include "files.h"
#include "main.h"

//Шаблон для проверки типа ввода
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

//Функция для ввода чисел
int inputInt() {
	return checkInput<int>();
}

//Функция для ввода дробных чисел
double inputDouble() {
	return checkInput<double>();
}

//Приветственное меню
//TODO: ЛОКАЛИЗИРОВАТЬ
void giveWelcomeMenu() {
	cout	<< "temporary Welcome  msg" << endl; //поменять потом
	cout	<< "1. Start" << endl
				<< "2. Test" << endl
				<< "3. Exit" << endl
				<< "> ";
}

std::vector<double>fillArrayManual() {
	std::vector<double>arr;
	cout << "size: " << endl << "> ";
	int	size = inputInt();
	for (int i = 0; i < size; i++) {
		double input = inputDouble();
		arr.push_back(input);
	}

	return arr;
}

std::vector<double>fillArrayRandom() {
	std::vector<double>arr;
	double lowestRandomNumber = 0;
	double highestRandomNumber = 0;
	cout << "size: " << endl << "> ";
	int	size = inputInt();
	cout << "lowest" << endl << "> ";
	lowestRandomNumber = inputDouble();
	do {
		cout << "Enter highest random number: " << endl;
		highestRandomNumber = inputDouble();
	} while (highestRandomNumber < lowestRandomNumber);
	
	std::uniform_real_distribution<double>unif(lowestRandomNumber, highestRandomNumber);
	std::default_random_engine re;

	for (int i = 0; i < size; i++) {
		arr.push_back(unif(re));
	}

	return arr;
}


//Меню выбора заполнения массива
std::vector<double> arrayFillMethodMenu() {
	std::vector<double>temp;
	return temp;
}