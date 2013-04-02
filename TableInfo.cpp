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

/*
 * @ brief: ��ȡ̨�������Ϣ
 * @ param: floor_name [in] ̨������¥������
 * @ param: room_name [in] ̨�����ڷ�������
 * @ return: �ɹ���ȡ̨����Ϣ��¼������true
 **/
bool CTableInfo::GetTableInfoSet(const char *floor_name) {
	this->Initialize();
	BindReturn();
	// ���������
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
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
	BindingParameter();
	return true;
}

bool CTableInfo::GetTableInfoSet(const char *floor_name, const char *room_name) {
	this->Initialize();
	BindReturn();
	// ���������
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(floor_name_) - 1, 0, floor_name_,\
		sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	                              	  sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		// ������ֵ
	strcpy(floor_name_, floor_name);
	strcpy(room_name_, room_name);
	std::string err_info;	
	// ִ�д洢����
	ExecSQLProc("{? = call GetTableInfoByFloorRoom(?,?)}", err_info);
	// ��¼����
    BindingParameter();
	return true;
}

/*
 * @ brief: ����¥������ȡָ��״̬�ķ���̨��
 * @ param: floor_name [in] ¥������
 * @ param: status [in] ״̬
 * @ return: ���ɹ�����true,�ɻ�ȡ̨��,������������������
 **/
bool CTableInfo::GetStartTableSet(const char *floor_name, short status) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
	                                  0, 0, &status_, 0, &sql_status_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	status_ = status;
	std::string err_info;
	ExecSQLProc("{? = call GetStartTableInfo(?,?)}", err_info);
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, table_no_, sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, room_name_, sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_SSHORT, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	return true;
}

/*
 * @ brief: ���̨����Ϣ
 * @ param: floor_name [in] ¥������
 * @ param: room_name [in] ��������
 * @ param: table_no [in] ̨��
 * @ param: payable [in] ̨�ſ���������
 * @ return: ���ɹ�����true
 **/
bool CTableInfo::AddTable(const char *floor_name, const char *room_name, 
	                      const char *table_no, short payable) {
    Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(table_no_) - 1, 0, table_no_,\
		                              sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SHORT, SQL_SMALLINT,\
		                              0, 0, &payable_, 0, &sql_payable_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RECODE_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(room_name_, room_name);
	strcpy(table_no_, table_no);
	payable_ = payable;
	ExecSQLProc("{? = call AddTable(?,?,?,?)}");
	return IsSQLProcRetRight();
}

/*
 * @ brief: ɾ��̨����Ϣ
 * @ param: floor_name [in] ¥������
 * @ param: room_name [in] ��������
 * @ param: table_no [in] ̨��
 * @ return: ���ɹ�����true
 **/
bool CTableInfo::DeleteTable(const char *floor_name, const char *room_name, const char *table_no) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(floor_name_) - 1, 0, floor_name_,\
		                              sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
	                                  sizeof(room_name_) - 1, 0, room_name_,\
		                              sizeof(room_name_), &sql_room_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(table_no_) - 1, 0, table_no_,\
		                              sizeof(table_no_), &sql_table_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(floor_name_, floor_name);
	strcpy(room_name_, room_name);
	strcpy(table_no_, table_no);
	ExecSQLProc("{? = call DeleteTable(?,?,?)}");
	return IsSQLProcRetRight();
}
/*
 * @ brief: ��ʼ���������
 **/
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

/*
 * @ brief: �󶨼�¼��
 * @ return: �ɹ�����true
 **/
bool CTableInfo::BindingParameter()
{
	// �󶨼�¼��
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
