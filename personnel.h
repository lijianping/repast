#ifndef REPAST_PERSONNEL_H_
#define REPAST_PERSONNEL_H_

#include "ListView.h"
#include "Button.h"
#include "Static.h"
#include "ComboBox.h"
#include "Edit.h"
#include "StaffForm.h"
#include "childwindowid.h"
#include "resource.h"

LRESULT CALLBACK PersonnelProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK StaffListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK EditStaff(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool CreateStaffListView(HWND parent_hwnd);

bool InitListView(HWND parent_hwnd, UINT id);

void SetListViewData(HWND parent_hwnd, UINT id);

bool CreateGroupBox(HWND parent_hwnd);

bool CreateChildWindow(HWND parent_hwnd, std::string &error);

bool InitComboBox(HWND parent_hwnd, int id);

bool IsCheckName(HWND parent_hwnd);

bool IsCheckSex(HWND parent_hwnd);

bool IsCheckDept(HWND parent_hwnd);

std::string GetID(const HWND parent_hwnd);

std::string GetName(const HWND parent_hwnd);

std::string GetSex(const HWND parent_hwnd);

std::string GetDept(const HWND parent_hwnd);

std::string GetQueryStatement(const HWND parent_hwnd);

bool ExecQuery(const HWND hwnd, const char *sql_query, std::string &error);

bool OnStartQuery(const HWND parent_hwnd);


/* struct define */
typedef struct StaffInfo
{
    std::string id;
    std::string name;
    std::string sex;
    std::string age;
    std::string salary;
}STAFFINFO;

#endif