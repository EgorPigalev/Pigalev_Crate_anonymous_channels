#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>

char* decision(float a, float b, float c, char* fileNameResult);

int main(int argc, char* argv[])
{
	HANDLE hWrite = (HANDLE)atoi(argv[0]);
	HANDLE hRead = (HANDLE)atoi(argv[1]);
	DWORD d1;
	LPSTR buffer = calloc(256, 1);
	BOOL b = ReadFile(hRead, buffer, 256, &d1, NULL);
	float d[3];
	int i = 0;
	char* istr;
	istr = strtok(buffer, " ");
	while (istr != NULL)
	{
		d[i] = atof(istr);
		i++;
		istr = strtok(NULL, " ");
	}
	free(buffer);
	char* result = calloc(256, 1);
	if (d[0] == 0)
	{
		sprintf(result, "%s\n", "Коэфицент a не может принимать значение 0 (ноль)!");
		return 0;
	}
	if (d[0] == -107374176. || d[1] == -107374176. || d[2] == -107374176. || isinf(d[0]) != 0 || isinf(d[1]) != 0 || isinf(d[2]) != 0)
	{
		sprintf(result, "%s\n", "Входные данные неккоректны!");
		return 0;
	}
	result = decision(d[0], d[1], d[2], result);
	DWORD f;
	BOOL k = WriteFile(hWrite, result, 256, &f, NULL);
	return 0;
}

char* decision(float a, float b, float c, char* result)
{
	char* primer = calloc(100, 1);
	sprintf(primer, "Уравнение: %g*a + %g * b + %g = 0\n", a, b, c);
	sprintf(result, "%s%s", result, primer);
	float D = b * b - 4 * a * c;
	char* disc = calloc(100, 1);
	sprintf(disc, "Дискриминант равен %g\n", D);
	sprintf(result, "%s%s", result, disc);
	if (D > 0)
	{
		float x1 = (-b - sqrt(D)) / (2 * a);
		float x2 = (-b + sqrt(D)) / (2 * a);
		char* str = calloc(100, 1);
		sprintf(str, "Данное уравнение имеет два корня:\n%g %g", x1, x2);
		sprintf(result, "%s%s", result, str);
	}
	else if (D == 0)
	{
		float x = (-b) / (2 * a);
		char* str = calloc(100, 1);
		sprintf(str, "Данное уравнение имеет один корень:\n%g", x);
		sprintf(result, "%s%s", result, str);
	}
	else if (D < 0)
	{
		sprintf(result, "%s%s", result, "Действительных корней нет\n");
	}
	return result;
}