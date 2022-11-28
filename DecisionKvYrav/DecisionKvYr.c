#include "..\\Pigalev_Crate_anonymous_channels\Header.h"

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
	DWORD f;
	struct Result result;
	if (d[0] == 0)
	{
		result.equation = "Коэфицент a не может принимать значение 0 (ноль)!";
		BOOL k = WriteFile(hWrite, &result, sizeof(struct Result), &f, NULL);
		return 0;
	}
	if (d[0] == -107374176. || d[1] == -107374176. || d[2] == -107374176. || isinf(d[0]) != 0 || isinf(d[1]) != 0 || isinf(d[2]) != 0)
	{
		result.equation = "Входные данные неккоректны!";
		BOOL k = WriteFile(hWrite, &result, sizeof(struct Result), &f, NULL);
		return 0;
	}
	decision(d[0], d[1], d[2], &result);
	BOOL k = WriteFile(hWrite, &result, sizeof(struct Result), &f, NULL);
	printf("%s\n%s\n%s", result.answer, result.d, result.equation);
	return 0;
}

char* decision(float a, float b, float c, struct Result *result)
{
	char* primer = calloc(100, 1);
	sprintf(primer, "Уравнение: %g*a + %g * b + %g = 0\n", a, b, c);
	result->answer = primer;
	float D = b * b - 4 * a * c;
	char* disc = calloc(100, 1);
	sprintf(disc, "Дискриминант равен %g\n", D);
	result->d = disc;
	if (D > 0)
	{
		float x1 = (-b - sqrt(D)) / (2 * a);
		float x2 = (-b + sqrt(D)) / (2 * a);
		char* str = calloc(100, 1);
		sprintf(str, "Данное уравнение имеет два корня: %g %g", x1, x2);
		result->equation = str;
	}
	else if (D == 0)
	{
		float x = (-b) / (2 * a);
		char* str = calloc(100, 1);
		sprintf(str, "Данное уравнение имеет один корень: %g", x);
		result->equation = str;
	}
	else if (D < 0)
	{
		result->equation = "Действительных корней нет";
	}
	return result;
}