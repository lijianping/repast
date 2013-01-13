#ifndef REPAST_SERVICE_H_
#define REPAST_SERVICE_H_

#include "resource.h"
#include "StaffForm.h"
#include "childwindowid.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"

LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);

bool CreateTableListView(const HWND hwnd);

bool InitListView(const HWND hwnd, UINT id);

bool CreateGroupBox(const HWND hwnd);

bool CreateComboBox(const HWND hwnd);

bool InitComboBox(const HWND hwnd, int id);

bool CreateButton(const HWND hwnd);

BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK RetreatProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ChangeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool SetListInfo(const HWND hwnd, const UINT id, std::string &error);

bool CreateRefeshButton(const HWND hwnd, const UINT id);

/*
 *  @˵��: ��ʼ����̨�Ի����еĿ���̨��
 *  @����ֵ:
 *           ���ɹ�����true�����򷵻�false
 **/
bool InitAvailableTable(const HWND hwnd);

/* Create list view */
/*bool CreateList(HINSTANCE hinstance, HWND hwnd, CMyListView &list_view);*/

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);

/* struct define */

/* ̨����Ϣ */
struct Table {
	std::string no;              /* ̨�� */
	int payable_num;             /* Ӧ������ */
	int real_num;                /* ʵ������ */
	std::string founding_time;   /* ��̨ʱ�� */
};
#endif  