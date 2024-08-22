#include "MainWindow.h"


// Конструктор класса
MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
    : hInstance_(hInstance), hwnd_(NULL)
{
    // Регистрация класса окна
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWindow::WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance_;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className_;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
    }
}

// Деструктор класса
MainWindow::~MainWindow()
{
    UnregisterClass(className_, hInstance_);
}

// Создание окна
bool MainWindow::Create()
{
    hwnd_ = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        className_,
        L"My WinAPI Application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance_, NULL);

    if (hwnd_ == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    return true;
}

// Отображение окна
void MainWindow::Show(int nCmdShow)
{
    ShowWindow(hwnd_, nCmdShow);
    UpdateWindow(hwnd_);
}

// Получение дескриптора окна
HWND MainWindow::GetHwnd() const
{
    return hwnd_;
}

// Оконная процедура
LRESULT CALLBACK MainWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}