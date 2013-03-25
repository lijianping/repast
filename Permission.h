// Permission.h: interface for the CPermission class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_PERMISSION_H_
#define REPAST_PERMISSION_H_

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
	short m_no_;            /*Ȩ�ޱ��*/
	char m_name_[33];       /*Ȩ������*/
	SQLINTEGER m_sql_no_;   /*���Ȩ�ޱ�ŵĳ���*/
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

#endif 
