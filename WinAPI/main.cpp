#include<Windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MessageBox
	(
		NULL, 
		"Hello Windows!", 
		"Message Box", 
		MB_YESNO | MB_ICONQUESTION | MB_HELP | MB_DEFBUTTON3 | MB_TASKMODAL
	);
	return 0;
}