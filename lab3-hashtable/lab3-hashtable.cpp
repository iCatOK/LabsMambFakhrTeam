// lab3-hashtable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define A 79 /* a prime */
#define B 131 /* another prime */
#define C 23 /* yet another prime */
#define CHAR_PRIME 211
#define FIRSTH 37 /* also prime */

#include <iostream>
#include <fstream>
#include <locale.h>
#include <string>
#include <ctime>
#include <stdio.h>


unsigned MAXCOUNT = 800000;

using namespace std;


struct City {
	
	string country = "-";
	string year;
	string quantity;
	string category;
	//string key;
	City* next = NULL;

	City() {
	}

	City(string _country, string _year, string _quantity, string _category) {
		country = _country;
		year = _year;
		quantity = _quantity;
		category = _category;
		next = NULL;
	}

	City(City* city) {
		country = city->country;
		year = city->year;
		quantity = city->quantity;
		category = city->category;
		next = NULL;
	}

};

City* getCityFromFile(ifstream& file);
City* getElement(City* hashtable, string country, string year, string quantity, string category);
City* setElement(City* hashtable, City* entry, int* cols_count);
City* setElement(City* hashtable, string country, string year, string quantity, string category, int* cols_count);
City* popElement(City* hashtable, string country, string year, string quantity, string category);
unsigned getHash(string);
string getKey(string country, string year, string quantity, string category);
void enterData(City* hashtable, ifstream& file, int k);


