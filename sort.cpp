#include "sort.h"
#include "interface.h"
#include "main.h"

/*
     Слияние двух подмассивов вектора в порядке возрастания.
     array - Вектор, который нужно отсортировать.
     left - Начальный индекс первого подмассива.
     mid - Конечный индекс первого подмассива.
     right - Конечный индекс второго подмассива.
 */
void merge(std::vector<double>& array, int left, int mid, int right) {

    // Создание подмассивов
    std::vector<double> firstSubarray(mid - left + 1);
    std::vector<double> secondSubarray(right - mid);

    // Копирование элементов из основного массива в подмассивы
    for (int i = 0; i < firstSubarray.size(); i++) {
        firstSubarray[i] = array[left + i];
    }
    for (int j = 0; j < secondSubarray.size(); j++) {
        secondSubarray[j] = array[mid + 1 + j];
    }

    // Слияние подмассивов в основной массив
    int i = 0;  // Индекс первого подмассива
    int j = 0;  // Индекс второго подмассива
    int k = left;  // Индекс основного массива

    while (i < firstSubarray.size() && j < secondSubarray.size()) {
        if (firstSubarray[i] <= secondSubarray[j]) {
            array[k] = firstSubarray[i];
            i++;
        } else {
            array[k] = secondSubarray[j];
            j++;
        }
        k++;
    }

    // Если один из подмассивов закончился, копируем оставшиеся элементы в основной массив
    while (i < firstSubarray.size()) {
        array[k] = firstSubarray[i];
        i++;
        k++;
    }

    while (j < secondSubarray.size()) {
        array[k] = secondSubarray[j];
        j++;
        k++;
    }
}
/**
     Сортировка вектора с использованием сортировки слиянием.
     array - Вектор, который нужно отсортировать.
     left - Начальный индекс.
     right - Конечный индекс.
 */
void mergeSort(std::vector<double>& array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Рекурсивный вызов для первой половины массива
        mergeSort(array, left, mid);

        // Рекурсивный вызов для второй половины массива
        mergeSort(array, mid + 1, right);

        // Слияние двух подмассивов
        merge(array, left, mid, right);
    }
}