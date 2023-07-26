#include <iostream>
#include <vector>
#include <Windows.h>

int main() {
    HWND GameWindow = FindWindowA(NULL, "Command & Conquer Red Alert 3: Uprising");
    DWORD pID, gameBaseAddress, pointAddress, baseAddress, pointsAddress;
        gameBaseAddress = 0x00400000;
        pointAddress = 0x008FC734;
        baseAddress = NULL;
    GetWindowThreadProcessId(GameWindow, &pID);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
    std::vector<DWORD> pointsOffsets{0x28, 0x40, 0x70, 0x04, 0x34, 0x00, 0x04};


    ReadProcessMemory(processHandle, (LPVOID)(gameBaseAddress + pointAddress), &baseAddress, sizeof(baseAddress), NULL);
    pointsAddress = baseAddress;
    for (int i = 0; i < pointsOffsets.size() - 1; i++)
    {
        ReadProcessMemory(processHandle, (LPVOID)(pointsAddress + pointsOffsets.at(i)), &pointsAddress, sizeof(pointsAddress), NULL);
    }
    pointsAddress += pointsOffsets.at(pointsOffsets.size() - 1);

    std::cout << "Press Numpad 0 to EXIT" << std::endl;
    std::cout << "Press Numpad 1 to set Points" << std::endl;
    while (true) {
        Sleep(50);
        if (GetAsyncKeyState(VK_NUMPAD0)) {
            return 0;
        }
        if (GetAsyncKeyState(VK_NUMPAD1)) {
            std::cout << "How many credits would you like?" << std::endl;
            int newPoints {};
            std::cin >> newPoints;
            WriteProcessMemory(processHandle, (LPVOID)(pointsAddress), &newPoints, sizeof(newPoints), NULL);
        }
    }
    CloseHandle(processHandle);
    return 0;
}
