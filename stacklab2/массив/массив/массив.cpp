#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
using namespace std;
unsigned int startvvod, endvvod, startdelete, enddelete, start1, end1, startadd,endadd,enddel,startdel;
int MAX = 150;
struct power
{
	 string country;
	 string year;//год
	 string quantity;//количество
	 string category;//категория
};

//вывод
void vivod(power* a)
{
	for (int i = 0; i < 10; i++)
	{
		cout << i+1<<" " << a[i].country <<" "<< a[i].year << " " << a[i].quantity << " " << a[i].category << endl;
	}
}
//ввод
void vvod(power* a)
{
		setlocale(LC_ALL, "rus");
		ifstream fin("power.csv"); // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
		if (!fin.is_open()) // если файл не открыт
			cout << "Файл не может быть открыт!\n"; // сообщить об этом
		else {
			int i = 0;
			while(fin.good() && i < MAX)
			{				
				getline(fin, a[i].country, ',');
				if (a[i].country[0] == '\"')
				{
					string addition;
					getline(fin, addition, '\"');
					a[i].country.append(",");
					a[i].country.append(addition);
					a[i].country.erase(0, 1);
					getline(fin, addition, ',');
				}
				getline(fin, a[i].year, ',');
				getline(fin, a[i].quantity, ',');
				getline(fin, a[i].category, '\n');
				//cout << i<<endl;
				i++;
			}
		}
}
//удаление
void delete_(power* a, int count) {
	startdelete = clock();
	power* b = new power[count - 1];
		for (int i = 0; i < count - 1; i++) {
				b[i].country = a[i].country;
				b[i].year = a[i].year;
				b[i].quantity = a[i].quantity;
				b[i].category = a[i].category;
		}
		enddelete = clock();
			cout << "Удаление последнего элемента прошло успешно\nПоследние элементы массива" << endl;
			for (int i = count - 10; i < count - 1; i++) {
				cout << i+1 << "\t" << b[i].country << "\t" << b[i].year << "\t" 
					<< b[i].quantity << "\t" << b[i].category<<endl;
			}
			cout << "Удаленный элемент:\n"<< count<< "\t" 
				<<a[count-1].country
				<< "\t"<<a[count-1].year<< "\t" 
				<<a[count-1].quantity<< "\t" 
				<<a[count-1].category<<endl ;
			printf("\nВремя работы удаления данных:  %1.10f\n", (float)(enddelete - startdelete) / 1000);
}
//добавление
void add(power* a, int count) {
	power* c=new power[count+1];
	power x;
	cout << "Введите новую строку\n";
	cin >> x.country >> x.year>>x.quantity >>x.category ;
	startadd = clock();
	for (int i = 0; i < count; i++) {
		c[i].country = a[i].country;
		c[i].year = a[i].year;
		c[i].quantity = a[i].quantity;
		c[i].category = a[i].category;
	}
	c[count].country = x.country; c[count].year = x.year;
	c[count].quantity = x.quantity; c[count].category = x.category;
	endadd = clock();
	printf("\nВремя работы добавления данных:  %1.10f\n", (float)(endadd - startadd)/1000);
	cout << "Элемент успешно добавлен в конец массива\nПоследние элементы массива" << endl;
	for (int i = count - 9; i <= count; i++) {
			cout << i + 1 << "\t" << c[i].country << "\t" << c[i].year << "\t"
				<< c[i].quantity << "\t" << c[i].category << endl;
		
	}
}
int find_count(power* a) {
	int maxcount = 0;
	while (a[maxcount].country[0] != NULL)maxcount++;
	return maxcount;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	//max 1048576
	power* a = new power[MAX];
	startvvod = clock();
	vvod(a);
	endvvod = clock();
	printf("\nВВОД ДАННЫХ\nВремя работы ввода данных:  %1.10f\n", (float)(endvvod - startvvod)/1000);
	start1 = clock();
	int count = find_count(a);
	end1 = clock();
	cout <<"\nСКОЛЬКО ЭЛЕМЕНТОВ В МАССИВЕ?\nКоличество элементов в массиве:\t "<< count<<endl;
	printf("\nВремя работы функции нахождения размера массива:  %1.10f\n", (float)(end1 - start1) / 1000);
	cout << "\nМассив занимает " <<sizeof(a)<<" байт памяти" << endl;
	cout << endl;
	cout << "\nУДАЛЕНИЕ ПОСЛЕДНЕГО ЭЛЕМЕНТА МАССИВА\n";
	delete_(a,count);	
	cout << "\nДОБАВЛЕНИЕ ЭЛЕМЕНТА В КОНЕЦ МАССИВА\n";
	add(a,count);
	cout << endl;
	cout<<"\nВЫВОД ДЕСЯТОГО ЭЛЕМЕНТА С КОНЦА\n10 элемент с конца:\n"<<a[count - 10].country
		<< "\t" << a[count - 10].year << "\t"
		<< a[count - 10].quantity << "\t"
		<< a[count - 10].category << endl;
	startdel = clock();
	cout << "\nУДАЛЕНИЕ МАССИВА\n";
	delete[]a;
	enddel = clock();
	printf("\nВремя работы удаления массива:  %1.10f\n", (float)(enddel - startdel) / 1000);
	return(0);
}
