// Permission.h: interface for the CPermission class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERMISSION_H__E423BCD8_03A6_429D_852C_BA4C674D6EF5__INCLUDED_)
#define AFX_PERMISSION_H__E423BCD8_03A6_429D_852C_BA4C674D6EF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBForm.h"


//�󶨲�������
#define  ADDPERMISSION 0
#define  UPDATEPERMISSION 1
#define  DELETEPERMISSION 2

struct PERMISSION
{
	std::string old_no;
	std::string no;
	std::string name;
};

class CPermission  :public CDBForm
{
public:
	CPermission();
	virtual bool BindingParameter();
	virtual bool BindingParameter(int bind_type, std::string error);
	inline short no();
	inline char* name();
	virtual ~CPermission();
	bool CheckPermission(PERMISSION *permission, std::string &error);
	void SetPermission(PERMISSION *permission);
	bool InsertPermission(PERMISSION *permission, std::string &error);
	bool UpdatePermission(PERMISSION *permission, std::string &error);
	bool DeletePermission(PERMISSION *permission, std::string &error);
private:
	short m_no_;            /*Ȩ�ޱ��*/
	short m_old_no_;        /*ԭ����Ȩ�ޱ��*/
	char m_name_[33];       /*Ȩ������*/
	SQLINTEGER m_sql_no_;   /*���Ȩ�ޱ�ŵĳ���*/
	SQLINTEGER m_sql_old_no_;
	SQLINTEGER m_sql_name_; /*���Ȩ�����Ƶĳ���*/
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