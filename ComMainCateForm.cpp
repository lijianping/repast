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
}

bool ComMainCateForm::GetMainCateName() {
	Initialize();
	SQLRETURN sql_ret;
	// 绑定返回值
	sql_ret = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,\
		                       0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) {
		return false;
	}
	// 执行存储过程
	sql_ret = SQLExecDirect(m_hstmt_, (SQLCHAR *)"{? = call GetMainCategoryName}", SQL_NTS);
	m_return_code_ = sql_ret;
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) {
		std::string err_info;
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	// 绑定记录集
	sql_ret = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, name_, sizeof(name_), &sql_name_);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) {
		return false;
	}
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) {
		std::string err_info;
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	return true;
}