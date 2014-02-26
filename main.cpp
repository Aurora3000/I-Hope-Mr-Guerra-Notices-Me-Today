//Collin Leonheart, Kavan Mally, Mitchell Leng
//calculate gpa
#include <windows.h>
#include <iostream>
#include <fstream>
#include "resource.h"
#include "FileReadin.h"
#include "SaveFile.h"
#include "misc.h"
#include "A.h"
#include <cstdio>
#include <Tchar.h>

const char g_szClassName[] = "myWindowClass";
int temp = 0;
int curCla = 0;
string uFName, uLName, uGrade;
vector<string> uClasses, uGrades;
vector<A> asmnt;
bool edit = false;
bool about = false;
bool names = false;
bool read = false;
bool newF = false;

void makeClasses(HWND, FileReadin);
void makeClasses(HWND);
void makeClassNames(HWND);
void makeGrades();
void getNewName(HWND, int);

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
            {
                if (!about && !names && !newF)
                {
                    if (asmnt.at(curCla).getSize() != 0)
                    {
                        SetDlgItemText(hwnd, IDC_LIST_G, asmnt.at(curCla).getG(0).c_str());
                        SetDlgItemText(hwnd, IDC_LIST_T, asmnt.at(curCla).totGra().c_str());
                        for(int x = 0; x < asmnt.at(curCla).getSize(); x++)
                        {
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_INSERTSTRING, -1, (LPARAM)asmnt.at(curCla).get(x).c_str());
                        }
                        SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_SETCURSEL, 0, (LPARAM)asmnt.at(curCla).get(0).c_str());
                        asmnt.at(curCla).lbPos = 0;
                    }
                    else
                    {
                        SetDlgItemText(hwnd, IDC_LIST_G, "");
                        SetDlgItemText(hwnd, IDC_LIST_T, "No assignments.");
                    }
                }
                else if (!about && !newF && names)
                {
                    makeClassNames(hwnd);
                    names = false;
                }
                else if (!about && !names && newF){}
                else{}
                return TRUE;
            }
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    about = false;
                    EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    about = false;
                    EndDialog(hwnd, IDCANCEL);
                    break;
                case IDB_INPUTB_A:
                    {
                        char t[2];
                        GetDlgItemText(hwnd, IDE_INPUT_A, t, 2);
                        if (strlen(t)==0)
                            t[0] = '9';
                        temp = atoi(t);
                        if (temp > 15){temp=15;}
                        uClasses.assign(temp, "");
                        uGrades.assign(temp, "");
                        A moreTemp = A(0);
                        asmnt.assign(temp, moreTemp);
                        uFName = "First";
                        uLName = "Last";
                        uGrade = "9";
                        EndDialog(hwnd, IDB_INPUTB_A);
                        break;
                    }
                case IDL_ASSIGN:
                    {
                        switch(HIWORD(wParam))
                        {
                            case LBN_SELCHANGE:
                                {
                                    asmnt.at(curCla).lbPos = SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_GETCURSEL, 0, 0);
                                    SetDlgItemText(hwnd, IDC_LIST_G, asmnt.at(curCla).getG(asmnt.at(curCla).lbPos).c_str());
                                    break;
                                }
                        }
                        break;
                    }
                case IDB_LIST_R:
                    {
                        if (SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_GETCOUNT, 0, 0) > 1)
                        {
                            asmnt.at(curCla).rem();
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_DELETESTRING, (WPARAM)asmnt.at(curCla).lbPos, 0);
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_SETCURSEL, 0, (LPARAM)asmnt.at(curCla).get(asmnt.at(curCla).lbPos-1).c_str());
                            SetDlgItemText(hwnd, IDC_LIST_G, asmnt.at(curCla).getG(asmnt.at(curCla).lbPos-1).c_str());
                            SetDlgItemText(hwnd, IDC_LIST_T, asmnt.at(curCla).totGra().c_str());
                        }
                        else if (SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_GETCOUNT, 0, 0) == 1)
                        {
                            asmnt.at(curCla).rem();
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_DELETESTRING, (WPARAM)asmnt.at(curCla).lbPos, 0);
                            SetDlgItemText(hwnd, IDC_LIST_G, "");
                            SetDlgItemText(hwnd, IDC_LIST_T, "No assignments.");
                        }else{}
                        break;
                    }
                case IDB_LIST_A:
                    {
                        SetWindowPos(hwnd, NULL, 203, 245, 500, 329, SWP_SHOWWINDOW);
                        SendMessage(hwnd, WM_SETFOCUS, (WPARAM)GetDlgItem(hwnd, IDB_ADD_B), 0);
                        break;
                    }
                case IDB_LIST_E:
                    {
                        edit = true;
                        SetWindowPos(hwnd, NULL, 203, 245, 500, 329, SWP_SHOWWINDOW);
                        SendMessage(hwnd, WM_SETFOCUS, (WPARAM)GetDlgItem(hwnd, IDB_ADD_B), 0);
                        break;
                    }
                case IDB_ADD_B:
                    {
                        misc a;
                        char tN[100], tG[4], tGG[4];
                        GetDlgItemText(hwnd, IDE_ADD_N, tN, 100);
                        GetDlgItemText(hwnd, IDE_ADD_G, tG, 4);
                        GetDlgItemText(hwnd, IDE_ADD_GG, tGG, 4);
                        if (!edit)
                        {
                            asmnt.at(curCla).add(a.makeString(tN));
                            asmnt.at(curCla).addG(a.makeString(tGG), a.makeString(tG));
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_INSERTSTRING, -1, (LPARAM)asmnt.at(curCla).get(asmnt.at(curCla).getSize()-1).c_str());
                            SetDlgItemText(hwnd, IDC_LIST_G, asmnt.at(curCla).getG(asmnt.at(curCla).getSize()-1).c_str());
                            SetDlgItemText(hwnd, IDC_LIST_T, asmnt.at(curCla).totGra().c_str());
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_SETCURSEL, 0, (LPARAM)asmnt.at(curCla).get(asmnt.at(curCla).getSize()-1).c_str());
                            asmnt.at(curCla).lbPos = asmnt.at(curCla).getSize()-1;
                        }
                        else
                        {
                            asmnt.at(curCla).edit(a.makeString(tN));
                            asmnt.at(curCla).editG(a.makeString(tGG), a.makeString(tG));
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_INSERTSTRING, asmnt.at(curCla).lbPos, (LPARAM)asmnt.at(curCla).get(asmnt.at(curCla).lbPos).c_str());
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_DELETESTRING, asmnt.at(curCla).lbPos+1, 0);
                            SendMessage(GetDlgItem(hwnd, IDL_ASSIGN), LB_SELECTSTRING, asmnt.at(curCla).lbPos-1, (LPARAM)asmnt.at(curCla).get(asmnt.at(curCla).lbPos).c_str());
                            SetDlgItemText(hwnd, IDC_LIST_G, asmnt.at(curCla).getG(asmnt.at(curCla).lbPos).c_str());
                            SetDlgItemText(hwnd, IDC_LIST_T, asmnt.at(curCla).totGra().c_str());
                        }
                        SetWindowPos(hwnd, NULL, 203, 245, 305, 329, SWP_SHOWWINDOW);
                        edit = false;
                        break;
                    }
                case EB_01:
                    {
                        getNewName(hwnd, EE_01);
                        break;
                    }
                case EB_02:
                    {
                        getNewName(hwnd, EE_02);
                        break;
                    }
                case EB_03:
                    {
                        getNewName(hwnd, EE_03);
                        break;
                    }
                case EB_04:
                    {
                        getNewName(hwnd, EE_04);
                        break;
                    }
                case EB_05:
                    {
                        getNewName(hwnd, EE_05);
                        break;
                    }
                case EB_06:
                    {
                        getNewName(hwnd, EE_06);
                        break;
                    }
                case EB_07:
                    {
                        getNewName(hwnd, EE_07);
                        break;
                    }
                case EB_08:
                    {
                        getNewName(hwnd, EE_08);
                        break;
                    }
                case EB_09:
                    {
                        getNewName(hwnd, EE_09);
                        break;
                    }
                case EB_10:
                    {
                        getNewName(hwnd, EE_10);
                        break;
                    }
                case EB_11:
                    {
                        getNewName(hwnd, EE_11);
                        break;
                    }
                case EB_12:
                    {
                        getNewName(hwnd, EE_12);
                        break;
                    }
                case EB_13:
                    {
                        getNewName(hwnd, EE_13);
                        break;
                    }
                case EB_14:
                    {
                        getNewName(hwnd, EE_14);
                        break;
                    }
                case EB_15:
                    {
                        getNewName(hwnd, EE_15);
                        break;
                    }
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
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDB_BUTTON_A:
                    {
                        misc m;
                        char temp[31];
                        GetWindowText(GetDlgItem(hwnd, IDE_LABEL_A), temp, 31);
                        uFName = m.makeString(temp);
                        break;
                    }
                case IDB_BUTTON_B:
                    {
                        misc m;
                        char temp[41];
                        GetWindowText(GetDlgItem(hwnd, IDE_LABEL_B), temp, 41);
                        uLName = m.makeString(temp);
                        break;
                    }
                case IDB_BUTTON_C:
                    {
                        misc m;
                        char temp[3];
                        GetWindowText(GetDlgItem(hwnd, IDE_LABEL_C), temp, 3);
                        uGrade = m.makeString(temp);
                        break;
                    }
                case 9700:
                    {
                        curCla = 0;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9701:
                    {
                        curCla = 1;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9702:
                    {
                        curCla = 2;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9703:
                    {
                        curCla = 3;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9704:
                    {
                        curCla = 4;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9705:
                    {
                        curCla = 5;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9706:
                    {
                        curCla = 6;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9707:
                    {
                        curCla = 7;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9708:
                    {
                        curCla = 8;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9709:
                    {
                        curCla = 9;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9710:
                    {
                        curCla = 10;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9711:
                    {
                        curCla = 11;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9712:
                    {
                        curCla = 12;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9713:
                    {
                        curCla = 13;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9714:
                    {
                        curCla = 14;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case 9715:
                    {
                        curCla = 15;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LIST), hwnd, AboutDlgProc);
                        break;
                    }
                case ID_FILE_NEW:
                    {
                        newF = true;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUT), hwnd, AboutDlgProc);
                        newF = false;
                        makeClasses(hwnd);
                        names = true;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NAMES), hwnd, AboutDlgProc);
                        for (int x = 0; x < temp; x++)
                        {
                            SetWindowText(GetDlgItem(hwnd, x+9500), uClasses.at(x).c_str());
                        }
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
                        ofn.lpstrFilter = "User File *.aur\0*.aur\0All *.*\0*.*\0";
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
                                FileReadin fr(ReadBuffer);
                                temp = fr.numClasses;
                                uClasses.assign(temp, "");
                                uGrades.assign(temp, "");
                                asmnt.assign(temp, A(fr.getLen()));
                                for (int x = 0; x < temp; x++)
                                {
                                    uClasses.at(x) = fr.getClassName(x);
                                    uGrades.at(x) = fr.getClassGrade(x);
                                }
                                int xx = -1;
                                while (!fr.endCheck(ReadBuffer))
                                {
                                    if (!fr.nlCheck(ReadBuffer))
                                    {
                                        asmnt.at(xx).add(fr.getNext(ReadBuffer));
                                        asmnt.at(xx).addG(fr.getNext(ReadBuffer), fr.getNext(ReadBuffer));
                                    }
                                    else
                                    {
                                        xx++;
                                        asmnt.at(xx).add(fr.getNext(ReadBuffer));
                                        asmnt.at(xx).addG(fr.getNext(ReadBuffer), fr.getNext(ReadBuffer));
                                    }
                                }
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
                                CreateWindowEx(NULL, "STATIC", "First Name", WS_VISIBLE | WS_CHILD | SS_CENTER, 5, 5, 75, 20, hwnd, (HMENU)IDC_FNAME, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 5, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_A, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(NULL, "STATIC", "Last Name", WS_VISIBLE | WS_CHILD | SS_CENTER, 90, 5, 75, 20, hwnd, (HMENU)IDC_LNAME, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 90, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_B, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(NULL, "STATIC", "Grade", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 5, 75, 20, hwnd, (HMENU)IDC_GRADE, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 175, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_C, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 5, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_A, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_B, GetModuleHandle(NULL), NULL);
                                CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 175, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_C, GetModuleHandle(NULL), NULL);
                                SendDlgItemMessage(hwnd, IDC_FNAME, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDC_LNAME, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDC_GRADE, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDE_LABEL_A, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDE_LABEL_B, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDE_LABEL_C, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDB_BUTTON_A, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDB_BUTTON_B, WM_SETFONT, (WPARAM)hFont, TRUE);
                                SendDlgItemMessage(hwnd, IDB_BUTTON_C, WM_SETFONT, (WPARAM)hFont, TRUE);
                                makeClasses(hwnd, fr);
                                uFName = fr.getFirstName();
                                uLName = fr.getLastName();
                                uGrade = fr.getGrade();
                                SetWindowText(GetDlgItem(hwnd, IDE_LABEL_A), TEXT(fr.getFirstName().c_str()));
                                SetWindowText(GetDlgItem(hwnd, IDE_LABEL_B), TEXT(fr.getLastName().c_str()));
                                SetWindowText(GetDlgItem(hwnd, IDE_LABEL_C), TEXT(fr.getGrade().c_str()));
                                read = true;
                            }
                            if (CloseHandle(hf)==0)
                                printf("Error closing file after reading.");
                        }
                    }
                    break;
                case ID_FILE_SAVE:
                    {
                        makeGrades();
                        SaveFile save = SaveFile(uFName, uLName, uGrade, temp,  uClasses, uGrades, asmnt);
                        string saveData = save.makeData();
                        OPENFILENAME ofn;
                        char szFile[200];
                        DWORD dwBytesRead = 0;
                        HWND hwn = NULL;
                        HANDLE hf;
                        ZeroMemory(&ofn, sizeof(ofn));
                        ofn.lStructSize = sizeof(ofn);
                        ofn.hwndOwner = hwn;
                        ofn.lpstrFile = szFile;
                        ofn.lpstrFile[0] = '\0';
                        ofn.nMaxFile = sizeof(szFile);
                        ofn.lpstrFilter = "User File *.aur\0*.aur\0All *.*\0*.*\0";
                        ofn.nFilterIndex = 1;
                        ofn.lpstrFileTitle = NULL;
                        ofn.nMaxFileTitle = 0;
                        ofn.lpstrInitialDir = NULL;
                        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                        if (GetSaveFileName(&ofn)==true)
                        {
                            if(!save.checkFileName(szFile))
                                ofn.lpstrFile = (LPSTR)save.makeFileName(szFile).c_str();
                            hf = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, (LPSECURITY_ATTRIBUTES)NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
                        }
                        if (hf == INVALID_HANDLE_VALUE)
                            printf("Error opening file.");
                        if (FALSE == WriteFile(hf, saveData.c_str(), strlen(saveData.c_str()), &dwBytesRead, NULL))
                            printf("Error writing to file.");
                        if (CloseHandle(hf)==0)
                            printf("Error closing file after writing.");
                    }
                    break;
                case ID_FILE_EXIT:
                    PostMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case ID_EDIT_NAMES:
                    {
                        if (read)
                        {
                            names = true;
                            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NAMES), hwnd, AboutDlgProc);
                            for (int x = 0; x < temp; x++)
                            {
                                SetWindowText(GetDlgItem(hwnd, x+9500), uClasses.at(x).c_str());
                            }
                        }
                    }
                    break;
                case ID_HELP_ABOUT:
                    {
                        about = true;
                        DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
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
    hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, g_szClassName, "Aurora 3000", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 250, 250, 200, 70, NULL, NULL, hInstance, NULL);
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

void getNewName(HWND hwnd, int lo)
{
    misc m;
    char t[50];
    GetWindowText(GetDlgItem(hwnd, lo), t, 50);
    SetWindowText(GetDlgItem(hwnd, lo+200), TEXT(t));
    uClasses.at(lo-9800) = m.makeString(t);
}

void makeClasses(HWND hwnd)
{
    bool pl = false;
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
    CreateWindowEx(NULL, "STATIC", "First Name", WS_VISIBLE | WS_CHILD | SS_CENTER, 5, 5, 75, 20, hwnd, (HMENU)IDC_FNAME, GetModuleHandle(NULL), NULL);
    CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "First Name", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 5, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_A, GetModuleHandle(NULL), NULL);
    CreateWindowEx(NULL, "STATIC", "Last Name", WS_VISIBLE | WS_CHILD | SS_CENTER, 90, 5, 75, 20, hwnd, (HMENU)IDC_LNAME, GetModuleHandle(NULL), NULL);
    CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "Last Name", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 90, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_B, GetModuleHandle(NULL), NULL);
    CreateWindowEx(NULL, "STATIC", "Grade", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 5, 75, 20, hwnd, (HMENU)IDC_GRADE, GetModuleHandle(NULL), NULL);
    CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "Grade", WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, 175, 25, 75, 20, hwnd, (HMENU)IDE_LABEL_C, GetModuleHandle(NULL), NULL);
    CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 5, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_A, GetModuleHandle(NULL), NULL);
    CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_B, GetModuleHandle(NULL), NULL);
    CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 175, 50, 75, 20, hwnd, (HMENU)IDB_BUTTON_C, GetModuleHandle(NULL), NULL);
    int x = 5;
    int y = 80;
    for (int a = 0; a < temp; a++)
    {
        int def = a + 9500;
        int defB = a + 9700;
        CreateWindowEx(NULL, "STATIC", "Class", WS_VISIBLE | WS_CHILD | SS_CENTER, x, y, 75, 20, hwnd, (HMENU)def, GetModuleHandle(NULL), NULL);
        uClasses.at(a) = "Class";
        uGrades.at(a) = "0";
        CreateWindowEx(NULL, "BUTTON", "Edit Class", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y+20, 75, 20, hwnd, (HMENU)defB, GetModuleHandle(NULL), NULL);
        x += 85;
        if ((a+1)%3==0)
        {
            x = 5;
            y += 60;
            pl = true;
        }
        else
            pl = false;
    }
    if (pl)
        SetWindowPos(hwnd, NULL, 200, 200, 270, y+40, SWP_SHOWWINDOW);
    else
        SetWindowPos(hwnd, NULL, 200, 200, 270, y+100, SWP_SHOWWINDOW);
    for (int lerpz = 9500; lerpz <= 9700 + temp; lerpz++)
    {
        SendDlgItemMessage(hwnd, lerpz, WM_SETFONT, (WPARAM)hFont, TRUE);
        if (lerpz == 9500+temp)
            lerpz = 9699;
    }
    for (int lerpz = IDE_LABEL_A; lerpz <= IDC_GRADE; lerpz++)
    {
        SendDlgItemMessage(hwnd, lerpz, WM_SETFONT, (WPARAM)hFont, TRUE);
        if (lerpz == IDE_LABEL_C)
            lerpz = IDB_BUTTON_A-1;
        else if (lerpz == IDB_BUTTON_C)
            lerpz = IDC_FNAME-1;
    }
}

