#pragma once
#include <windows.h>



// Gets the current window and outputs it as a string - in ASCII
// This one works better than all the others because it adds newlines
// REMEMBER - MUST free string after use
char* getScreenWindowA(HANDLE outBuffer);


// Gets the screenbuffer and outputs it as a string - in ASCII
// REMEMBER - MUST free string after use
char* getScreenBufferA(HANDLE outBuffer);

// Gets the current window and outputs it as a string - in UNICODE
// This one works better than all the others because it adds newlines
// REMEMBER - MUST free string after use
wchar_t* getScreenWindowW(HANDLE outBuffer);


// Gets the screenbuffer and outputs it as a string - in UNICODE (Does not actually do it in UNICODE YET)
// REMEMBER - MUST free string after use
char* getScreenBufferW(HANDLE outBuffer);
