#include "tester.h"
#include "sort.h"
#include "main.h"
#include "interface.h"

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
		giveArrayToUser(testVector);
		cout << "\033[36m" << "��������� ���������!" << "\033[0m" << endl;
	}
	else {
		cout << "\033[31m" << "��������� ������!" << "\033[0m" << endl;
		cout << "���������� ������" << endl;
		giveArrayToUser(testVector);
		cout << "�������� ������" << endl;
		giveArrayToUser(controlVector);
	}
}