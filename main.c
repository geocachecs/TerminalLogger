#include <stdio.h>
#include <windows.h>
#include "getScreenBuffer.h"


void usage(char* argv[]) {
	printf("\n\nUsage:\n\ttranscriber.exe <target application> <path to logfle folder>\n\n");
	exit(0);

}

void CheckIfChildIsClosedA(HANDLE childHandle, char* filenameA) {
	DWORD exitCode;
	int closeAll = 0;

	GetExitCodeProcess(childHandle, &exitCode);

	if (exitCode == 259) {
		// STILL_ACTIVE
		return;
	}
	
	DeleteFileA(filenameA);

	exit(0);
}


int main(int argc, char* argv[]) {

	if (argc != 3) {
		usage(argv);
	}

	char* logfileFolder = argv[2];
	int pid;

	// definitions for CreateProcessA
	char* lpApplicationName = NULL;
	char* lpCommandLine = argv[1];
	LPSECURITY_ATTRIBUTES lpProcessAttributes=NULL;
	LPSECURITY_ATTRIBUTES lpThreadAttributes=NULL;
	BOOL bInheritHandles = 1;
	DWORD dwCreationFlags=0;
	char* lpEnvironment=NULL;
	char* lpCurrentDirectory=NULL;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE childHandle;


	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	// Open target process
	if (NULL == CreateProcessA(
		lpApplicationName,
		lpCommandLine,
		lpProcessAttributes,
		lpThreadAttributes,
		bInheritHandles,
		dwCreationFlags,
		lpEnvironment,
		lpCurrentDirectory,
		&si,
		&pi))
	{
		printf("Failed to load application: %s\n", argv[1]);
		usage(argv);
	}

	// Definitions for reading window and writing to file (later)
	HANDLE screenOutHandle = CreateFileW(L"CONOUT$", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	FILE* outputFile;
	char* s;
	pid = pi.dwProcessId;
	childHandle = pi.hProcess;

	// Get name of output file
	char* logFileName = malloc(255 * sizeof(char));
	snprintf(logFileName, 255 * sizeof(char), "%s\\app%d.screenlog", logfileFolder, pid);

	while (1) {

		// Read from screen window
		if ((s = getScreenWindowA(screenOutHandle)) == NULL) {
			Sleep(2000);
			continue;
		}
		// Open log file
		if (fopen_s(&outputFile, logFileName, "w+") != 0) {
			free(s);
			Sleep(2000);
			continue;
		}

		// Write to log file, clean up
		fwrite(s, strlen(s) * sizeof(char), 1, outputFile);
		fclose(outputFile);
		free(s);

		/* // this is for UNICODE logging
		// Read from screen window
		if( (ws = getScreenWindowW(screenOutHandle)) == NULL) {
			Sleep(2000);
			continue;
		}
		// Open log file
		if (fopen_s(&outputFile, logFileName, L"w+, ccs=UTF-16LE") != 0) {
			free(ws);
			Sleep(2000);
			continue;
		}

		// Write to log file, clean up
		fwrite(ws, wcslen(ws) * sizeof(wchar_t), 1, outputFile);
		fclose(outputFile);
		free(ws);
		*/


		for (int i = 0; i < 200; i++) {
			CheckIfChildIsClosedA(childHandle, logFileName);
			Sleep(10);
		}

		Sleep(2000);

	}





}





