#ifndef REPAST_SERVICE_H_
#define REPAST_SERVICE_H_

#include "resource.h"
#include "StaffForm.h"
#include "Static.h"
#include "Button.h"
#include "ComboBox.h"
#include "ListView.h"

/* ̨����Ϣ */
typedef struct CustomerTable {
	UINT menu_id;
	std::string customer_no;
	std::string table_no;
	std::string room_name;
	std::string table_state;
	std::string customer_num;
	std::string start_time;
	std::string floor_name;
}CUSTOMERTABLE, *PCUSTOMERTABLE;


LRESULT CALLBACK ListProcesses(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);

bool ShowConsumerTableInfo(const HWND hwnd, const UINT id, const char *floor_name);
bool InitFloorName(const HWND hwnd, int id);


BOOL CALLBACK OrderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


BOOL CALLBACK CheckOutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK ChangeTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK StartTableProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool SetListInfo(const HWND hwnd, const UINT id, const char *find, std::string &error);

bool CreateRefeshButton(const HWND hwnd, const UINT id);

bool InitTableList(const HWND hwnd, int id, const char *floor_name, short status);

bool CreateStartButton(HINSTANCE hinstance, HWND hwnd, std::string error_info);

/*
 * @ ˵��: �µ��Ի����еĲ˵�list view���ڴ�����̺���
 **/
LRESULT CALLBACK OrderMenuListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ChangeTableListProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
/* struct define */

void ReciveConsumerTableInfo(PCUSTOMERTABLE send_in, PCUSTOMERTABLE revice);

#endif  