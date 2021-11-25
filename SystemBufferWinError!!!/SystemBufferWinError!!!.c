#define _CRT_SERUCE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
//#include <strsafe.h>

LPWSTR ClipboardOutputText();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	while (TRUE)
	{
		LPSTR Data = ClipboardOutputText();	
		TCHAR Alert[] = L"Вы нарушили АВТОРСКИЕ ПРАВА, скопировав следующий текст: ";		
		TCHAR third[512];
		swprintf(third, sizeof third, L"%s%s", Alert, Data);
		if (*Data != 0)
		{
			MessageBoxW(NULL, &third, L"Внимание!!! Нарушение!!!", MB_OK | MB_ICONWARNING);
			ClipboardOutputText("");
		}			
		Sleep(1000);
	}
	return 0;
}
TCHAR* ClipboardOutputText()
{

	TCHAR* Message = NULL;
	OpenClipboard(NULL); //открыть буфер обмена
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT); // записать в буфер обмена данные соответсвующего типа
	Message = (TCHAR*)GlobalLock(hClipboardData); // считать из глобального участка памяти, привести это все к стороке
	GlobalUnlock(hClipboardData);// освободить глобальных участок памяти
	CloseClipboard(); // закрыть буфер обмена, сделать его доступным для других приложений
	EmptyClipboard(); //очистить буфер обмена
	return Message;
}
int ClipboardInputText(LPWSTR buffer)
{
	DWORD len;
	HANDLE hMem;
	len = wcslen(buffer) + 1; // определние длины строки в формате юникода

	hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR)); // выделение памяти в глобальной области видимости
	memcpy(GlobalLock(hMem), buffer, len * sizeof(LPWSTR)); // копирование области памяти из buffer в hMem
	GlobalUnlock(hMem); // разблокировать содержимое этой памяти (сделать доступным для других программ)
	OpenClipboard(0); //открыть буфер обмена
	EmptyClipboard(); //очистить буфер обмена
	SetClipboardData(CF_UNICODETEXT, hMem); // записать в буфер обмена данные соответствующего типа
	CloseClipboard(); //закрыть буфер обмена, сделать его доступным для других приложений
	return 0;
}
