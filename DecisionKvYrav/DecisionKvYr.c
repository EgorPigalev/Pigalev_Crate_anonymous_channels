#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>

void decision(float a, float b, float c, char* fileNameResult);

int main(int argc, char* argv[])
{
	const char* fileNameResult = "..\\Result.txt";
	HANDLE hWrite = (HANDLE)atoi(argv[0]);
	HANDLE hRead = (HANDLE)atoi(argv[1]);
	DWORD d1;
	LPSTR buffer = calloc(256, 1);
	BOOL b = ReadFile(hRead, buffer, 256, &d1, NULL);
	printf("дочерний процесс принял строку: %s\n", buffer);
	free(buffer);
	float d[3];
	for (int i = 0; i < 3; i++)
	{
		d[i] = atof(argv[i]);
	}
	if (d[0] == 0)
	{
		printf("Коэфицент a не может принимать значение 0 (ноль)!");
		return 0;
	}
	if (d[0] == -107374176. || d[1] == -107374176. || d[2] == -107374176. || isinf(d[0]) != 0 || isinf(d[1]) != 0 || isinf(d[2]) != 0)
	{
		printf("Входные данные неккоректны!");
		return 0;
	}
	decision(d[0], d[1], d[2], fileNameResult);
	return 0;
}

void decision(float a, float b, float c, char* fileNameResult)
{
	FILE* fileResult = fopen(fileNameResult, "w");
	fprintf(fileResult, "Уравнение: %g*a + %g * b + %g = 0\n", a, b, c);
	float D = b * b - 4 * a * c;
	fprintf(fileResult, "Дискриминант равен %g\n", D);
	if (D > 0)
	{
		float x1 = (-b - sqrt(D)) / (2 * a);
		float x2 = (-b + sqrt(D)) / (2 * a);
		fprintf(fileResult, "Данное уравнение имеет два корня:\n%g %g", x1, x2);
	}
	else if (D == 0)
	{
		float x = (-b) / (2 * a);
		fprintf(fileResult, "Данное уравнение имеет один корень:\n%g", x);
	}
	else if (D < 0)
	{
		fprintf(fileResult, "Действительных корней нет\n");
	}
	fclose(fileResult);
}