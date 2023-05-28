#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "sys/stat.h"

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

#define START_M_SIZE 4
#define EXP_M_SIZE 3
#define ALG_M_SIZE 3
#define SETT_M_SIZE 4
#define CrMass_M_SIZE 4
#define FoundAlg_M_SIZE 3
#define SortAlg_M_SIZE 5
#define Quant_Sort 4

struct INFO {
	int time;
	int permut;
	int comprasion;
};


void enter_path(char** input_filepath, char** output_filepath, FILE** input_file, FILE** output_file) {
	int ans = 0;
	int mass[100];
	errno_t error;

	printf("Текущий путь до файла ввода: %s\n", input_filepath);
	printf("Текущий путь до фвйла вывода: %s\n", output_filepath);
	system("pause");
	system("cls");
	printf("Желаете изменть путь до файла ввода? (да - 1, нет - 0): ");
	scanf_s("%d", &ans);
	if (ans) {
		printf("Введите новый путь до файла: ");
		getchar();
		gets(input_filepath);
		error = fopen_s(input_file, input_filepath, "r+");
		while (error != 0) {
			system("cls");
			printf("Неверно указан путь, введите еще раз: ");
			gets(input_filepath);
			error = fopen_s(input_file, input_filepath, "r+");
		}
		fclose(*input_file);
		printf("Путь изменнен\n");
		system("pause");
		system("cls");
	}
	printf("Желаете изменить путь до файла вывода? (да - 1, нет - 0): ");
	scanf_s("%d", &ans);
	if (ans) {
		printf("Введите новый путь до файла: ");
		getchar();
		gets(output_filepath);
		error = fopen_s(output_file, output_filepath, "r+");
		while (error != 0) {
			system("cls");
			printf("Неверно указан путь, введите еще раз: ");
			gets(output_filepath);
			error = fopen_s(output_file, output_filepath, "r+");
		}
		fclose(*output_file);
		printf("Путь изменнен\n");
		system("pause");
	}
}

void show(int* mass, int size, char** output_filepath, FILE** output_file) {
	if (size < 21) {
		for (int i = 0; i < size; i++) {
			printf("%d ", mass[i]);
		}
	}
	else {
		fopen_s(output_file, output_filepath, "w+");
		for (int i = 0; i < size; i++) {
			fprintf(*output_file,"%d ", mass[i]);
		}
		fprintf(*output_file, "\n");
		printf("Массив записан в файл вывода\n");
		fclose(*output_file);
	}
	printf("\n");
}

void generate(int** mass, int* size_mass, char** input_filepath, char** output_filepath, FILE** input_file, FILE** output_file,
	void (generate_exact)(int*, int)) {
	*size_mass = 0;
	system("cls");
	printf("Введите размер массива: ");
	scanf_s("%d", size_mass);
	while (*size_mass > 20 && (input_filepath[0] == '\0' && output_filepath[0] == '\0')) {
		int ans_1 = 0;
		printf("Чтобы ввести массив данного размера вам нужно ввести расположение файлов ввода и вывода\n");
		printf("Вы можете изменить размер массива или задать расположение файлов (0 - размер, 1 - расположение): ");
		scanf_s("%d", &ans_1);
		system("cls");
		if (ans_1) {
			enter_path(input_filepath, output_filepath, input_file, output_file);
			system("cls");
		}
		else {
			printf("Введите размер массива: ");
			scanf_s("%d", size_mass);
		}
	}
	while (*size_mass < 1) {
		system("cls");
		printf("Введите размер массива (он должен быть больше 1): ");
		scanf_s("%d", size_mass);
	}
	free(*mass);
	*mass = (int)malloc(sizeof(int) * *size_mass);
	generate_exact(*mass, *size_mass);
}

void generaterand(int* mass, int size) {
	int maximum = 1000;
	int minimum = -1000;
	printf("Введите промежуток значений: ");
	scanf_s("%d %d", &minimum, &maximum);
	for (int i = 0; i < size; i++) {
		mass[i] = minimum + rand() % (maximum - minimum + 1);
	}
}

