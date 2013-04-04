#ifndef REPAST_TABLE_INFO_H_
#define REPAST_TABLE_INFO_H_
#include <Windows.h>
#include "ListView.h"
#include "Button.h"
#include "Static.h"
#include "ComboBox.h"
#include "Edit.h"
#include "treectrl.h"
#include "resource.h"
#include "Commodity.h"
#include "tabctrl.h"
#include "pagectrl.h"

/*
 * @ brief: ̨�Ź�������Ϣ
 **/
BOOL CALLBACK TableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
 *˵����¥����Ϣ����
 */
BOOL CALLBACK FloorInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
 * @ brief: ������Ϣ��������̺���
 **/
BOOL CALLBACK RoomInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
 * @ brief: ̨����Ϣ��������̺���
 **/
BOOL CALLBACK ChildTableInfoProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


void ShowFloorList(HWND hwnd);
bool AddFloor(HWND hwnd);
bool UpdateFloor(HWND hwnd);
bool DeleteFloor(HWND hwnd);

bool AddTable(HWND hwnd);
bool UpdateTable(HWND hwnd);
bool DeleteTable(HWND hwnd);


void ShowRoomInfo(HWND hwnd, UINT id, const char *floor_name);
bool InitFloorRoomInfo(HWND hwnd,UINT id);
bool InitRoomCombo(HWND hwnd,const char *floor_name, UINT id);



#endif