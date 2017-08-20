// hoot Drag and Drop tool
//
// @auther Ru^3

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <tchar.h>

int WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	// check parameter
	int argc;
	LPTSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc < 2) {
		// usage
		MessageBox(NULL, L"usage : hootdnd [filename]", L"HootDrop", MB_OK);
		return 1;
	}

	wchar_t file_name[MAX_PATH] = {};
//	for (int i=1; i<argc; i++) {
	{
		int i=1;

		//if (argv[i][0] == '-') {
		//   // parse option
		//   MessageBox(NULL, L"get option", L"HootDrop", MB_OK);
		//   continue;
		//}

		// check file name
		// make full path name
		if (GetFullPathName(argv[i], MAX_PATH-1, file_name, NULL) == 0) {
			MessageBox(NULL, L"get full path", L"HootDrop", MB_OK);
			return 2;
		}

		if (PathFileExists(file_name) == FALSE) {
			MessageBox(NULL, L"path file exits", L"HootDrop", MB_OK);
			
			return 3;
		}
	}

	// find window
	HWND Wnd = FindWindowEx(NULL, NULL, NULL, L"hoot... - Sound Hardware Emulator");
	if (Wnd == NULL) {
		// not found
		MessageBox(NULL, L"find window", L"HootDrop", MB_OK);
		return 1;
	}

	// post message
	HGLOBAL hGlobal = GlobalAlloc(GHND, sizeof(DROPFILES) + (lstrlen(file_name) + 2) * sizeof(wchar_t));
	DROPFILES *dropfile = (DROPFILES *)GlobalLock(hGlobal);
	POINT pt = { 100, 100 };
	dropfile->pFiles = sizeof(DROPFILES);
	dropfile->fNC = FALSE;
	dropfile->fWide = TRUE;
	dropfile->pt = pt;
	lstrcpy((TCHAR*)(dropfile + 1), file_name);
	GlobalUnlock(hGlobal);
	PostMessage(Wnd, WM_DROPFILES, (WPARAM)hGlobal, 0);
	GlobalFree(hGlobal);

	return 0;
}

