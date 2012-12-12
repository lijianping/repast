#include "Wind.h"
#include "MyListView.h"
#include "DBConnect.h"
#include "resource.h"
#include "childwindowid.h"

/*#include <WINDOWS.H>*/


/* global variable */

// int g_user_permission = 0;
/*HINSTANCE g_hinstance;*/
bool g_is_connect;
CDBConnect database;

/* The login window processes */
BOOL CALLBACK LoginProcesses(HWND hwnd, UINT message,
                                WPARAM wParam, LPARAM lParam);
/* The Service Management window processes */
LRESULT CALLBACK ServiceProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam);
/* 
 * 说明: 人事部门窗口过程处理函数
 * The Personnel Management window process
 **/
LRESULT CALLBACK PersonnelProcesses(HWND hwnd, UINT message,
                                  WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nShowCmd)
{
    std::string information;
    int user_permission = 0;  /* The user permission flag */
    g_is_connect = database.Connect("repast", "repast", "repast", information);
    if (!g_is_connect)
    {
        MessageBox(NULL, information.c_str(),
                   TEXT("WINMAIN"), MB_OK | MB_ICONWARNING);
        return 0;
    }
/*    g_hinstance = hInstance;*/
    user_permission = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_LOGIN), NULL,
                                     (DLGPROC)LoginProcesses, (long)&hInstance);
    switch (user_permission)
    {
    case PERMISSION_SERVICE:
        {
            CWind user;
            user.SetWindowInfo(hInstance, TEXT("服务管理"));
            user.set_window_processes((LONG)ServiceProcesses);
            user.set_show_state(nShowCmd);
            user.UserCreateWindow();
            user.MessageLoop();
            break;
        }
    case PERMISSION_FINANCIAL:
        {
            break;
        }
    case PERMISSION_INVENTORY:
        {
            break;
        }
    case PERMISSION_PERSONNEL:
        {
            CWind user;
            DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
            
            user.SetWindowInfo(hInstance, TEXT("人事管理"), style);
            user.set_window_width(800);
            user.set_window_height(600);
            user.set_window_processes((LONG)PersonnelProcesses);
            user.set_show_state(nShowCmd);
            user.UserCreateWindow();
            user.MessageLoop();
            break;
        }
    case PERMISSION_MANAGER:
        {
            break;
        }
    default:
        {
            /* HIT: There must be no statement.
             *      Because user can start this program, and end it
             *      without any operate, so the g_user_permission can 
             *      not be assignment. If there has statement, the 
             *      g_user_permission will be zero. So this block will
             *      be executed.
             */
 /*           MessageBox(NULL, TEXT("permission error!"), 
                      TEXT("ERROR"), MB_ICONINFORMATION | MB_OK);
 */     
        }
    }
    
    return 0;
}






