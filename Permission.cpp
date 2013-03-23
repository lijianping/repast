// Permission.cpp: implementation of the CPermission class.
//
//////////////////////////////////////////////////////////////////////

#include "Permission.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPermission::CPermission()
{
	m_sql_old_no_ = SQL_NTS;
	m_sql_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_query_sql_ = "exec SelectPermissionAll";
}

CPermission::~CPermission()
{

}

bool CPermission::BindingParameter()
{
	//TODO:未检测返回值
	SQLBindCol(m_hstmt_, 1, SQL_C_SHORT, &m_no_, 0, &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	return true;
}

/*
 * 说明：
 *    绑定执行存储过程的参数
 * 参数：
 *       bind_type  [in]    绑定类型：ADD, MODIFY, DELETE
 *       error      [out]   存放错误信息
 * 返回值：
 *      成功返回true, 否则返回false
 **/
bool CPermission::BindingParameter(int bind_type, std::string error)
{
	m_sql_no_ = SQL_NTS;
	m_sql_old_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;

	//绑定存储过程返回值
	if(!this->BindReturn())
	{
		error="绑定存储过程返回值失败";
		return false;
	}
	/* 绑定列参数*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_SHORT, \
		SQL_SMALLINT, 0, 0, &m_no_, 0, &m_sql_no_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error = "绑定参数2失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
        return false;
    }
	if (bind_type == DELETEPERMISSION)//绑定类型为delete,则只需要绑定返回值和输入的ID
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR, sizeof(m_name_)-1, 0, m_name_, sizeof(m_name_), &m_sql_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error = "绑定参数3失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
        return false;
    }
	if (bind_type == ADDPERMISSION)//绑定类型为add,则只需要绑定返回值和输入的ID,name
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_SHORT, \
		SQL_SMALLINT, 0, 0, &m_old_no_, 0, &m_sql_old_no_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error = "绑定参数4失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
        return false;
    }
	return true;
}

/*
 * 说明：
 *    检查权限的各个字段是否正确
 * 参数：
 *       permission  [in]    权限信息结构体
 *       error       [out]   存放错误信息
 * 返回值：
 *      成功返回true, 否则返回false
 **/
bool CPermission::CheckPermission(PERMISSION *permission, std::string &error)
{
	if (0 == permission->no.length())
	{
		error = "编号不能为空！";
		return false;
	}
	if (permission->no.length() > sizeof(m_name_)-1)
	{
		error = "用户编号长度超出允许的范围，请适当减短后再试！";
		return false;
	}
	if (0 == permission->name.length())
	{
		error = "用户名不能为空！";
		return false;
	}
	if (permission->name.length() > sizeof(m_name_)-1)
	{
		error = "用户名长度超出允许的范围，请适当减短后再试！";
		return false;
	}
	return true;
}

/*
 * 说明：
 *    为权限的各个字段赋值
 * 参数：
 *       permission  [in]    权限信息结构体
 **/
void CPermission::SetPermission(PERMISSION *permission)
{
	m_no_ = atoi(permission->no.c_str());
	m_old_no_ = atoi(permission->old_no.c_str());
	strcpy(m_name_ , permission->name.c_str());
}

/*
 * 说明：
 *    增加用户权限
 * 参数：
 *       permission  [in]    权限信息结构体
 *       error       [out]   保存错误信息
 * 返回值：
 *       增加成功返回true, 否则返回false
 */
bool CPermission::InsertPermission(PERMISSION *permission, std::string &error)
{
	if (!CheckPermission(permission,error))
	{
		return false;
	}
	SetPermission(permission);
	if (!BindingParameter(ADDPERMISSION, error))
	{
		return false;
	}
	if (!ExecSQLProc("{? = call InsertPermission(?,?)}",error))
	{
		return false;
	}
	if(!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}


/*
 * 说明：
 *    修改用户权限
 * 参数：
 *       permission  [in]    权限信息结构体
 *       error       [out]   保存错误信息
 * 返回值：
 *       =修改成功返回true, 否则返回false
 */
bool CPermission::UpdatePermission(PERMISSION *permission, std::string &error)
{
	if (!CheckPermission(permission,error))
	{
		return false;
	}
	SetPermission(permission);
	if (!BindingParameter(UPDATEPERMISSION, error))
	{
		return false;
	}
	if (!ExecSQLProc("{? = call UpdatePermission(?,?,?)}",error))
	{
		return false;
	}
	if(!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}

/*
 * 说明：
 *    删除用户权限
 * 参数：
 *       permission  [in]    权限信息结构体
 *       error       [out]   保存错误信息
 * 返回值：
 *       删除成功返回true, 否则返回false
 */
bool CPermission:: DeletePermission(PERMISSION *permission, std::string &error)
{
	SetPermission(permission);
	if (!BindingParameter(DELETEPERMISSION, error))
	{
		return false;
	}
	if (!ExecSQLProc("{? = call DeletePermission(?)}",error))
	{
		return false;
	}
	if(!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}
