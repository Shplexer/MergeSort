#include "tester.h"
#include "sort.h"
#include "main.h"

//�������� ����������
void test() {
	//������ �������� ���������� � �������������� ����������
	const std::vector<double>controlVector{ -5, -2.9, 0.0, 9.5, 64.2, 100.1 };
	//������ ������������ ����������, ������� ������ � �������� �������
	std::vector<double>testVector = controlVector;
	std::reverse(testVector.begin(), testVector.end());
	//���������
	mergeSort(testVector, 0, static_cast<int>(testVector.size()) - 1);
	//��������� ���������������� � ������������ ��������
	if (testVector == controlVector) {
		cout << "\033[36m" << "GOOD" << "\033[0m" << endl;
	}
	else {
		cout << "\033[31m" << "BAD" << "\033[0m" << endl;
		cout << "INPUT ARRAY" << endl;
		//������� testVector
		cout << "CONTROL ARRAY" << endl;
		//������� controlVector
	}
}