void makeClasses(HWND hwnd, FileReadin fr)
{
    bool pl = false;
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
    int x = 5;
    int y = 80;
    for (int a = 0; a < temp; a++)
    {
        int def = a + 9500;
        int defB = a + 9700;
        CreateWindowEx(NULL, "STATIC", fr.getClassName(a).c_str(), WS_VISIBLE | WS_CHILD | SS_CENTER, x, y, 75, 20, hwnd, (HMENU)def, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, "BUTTON", "Edit Class", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y+20, 75, 20, hwnd, (HMENU)defB, GetModuleHandle(NULL), NULL);
        x += 85;
        if ((a+1)%3==0)
        {
            x = 5;
            y += 60;
            pl = true;
        }
        else
        {
            pl = false;
        }
    }
    if (pl)
        SetWindowPos(hwnd, NULL, 200, 200, 270, y+40, SWP_SHOWWINDOW);
    else
        SetWindowPos(hwnd, NULL, 200, 200, 270, y+100, SWP_SHOWWINDOW);
    for (int lerpz = 9500; lerpz <= 9700 + temp; lerpz++)
    {
        SendDlgItemMessage(hwnd, lerpz, WM_SETFONT, (WPARAM)hFont, TRUE);
        if (lerpz == 9500+temp)
            lerpz = 9699;
    }
}

