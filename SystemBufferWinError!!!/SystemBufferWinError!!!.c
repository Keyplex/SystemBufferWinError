#define _CRT_SERUCE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <locale.h>
//#include <strsafe.h>

LPWSTR ClipboardOutputText();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{	
	//while (TRUE)
	//{	
		setlocale(LC_ALL, "Russian");		 
		LPSTR Data = ClipboardOutputText();			
		TCHAR Alert[] = L"Вы нарушили АВТОРСКИЕ ПРАВА, скопировав следующий текст: ";		
		TCHAR third[512];
		swprintf(third, sizeof third, L"%s%s", Alert, Data);
		
		if (*Data != 0)
		{
			MessageBoxW(NULL, &third, L"Внимание!!! Нарушение!!!", MB_OK | MB_ICONWARNING);
			ClipboardOutputText("1");
		}			
		Sleep(1000);
	//}
	return 0;
}
DWORD ConvertToDword(LPWSTR str)
{
	DWORD dw = 0;

	for (size_t i = 0; i < wcslen(str); i++)
	{
		dw += (str[i] - '0');
		dw *= 10;
	}

	return dw / 10;
}
LPWSTR GetToAnswer(DWORD num)
{
	switch (num)
	{
	case 1:
		return L"Один";
	case 2:
		return L"Два";
	case 3:
		return L"Три";
	case 4:
		return L"Четыре";
	case 5:
		return L"Пять";
	case 6:
		return L"Шесть";
	case 7:
		return L"Семь";
	case 8:
		return L"Восемь";
	case 9:
		return L"Девять";
	case 10:
		return L"Десять";
	default:
		return L"Error";
	}
}
TCHAR* ClipboardOutputText()
{

	TCHAR* Message = NULL;
	OpenClipboard(NULL); //открыть буфер обмена
	HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT); // записать в буфер обмена данные соответсвующего типа
	Message = (TCHAR*)GlobalLock(hClipboardData); // считать из глобального участка памяти, привести это все к стороке
	GlobalUnlock(hClipboardData);// освободить глобальных участок памяти

	DWORD num = ConvertToDword(Message);
	LPWSTR word = GetToAnswer(num);
	ClipboardInputText(word);
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
