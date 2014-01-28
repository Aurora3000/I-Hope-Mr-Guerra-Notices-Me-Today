//Collin Leonheart, Kavan Mally, Mitchell Leng
#include <windows.h>
#include <iostream>
#include <fstream>
#include "resource.h"
#include "FileReadin.h"
#include "misc.h"
#include <cstdio>
#include <Tchar.h>

const char g_szClassName[] = "myWindowClass";
int temp = 0;
HWND fName, lName, Grade, fNameLab, lNameLab, gradeLab;
string uFName, uLName, uGrade;
vector<string> uClasses, uGrades;
vector<HWND> classButton, classLabel;
void makeClasses(HWND, FileReadin);

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
                    char t[2];
                    GetDlgItemText(hwnd, IDE_INPUT_A, t, 2);
                    temp = atoi(t);
                    if (temp > 15){temp=15;}
                    uClasses.assign(temp, "");
                    uGrades.assign(temp, "");
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
                HWND hwndButton = CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 5, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_A, GetModuleHandle(NULL), NULL);
                HWND hwndButtonB = CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_B, GetModuleHandle(NULL), NULL);
                HWND hwndButtonC = CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 175, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_C, GetModuleHandle(NULL), NULL);
                SendDlgItemMessage(hwnd, IDC_FNAME, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDC_LNAME, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDC_GRADE, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDE_LABEL_A, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDE_LABEL_B, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDE_LABEL_C, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDB_BUTTON_A, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDB_BUTTON_B, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendDlgItemMessage(hwnd, IDB_BUTTON_C, WM_SETFONT, (WPARAM)hFont, TRUE);
                int lbt = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
            }
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_BUTTON_A:
                    {
                        misc m;
                        char temp[31];
                        GetWindowText(fName, temp, 31);
                        uFName = m.makeString(temp);
                        break;
                    }
                case IDB_BUTTON_B:
                    {
                        misc m;
                        char temp[41];
                        GetWindowText(lName, temp, 41);
                        uLName = m.makeString(temp);
                        break;
                    }
                case IDB_BUTTON_C:
                    {
                        misc m;
                        char temp[3];
                        GetWindowText(Grade, temp, 3);
                        uGrade = m.makeString(temp);
                        break;
                    }
                case ID_FILE_NEW:
                    {
                        int inp = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT), hwnd, AboutDlgProc);
                        break;
                    }
                case ID_FILE_OPEN:
                    {
                        OPENFILENAME ofn;
                        char szFile[200];
                        char ReadBuffer[800] = {0};
                        boolean opre = true;
                        DWORD dwBytesRead = 0;
                        HWND hwn = NULL;
                        HANDLE hf;
                        ZeroMemory(&ofn, sizeof(ofn));
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = hwn;
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
                                FileReadin fr(ReadBuffer);
                                temp = fr.numClasses;
                                uClasses.assign(temp, "");
                                uGrades.assign(temp, "");
                                for (int x = 0; x < temp; x++)
                                {
                                    uClasses.at(x) = fr.getClassName(x);
                                    uGrades.at(x) = fr.getClassGrade(x);
                                }
                                makeClasses(hwnd, fr);
                                uFName = fr.getFirstName();
                                uLName = fr.getLastName();
                                uGrade = fr.getGrade();
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
    //Registering Window Class
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
    //Creating Window
    hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, g_szClassName, "Aurora 3000", WS_OVERLAPPEDWINDOW, 250, 250, 280, 200, NULL, NULL, hInstance, NULL);
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    //Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

void makeClasses(HWND hwnd, FileReadin fr)
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
    SetWindowPos(hwnd, NULL, 200, 200, 280, 310, SWP_SHOWWINDOW);
    HWND hw;
    int x = 5;
    int y = 80;
    classLabel.assign(temp, hw);
    classButton.assign(temp, hw);
    for (int a = 0; a < temp; a++)
    {
        int def = a + 9500;
        int defE = a + 9600;
        int defB = a + 9700;
        classLabel.at(a) = CreateWindowEx(NULL, "STATIC", fr.getClassName(a).c_str(), WS_VISIBLE | WS_CHILD | SS_CENTER, x, y, 75, 20, hwnd, (HMENU)def, GetModuleHandle(NULL), NULL);
        classButton.at(a) = CreateWindowEx(NULL, "BUTTON", "Edit Class", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y+20, 75, 20, hwnd, (HMENU)defB, GetModuleHandle(NULL), NULL);
        x += 85;
        if ((a+1)%3==0)
        {
            x = 5;
            y += 60;
        }
    }
    for (int lerpz = 9500; lerpz <= 9700 + temp; lerpz++)
    {
        SendDlgItemMessage(hwnd, lerpz, WM_SETFONT, (WPARAM)hFont, TRUE);
        if (lerpz == 9500+temp)
            lerpz = 9599;
        else if (lerpz == 9600+temp)
            lerpz = 9699;
    }
}
