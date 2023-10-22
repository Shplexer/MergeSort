#include "tester.h"
#include "sort.h"
#include "main.h"

//Проверка сортировки
void test() {
	//вектор контроля сортировки с фиксированными значениями
	const std::vector<double>controlVector{ -5, -2.9, 0.0, 9.5, 64.2, 100.1 };
	//вектор тестирования сортировки, который собран в обратном порядке
	std::vector<double>testVector = controlVector;
	std::reverse(testVector.begin(), testVector.end());
	//сортровка
	mergeSort(testVector, 0, static_cast<int>(testVector.size()) - 1);
	//сравнение отсортированного и контрольного массивов
	if (testVector == controlVector) {
		cout << "\033[36m" << "GOOD" << "\033[0m" << endl;
	}
	else {
		cout << "\033[31m" << "BAD" << "\033[0m" << endl;
		cout << "INPUT ARRAY" << endl;
		//вывести testVector
		cout << "CONTROL ARRAY" << endl;
		//вывести controlVector
	}
}