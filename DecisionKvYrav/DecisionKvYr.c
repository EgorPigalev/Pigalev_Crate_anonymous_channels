#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <math.h>

void decision(float a, float b, float c, char* fileNameResult);

int main(int argc, char* argv[])
{
	const char* fileNameResult = "..\\Result.txt";
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	HANDLE hWrite = (HANDLE)atoi(argv[0]);
	//HANDLE hRead = (HANDLE)atoi(argv[1]);
	/*DWORD d1;
	LPSTR buffer = calloc(256, 1);
	BOOL b = ReadFile(hRead, buffer, 256, &d1, NULL);
	printf("%p %p\n", hWrite, hRead);
	printf("�������� ������� ������ ������: %s\n", buffer);
	free(buffer);*/
	DWORD f;
	BOOL b = WriteFile(hWrite, "fgfgfgfg", 9, &f, NULL);
	/*float d[3];
	for (int i = 0; i < 3; i++)
	{
		d[i] = atof(argv[i]);
	}
	if (d[0] == 0)
	{
		printf("��������� a �� ����� ��������� �������� 0 (����)!");
		return 0;
	}
	if (d[0] == -107374176. || d[1] == -107374176. || d[2] == -107374176. || isinf(d[0]) != 0 || isinf(d[1]) != 0 || isinf(d[2]) != 0)
	{
		printf("������� ������ �����������!");
		return 0;
	}*/
	//decision(d[0], d[1], d[2], fileNameResult);
	return 0;
}

void decision(float a, float b, float c, char* fileNameResult)
{
	/*FILE* fileResult = fopen(fileNameResult, "w");
	fprintf(fileResult, "���������: %g*a + %g * b + %g = 0\n", a, b, c);
	float D = b * b - 4 * a * c;
	fprintf(fileResult, "������������ ����� %g\n", D);
	if (D > 0)
	{
		float x1 = (-b - sqrt(D)) / (2 * a);
		float x2 = (-b + sqrt(D)) / (2 * a);
		fprintf(fileResult, "������ ��������� ����� ��� �����:\n%g %g", x1, x2);
	}
	else if (D == 0)
	{
		float x = (-b) / (2 * a);
		fprintf(fileResult, "������ ��������� ����� ���� ������:\n%g", x);
	}
	else if (D < 0)
	{
		fprintf(fileResult, "�������������� ������ ���\n");
	}
	fclose(fileResult);*/
}