void generaterand_testmode(int** mass, int j, int size, int minimum, int maximum) {
	for (int i = 0; i < size; i++) {
		mass[j][i] = rand() % (maximum - minimum + 1) - maximum;
	}
}

void generatehandle(int* mass, int size) {
	printf("Введите элементы массива: ");
	for (int i = 0; i < size; i++) {
		scanf_s("%d", &mass[i]);
	}
}

void read(int** mass, int* size_mass, char** input_filepath, char** output_filepath, FILE** input_file, FILE** output_file) {
	int x;
	system("cls");
	while (input_filepath[0] == '\0') {
		printf("Чтобы прочитать массив из файла, нужно уаказать путь до файла ввода\n");
		enter_path(input_filepath, output_filepath, input_file, output_file);
		system("cls");
	}
	fopen_s(input_file, input_filepath, "r+");
	if (fscanf_s(*input_file, "%d", size_mass) != 1) {
		printf("Ошибка в файле ввода\n");
		system("pause");
		return;
	}
	while (*size_mass > 20 && output_filepath[0] == '\0') {
		system("cls");
		printf("Чтобы проичтать массив данной длины нужно ввести путь до файла вывода\n");
		enter_path(input_filepath, output_filepath, input_file, output_file);
	}
	free(*mass);
	*mass = (int)malloc(sizeof(int) * *size_mass);
	for (int i = 0; i < *size_mass; i++) {
		if (fscanf_s(*input_file, "%d", &x) != 1) {
			
			printf("Ошибка в файле ввода\n");
			system("pause");
			return;
		}
		mass[0][i] = x;
	}
	fclose(*input_file);
	printf("Массив записан\n");
	system("pause");
}

void search(int** mass, int* size, void (search_exact)(int*, int, int)) {
	int element;
	if (*size < 1) {
		printf("Массив еще не был задан, вы можете задать его в разделе \"Настройки\"\n");
		system("pause");
		return;
	}
	printf("Введите искомый элемент: ");
	scanf_s("%d", &element);
	search_exact(*mass, *size, element);
}

void naive_search(int* mass, int size, int element) {
	for (int i = 0; i < size; i++) {
		if (mass[i] == element) {
			printf("Искомый элемент находится на %d позиции\n", i + 1);
			system("pause");
			return;
		}
	}
	printf("Указанного элемента нет в данном масиве\n");
	system("pause");
}

void binar_search(int* mass, int size, int element) {
	int flag = 0;
	int k = size / 2;
	int left = 0;
	int right = size - 1;
	for (int i = 0; i < size - 1; i++) {
		if (mass[i] > mass[i + 1]) {
			printf("Массив не отсортирован, вы можете отсортировать его в разделе \"Сортировки\"\n");
			system("pause");
			return;
		}
	}
	if (element > mass[size - 1] || element < mass[0]) {
		printf("Указанного элемента нет в данном масиве\n");
		system("pause");
		return;
	}
	while (!flag) {
		if (mass[k] == element) {
			flag = 1;
			printf("Искомый элемент находится на %d позиции\n", k + 1);
			system("pause");
		}
		else if (mass[k] < element && mass[k + 1] > element) {
			flag = 1;
			printf("Указанного элемента нет в данном масиве\n");
			system("pause");
		}
		else if (mass[k] > element) {
			right = k;
			k = left + (right - left) / 2;
		}
		else {
			left = k;
			k = right - (right - left) / 2;
		}
	}
}

void swap(int* a, int* b) {
	int c = *a;
	*a = *b;
	*b = c;
}

void bubble_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant) {
	int size = last + 1;
	int b;
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			*comprasion_quant += 1;
			if (mass[i] > mass[j]) {
				swap(&mass[i], &mass[j]);
				*permut_quant += 1;
			}
		}
	}
}

