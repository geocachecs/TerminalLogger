#include <stdio.h>
#include <windows.h>
#include "getScreenBuffer.h"


// Gets the current window and outputs it as a string in ASCII
// REMEMBER - MUST free string after use
char* getScreenWindowA(HANDLE outBuffer) {
	int bufWidth;
	int bufHeight;
	int winWidth;
	int winHeight;
	int strWidth;
	CHAR_INFO* char_buffer;
	COORD  dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT lpReadRegion;
	char* outstring;

	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(outBuffer, &lpConsoleScreenBufferInfo);

	bufWidth = lpConsoleScreenBufferInfo.dwSize.X;
	bufHeight = lpConsoleScreenBufferInfo.dwSize.Y;

	winWidth = lpConsoleScreenBufferInfo.srWindow.Right - lpConsoleScreenBufferInfo.srWindow.Left + 1;
	winHeight = lpConsoleScreenBufferInfo.srWindow.Bottom - lpConsoleScreenBufferInfo.srWindow.Top + 1;

	if ((char_buffer = malloc(sizeof(CHAR_INFO) * winWidth * winHeight)) == NULL) {
		return NULL;
	}

	strWidth = winWidth + 1;
	if ((outstring = malloc(sizeof(wchar_t) * strWidth * winHeight + 1)) == NULL) {
		return NULL;
	}

	// COORD describing buffer size
	dwBufferSize.X = winWidth;
	dwBufferSize.Y = winHeight;

	// COORD designating what part of char_buffer will be used to store the data
	dwBufferCoord.X = 0;
	dwBufferCoord.Y = 0;

	// SMALL_RECT describing what part of the screen buffer will be read
	lpReadRegion = lpConsoleScreenBufferInfo.srWindow;

	if (ReadConsoleOutput(outBuffer, char_buffer, dwBufferSize, dwBufferCoord, &lpReadRegion) == NULL) {
		return NULL;
	}

	for (int i = 0; i < winWidth * winHeight; i++) {
		outstring[i] = char_buffer[i].Char.AsciiChar;
	}
	outstring[winWidth * winHeight] = NULL;

	// Write window characters to output string
	for (int i = 0; i < winHeight; i++) {
		for (int j = 0; j < winWidth; j++) {


			outstring[i * strWidth + j] = char_buffer[i * winWidth + j].Char.AsciiChar;
		}
		outstring[i * strWidth + winWidth] = '\n';
	}
	outstring[winWidth * winHeight] = NULL;



	free(char_buffer);

	return outstring;
}



// Gets the screenbuffer and outputs it as a string - in ASCII
// REMEMBER - MUST free string after use
char* getScreenBufferA(HANDLE outBuffer) {
	int bufWidth;
	int bufHeight;
	CHAR_INFO* char_buffer;
	COORD  dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT lpReadRegion;
	char* outstring;

	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(outBuffer, &lpConsoleScreenBufferInfo);

	bufWidth = lpConsoleScreenBufferInfo.dwSize.X;
	bufHeight = lpConsoleScreenBufferInfo.dwSize.Y;

	if ((char_buffer = malloc(sizeof(CHAR_INFO) * bufWidth * bufHeight)) == NULL) {
		return NULL;
	}
	if ((outstring = malloc(sizeof(char) * bufWidth * bufHeight + 1)) == NULL) {
		return NULL;
	}

	// COORD describing buffer size
	dwBufferSize.X = bufWidth;
	dwBufferSize.Y = bufHeight;

	// COORD designating what part of char_buffer will be used to store the data
	dwBufferCoord.X = 0;
	dwBufferCoord.Y = 0;

	// SMALL_RECT describing what part of the screen buffer will be read
	lpReadRegion.Top = 0;
	lpReadRegion.Left = 0;
	lpReadRegion.Right = bufWidth - 1;
	lpReadRegion.Bottom = bufHeight - 1;

	if (ReadConsoleOutput(outBuffer, char_buffer, dwBufferSize, dwBufferCoord, &lpReadRegion) == NULL) {
		return NULL;
	}

	for (int i = 0; i < bufWidth * bufHeight; i++) {
		outstring[i] = char_buffer[i].Char.AsciiChar;
	}
	outstring[bufWidth * bufHeight] = NULL;
	free(char_buffer);

	return outstring;
}




