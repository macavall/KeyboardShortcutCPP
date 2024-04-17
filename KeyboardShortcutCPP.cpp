#include <iostream>
#include <windows.h>

HHOOK hookHandle = NULL;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000) && p->vkCode == 'M') {
            std::cout << "Ctrl+Shift+M pressed. Opening Edge browser..." << std::endl;
            system("start msedge.exe");
        }
    }
    return CallNextHookEx(hookHandle, nCode, wParam, lParam);
}

int main() {
    hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (hookHandle == NULL) {
        std::cerr << "Failed to install hook." << std::endl;
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hookHandle);
    return 0;
}