void hoar_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant) {
	int i = first;
	int j = last;
	int supp_el = mass[(i + j) / 2];
	while (i <= j) {
		while (mass[i] < supp_el) i++;
		while (mass[j] > supp_el) j--;
		if(i <= j){
			*comprasion_quant += 1;
			if (mass[i] > mass[j]) {
				swap(&mass[i], &mass[j]);
				*permut_quant += 1;
			}
			i++;
			j--;
		}
	}
	if (i < last) {
		hoar_sort(mass, i, last, permut_quant, comprasion_quant);
	}
	if (j > first) {
		hoar_sort(mass, first, j, permut_quant, comprasion_quant);
	}
}

void shella_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant) {
	int size = last + 1;
	for (int step = size / 2; step > 0; step /= 2) {
		for (int i = step; i < size; i++) {
			for (int j = i - step; j >= 0 && mass[j] > mass[j + step]; j -= step) {
				swap(&mass[j], &mass[j + step]);
				*permut_quant += 1;
				*comprasion_quant += 1;
			}
			*comprasion_quant += 1;
		}
	}
}

void insert_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant) {
	int size = last + 1;
	int select_el = 0;
	for (int i = 0; i < size; i++) {
		select_el = mass[i];
		for (int j = i - 1; j >= 0; j--) {
			*comprasion_quant += 1;
			if (mass[j] >= select_el) {
				mass[j + 1] = mass[j];
				mass[j] = select_el;;
				*permut_quant += 1;
			}
			else { break; }
		}
	}
}

void copy(int* mass1, int* mass2, int size_mass) {
	for (int i = 0; i < size_mass; i++) {
		mass2[i] = mass1[i];
	}
}

void sort(int** mass, int first, int last, int* permut_quant, int* comprasion_quant, char** output_filepath, FILE** output_file,
	void sort_exact(int*, int, int, int*, int*)) {
	*permut_quant = 0;
	*comprasion_quant = 0;
	system("cls");
	if (last < 0) {
		printf("Массив не задан\n");
		system("pause");
		return;
	}
	if (last < 20) {
		printf("Данный массив: ");
		show(*mass, last + 1, output_filepath, output_file);
	}
	sort_exact(*mass, 0, last, permut_quant, comprasion_quant);
	if (last < 20) {
		printf("Отсортированный массив: ");
		show(*mass, last + 1, output_filepath, output_file);
		printf("\n");
	}
	else {
		show(*mass, last + 1, output_filepath, output_file);
	}
	
	printf("Количество перестановок - %d\nКоличество сравнений - %d\n", *permut_quant, *comprasion_quant);
	system("pause");
 }

void create_info(struct INFO* info, int number, int* mass, int size_mass, void sort_exact(int*, int, int, int*, int*)) {
	int* mass_test = (int)malloc(sizeof(int) * size_mass);
	info[number].permut = 0;
	info[number].comprasion = 0;
	copy(mass, mass_test, size_mass);
	info[number].time = clock();
	sort_exact(mass_test, 0, size_mass - 1, &info[number].permut, &info[number].comprasion);
	info[number].time = clock() - info[number].time;
}

