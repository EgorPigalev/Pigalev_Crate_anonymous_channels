#define _CRT_SECURE_NO_WARNINGS
#define PATH "..\\x64\\Debug\\DecisionKvYrav.exe"

#include <Windows.h>
#include <stdio.h>


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
	LPSTARTUPINFOA sti = calloc(1, sizeof(STARTUPINFO));
	LPPROCESS_INFORMATION li = calloc(1, sizeof(PROCESS_INFORMATION));
	HANDLE hRead, hWrite;
	BOOL b = CreatePipe(&hRead, &hWrite, NULL, 256);
	DWORD f;
	b = WriteFile(hWrite, command_line, 256, &f, NULL);
	LPCSTR cmd = calloc(4, 1);
	sprintf(cmd, "%d %d", hWrite, hRead);
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
	WaitForSingleObject(li->hProcess, INFINITE);
	printf("Я дождусь завершения дочернего процесса");
	DWORD ecode;
	GetExitCodeProcess(li->hProcess, &ecode);
	CloseHandle(li->hProcess);
	CloseHandle(li->hThread);
	float r[2]; // результат

	DWORD d1;
	LPSTR buffer = calloc(256, 1);
	b = ReadFile(hRead, buffer, 256, &d1, NULL);
	
	if (r[0] != -107374176. && r[1] != -107374176.)
	{
		printf("\nУравнение имеет два корня: %g и %g", r[0], r[1]);
	}
	else if (r[0] != -107374176.)
	{
		printf("\nУравнение имеет один корень: %g", r[0]);
	}
	else
	{
		printf("\nУравнение не имеет ни одного корня");
	}
	return 0;
}