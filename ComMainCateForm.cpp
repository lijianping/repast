// ComMainCateForm.cpp: implementation of the CComMainCateForm class.
//
//////////////////////////////////////////////////////////////////////

#include "ComMainCateForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComMainCateForm::CComMainCateForm()
{
	m_sql_name_ = SQL_NTS;
	m_sql_no_ = SQL_NTS;
	m_sql_old_no_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;

}

CComMainCateForm::~CComMainCateForm()
{

}


/*
 * 说明：
 *     绑定主商品分类的所有字段
 * 返回值：
 *     成功返回true，失败返回false
 */
bool CComMainCateForm::BindingParameter()
{
// 	SQLBindCol(m_hstmt_, 1, SQL_C_SHORT, &m_no_, sizeof(m_no_), &m_sql_no_);
// 	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	return true;
}


/*
 * 说明：
 *     获取主商品分类名称
 * 返回值：
 *     成功返回true，失败返回false
 */
bool CComMainCateForm:: GetMainCategoryName(std::string &error)
{
	m_sql_old_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_sql_no_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	if (false == BindReturn())
	{
		return false;
	}
	if(false == ExecSQLProc("{?=call GetMainCategoryName}", error))
	{
		return false;
	} 
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if ((m_return_code_ != SQL_SUCCESS) && (m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		return false;
	}
	m_return_code_ = SQLFetch(m_hstmt_);
	if ((SQL_SUCCESS != m_return_code_) &&
		(SQL_SUCCESS_WITH_INFO != m_return_code_))
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		if (SQL_NO_DATA == m_return_code_)
		{
			error = "无数据!";
		}
		return false;
	}
// 	if(false == MoveFirst())
// 	{
// 		return false;
// 	}
	return true;
}



bool CComMainCateForm:: BindingParameter(bool is_add, std::string &error_info)
{
	m_sql_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_sql_old_no_ = SQL_NTS;

	/*绑定存储过程返回值*/
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定返回值失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
    /* 绑定列参数*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_SHORT, \
		SQL_SMALLINT, 0, 0, &m_no_, 0, &m_sql_no_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数2失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	/* 绑定列参数*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR, sizeof(m_name_)-1, 0, m_name_, sizeof(m_name_), &m_sql_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数3失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	if (false == is_add)
	{
		/*绑定旧编号，用于“更新商品分类存储过程”*/
		m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_SHORT, \
			SQL_SMALLINT, 0, 0, &m_old_no_, 0, &m_sql_old_no_);
		if ((m_return_code_ != SQL_SUCCESS) &&
			(m_return_code_ != SQL_SUCCESS_WITH_INFO))
		{
			error_info = "绑定参数2失败!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
			return false;
    }
	}
	return true;
}

bool CComMainCateForm::InsertCategory(
											std::string id,
											std::string name,
											std::string &error)
{
	char insert[128]={0};
	if (!CheckCategory(id,name,error))
	{
		return false;
	}
	if (!BindingParameter(true, error))
	{
		return false;
	}
	sprintf(insert, "{?=call InsertCommodityCategory(?,?)}");
	if (!ExecSQLProc(insert, error))
	{
		return false;
	}
	if (!IsSQLProcRetRight(error))
	{
		return false;
	}
	return true;
}

bool CComMainCateForm::UpdateCategory(std::string old_id, 
											std::string id, 
											std::string name,
											std::string &error)
{
	char update[128];
	if (!CheckCategory(id,name,error))
	{
		return false;
	}
	/*TODO: 绑定存储过程返回值*/
	sprintf(update, "exec UpdateCommodityCategory %d,%d,'%s'",\
		atoi(old_id.c_str()),atoi(id.c_str()),name.c_str());
	if (false == ExecuteSQL(update,error))
	{
		return false;
	}
	return true;
}


bool CComMainCateForm::DeleteCategory(std::string id,std::string &error)
{
	char delete_sql[128];
	sprintf(delete_sql, "delete from CommodityCategory where CCno = %d",atoi(id.c_str()));
	if (false == ExecuteSQL(delete_sql,error))
	{
		return false;
	}
		return true;
}

bool CComMainCateForm::CheckCategory(std::string id, std::string name, std::string &error)
{
	if (name.length()==0)
	{
		error = "商品分类名称不能为空";
		return false;
	}
	m_no_=atoi(id.c_str());
	strcpy(m_name_,name.c_str());
	return true;
}

/*
 * @ brief: 初始化sql类型数据
 **/
void CComMainCateForm::Initialize() 
{
	this->m_sql_name_ = SQL_NTS;
	this->m_sql_no_ = SQL_NTS;
	this->m_sql_old_no_ = SQL_NTS;
}