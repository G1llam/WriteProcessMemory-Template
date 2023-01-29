#include <iostream>
#include <Windows.h>

DWORD pid;
DWORD Credits = 0x133D2BE4; //Hex address for the games credits, as this isnt a pointer, you will need to find this each time - getting pointers is better
int value{};

int main()
{
	HWND hwnd = FindWindowA(0, ("Command & Conquer Red Alert 3")); //find the games process window.

	GetWindowThreadProcessId(hwnd, &pid); //get the games process ID
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid); //Opens the games process with all access

	std::cout << "How many credits would you like?: "; //Asks how many credits you would like to add
	std::cin >> value; //stores the given amount of credits into the value variable

	WriteProcessMemory(pHandle, (LPVOID)Credits, &value, sizeof(value), 0); //writes the new value to the game
}