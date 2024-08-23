#include "MainWindow.h"
#include "Audio.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MainWindow mainWindow(hInstance, nCmdShow);
    Audio      audio;

    audio.InputList();

    if (!mainWindow.Create())
    {
        return 0;
    }

    mainWindow.Show(nCmdShow);

    // Основной цикл обработки сообщений
    MSG Msg;
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}