void makeClassNames(HWND hwnd)
{
    bool pl = false;
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
    int x = 5;
    int y = 25;
    for (int a = 0; a < temp; a++)
    {
        int defA = a + 9800;
        int defB = a + 9900;
        int defC = a + 10000;
        CreateWindowEx(NULL, "STATIC", uClasses.at(a).c_str(), WS_VISIBLE | WS_CHILD | SS_CENTER, x, y, 75, 20, hwnd, (HMENU)defC, GetModuleHandle(NULL), NULL);
        CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", uClasses.at(a).c_str(), WS_VISIBLE | WS_CHILD |  ES_AUTOHSCROLL, x, y+20, 75, 20, hwnd, (HMENU)defA, GetModuleHandle(NULL), NULL);
        CreateWindowEx(NULL, "BUTTON", "Change", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, x, y+40, 75, 20, hwnd, (HMENU)defB, GetModuleHandle(NULL), NULL);
        x += 85;
        if ((a+1)%3==0)
        {
            x = 5;
            y += 90;
            pl = true;
        }
        else
            pl = false;
    }
    if (pl)
        SetWindowPos(hwnd, NULL, 205, 220, 270, y+5, SWP_SHOWWINDOW);
    else
        SetWindowPos(hwnd, NULL, 205, 220, 270, y+95, SWP_SHOWWINDOW);
    for (int lerpz = 9800; lerpz <= 10000 + temp; lerpz++)
    {
        SendDlgItemMessage(hwnd, lerpz, WM_SETFONT, (WPARAM)hFont, TRUE);
        if (lerpz == 9800+temp)
            lerpz = 9899;
        else if (lerpz == 9900+temp)
            lerpz = 9999;
    }
}

void makeGrades()
{
    for (unsigned int x = 0; x < uGrades.size(); x++)
    {
        if (atoi(asmnt.at(x).getFGrade().c_str()) >= 0)
            uGrades.at(x) = asmnt.at(x).getFGrade();
    }
}