void efficiency_table(int** mass, int first, int last) {
	int min_per = (last + 10) * (last + 10);
	int min_compr = (last + 10) * (last + 10);
	int min_time = INT_MAX;
	struct INFO info[Quant_Sort];
	char efficiency_table_name[8][25] = { {"Сортировка\0"} , {"Время работы\0"}, {"Замедление\0"}, {"Перестановки\0"}, {"Увелич. перестанов.\0"},
	{"Сравнения\0"}, {"Увелич. сравнений\0"} };
	char sort_name[Quant_Sort][20] = { {"Пузырьковая "}, {"Хоара (быстрая) "}, {"Шелла "}, {"Вставками "} };
	
	system("cls");
	for (int i = 0; i < 8; i++) {
		printf("|%-19s ", efficiency_table_name[i]);
	}
	printf("\n");
	create_info(info, 0, *mass, last + 1, bubble_sort);
	create_info(info, 1, *mass, last + 1, hoar_sort);
	create_info(info, 2, *mass, last + 1, shella_sort);
	create_info(info, 3, *mass, last + 1, insert_sort);
	for (int i = 0; i < Quant_Sort; i++) {
		if (info[i].permut < min_per) {
			min_per = info[i].permut;
		}
		if (info[i].comprasion < min_compr) {
			min_compr = info[i].comprasion;
		}
		if (info[i].time < min_time) {
			min_time = info[i].time;
		}
	}
	for (int i = 0; i < Quant_Sort; i++) {
		printf("|%-19s ", sort_name[i]);
		printf("|%-19d ", info[i].time);
		printf("|%-19.3f ", (float)info[i].time / min_time);
		printf("|%-19d ", info[i].permut);
		printf("|%-19.3f ", (float)info[i].permut / min_per);
		printf("|%-19d ", info[i].comprasion);
		printf("|%-19.3f \n", (float)info[i].comprasion / min_compr);
	}
	system("pause");
}

void efficienty_test() {
	int quant_test = 0;
	int ans = 0;
	int quant_el;
	int mini, maxi;
	int time_min;
	void (*sort)(int*, int, int, int*, int*) = bubble_sort;
	int x, y;

	system("cls");
	while (ans < 1 || ans > 4) {
		system("cls");
		printf("Выберете сортировку(1 - Пузырьковая, 2 - Хоара, 3 - Шелла, 4 - вставками): ");
		scanf_s("%d", &ans);
	}
	if (ans == 1) { sort = bubble_sort; }
	if (ans == 2) { sort = hoar_sort; }
	if (ans == 3) { sort = shella_sort; }
	if (ans == 4) { sort = insert_sort; }
	while (quant_test < 1) {
		system("cls");
		printf("Введите количество тестов: ");
		scanf_s("%d", &quant_test);
	}
	int** massofmass = (int*)malloc(sizeof(int*) * quant_test);
	int* massofsize = (int)malloc(sizeof(int) * quant_test);
	printf("Введите промежуток значений: ");
	scanf_s("%d %d", &mini, &maxi);
	printf("Введите размеры массивов: ");
	for (int i = 0; i < quant_test; i++) {
		scanf_s("%d", &quant_el);
		massofmass[i] = (int)malloc(sizeof(int) * quant_el);
		massofsize[i] = quant_el;
		generaterand_testmode(massofmass, i, quant_el, mini, maxi);
	}
	time_min = clock();
	sort(massofmass[0], 0, massofsize[0] - 1, &x, &y);
	time_min = clock() - time_min;
	system("cls");
	printf("%-15s |%-15s | %-15s\n", "Размер массива\0", "Время работы\0", "Замедление\0");
	for (int i = 0; i < quant_test; i++) {
		int time = clock();
		sort(massofmass[i], 0, massofsize[i] - 1, &x, &y);
		time = clock() - time;
		printf("%-15d |%-15d |%-15.3f\n", massofsize[i], time, (float)time / time_min);
	}
	system("pause");
}

void constract_Experement_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file) {
	int iKey;
	char menu_names[EXP_M_SIZE][21] = { "Сравнение сортировок", "Эффективность", "Назад" };
	int choose_pos;
	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	choose_pos = 0;

	system("cls");
	iKey = 67;
	cursorPos = (COORD){ 0, 0 };
	SetConsoleCursorPosition(hStdOut, cursorPos);

	while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
		switch (iKey) {
		case KEY_ARROW_UP:
			(choose_pos)--;
			break;
		case KEY_ARROW_DOWN:
			(choose_pos)++;
			break;
		}
		system("cls");

		if (choose_pos < 0) { choose_pos = EXP_M_SIZE - 1; }
		if (choose_pos > EXP_M_SIZE - 1) { choose_pos = 0; }
		for (int i = 0; i < EXP_M_SIZE; i++) {
			cursorPos = (COORD){ 3, i };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("%s \n", menu_names[i]);
		}

		cursorPos = (COORD){ 0, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf("<<");
		cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf(">>");

		iKey = _getch();
	}

	switch (choose_pos) {
	case 0:
		efficiency_table(mass, 0, *size_mass - 1);
		break;
	case 1:
		efficienty_test();
		break;
	case 2:
		*return_flag = 1;
		break;
	}
}

