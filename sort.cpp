#include "sort.h"
#include "interface.h"
#include "main.h"

/*
     ������� ���� ����������� ������� � ������� �����������.
     array - ������, ������� ����� �������������.
     left - ��������� ������ ������� ����������.
     mid - �������� ������ ������� ����������.
     right - �������� ������ ������� ����������.
 */
void merge(std::vector<double>& array, int left, int mid, int right) {

    // �������� �����������
    std::vector<double> firstSubarray(mid - left + 1);
    std::vector<double> secondSubarray(right - mid);

    // ����������� ��������� �� ��������� ������� � ����������
    for (int i = 0; i < firstSubarray.size(); i++) {
        firstSubarray[i] = array[left + i];
    }
    for (int j = 0; j < secondSubarray.size(); j++) {
        secondSubarray[j] = array[mid + 1 + j];
    }

    // ������� ����������� � �������� ������
    int i = 0;  // ������ ������� ����������
    int j = 0;  // ������ ������� ����������
    int k = left;  // ������ ��������� �������

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

    // ���� ���� �� ����������� ����������, �������� ���������� �������� � �������� ������
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
     ���������� ������� � �������������� ���������� ��������.
     array - ������, ������� ����� �������������.
     left - ��������� ������.
     right - �������� ������.
 */
void mergeSort(std::vector<double>& array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // ����������� ����� ��� ������ �������� �������
        mergeSort(array, left, mid);

        // ����������� ����� ��� ������ �������� �������
        mergeSort(array, mid + 1, right);

        // ������� ���� �����������
        merge(array, left, mid, right);
    }
}