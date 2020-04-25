#include <iostream>
#include <random>
#include <ctime>

const long int RUN = 32;
using namespace std;
void QuickSort(long int A[], long int from, long int to)
{
    long int x, i, j, temp;
    if (from >= to) return; // условие окончания рекурсии
    i = from; // рассматриваем элементы с A[from] до A[to]
    j = to;
    x = A[(from + to) / 2]; // выбрали средний элемент
    while (i <= j) {
        while (A[i] < x) i++; // ищем пару для перестановки
        while (A[j] > x) j--;
        if (i <= j) {
            temp = A[i]; A[i] = A[j]; A[j] = temp; // перестановка
            i++; // двигаемся дальше
            j--;
        }
    }
    QuickSort(A, from, j); // сортируем левую часть
    QuickSort(A, i, to); // сортируем правую часть
}
void GnomSort(long int arr[], long int n) {
    long int i = 1; // счётчик

    while (i < n/*если мы не в конце*/) {
        if (i == 0) {
            i = 1;
        }
        if (arr[i - 1] <= arr[i]) {
            ++i; // идём вперед
        }
        else {
            // меняем местами
            long tmp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = tmp;
            // идём назад
            --i;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    long int n;
    long int choice;
    do {
        cout << "\nВыберите сортировку\n1 - гномья\n2 - быстрая\n \n0 - Выход из программы\n";
        cin >> choice;
        if (choice != 0) {
            cout << "Количество элементов в массиве: ";
            cin >> n;
            long int* mass = new long int[n - 1];
            for (long int i = 0; i < n; i++) {
                mass[i] = rand() % 100 + 1;
            }
            cout << "Последние 10 элементов массива\n";
            for (long int i = n - 10; i < n; i++) {
                cout << mass[i] << "\t";
            }
            double start = 0, end = 0;
            switch (choice) {
            case 1: start = clock(); GnomSort(mass, n); end = clock(); break;
            case 2:start = clock(); QuickSort(mass, 0, n); end = clock(); break;
            default: return 0;
            }
            printf("\n\nВремя работы сортировки:  %1.10f", (float)(end - start) / CLOCKS_PER_SEC);

            cout << "\nОтсортированный массив (первые 10 элементов)\n";
            for (long int i = 0; i < 10; i++) {
                cout << mass[i] << "\t";
            }
            cout << "\nОтсортированный массив (последние 10 элементов)\n";
            for (long int i = n - 10; i < n; i++) {
                cout << mass[i] << "\t";
            }
        }
        } while (choice > 0);
    
    return 0;
}