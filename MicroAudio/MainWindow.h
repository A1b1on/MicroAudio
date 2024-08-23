#pragma once

#include <windows.h>

class MainWindow
{
public:
    MainWindow(HINSTANCE hInstance, int nCmdShow);
    ~MainWindow();

    bool Create();
    void Show(int nCmdShow);
    HWND GetHwnd() const;

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HINSTANCE hInstance_;
    HWND hwnd_;
    HWND hComboBox_;
    HWND hEditBox_;
    HWND hFileButton_;
    HWND hPlayButton_;
    HWND hListBox_;
    const wchar_t* className_ = L"MainWindowClass";
};