// Gets the screenbuffer and outputs it as a string - in UNICODE!
// REMEMBER - MUST free string after use
char* getScreenBufferW(HANDLE outBuffer) {
	int bufWidth;
	int bufHeight;
	CHAR_INFO* char_buffer;
	COORD  dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT lpReadRegion;
	char* outstring;

	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(outBuffer, &lpConsoleScreenBufferInfo);

	bufWidth = lpConsoleScreenBufferInfo.dwSize.X;
	bufHeight = lpConsoleScreenBufferInfo.dwSize.Y;

	if ((char_buffer = malloc(sizeof(CHAR_INFO) * bufWidth * bufHeight)) == NULL) {
		return NULL;
	}
	if ((outstring = malloc(sizeof(char) * bufWidth * bufHeight + 1)) == NULL) {
		return NULL;
	}

	// COORD describing buffer size
	dwBufferSize.X = bufWidth;
	dwBufferSize.Y = bufHeight;

	// COORD designating what part of char_buffer will be used to store the data
	dwBufferCoord.X = 0;
	dwBufferCoord.Y = 0;

	// SMALL_RECT describing what part of the screen buffer will be read
	lpReadRegion.Top = 0;
	lpReadRegion.Left = 0;
	lpReadRegion.Right = bufWidth - 1;
	lpReadRegion.Bottom = bufHeight - 1;

	if (ReadConsoleOutput(outBuffer, char_buffer, dwBufferSize, dwBufferCoord, &lpReadRegion) == NULL) {
		return NULL;
	}

	for (int i = 0; i < bufWidth * bufHeight; i++) {
		outstring[i] = char_buffer[i].Char.UnicodeChar;
	}


	outstring[bufWidth * bufHeight] = NULL;
	free(char_buffer);

	return outstring;
}


// Gets the current window and outputs it as a string - in UNICODE!
// This one works better than all the others because it adds newlines
// REMEMBER - MUST free string after use
wchar_t* getScreenWindowW(HANDLE outBuffer) {
	int bufWidth;
	int bufHeight;
	int winWidth;
	int winHeight;
	int strWidth;
	CHAR_INFO* char_buffer;
	COORD  dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT lpReadRegion;
	wchar_t* outstring;

	CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(outBuffer, &lpConsoleScreenBufferInfo);

	bufWidth = lpConsoleScreenBufferInfo.dwSize.X;
	bufHeight = lpConsoleScreenBufferInfo.dwSize.Y;

	winWidth = lpConsoleScreenBufferInfo.srWindow.Right - lpConsoleScreenBufferInfo.srWindow.Left + 1;
	winHeight = lpConsoleScreenBufferInfo.srWindow.Bottom - lpConsoleScreenBufferInfo.srWindow.Top + 1;

	if ((char_buffer = malloc(sizeof(CHAR_INFO) * winWidth * winHeight)) == NULL) {
		return NULL;
	}

	strWidth = winWidth + 1;
	if ((outstring = malloc(sizeof(wchar_t) * strWidth * winHeight + 1)) == NULL) {
		return NULL;
	}

	// COORD describing buffer size
	dwBufferSize.X = winWidth;
	dwBufferSize.Y = winHeight;

	// COORD designating what part of char_buffer will be used to store the data
	dwBufferCoord.X = 0;
	dwBufferCoord.Y = 0;

	// SMALL_RECT describing what part of the screen buffer will be read
	lpReadRegion = lpConsoleScreenBufferInfo.srWindow;

	if (ReadConsoleOutput(outBuffer, char_buffer, dwBufferSize, dwBufferCoord, &lpReadRegion) == NULL) {
		return NULL;
	}

    // Write window characters to output string
	for (int i = 0; i < winHeight; i++) {
		for (int j = 0; j < winWidth; j++) {

			
			outstring[i * strWidth + j] = char_buffer[i * winWidth + j].Char.UnicodeChar;
		}
		outstring[i * strWidth + winWidth] = L'\n';
	}
	outstring[winWidth * winHeight] = NULL;

	free(char_buffer);

	return outstring;
}