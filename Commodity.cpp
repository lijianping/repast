// Commodity.cpp: implementation of the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#include "Commodity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommodity::CCommodity()
{  
	
}

CCommodity::~CCommodity()
{

}

/*
 * @ breif: ������Ʒ�������η������ƻ�ȡ��Ʒ����
 * @ param: main_name [in] ��������
 * @ param: child_name [in] �η�����
 * @ parem: err_info [out] ������Ϣ
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool CCommodity::GetCommodityNameSet(const char* main_name,
	                                 const char *child_name,
	                                 std::string &err_info)
{
	Initialize();
	SQLRETURN sql_ret;   // sql ��������
	// �󶨷���ֵ
	sql_ret = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,\
		                       0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RETURN_ERROR)
	sql_ret = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(main_name_) - 1,\
		                       0, main_name_, sizeof(main_name_), &sql_main_name_);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	sql_ret = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(child_name_) - 1,\
		                       0, child_name_, sizeof(child_name_), &sql_child_name_);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(main_name_, main_name);
	strcpy(child_name_, child_name);
	ExecSQLProc("{? = call GetCommodityName(?,?)}", err_info);
	sql_ret = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, name_, sizeof(name_), &sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	return true;
}

/*
 * @ brief: ��ʼ������
 **/
void CCommodity::Initialize() {
	sql_name_ = SQL_NTS;
	sql_main_name_ = SQL_NTS;
	sql_child_name_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	memset(name_, 0, sizeof(name_));
	memset(main_name_, 0, sizeof(main_name_));
	memset(child_name_, 0, sizeof(child_name_));
}