#include "ComMainCateForm.h"

ComMainCateForm::ComMainCateForm() 
    : no_(0),
      old_no_(0) {
    memset(name_, 0, sizeof(name_));
}

ComMainCateForm::~ComMainCateForm() {

}

void ComMainCateForm::Initialize() {
	sql_old_no_ = SQL_NTS;
	sql_no_ = SQL_NTS;
	sql_name_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
}

bool ComMainCateForm::GetMainCateName() {
	Initialize();
	SQLRETURN sql_ret;
	// 绑定返回值
	sql_ret = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,\
		                       0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RETURN_ERROR)
	// 执行存储过程
	sql_ret = SQLExecDirect(m_hstmt_, (SQLCHAR *)"{? = call GetMainCategoryName}", SQL_NTS);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) {
		std::string err_info;
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	// 绑定记录集
	sql_ret = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, name_, sizeof(name_), &sql_name_);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	return true;
}

/*
 * 说明：
 *     通过主分类的名称获取主分类的具体信息
 * 参数：
 *     name [in] 主分类名称
 * 返回值：
 *     成功返回true, 否则返回false;
 *
 */
bool ComMainCateForm::GetMainCateByName(const char* name)
{
    Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	       sizeof(name_)-1,0, name_, sizeof(name_), &sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_RETURN_ERROR)
	}
	strcpy(name_,name);
	ExecSQLProc("{?=call GetMainCateByname(?)}");
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_SSHORT, &no_, 0, &sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_RECODE_ERROR)
	}
	this->IsEOF();
	return true;
}