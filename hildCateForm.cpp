// hildCateForm.cpp: implementation of the ChildCateForm class.
//
//////////////////////////////////////////////////////////////////////

#include "hildCateForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ChildCateForm::ChildCateForm()
{

}

ChildCateForm::~ChildCateForm()
{

}

/*
 * @ brief: 初始化sql类型数据
 **/
void ChildCateForm::Initialize()
{
	this->sql_cate_no_ = SQL_NTS;
	this->sql_main_cate_no_ = SQL_NTS;
	this->sql_cate_name_ = SQL_NTS;
	this->sql_main_cate_name_ = SQL_NTS;
}


/*
 * @ brief: 通过主分类名称获取子分类名称
 * @ param: main_cate_no [in] 主分类名称
 * @ param: err_info [out] 错误信息
 * @ return: 若成功返回true，否则返回false
 **/
bool ChildCateForm::GetChildCateName(const char *name, std::string &err_info)
{
	this->Initialize(); // 初始化sql类型
	if (!BindReturn())  // 绑定返回值
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	//  绑定参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
		SQL_CHAR,sizeof(main_cate_name_)-1, 0, main_cate_name_, 0, &sql_main_cate_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        err_info = "绑定主分类名称失败!"; 
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
        return false;
    }
	strcpy(main_cate_name_, name);  // 参数赋值
	if (!this->ExecSQLProc("{? = call GetChildCateNameByMainCateName(?)}", err_info))
	{
		return false;
	}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, cate_name_, sizeof(cate_name_), &sql_cate_name_);
	if ((m_return_code_ != SQL_SUCCESS) && (m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	MoveFirst();
	return true;
}