void constract_Sort_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file) {
	int iKey;
	char menu_names[SortAlg_M_SIZE][25] = { "Пузырьковая сортировка", "Сортировка Хоара", "Сортировка Шелла", "Сортирвка вставками",  "Назад" };
	int choose_pos;
	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	choose_pos = 0;

	int permut_quant = 0;
	int comprasion_quant = 0;

	system("cls");
	iKey = 67;
	cursorPos = (COORD){ 0, 0 };
	SetConsoleCursorPosition(hStdOut, cursorPos);

	while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
		switch (iKey) {
		case KEY_ARROW_UP:
			(choose_pos)--;
			break;
		case KEY_ARROW_DOWN:
			(choose_pos)++;
			break;
		}
		system("cls");

		if (choose_pos < 0) { choose_pos = SortAlg_M_SIZE - 1; }
		if (choose_pos > SortAlg_M_SIZE - 1) { choose_pos = 0; }
		for (int i = 0; i < SortAlg_M_SIZE; i++) {
			cursorPos = (COORD){ 3, i };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("%s \n", menu_names[i]);
		}

		cursorPos = (COORD){ 0, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf("<<");
		cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf(">>");

		iKey = _getch();
	}

	switch (choose_pos) {
	case 0:
		sort(mass, 0, *size_mass - 1, &permut_quant, &comprasion_quant, output_filepath, output_file, bubble_sort);
		break;
	case 1:
		sort(mass, 0, *size_mass - 1, &permut_quant, &comprasion_quant, output_filepath, output_file, hoar_sort);
		break;
	case 2:
		sort(mass, 0, *size_mass - 1, &permut_quant, &comprasion_quant, output_filepath, output_file, shella_sort);
		break;
	case 3:
		sort(mass, 0, *size_mass - 1, &permut_quant, &comprasion_quant, output_filepath, output_file, insert_sort);
		break;
	case 4:
		*return_flag = 1;
		break;
	}
}

void constract_Found_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file) {
	int iKey;
	char menu_names[FoundAlg_M_SIZE][20] = { "Наивный поиск", "Бинарный поиск", "Назад" };
	int choose_pos;
	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	choose_pos = 0;

	system("cls");
	iKey = 67;
	cursorPos = (COORD){ 0, 0 };
	SetConsoleCursorPosition(hStdOut, cursorPos);

	while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
		switch (iKey) {
		case KEY_ARROW_UP:
			(choose_pos)--;
			break;
		case KEY_ARROW_DOWN:
			(choose_pos)++;
			break;
		}
		system("cls");

		if (choose_pos < 0) { choose_pos = FoundAlg_M_SIZE - 1; }
		if (choose_pos > FoundAlg_M_SIZE - 1) { choose_pos = 0; }
		for (int i = 0; i < FoundAlg_M_SIZE; i++) {
			cursorPos = (COORD){ 3, i };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("%s \n", menu_names[i]);
		}

		cursorPos = (COORD){ 0, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf("<<");
		cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf(">>");

		iKey = _getch();
	}

	switch (choose_pos) {
	case 0:
		system("cls");
		search(mass, size_mass, naive_search);
		break;
	case 1:
		system("cls");
		search(mass, size_mass, binar_search);
		break;
	case 2:
		*return_flag = 1;
		break;
	}
}

