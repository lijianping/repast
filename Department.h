// Department.h: interface for the CDepartment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEPARTMENT_H__74043D5B_10BE_4ADA_8D66_AE3051938DDC__INCLUDED_)
#define AFX_DEPARTMENT_H__74043D5B_10BE_4ADA_8D66_AE3051938DDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBForm.h"

class CDepartment: public CDBForm
{
public:
	CDepartment();
	virtual ~CDepartment();
	virtual bool BindingParameter();
	char *id();
	char *name();
	int GetDeptSum();
private:
	char m_id_[5];
	char m_name_[41];
	SQLINTEGER m_sql_id_;
	SQLINTEGER m_sql_name_;
	
};

/*
 *说明：获取部门编号
 *返回值：返回部门编号字符串指针
 **/
char* CDepartment::id()
{
	return m_id_;
}

/*
 *说明：获取部门名称
 *返回值：返回部门名称字符串指针
 **/
char* CDepartment::name()
{
	return m_name_;
}


#endif // !defined(AFX_DEPARTMENT_H__74043D5B_10BE_4ADA_8D66_AE3051938DDC__INCLUDED_)
