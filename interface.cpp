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
		cout << "Введите " << i+1 << "-ый элемент массива" << endl
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

//Вывод массива
void giveArrayToUser(std::vector<double> array) {
	cout << "Отсортированный массив: [";
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
	cout << "Хотите сохранить массив в файл? Выберите один из вариантов:" << endl
		<< "1. Да" << endl
		<< "2. Нет";
	cout << "> ";
	saveChoice choice = static_cast<saveChoice>(inputInt());
	while (!exitFlag) {
		switch (choice) {
		case saveChoice::yes:
			outputToFile(arr);
			exitFlag = true;
			break;
		case saveChoice::no:
			cout << "Файл не будет записан" << endl;
			exitFlag = true;
			break;


		default:
			cout << "Такого варианта нет, выберите существующий" << endl;
			exitFlag = false;
			break;

		}

	}


}


//Меню выбора заполнения массива
std::vector<double> arrayFillMethodMenu() {
	std::vector<double>temp;
	bool exitFlag = false;
	cout << "Укажите один из предстваленных способов заполнения массива: " << endl;
	cout << "1. Вручную" << endl
		<< "2. Случанйными числами" << endl
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
			cout << "Укажите имя файла с данными:" << endl
				 << "> ";
			temp = inputFromFile();
			exitFlag = true;
			break;

		default:
			cout << "Такого варианта нет, выберите существующий" << endl;
			exitFlag = false;
			break;
		}
	}
	return temp;
}