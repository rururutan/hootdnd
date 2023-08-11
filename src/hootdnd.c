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
#include <stdbool.h>
#include <winuser.h>

#define DIALOG_TITLE L"HootDrop"

static void ShowLastError(DWORD _code){
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, _code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL);
	MessageBox(NULL, lpMsgBuf, DIALOG_TITLE, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

int WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	// check parameter
	int argc;
	LPTSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc < 2) {
		// usage
		MessageBox(NULL, L"Usage : hootdnd [filename]", DIALOG_TITLE, MB_ICONWARNING);
		return 1;
	}

	wchar_t fileName[MAX_PATH] = {0};
//	for (int i=1; i<argc; i++) {
	{
		int i=1;

		//if (argv[i][0] == '-') {
		//   // parse option
		//   MessageBox(NULL, L"get option", DIALOG_TITLE, MB_OK);
		//   continue;
		//}

		// check file name
		// make full path name
		DWORD result = GetFullPathName(argv[i], MAX_PATH-1, fileName, NULL);
		if (result > MAX_PATH-1) {
			MessageBox(NULL, L"Path name longer than MAX_PATH.", DIALOG_TITLE, MB_ICONERROR);
			return 2;
		}
		if (result == 0) {
			DWORD error_code = GetLastError();
			ShowLastError(error_code);
			return 2;
		}

		if (GetLongPathName(fileName, fileName, MAX_PATH) == 0) {
			DWORD error_code = GetLastError();
			ShowLastError(error_code);
			return 3;
		}
	}

	LocalFree(argv);

	// find window
	HWND Wnd = FindWindowEx(NULL, NULL, NULL, L"hoot... - Sound Hardware Emulator");
	if (Wnd == NULL) {
		// not found
		MessageBox(NULL, L"Couldn't find the hoot window.", DIALOG_TITLE, MB_ICONERROR);
		return 1;
	}

	// post message
	HGLOBAL hGlobal = GlobalAlloc(GHND, sizeof(DROPFILES) + (lstrlen(fileName) + 2) * sizeof(wchar_t));
	DROPFILES *dropfile = (DROPFILES *)GlobalLock(hGlobal);
	POINT pt = { 0, 0 };
	dropfile->pFiles = sizeof(DROPFILES);
	dropfile->pt = pt;
	dropfile->fNC = FALSE;
	dropfile->fWide = TRUE;
	lstrcpy((wchar_t*)(dropfile + 1), fileName);
	GlobalUnlock(hGlobal);
	BOOL result = PostMessage(Wnd, WM_DROPFILES, (WPARAM)hGlobal, 0);
	if (result == 0) {
		GlobalFree(hGlobal);
		MessageBox(NULL, L"Faild to PostMessage", DIALOG_TITLE, MB_ICONERROR);
		return 3;
	}

	// check extension
	const wchar_t* extTable[] = {
		L".nsf", L".nez", L".gbs", L".gbr", L".hes", L".kss", L".ay", NULL
	};
	bool sendPlay = false;
	PTSTR ext = PathFindExtension(fileName);
	for (int i=0; extTable[i] != NULL; i++) {
		if (_wcsicmp(extTable[i], ext) == 0) {
			sendPlay = true;
			break;
		}
	}

	// send "return" key
	if (sendPlay == true) {
		PostMessage(Wnd, WM_KEYDOWN, VK_RETURN, 0);
	}

	GlobalFree(hGlobal);

	return 0;
}

