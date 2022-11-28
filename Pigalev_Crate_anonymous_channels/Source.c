#define PATH "..\\Debug\\DecisionKvYrav.exe"

#include "..\\Pigalev_Crate_anonymous_channels\Header.h"


int main()
{
	system("chcp 1251>nul");
	const char* fileNameStart = "..\\VhodData.txt";
	const char* fileNameResult = "..\\Result.txt";
	float d[3];
	FILE* fileStart = fopen(fileNameStart, "r");
	if (fileStart == NULL)
	{
		printf("При открытие файла возникла ошибка!");
		return 0;
	}
	for (int i = 0; i < 3; i++)
	{
		fscanf(fileStart, " %f", &d[i]);
	}
	fclose(fileStart);
	char* str = calloc(100, sizeof(char));
	sprintf(str, "%f %f %f", d[0], d[1], d[2]);
	char* command_line = str;
	SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
	HANDLE hRead, hWrite;
	BOOL b = CreatePipe(&hRead, &hWrite, &sa, 256);
	DWORD f;
	b = WriteFile(hWrite, command_line, 256, &f, NULL);
	LPCSTR cmd = calloc(4, 1);
	sprintf(cmd, "%d %d", hWrite, hRead);
	LPSTARTUPINFOA sti = calloc(1, sizeof(STARTUPINFO));
	LPPROCESS_INFORMATION li = calloc(1, sizeof(PROCESS_INFORMATION));
	if (!CreateProcessA(
		PATH,
		cmd,
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		sti,
		li
	))
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	Sleep(100);
	struct Result res;
	DWORD d1;
	BOOL l = ReadFile(hRead, &res, sizeof(struct Result), &d1, NULL);

	if (res.eror != -858993460)
	{
		printf("Входные данные неккоректны!");
	}
	else
	{
		printf("Уравнение: %g*a + %g * b + %g = 0\n", d[0], d[1], d[2]);
		if (res.x1 != -107374176. && res.x2 != -107374176.)
		{
			printf("Данное уравнение имеет два корня: %g %g", res.x1, res.x2);
		}
		else if (res.x1 != -107374176.)
		{
			printf("Данное уравнение имеет один корень: %g", res.x1);
		}
		else
		{
			printf("Действительных корней нет\n");
		}
	}

	//printf("%g\n%g\n%d\n", res.x1, res.x2, res.eror);

	DWORD ecode;
	WaitForSingleObject(li->hProcess, INFINITE);

	GetExitCodeProcess(li->hProcess, &ecode);
	CloseHandle(li->hProcess);
	CloseHandle(li->hThread);

	CloseHandle(hRead);
	CloseHandle(hWrite);
	return 0;
}