#pragma once
#include <windows.h>
#include <conio.h>
#include "sys/stat.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void enter_path(char** input_filepath, char** output_filepath, FILE** input_file, FILE** output_file);
void show(int* mass, int size, char** output_filepath, FILE** output_file);
void generate(int** mass, int* size_mass, char** input_filepath, char** output_filepath, FILE** input_file, FILE** output_file,
	void (generate_exact)(int*, int));
void generaterand(int* mass, int size);
void generaterand_testmode(int** mass, int j, int size, int minimum, int maximum);
void generatehandle(int* mass, int size);
void read(int** mass, int* size_mass, char** input_filepath, char** output_filepath, FILE** input_file, FILE** output_file);
void search(int** mass, int* size, void (search_exact)(int*, int, int));
void naive_search(int* mass, int size, int element);
void binar_search(int* mass, int size, int element);
void swap(int* a, int* b);
void bubble_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant);
void hoar_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant);
void shella_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant);
void insert_sort(int* mass, int first, int last, int* permut_quant, int* comprasion_quant);
void copy(int* mass1, int* mass2, int size_mass);
void sort(int** mass, int first, int last, int* permut_quant, int* comprasion_quant, char** output_filepath, FILE** output_file,
	void sort_exact(int*, int, int, int*, int*));
void create_info(struct INFO* info, int number, int* mass, int size_mass, void sort_exact(int*, int, int, int*, int*));
void efficiency_table(int** mass, int first, int last);
void efficienty_test();
void constract_Experement_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file);
void constract_Sort_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file);
void constract_Found_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file);
void constract_Alg_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file);
void constract_CreateMass_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file);
void constract_Setting_Menu(int* return_flag, int** mass, int* size_mass, char** input_filepath, char** output_filepath,
	FILE** input_file, FILE** output_file);
void constract_Start_Menu();

struct INFO;

