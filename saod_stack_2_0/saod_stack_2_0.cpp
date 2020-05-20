// saod_stack_2_0.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <locale.h>
#include <string>
#include <ctime>

using namespace std;

int MAXCOUNT = 100;

extern "C" {
	#include "stack.h"
}

struct City {
	string country;
	string year;
	string quantity;
	string category;
	
	City() {

	}

	City(string _country, string _year, string _quantity, string _category) {
		country = _country;
		year = _year;
		quantity = _quantity;
		category = _category;
	}

};

bool enterData(STACK* s, int count);
City* popData(STACK* s);
City* popData(STACK* s, STACK* b, int index);

int main()
{
	setlocale(LC_ALL, "ru-RU");
	
	STACK a = {0};
	a.CheckInit1 = 0;
	a.CheckInit2 = 0;

	STACK b = { 0 };
	b.CheckInit1 = 0;
	b.CheckInit2 = 0;

	//int b = 9;
	int c, start, end, k;
	City* popped;
	City* push = new City("Russia", "2020", "12434.2", "102");

	//-----------
	//0-сколько ввести
	//-----------
	cout << "Введите кол-во элементов: ";
	cin >> k;

	//-----------
	//1-enterData
	//-----------
	cout << "1 - ВВОД ДАННЫХ\n";
	
	start = clock();
	if (!enterData(&a, k)) return 0;
	end = clock();
	printf("Время работы ввода данных:  %1.10f\n\n", (float)(end - start) / CLOCKS_PER_SEC);

	//------------------
	//2-добавить элемент
	//------------------
	cout << "2 - ДОБАВЛЕНИЕ ЭЛЕМЕНТА\n";
	start = clock();
	StackPush(&a, 1, &push, sizeof(&push));
	end = clock();
	printf("Время работы добавления элемента:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);
	printf("Кол-во элементов:  %d\n\n", StackCount(&a));

	//------------------
	//3-удалить элемент
	//------------------
	cout << "3 - УДАЛЕНИЕ ЭЛЕМЕНТА\n";
	start = clock();
	popped = popData(&a);
	end = clock();
	printf("Время работы удаления элемента:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);
	printf("Кол-во элементов:  %d\n\n", StackCount(&a));

	//------------------
	//4-доступ к элементу
	//------------------
	cout << "4 - ДОСТУП К ЭЛЕМЕНТУ\n";
	start = clock();
	popped = popData(&a, &b, 10);
	end = clock();
	printf("Время доступа к элементу:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);
	printf("Кол-во элементов:  %d\n", StackCount(&a));
	printf("Элемент (индекс - 10):  \"%s %s %s %s\"\n\n", popped->country.c_str(), popped->year.c_str(), popped->quantity.c_str(), popped->category.c_str());

	//------------------
	//5-кол-во элементов
	//------------------
	cout << "5 - КОЛ-ВО ЭЛЕМЕНТОВ\n";
	start = clock();
	int counter = StackCount(&a);
	end = clock();
	printf("Время подсчёта кол-ва элементов:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);
	printf("Кол-во элементов:  %d\n\n", counter);

	//------------------
	//6-удалить все
	//------------------
	cout << "6 - УДАЛЕНИЕ ВСЕХ ДАННЫХ\n";
	start = clock();
	StackDestroy(&a);
	end = clock();
	printf("Время удаления всех данных:  %1.10f\n\n", (float)(end - start) / CLOCKS_PER_SEC);
	

	//exportDataToFile(&a, 100);

}

bool enterData(STACK* s, int count) {

	bool firstline = true;
	int k = 0;

	ifstream file("power.csv");
	if (!file.is_open()) {
		cout << "opening error" << endl;
		return 0;
	}

	cout << "Считывание информации о городах:\n\n";

	while (file.good() && StackCount(s) < count)
	{
		City current;
		getline(file, current.country, ',');
		if (current.country[0] == '\"') {
			string addition;
			getline(file, addition, '\"');
			current.country.append(",");
			current.country.append(addition);
			current.country.erase(0, 1);
			getline(file, addition, ',');
		}
		getline(file, current.year, ',');
		getline(file, current.quantity, ',');
		getline(file, current.category, '\n');
		if (firstline) {
			firstline = false;
			continue;
		}
		StackPush(s, 1, &current, sizeof(current));
		//cout << current.country << " " << current.year << " :: count = " << StackCount(s) << endl;
		/*if (k == 72) {
			City* check = popData(s);
			cout << check->country << endl;
		}*/

		k++;
	}
	file.close();
	return 1;
}
City* popData(STACK* s) {
	City* popped = new City;
	int res = StackPop(popped, s);
	if (res == 0) return popped;
	else return NULL;
}

City* popData(STACK* s, STACK *b, int index) {
	City* popped = new City();
	City pop;
	
	int counter = StackCount(s);

	if (index >= counter) {
		return NULL;
	}

	for (int i = 0; i < counter - index + 1; i++) {
		StackPop(popped, s);
		StackPush(b, 1, popped, sizeof(pop));
	}

	StackPop(popped, s);
	City* res = new City(popped->country, popped->year, popped->quantity, popped->category);
	StackPush(s, 1, popped, sizeof(pop));

	for (int i = 0; StackCount(b) > 0; i++) {
		StackPop(popped, b);
		StackPush(s, 1, popped, sizeof(pop));
	}

	return res;
}