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
#include "Department.h"

#define ADD_STAFF 0
#define DELETE_STAFF 1
#define MODIFY_STAFF 2

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

std::string GetEmailAddress(const HWND parent_hwnd);

bool ExecQuery(const HWND hwnd, UINT id, const char *sql_query, std::string &error);

bool OnStartQuery(const HWND hwnd);

bool GetStaffToDialog(const HINSTANCE hinstance, const HWND hwnd, const unsigned int edit_status);



/* struct define */
typedef struct StaffInfo
{
    std::string id;
    std::string name;
    std::string sex;
    std::string age;
    std::string salary;
	std::string department;
	std::string email_address;
	std::string phone;
	std::string address;

}STAFFINFO;


#endif

