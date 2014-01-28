#include <windows.h>
#include <iostream>
#include <fstream>
#include "resource.h"
#include "FileReadin.h"
#include <cstdio>
#include <Tchar.h>

const char g_szClassName[] = "myWindowClass";
int temp = 0;
HWND fName, lName, Grade, fNameLab, lNameLab, gradeLab;

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
                case IDB_INPUTB_A:
                    temp = 9;
                    EndDialog(hwnd, IDB_INPUTB_A);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            {
                HFONT g_hfFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
                HDC hdc = GetDC(NULL);
                ReleaseDC(NULL, hdc);
                HFONT hFont = CreateFont(-12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "MS Sans Serif");
                if (hFont)
                {
                    DeleteObject(g_hfFont);
                    g_hfFont = hFont;
                }
                else
                    printf("Font creation failed!");
                fNameLab = CreateWindowEx(NULL, "STATIC", "First Name", WS_VISIBLE | WS_CHILD | SS_CENTER, 5, 5, 75, 20, hwnd, (HMENU)IDC_FNAME, GetModuleHandle(NULL), NULL);
                fName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 5, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_A, GetModuleHandle(NULL), NULL);
                lNameLab = CreateWindowEx(NULL, "STATIC", "Last Name", WS_VISIBLE | WS_CHILD | SS_CENTER, 90, 5, 75, 20, hwnd, (HMENU)IDC_LNAME, GetModuleHandle(NULL), NULL);
                lName = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 90, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_B, GetModuleHandle(NULL), NULL);
                gradeLab = CreateWindowEx(NULL, "STATIC", "Grade", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 5, 75, 20, hwnd, (HMENU)IDC_GRADE, GetModuleHandle(NULL), NULL);
                Grade = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 175, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_C, GetModuleHandle(NULL), NULL);
                HWND hwndButton = CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 5, 105, 75, 20, hwnd, (HMENU)IDB_BUTTON_A, GetModuleHandle(NULL), NULL);
                SendDlgItemMessage(hwnd, IDC_FNAME, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDC_LNAME, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDC_GRADE, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDE_LABEL_A, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDE_LABEL_B, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDE_LABEL_C, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDB_BUTTON_A, WM_SETFONT, (WPARAM)hFont, TRUE);
            }
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_BUTTON_A:
                    {
                        break;
                    }
                case ID_FILE_OPEN:
                    {
                        OPENFILENAME ofn;
                        char szFile[200];
                        char ReadBuffer[800] = {0};
                        boolean opre = true;
                        DWORD dwBytesRead = 0;
                        HWND hwnd = NULL;
                        HANDLE hf;
                        ZeroMemory(&ofn, sizeof(ofn));
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = hwnd;
                        ofn.lpstrFile = szFile;
                        ofn.lpstrFile[0] = '\0';
                        ofn.nMaxFile = sizeof(szFile);
                        ofn.lpstrFilter = "All\0*.*\0";
                        ofn.nFilterIndex = 1;
                        ofn.lpstrFileTitle = NULL;
                        ofn.nMaxFileTitle = 0;
                        ofn.lpstrInitialDir = NULL;
                        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                        if (GetOpenFileName(&ofn)==true)
                            hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
                        if (hf == INVALID_HANDLE_VALUE)
                        {
                            printf("Error opening file.");
                            opre = false;
                        }
                        if (FALSE == ReadFile(hf, ReadBuffer, 800, &dwBytesRead, NULL))
                        {
                            printf("Error reading file");
                            opre = false;
                        }
                        if (opre)
                        {
                            if (dwBytesRead > 0 && dwBytesRead <= 800)
                            {
                                ReadBuffer[dwBytesRead] = '\0';
                                _tprintf(TEXT("Data read from %s (%d bytes): \n"), szFile, dwBytesRead);
                                printf("%s\n", ReadBuffer);
                                int inp = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT), hwnd, AboutDlgProc);
                                FileReadin fr(ReadBuffer, temp);
                                SetWindowText(fName, TEXT(fr.getFirstName().c_str()));
                                SetWindowText(lName, TEXT(fr.getLastName().c_str()));
                                SetWindowText(Grade, TEXT(fr.getGrade().c_str()));
                            }
                        }
                    }
                    break;
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case ID_HELP_ABOUT:
                    {
                        int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
                    }
                    break;
            }
            break;
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    //Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    //Creating the Window
    hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, g_szClassName, "Aurora 3000", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInstance, NULL);
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    //The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