int main()
{
	int start, end;
	setlocale(LC_ALL, "ru-RU");

	int cols_count = 0;
	
	ifstream file("power.csv");
	if (!file.is_open()) {
		cout << "opening error" << endl;
		return 0;
	}

	City* hashTable = new City[MAXCOUNT];


	//------------------------
	//1-ввод элементов с файла
	//------------------------

	cout << "1 - ВВОД ДАННЫХ\n";

	start = clock();
	enterData(hashTable, file, MAXCOUNT);
	end = clock();
	printf("Время работы ввода данных:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);

	//------------------
	//2-добавить элемент
	//------------------
	cout << "2 - ДОБАВЛЕНИЕ ЭЛЕМЕНТА\n";
	start = clock();
	setElement(hashTable, "Russia", "2020", "12434.2", "102", &cols_count);
	end = clock();
	printf("Время работы добавления элемента:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);

	//------------------
	//3-доступ к элементу
	//------------------
	cout << "3 - ДОСТУП К ЭЛЕМЕНТУ\n";
	start = clock();
	City* popped = getElement(hashTable, "Russia", "2020", "12434.2", "102");
	end = clock();
	printf("Время доступа к элементу:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);

	if (popped)
		printf("Элемент:  \"%s %s %s %s\"\n\n", popped->country.c_str(), popped->year.c_str(), popped->quantity.c_str(), popped->category.c_str());
	else
		printf("Элемент не найден\n");

	//------------------
	//4-удалить элемент
	//------------------
	cout << "4 - УДАЛЕНИЕ ЭЛЕМЕНТА\n";
	start = clock();
	popped = popElement(hashTable, "Russia", "2020", "12434.2", "102");
	end = clock();
	printf("Время работы удаления элемента:  %1.10f\n", (float)(end - start) / CLOCKS_PER_SEC);

	if(popped)
		printf("Элемент:  \"%s %s %s %s\"\n\n", popped->country.c_str(), popped->year.c_str(), popped->quantity.c_str(), popped->category.c_str());
	else
		printf("Элемент не найден\n");
	
		
	//-------
	//-------
	//-------

	////взять данные с файла
	//City* one = getCityFromFile(file);
	//City* two = getCityFromFile(file);
	////взять индекс
	//int index = getHash(one->getKey());

	////добавить в таблицу
	//one = setElement(hashTable, one);
	//two = setElement(hashTable, two);

	////взять из таблицы
	//City* getOne = getElement(hashTable, "country", "year", "quantity", "category");
	//City* getTwo = getElement(hashTable, two->country, two->year, two->quantity, two->category);

	////проверка на ошибки
	//if (!getTwo)
	//	cout << "err" << endl;
	//else
	//	cout << getTwo->country << " " << getTwo->year << " " << getTwo->quantity << " " << getTwo->category << " its getTwo " << endl;

	////удалить из таблицы
	//City* popOne = popElement(hashTable, "country", "year", "quantity", "category");

	////проверка на ошибки
	//if (!popOne)
	//	cout << "err" << endl;
	//else
	//	cout << popOne->country << " " << popOne->year << " its popOne " << endl;

	//cout << hashTable[index].country << " " << hashTable[index].year << " :: count = " << endl;
	//int hash = getHash(one->getKey());
	//cout << hash;

	file.close();
}

//unsigned getHash(string key)
//{
//	unsigned h = FIRSTH;
//	for (int i = 0; i < 4; i++) {
//		h += key[i] * (i + 2);
//		//cout << (int)key[i] << endl;
//	}
//	//printf("Hash is %d === %s\n", h % 599, key.c_str());
//	return h % MAXCOUNT; // or return h % C;
//}

unsigned getHash(string key)
{
	unsigned h = FIRSTH;
	unsigned MAXL = key.length();
	for (int i = 0; i < key.length(); i++) {
		h = ((h * A) + ((key[i] % CHAR_PRIME * B) / (MAXL - i + 1)))%193;
		//cout << (int)key[i] << endl;
	}
	//cout << "Hash is " << h << "===" << key << endl;
	return h%MAXCOUNT; // or return h % C;
}

string getKey(string country, string year, string quantity, string category) {
	string key;
	key.append(country);
	key.append(quantity);
	key.append(year);
	key.append(category);
	return key;
}

City* getCityFromFile(ifstream &file) {
	string country, year, quantity, category;
	getline(file, country, ',');
	if (country[0] == '\"') {
		string addition;
		getline(file, addition, '\"');
		country.append(",");
		country.append(addition);
		country.erase(0, 1);
		getline(file, addition, ',');
	}
	getline(file, year, ',');
	getline(file, quantity, ',');
	getline(file, category, '\n');
	City* newCity = new City(country, year, quantity, category);
	return newCity;
}

City* getElement(City* hashtable, string country, string year, string quantity, string category) {
	string key = getKey(country, year, quantity, category);
	int index = getHash(key);
	string entry_key = getKey(hashtable[index].country, 
		hashtable[index].year, 
		hashtable[index].quantity, 
		hashtable[index].category);

	

	if (!(hashtable[index].country == "-"))
		return NULL;

	if (key == entry_key)
		return &hashtable[index];
	else {
		City* current = hashtable[index].next;
		for (current, current == NULL;
			current = current->next;) {
			if (key == getKey(current->country, current->year, current->quantity, current->category))
				return current;
		}

		return NULL;
	}
}

City* setElement(City* hashtable, City* entry, int* cols_count) {
	int index = getHash(getKey(entry->country, entry->year, entry->quantity, entry->category));
	if (hashtable[index].country == "-") {
		hashtable[index] = entry;
		delete entry;
		return &hashtable[index];
	}
	else {
		//printf("Collision: %s - %s\n", entry->key.c_str(), hashtable[index].key.c_str());
		cols_count++;
		City* current = &hashtable[index];
		while (current->next != NULL)
			current = current->next;
		current->next = entry;
		return entry;
	}

}

City* setElement(City* hashtable, string country, string year, string quantity, string category, int* cols_count) {
	string key = getKey(country, year, quantity, category);

	int index = getHash(key);

	if (hashtable[index].country == "-") {
		hashtable[index] = City(country, year, quantity, category);
		return &hashtable[index];
	}
	else {
		//printf("Collision: %s - %s", key.c_str(), hashtable[index].key.c_str());
		cols_count++;
		City* current = hashtable[index].next;
		while (current->next != NULL)
			current = current->next;
		current->next = new City(country, year, quantity, category);
		return current;
	}
}

City* popElement(City* hashtable, string country, string year, string quantity, string category) {
	string key = getKey(country, year, quantity, category);
	int index = getHash(key);
	string entry_key = getKey(hashtable[index].country,
		hashtable[index].year,
		hashtable[index].quantity,
		hashtable[index].category);

	if (hashtable[index].country == "-")
		return NULL;

	if (key == entry_key) {
		City* popped = new City(&hashtable[index]);
		if (hashtable[index].next) {
			hashtable[index].country = hashtable[index].next->country;
			hashtable[index].year = hashtable[index].next->year;
			hashtable[index].quantity = hashtable[index].next->quantity;
			hashtable[index].category = hashtable[index].next->category;
			hashtable[index].next = hashtable[index].next->next;
		}
		else {
			hashtable[index].country = "-";
		}
		return popped;
	}
	else {
		City* current = &hashtable[index];
		for (current, current->next == NULL;current = current->next;) {
			string current_next_key = getKey(current->next->country, 
				current->next->year, 
				current->next->quantity, 
				current->next->category);
			if (key == current_next_key) {
				City* popped = current->next;
				current->next = current->next->next;
				return popped;
			}
		}

		return NULL;
	}
}

void enterData(City* hashtable, ifstream& file, int k) {

	int count = 0, cols_count = 0;
	cout << "Считывание информации о городах:\n";

	while (file.good() && count < k) {
		setElement(hashtable, getCityFromFile(file), &cols_count);
		count++;
	}
	//cout << "Collisions - " << cols_count << endl;

}