void constract_Alg_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file) {
	int iKey;
	char menu_names[ALG_M_SIZE][20] = { "Сортировка", "Поиск", "Назад" };
	int choose_pos;
	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	choose_pos = 0;

	system("cls");
	iKey = 67;
	cursorPos = (COORD){ 0, 0 };
	SetConsoleCursorPosition(hStdOut, cursorPos);

	while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
		switch (iKey) {
		case KEY_ARROW_UP:
			(choose_pos)--;
			break;
		case KEY_ARROW_DOWN:
			(choose_pos)++;
			break;
		}
		system("cls");

		if (choose_pos < 0) { choose_pos = ALG_M_SIZE - 1; }
		if (choose_pos > ALG_M_SIZE - 1) { choose_pos = 0; }
		for (int i = 0; i < ALG_M_SIZE; i++) {
			cursorPos = (COORD){ 3, i };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("%s \n", menu_names[i]);
		}

		cursorPos = (COORD){ 0, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf("<<");
		cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf(">>");

		iKey = _getch();
	}

	switch (choose_pos) {
	case 0:
		while (!*return_flag) {
			constract_Sort_Menu(return_flag, mass, size_mass, input_filepath, output_filepath, input_file, output_file);
		}
		*return_flag = 0;
		break;
	case 1:
		while (!*return_flag) {
			constract_Found_Menu(return_flag, mass, size_mass, input_filepath, output_filepath, input_file, output_file);
		}
		*return_flag = 0;
		break;
	case 2:
		*return_flag = 1;
		break;
	}
}

void constract_CreateMass_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file) {
	int iKey;
	char menu_names[CrMass_M_SIZE][25] = { "Ручная генерация", "Случайная генерация", "Чтение из файла", "Назад" };
	int choose_pos;
	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	choose_pos = 0;

	system("cls");
	iKey = 67;
	cursorPos = (COORD){ 0, 0 };
	SetConsoleCursorPosition(hStdOut, cursorPos);

	while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
		switch (iKey) {
		case KEY_ARROW_UP:
			(choose_pos)--;
			break;
		case KEY_ARROW_DOWN:
			(choose_pos)++;
			break;
		}
		system("cls");

		if (choose_pos < 0) { choose_pos = CrMass_M_SIZE - 1; }
		if (choose_pos > CrMass_M_SIZE - 1) { choose_pos = 0; }
		for (int i = 0; i < CrMass_M_SIZE; i++) {
			cursorPos = (COORD){ 3, i };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("%s \n", menu_names[i]);
		}

		cursorPos = (COORD){ 0, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf("<<");
		cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf(">>");

		iKey = _getch();
	}

	switch (choose_pos) {
	case 0:
		generate(mass, size_mass, input_filepath, output_filepath, input_file, output_file, generatehandle);
		printf("\nМассив задан\n");
		system("pause");
		break;
	case 1:
		generate(mass, size_mass, input_filepath, output_filepath, input_file, output_file, generaterand);
		system("cls");
		printf("Массив сгенерирован\n");
		system("pause");
		break;
	case 2:
		read(mass, size_mass, input_filepath, output_filepath, input_file, output_file);
		system("cls");
		break;
	case 3:
		*return_flag = 1;
		break;
	}
}

