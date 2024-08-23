#include "MainWindow.h"

// ����������� ������
MainWindow::MainWindow(HINSTANCE hInstance, int nCmdShow)
    : hInstance_(hInstance), hwnd_(NULL)
{
    // ����������� ������ ����
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

// ���������� ������
MainWindow::~MainWindow()
{
    UnregisterClass(className_, hInstance_);
}

// �������� ����
bool MainWindow::Create()
{
    // ���������� ���������� ������, ����� ���������� ���� � ����� ������ ����
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);

    int xPos = 0;
    int yPos = desktop.bottom - 280;

    hwnd_ = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        className_,
        L"Micro Audio",
        WS_OVERLAPPEDWINDOW,
        xPos, yPos, 640, 280,
        NULL, NULL, hInstance_, NULL);

    if (hwnd_ == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    // �������� ��������� ����������
    hComboBox_ = CreateWindowEx(
        0, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
        10, 10, 150, 100, hwnd_, NULL, hInstance_, NULL);

    hEditBox_ = CreateWindowEx(
        WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
        170, 10, 200, 20, hwnd_, NULL, hInstance_, NULL);

    hFileButton_ = CreateWindowEx(
        0, L"BUTTON", L"Browse...", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        10, 50, 470, 20, hwnd_, NULL, hInstance_, NULL);

    hPlayButton_ = CreateWindowEx(
        0, L"BUTTON", L"Play", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        380, 10, 100, 20, hwnd_, NULL, hInstance_, NULL);

    hListBox_ = CreateWindowEx(
        WS_EX_CLIENTEDGE, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL,
        10, 80, 470, 180, hwnd_, NULL, hInstance_, NULL);

    // ���������� ������� ��������� � ���������� ������ � ������
    SendMessage(hComboBox_, CB_ADDSTRING, 0, (LPARAM)"Option 1");
    SendMessage(hComboBox_, CB_ADDSTRING, 0, (LPARAM)"Option 2");
    SendMessage(hComboBox_, CB_ADDSTRING, 0, (LPARAM)"Option 3");

    SendMessage(hListBox_, LB_ADDSTRING, 0, (LPARAM)"Item 1");
    SendMessage(hListBox_, LB_ADDSTRING, 0, (LPARAM)"Item 2");
    SendMessage(hListBox_, LB_ADDSTRING, 0, (LPARAM)"Item 3");

    return true;
}

// ����������� ����
void MainWindow::Show(int nCmdShow)
{
    ShowWindow(hwnd_, nCmdShow);
    UpdateWindow(hwnd_);
}

// ��������� ����������� ����
HWND MainWindow::GetHwnd() const
{
    return hwnd_;
}

// ������� ���������
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
