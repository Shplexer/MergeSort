#include "interface.h"
#include "sort.h"
#include "files.h"

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
	std::cout	<< "Welcome temporary msg" << std::endl; //поменять потом
	std::cout	<< "1. Start" << std::endl
				<< "2. Test" << std::endl
				<< "3. Exit" << std::endl
				<< "> ";
}

std::vector<double>fillArrayManual() {
	std::vector<double>arr;
	std::cout << "size: " << std::endl << "> ";
	int	size = inputInt();
	for (int i = 0; i < size; i++) {
		double input = inputDouble();
		arr.push_back(input);
	}

	return arr;
}

std::vector<double>fillArrayRandom() {
	std::vector<double>arr;
	int lowestRandomNumber = 0;
	int highestRandomNumber = 0;
	std::cout << "size: " << std::endl << "> ";
	int	size = inputInt();
	std::cout << "lowest" << std::endl << "> ";
	lowestRandomNumber = inputDouble();
	do {
		std::cout << "Enter highest random number: " << std::endl;
		highestRandomNumber = inputDouble();
	} while (highestRandomNumber < lowestRandomNumber);
	int range = (highestRandomNumber - lowestRandomNumber) + 1;

	srand(static_cast<double>(time(NULL)));

	for (int i = 0; i < size; i++) {
		double input = lowestRandomNumber + rand() % range;
		arr.push_back(input);
	}

	return arr;
}


//Меню выбора заполнения массива
std::vector<double> arrayFillMethodMenu() {


}