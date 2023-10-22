#include "Files.h"
#include "interface.h"

using namespace std;
using namespace filesystem;

void inputFromFile(vector<double>& vec) {
	bool isCorrect = false;
	string fileName;
	cout << "Имя файла дожно быть представлено в формате ***.txt" << endl
		 << "Данные в файле должны быть представлены в виде, например: '-5 34 7 18' " << endl;

	// Зацикленная попытка получения данных из файла для исключения возможных ошибок
	while (true) {
		fileName = OpenFile();
		//size = CalculateSize(fileName);
		isCorrect = GetValueFromFile(vec, fileName);
		if (isCorrect) break;
		else {
			cout << "Данные в файле некорректны, выберите другой файл или измените содержание текущего и попробуйте снова" << endl;
		}
	}
	cout << "Данные получены и записаны в массив!" << endl;
}

void outputToFile(vector<double>& vec) {
	bool isCorrect = false;
	string fileName;
	fstream fileStream;
	cout << "Имя файла дожно быть представлено в формате ***.txt" << endl;
	fileName = OpenFile();
	fileStream.open(fileName);
	for (int i = 0; i < vec.size(); i++) {
		fileStream << vec[i] << " ";
	}
	cout << "Данные записаны!" << endl;
}

string OpenFile() {
	bool isExit = false;
	bool isEmpty = false;
	string fileName;
	fstream fileStream;

	cout << "Укажите имя файла: ";
	getline(cin >> ws, fileName);
	// Цикл до ввода подходящего файла
	do {
		isExit = false;
		isEmpty = false;
		fileName = FileNameCheck(fileName);
		fileStream.open(fileName);
		// Проверка на наличие данных в файле
		if (fileStream.is_open() && fileStream.peek() == EOF) {
			cout << "Файл пуст! Попробуйте снова." << endl;
			fileStream.close();
			isExit = false;
			isEmpty = true;
		}
		//Проверха файла на существование
		else if (!fileStream.is_open()) {
			cout << endl << "Файл с таким именем не существует! Измените имя файла:" << endl;	
			getline(cin >> ws, fileName);
			fileName = FileNameCheck(fileName);
		}
		//Корректное открытие файла
		else if (fileStream.is_open() && !isEmpty) {
			cout << "Файл открыт!" << endl;
			isExit = true;
		}
	} while (!isExit);
	fileStream.close();
	return fileName;
}

string FileNameCheck(string inputName) {
	error_code ec{};
	bool exitFlag;

	//Цикл до получения корректного имени файла
	do {
		exitFlag = true;
		if (!ifstream(inputName)) continue;
		if (!is_regular_file(inputName, ec)) {
			cout << "Ошибка! Проверьте название файла и попробуйте снова:" << endl;
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
	// Цикл по получению данных из файла и их записи в вектор
	while (true) {
		fileStream >> tempDouble;
		// Если конец файла
		if (fileStream.eof()) {
			vec.push_back(tempDouble);
			break;
		};
		// Если не получлось взять данные
		if (fileStream.fail())
		{
			cout << "Данные записаны некорректно." << endl;
			isCorrect = false;
			break;
		}
		vec.push_back(tempDouble);
	}
	fileStream.close();
	return isCorrect;
}
