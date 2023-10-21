// chto eto takoe AAAAAAAAAAAAAAAAAAAфффф
#include "Files.h"

vector<double>& inputFromFile(vector<double>& vec) {
	bool isCorrect = false;
	cout << "Имя файла дожно быть представлено в формате ***.txt" << endl
		 << "Данные в файле должны быть представлены в виде, например: '-5 34 7 18' " << endl;
	while (true) {
		string fileName = OpenFile();
		//size = CalculateSize(fileName);
		isCorrect = GetValueFromFile(vec, fileName);
		if (isCorrect) break;
		else {
			cout << "Данные в файле некорректны, выберите другой файл или измените содержание текущего и попробуйте снова" << endl;
		}
	}
}

string OpenFile() {
	bool isExit = false;
	bool isEmpty = false;
	fileNameChoice choice;
	string fileName;
	fstream fileStream;
	cout << "Укажите имя файла: ";
	getline(cin >> ws, fileName);
	do {
		isExit = false;
		isEmpty = false;
		fileName = FileNameCheck(fileName);
		fileStream.open(fileName);
		if (fileStream.is_open() && fileStream.peek() == EOF) {
			cout << "Файл пуст! Попробуйте снова." << endl;
			fileStream.close();
			isExit = false;
			isEmpty = true;
		}
		else if (!fileStream.is_open()) {
			cout << endl << "Файл с таким именем не существует! Измените имя файла:" << endl;	
			getline(cin >> ws, fileName);
			fileName = FileNameCheck(fileName);
		}
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
	bool exitFlag = false;
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
	bool isCorrect;
	fstream fileStream;
	fileStream.open(fileName);
	while (true) {
		fileStream >> tempDouble;
		if (fileStream.eof()) break;
		if (fileStream.fail())
		{
			cout << "Данные записаны некорректно." << endl;
			isCorrect = false;
			break;
		}
		vec.push_back(tempDouble);
	}

	return isCorrect;
}
/*
int CalculateSize(string fileName) {
	string line;
	bool isTrue = false, exitFlag = true;
	int size = 0;
	ifstream tempFile(fileName);

	if (tempFile.is_open()) {
		while (true) {
			getline(tempFile, line, ' ');
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '\n'|| tempFile.eof()) {
					isTrue = true;
					break;
				}
			}
			size++;
			if (isTrue) { break; }
		}
	}
	tempFile.close();
	return size;
}
*/