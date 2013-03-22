// Permission.h: interface for the CPermission class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERMISSION_H__E423BCD8_03A6_429D_852C_BA4C674D6EF5__INCLUDED_)
#define AFX_PERMISSION_H__E423BCD8_03A6_429D_852C_BA4C674D6EF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBForm.h"

class CPermission  :public CDBForm
{
public:
	CPermission();
	bool BindingParameter();
	inline short no();
	inline char* name();
	virtual ~CPermission();
private:
	short m_no_;            /*权限编号*/
	char m_name_[33];       /*权限名称*/
	SQLINTEGER m_sql_no_;   /*存放权限编号的长度*/
	SQLINTEGER m_sql_name_; /*存放权限名称的长度*/
};

short CPermission::no()
{
	return m_no_;
}
char* CPermission::name()
{
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

#endif // !defined(AFX_PERMISSION_H__E423BCD8_03A6_429D_852C_BA4C674D6EF5__INCLUDED_)
