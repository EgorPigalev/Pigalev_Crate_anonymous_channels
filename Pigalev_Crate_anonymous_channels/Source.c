#define _CRT_SECURE_NO_WARNINGS
#define PATH "..\\Debug\\DecisionKvYrav.exe"

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
		printf("��� �������� ����� �������� ������!");
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
	BOOL b = CreatePipe(&hRead, &hWrite, &sa , 256);
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
	WaitForSingleObject(li->hProcess, INFINITE);
	printf("� ������� ���������� ��������� ��������\n");
	DWORD ecode;
	GetExitCodeProcess(li->hProcess, &ecode);
	CloseHandle(li->hProcess);
	CloseHandle(li->hThread);

	DWORD d1;
	LPSTR buffer = calloc(256, 1);
	BOOL l = ReadFile(hRead, buffer, 256, &d1, NULL);
	printf("%s\n", buffer);
	free(buffer);

	CloseHandle(hRead);
	CloseHandle(hWrite);
	//float r[2]; // ���������

	//DWORD d1;
	//LPSTR buffer = calloc(256, 1);
	//b = ReadFile(hRead, buffer, 256, &d1, NULL);
	//
	//if (r[0] != -107374176. && r[1] != -107374176.)
	//{
	//	printf("\n��������� ����� ��� �����: %g � %g", r[0], r[1]);
	//}
	//else if (r[0] != -107374176.)
	//{
	//	printf("\n��������� ����� ���� ������: %g", r[0]);
	//}
	//else
	//{
	//	printf("\n��������� �� ����� �� ������ �����");
	//}
	return 0;
}