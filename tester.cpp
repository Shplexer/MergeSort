#include "tester.h"
#include "sort.h"
#include "main.h"
#include "interface.h"

//ѕроверка сортировки
void test() {
	//вектор контрол€ сортировки с фиксированными значени€ми
	const std::vector<double>controlVector{ -5, -2.9, 0.0, 9.5, 64.2, 100.1 };
	//вектор тестировани€ сортировки, который собран в обратном пор€дке
	std::vector<double>testVector = controlVector;
	std::reverse(testVector.begin(), testVector.end());
	//сортровка
	mergeSort(testVector, 0, static_cast<int>(testVector.size()) - 1);
	//сравнение отсортированного и контрольного массивов
	if (testVector == controlVector) {
		giveArrayToUser(testVector);
		cout << "\033[36m" << "¬ыполнено корректно!" << "\033[0m" << endl;
	}
	else {
		cout << "\033[31m" << "ѕроизошла ошибка!" << "\033[0m" << endl;
		cout << "ѕолученный массив" << endl;
		giveArrayToUser(testVector);
		cout << "»сходный массив" << endl;
		giveArrayToUser(controlVector);
	}
}