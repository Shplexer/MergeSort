#include "interface.h"
#include "sort.h"
#include "files.h"
#include "main.h"

//Шаблон для проверки типа ввода
template<typename T>
T checkInput() {
	T userInput{};
	while (!(cin >> userInput)) {
		cin.clear();											//Сброс флага ошибки
		cin.ignore(INT_MAX, '\n');								//Очистка буффера на колличество символов, равное INT_MAX, или до '\n'
		cout << "Ошибка. Введёно некорректное значение, попробуйте снова" << endl;
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
void giveWelcomeMenu() {
	cout	<< "Добро пожаловать в программу! " << endl
				<< "Название: Лаборотоная N№ 2" << endl
				<< "Выполнили: Беликов Илья, Орехов Даниил, Лешуков Никита" << endl
				<< "Пожалуйста, выберите один вариантов, предстваленных ниже, и наберите соответствующую цифру:" << endl;
	cout	<< "1. Начать работу" << endl
				<< "2. Запустить тест программы" << endl
				<< "3. Выйти из программы" << endl
				<< "> ";
}

std::vector<double>fillArrayManual() {
	std::vector<double>arr;
	cout << "Введите размер: " << endl
		 << "> ";
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
	cout << "Укажите размер: " << endl
		 << "> ";
	int	size = inputInt();
	cout << "Укажите минимально допустимое число: " << endl
		 << "> ";
	lowestRandomNumber = inputDouble();
	do {
		cout << "Укажите максимально допустимое число: " << endl
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


//Меню выбора заполнения массива
std::vector<double> arrayFillMethodMenu() {
	std::vector<double>temp;
	return temp;
}