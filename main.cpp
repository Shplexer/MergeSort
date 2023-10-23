#include "main.h"
#include "interface.h"
#include "sort.h"
#include "tester.h"

// ��� ������� �������� ������ ����� � ���������
int main() {

    // ��������� ����������� ������������� ��������� � �������
    setlocale(LC_ALL, "Russian");
    // ��������� ������ ������ ��� �������� ����� � ��������� ������
    std::vector<double> array;
    // ������������� ���� ������ � �������� false
    bool exitFlag = false;

    // ���������� �������������� ����
    giveWelcomeMenu();
    while (!exitFlag) {
        // �������� ����� ������������ �� ��������������� ����
        welcomeMenuChoice choice = static_cast<welcomeMenuChoice>(inputInt());

        // ��������� �������� � ����������� �� ������ ������������
        switch (choice) {
        case welcomeMenuChoice::start:
            //��������� �������� ������� � ����������� �� ���������� ������������� ������
            array = arrayFillMethodMenu();
            // ��������� ������ � ������� ������� mergeSort
            mergeSort(array, 0, static_cast<int>(array.size()) - 1);
            giveArrayToUser(array);
            saveToFile(array);
            exitFlag = true;
            break;
        case welcomeMenuChoice::test:
            test();
            exitFlag = true;
            break;
        case welcomeMenuChoice::exit:
            // ��������� ���������
            std::exit(0);
            break;

            // ���� ������������ �������� ������������ �����
        default:
            // ������� ��������� �� ������
            cout << "������ �������� ���, �������� ������������" << endl; //��������
            exitFlag = false;
            break;
        }
    }
    return 0;
}