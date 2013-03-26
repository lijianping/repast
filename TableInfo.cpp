// TableInfo.cpp: implementation of the CTableInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "TableInfo.h"
#include "Err.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableInfo::CTableInfo()
{
//	m_query_sql_ = "select * from TableInfo";
	m_query_sql_ = "execute selecttable";
}

CTableInfo::~CTableInfo()
{

}

/*
 *  ˵��: ����̨����Ϣ��
 *  ����:
 *        sql [in] ���µ�sql���
 *        error [out] ����ʱ�Ĵ�����Ϣ
 *  ����ֵ: ���ɹ�����true�����򷵻�false
 */
bool CTableInfo::UpdateForm(std::string sql, std::string &error)
{
	return this->ExecuteSQL(sql.c_str(), error);
}

bool CTableInfo::BindingParameter()
{
	/* ���� */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR,   m_table_no_,      sizeof(m_table_no_),    &m_sql_table_no_);	
	SQLBindCol(m_hstmt_, 2, SQL_C_SSHORT, &m_table_status_, sizeof(m_table_status_),&m_sql_table_status_);
	SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &m_payable_num_,  sizeof(m_payable_num_), &m_sql_payable_num_);
	return true;
}

/*
 * @ brief: ��ȡ̨�������Ϣ
 * @ param: floor_name [in] ̨������¥������
 * @ return: �ɹ���ȡ̨����Ϣ��¼������true
 **/
bool CTableInfo::GetTableInfoSet(const char *floor_name) {
	this->Initialize();
	BindReturn();
	// ���������
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	// ������ֵ
	strcpy(floor_name_, floor_name);
	std::string err_info;	
	// ִ�д洢����
	ExecSQLProc("{? = call GetTableInfoByFloor(?)}", err_info);
	// ��¼����
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, table_no_, sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_SSHORT, &status_, 0, &sql_status_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR);
	return true;
}

void CTableInfo::Initialize() {
	this->sql_table_no_ = SQL_NTS;
	this->sql_floor_name_ = SQL_NTS;
	this->sql_room_name_ = SQL_NTS;
	this->sql_payable_ = SQL_NTS;
	this->sql_status_ = SQL_NTS;
	memset(table_no_, 0, sizeof(table_no_));
	memset(floor_name_, 0, sizeof(floor_name_));
	memset(room_name_, 0, sizeof(room_name_));
}