void constract_Setting_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file) {
	int iKey;
	char menu_names[SETT_M_SIZE][25] = { "Задать массив", "Показать текущий массив", "Изменить путь до файлов", "Назад" };
	int choose_pos;
	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	choose_pos = 0;

	system("cls");
	iKey = 67;
	cursorPos = (COORD){ 0, 0 };
	SetConsoleCursorPosition(hStdOut, cursorPos);

	while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
		switch (iKey) {
		case KEY_ARROW_UP:
			(choose_pos)--;
			break;
		case KEY_ARROW_DOWN:
			(choose_pos)++;
			break;
		}
		system("cls");

		if (choose_pos < 0) { choose_pos = SETT_M_SIZE - 1; }
		if (choose_pos > SETT_M_SIZE - 1) { choose_pos = 0; }
		for (int i = 0; i < SETT_M_SIZE; i++) {
			cursorPos = (COORD){ 3, i };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("%s \n", menu_names[i]);
		}

		cursorPos = (COORD){ 0, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf("<<");
		cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
		SetConsoleCursorPosition(hStdOut, cursorPos);
		printf(">>");

		iKey = _getch();
	}

	switch (choose_pos) {
	case 0:
		while (!*return_flag) {
			constract_CreateMass_Menu(return_flag, mass, size_mass, input_filepath, output_filepath, input_file, output_file);
		}
		*return_flag = 0;
		break;
	case 1:
		system("cls");
		if (*size_mass < 1) {
			printf("Сначала необходимо задать массив\n");
		}
		else {
			show(*mass, *size_mass, output_filepath, output_file);
		}
		system("pause");
		break;
	case 2:
		system("cls");
		enter_path(input_filepath, output_filepath, input_file, output_file);
		system("pause");
		break;
	case 3:
		*return_flag = 1;
		break;
	}
}

void constract_Start_Menu() {
	int iKey;
	int exit_flag = 0;
	int return_flag = 0;
	char menu_names[START_M_SIZE][20] = { "Режим эксперимента", "Алгоритмы", "Настройки", "Выход" };
	int choose_pos;

	char input_filepath[200] = { "\0" };
	char output_filepath[200] = { "\0" };
	FILE* input_file = NULL;
	FILE* output_file = NULL;
	int* mass = (int)malloc(sizeof(int) * 1);
	int size_mass = 0;

	COORD cursorPos;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while (!exit_flag) {
		choose_pos = 0;

		system("cls");
		iKey = 67;
		return_flag = 0;
		cursorPos = (COORD){ 0, 0 };
		SetConsoleCursorPosition(hStdOut, cursorPos);

		while (iKey != KEY_EXIT && iKey != KEY_ENTER) {
			switch (iKey) {
			case KEY_ARROW_UP:
				(choose_pos)--;
				break;
			case KEY_ARROW_DOWN:
				(choose_pos)++;
				break;
			}
			system("cls");

			if (choose_pos < 0) { choose_pos = START_M_SIZE - 1; }
			if (choose_pos > START_M_SIZE - 1) { choose_pos = 0; }
			for (int i = 0; i < START_M_SIZE; i++) {
				cursorPos = (COORD){ 3, i };
				SetConsoleCursorPosition(hStdOut, cursorPos);
				printf("%s \n", menu_names[i]);
			}

			cursorPos = (COORD){ 0, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf("<<");
			cursorPos = (COORD){ strlen(menu_names[choose_pos]) + 3 + 1, choose_pos };
			SetConsoleCursorPosition(hStdOut, cursorPos);
			printf(">>");

			iKey = _getch();
		}

		switch (choose_pos) {
		case 0: 
			if (size_mass == 0) {
				system("cls");
				printf("Чтобы перейти в режим эксперимента, задайте массив в настройках\n");
				system("pause");
			}
			else {
				while (!return_flag) {
					constract_Experement_Menu(&return_flag, &mass, &size_mass, &input_filepath, &output_filepath, &input_file, &output_file);
				}
			}
			break;
		case 1:
			while (!return_flag) {
				constract_Alg_Menu(&return_flag, &mass, &size_mass, &input_filepath, &output_filepath, &input_file, &output_file);
			}
			break;
		case 2:
			while (!return_flag) {
				constract_Setting_Menu(&return_flag, &mass, &size_mass, &input_filepath, &output_filepath, &input_file, &output_file);
			}
			break;
		case 3:
			exit_flag = 1;
			break;
		}
	}
	system("cls");
	printf("Спасибо за работу!\n");
	system("pause");
}



int main() {

	srand(time(0));
	setlocale(LC_ALL, "rus");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);

	constract_Start_Menu();
}