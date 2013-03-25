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
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		sizeof(main_cate_name_) - 1, 0, main_cate_name_, sizeof(main_cate_name_), &sql_main_cate_name_);
	strcpy(main_cate_name_, name);
// 	char sql[512];
// 	memset(sql, 0, sizeof(sql));
// 	sprintf(sql, "exec GetChildCateNameByMainCateName '%s'", name);
	if (m_return_code_ == SQL_SUCCESS || m_return_code_ == SQL_SUCCESS_WITH_INFO) {
		if (ExecSQLProc("{? = call GetChildCateNameByMainCateName(?)}"/* sql*/, err_info)) {
			m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, cate_name_, sizeof(cate_name_), &sql_cate_name_);
			SQLFetch(m_hstmt_);
			if (m_return_code_ == SQL_SUCCESS || m_return_code_ == SQL_SUCCESS_WITH_INFO) {
				return true;
			}
		}
	}
	return false;
}