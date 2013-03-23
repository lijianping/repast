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


bool InitListView(const HWND hwnd, UINT id);


bool InitComboBox(const HWND hwnd, int id);


BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ChangeProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool SetListInfo(const HWND hwnd, const UINT id, const char *find, std::string &error);

bool CreateRefeshButton(const HWND hwnd, const UINT id);

std::string GetFloor(std::string floor);
/*
 *  @ brief: ��ʼ����̨�Ի����еĿ���̨��
 *  @ return: ���ɹ�����true�����򷵻�false
 **/
bool InitAvailableTable(const HWND hwnd, int id);

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);

/*
 * @ ˵��: �µ��Ի����еĲ˵�list view���ڴ�����̺���
 **/
LRESULT CALLBACK OrderMenuListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/*
 * @ brief: ��ȡ̨����Ϣ
 * @ param: hwnd [in] �����ھ��
 * @ param: id [in] ����ʾ̨����Ϣ��Listview��id
 * @ param: use [in] ̨���Ƿ�ʹ�� 0 - δʹ�� 1 - �ѿ�̨ 2 - ��Ԥ��
 * @ param: floor [in] ¥����
 **/
void GetTableInfo(const HWND hwnd, const int id, const char *floor = "01", int use = 0);

LRESULT CALLBACK ChangeTableListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
/* struct define */

/* ̨����Ϣ */
struct CustomerTable {
	UINT menu_id;
	std::string table_no;
	std::string table_state;
	std::string customer_no;
	std::string founding_time;
};
#endif  