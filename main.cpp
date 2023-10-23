#include "main.h"
#include "interface.h"
#include "sort.h"
#include "tester.h"
// Эта функция является точкой входа в программу
int main() {
    // Добавляем возможность использования киррилицы в консоли
    setlocale(LC_CTYPE, "Russian");
    // Объявляем пустой вектор для хранения чисел с плавающей точкой
    std::vector<double> array;
    // Устанавливаем флаг выхода в значение false
    bool exitFlag = false;

    // Отображаем приветственное меню
    giveWelcomeMenu();
    while (!exitFlag) {
        // Получаем выбор пользователя из приветственного меню
        welcomeMenuChoice choice = static_cast<welcomeMenuChoice>(inputInt());

        // Выполняем действия в зависимости от выбора пользователя
        switch (choice) {
        case welcomeMenuChoice::start:
            //Заполняем значение вектора в зависимости от выбранного пользователем метода
            array = arrayFillMethodMenu();
            // Сортируем вектор с помощью функции mergeSort
            mergeSort(array, 0, static_cast<int>(array.size()) - 1);
            break;
        case welcomeMenuChoice::test:
            test();
            break;
        case welcomeMenuChoice::exit:
            // Завершаем программу
            std::exit(0);
            break;

            // Если пользователь выбирает недопустимую опцию
        default:
            // Выводим сообщение об ошибке
            cout << "Такого варианта нет, выберите существующий" << endl; //ПОМЕНЯТЬ
            exitFlag = false;
            break;
        }
    }
    return 0;
}