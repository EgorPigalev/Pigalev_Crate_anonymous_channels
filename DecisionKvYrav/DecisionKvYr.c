#include "..\\Pigalev_Crate_anonymous_channels\Header.h"

void decision(float a, float b, float c, char* fileNameResult);

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
		result.eror = TRUE;
		BOOL k = WriteFile(hWrite, &result, sizeof(struct Result), &f, NULL);
		return 0;
	}
	if (d[0] == -107374176. || d[1] == -107374176. || d[2] == -107374176. || isinf(d[0]) != 0 || isinf(d[1]) != 0 || isinf(d[2]) != 0)
	{
		result.eror = TRUE;
		BOOL k = WriteFile(hWrite, &result, sizeof(struct Result), &f, NULL);
		return 0;
	}
	decision(d[0], d[1], d[2], &result);
	BOOL k = WriteFile(hWrite, &result, sizeof(struct Result), &f, NULL);
	return 0;
}

void decision(float a, float b, float c, struct Result *result)
{
	float D = b * b - 4 * a * c;
	if (D > 0)
	{
		float x1 = (-b - sqrt(D)) / (2 * a);
		float x2 = (-b + sqrt(D)) / (2 * a);
		char* str = calloc(100, 1);
		sprintf(str, "Данное уравнение имеет два корня: %g %g", x1, x2);
		result->x1 = x1;
		result->x2 = x2;
	}
	else if (D == 0)
	{
		float x = (-b) / (2 * a);
		char* str = calloc(100, 1);
		sprintf(str, "Данное уравнение имеет один корень: %g", x);
		result->x1 = x;
	}
}