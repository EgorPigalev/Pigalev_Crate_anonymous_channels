#define PATH "C:\\Users\\ПигалевЕД\\source\\repos\\Pigalev_Crate_anonymous_channels\\Debug\\DecisionKvYrav.exe"

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
	Sleep(2000);
	struct Result res;
	DWORD d1;
	// LPSTR buffer = calloc(256, 1);
	BOOL l = ReadFile(hRead, &res, sizeof(struct Result), &d1, NULL);

	printf("%s\n", res.equation);

	DWORD ecode;
	WaitForSingleObject(li->hProcess, INFINITE);
	printf("Я дождусь завершения дочернего процесса\n");

	GetExitCodeProcess(li->hProcess, &ecode);
	CloseHandle(li->hProcess);
	CloseHandle(li->hThread);
	
	//free(buffer);

	CloseHandle(hRead);
	CloseHandle(hWrite);
	return 0;
}