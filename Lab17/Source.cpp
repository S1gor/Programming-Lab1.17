#include <iostream>

//sin(i-j),i>j
//ln(i),i=j
//cos(i*j),i<j
//18.Вычислить произведение положительных чисел в каждом столбце.

const int MAX = 100;

int askUserScan()
{
	int choise;
	do {
		printf("Введите способ записи:\n1 - вручную\n2 - случайными числами\n3 - по формуле\n4 - из файла\n5 - из бинарного файла\n");
		printf("Выбор:"); scanf_s("%d", &choise);
	} while (choise > 5 || choise < 1);
	return choise;
}

int askUserPrint()
{
	int choise;
	do {
		printf("Введите способ вывода:\n1 - в консоль\n2 - в файл\n3 - в бинарный файл\n");
		printf("Выбор:"); scanf_s("%d", &choise);
	} while (choise > 3 || choise < 1);
	return choise;
}

int scanArrSize(const char name[], int sizeMax)
{
	int size;
	do {
		printf("Введите количество %s [0;%d]\n", name, sizeMax);
		scanf_s("%d", &size);
	} while (size<0 || size>sizeMax);
	return size;
}

void fillArrManually(float mas[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			printf("mas[%d][%d] = ", i, j);
			scanf_s("%f", &mas[i][j]);
		}
}

void fillArrRandomly(float mas[MAX][MAX], int rows, int cols)
{
	srand(time(0));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			mas[i][j] = rand() % 10000 / 100.;
}

void fillArrFormula(float mas[MAX][MAX], int rows, int cols)							// СТРАННО
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (i > j)
				mas[i][j] = sin(i - j);
			if (i = j)
				mas[i][j] = log(i);
			else
				mas[i][j] = cos(i * j);
		}
}

void fillArrFromFile(float mas[MAX][MAX], int& rows, int& cols,const char filename[])			// ВЫЛЕТ
{
	FILE* f;
	if (fopen_s(&f, filename, "r") != 0)
		exit(1);

	fscanf_s(f, "%d %d\n", &rows, &cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(f, "%2.1f ", &mas[i][j]);
		fscanf_s(f, "\n");
	}
	fclose(f);
}

void fillArrFromBinFile(float mas[MAX][MAX], int& rows, int& cols, const char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "rb") != 0)
		exit(1);

	fread(&rows, sizeof(int), 1, f);
	fread(&cols, sizeof(int), 1, f);

	for (int i = 0; i < rows; i++)
		fread(&mas[i], sizeof(float), cols, f);
	fclose(f);
}

void outputArrToScreen(float mas[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%5.1f\t", mas[i][j]);
		}
			printf("\n");
	}
}

void writeArrToFile(float mas[MAX][MAX], int rows, int cols, const char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "w") != 0)
		exit(1);

	fprintf_s(f, "%d %d\n", rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fprintf_s(f, "%2.1f ", mas[i][j]);
		fprintf_s(f, "\n");
	}
	fclose(f);
}

void writeArrToBinFile(float mas[MAX][MAX], int rows, int cols, const char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "wb") != 0)
		exit(1);

	fwrite(&rows, sizeof(int), 1, f);
	fwrite(&cols, sizeof(int), 1, f);
	
	for (int i = 0; i < rows; i++)
		fwrite(&mas[i], sizeof(float), cols, f);
	fclose(f);
}

void arithmetic(float mas[MAX][MAX], int rows, int cols)
{
	int r;
	for (int i = 0; i < cols; i++)
	{
		float sum = 1;
		for (int j = 0; j < rows; j++)
		{
			if (mas[j][i] >= 0)
				sum *= mas[j][i];
			r = i;
		}
		printf("Столбец %d - произведение положительных =  %2.1f\n", r, sum);
	}
}

int main()
{
	system("chcp 1251");

	float mas[MAX][MAX];
	int cols, rows;

	char filename[] = "1.txt";
	char filenameBin[] = "2.bin";

	switch (askUserScan())
	{
	case 1:
		rows = scanArrSize("рядов", MAX);
		cols = scanArrSize("столбцов", MAX);
		fillArrManually(mas, rows, cols);
		break;
	case 2:
		rows = scanArrSize("рядов", MAX);
		cols = scanArrSize("столбцов", MAX);
		fillArrRandomly(mas, rows, cols);
		break;
	case 3:
		rows = scanArrSize("рядов", MAX);
		cols = scanArrSize("столбцов", MAX);
		fillArrFormula(mas, rows, cols);
		break;
	case 4:
		fillArrFromFile(mas, rows, cols, filename);	
		break;
	case 5:
		fillArrFromBinFile(mas, rows, cols, filenameBin);
		break;
	}

	switch (askUserPrint())
	{
	case 1:
		outputArrToScreen(mas, rows, cols);
		break;
	case 2:
		writeArrToFile(mas, rows, cols, filename);
		break;
	case 3:
		writeArrToBinFile(mas, rows, cols, filenameBin);
		break;
	}
	arithmetic(mas, rows, cols);

	return 0;
}