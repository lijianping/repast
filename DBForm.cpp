// DBForm.cpp: implementation of the CDBForm class.
//
//////////////////////////////////////////////////////////////////////

#include "DBForm.h"
#include <STDIO.H>   /* use sprintf function */
#include <ASSERT.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBForm::CDBForm()
	: m_henv_(SQL_NULL_HENV),
      m_hdbc_(SQL_NULL_HDBC),
	  m_hstmt_(SQL_NULL_HSTMT),
	  m_sql_pro_ret(SQL_NTS),
	  m_pro_ret(0),
	  m_return_code_(0)
{
	m_auto_commit_ = SQL_AUTOCOMMIT_ON;
	std::string error;
	this->Connect("repast", "repast", "repast", error);
}

CDBForm::CDBForm(std::string dns, std::string name, std::string password)
	: m_hdbc_(SQL_NULL_HDBC),
      m_hstmt_(SQL_NULL_HSTMT),
	  m_return_code_(NULL)
{
	std::string error;
	m_auto_commit_ = SQL_AUTOCOMMIT_ON;
	this->Connect(dns.c_str(), name.c_str(), password.c_str(), error);
}

CDBForm::~CDBForm()
{
	this->Disconnect();
}

/*
 * ˵�������������
 * ����ֵ������ɹ�����true,���򷵻�false
 **/
bool CDBForm::AllocHandleStmt()
{
	std::string error;
	if (NULL != m_hstmt_) {
		SQLFreeStmt(m_hstmt_, SQL_UNBIND);/*�ͷŰ�*/
		FreeStatemetHandle();
	}
	/* ��������� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(ALLOCATE_STATEMENT_HANDLE_ERROR)
	return true;
}

/*
 * ˵��: �ж��Ƿ��˼�¼���Ľ�β
 * ����ֵ: ��û�����ݷ���true�������ݷ���false
 */
bool CDBForm::IsEOF()
{
	return FetchData();
}

/*
 * ˵��: �ƶ�����¼�������һ������
 * ����ֵ: ִ�гɹ�����true�����򷵻�false
 */
bool CDBForm::GetRecordSet()
{
	std::string error_info;
	/*���������*/
    if (false == AllocHandleStmt())
	{
		return false;
	}
    /* ִ�в�ѯ��� */
    m_return_code_ = SQLExecDirect(m_hstmt_,
                                   (unsigned char*)m_query_sql_.c_str(),
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        MessageBox(NULL, error_info.c_str(),
                   TEXT("DBForm"), MB_OK| MB_ICONERROR);
        return false;
    }

    /* �󶨲��� */
    BindingParameter(); 
    return true;
}

/*
 * ˵��: �󶨼�¼���������ú�������������ɾ��������
 * ����ֵ: ִ�гɹ�����true, ���򷵻�false
 */
bool CDBForm::BindingParameter()
{
    MessageBox(NULL, TEXT("���ݿ������¼���󶨲���������"),
               TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
	return true;
}

/*
 * ˵��: 
 *       �󶨼�¼������,���ڻ�ȡ�洢���̷���ֵ,�ú�������������ɾ������
 * ������
 *       is_add       [in]  ��־�Ƿ������Ա�����ܵĲ����󶨺�������Ϊtrue,����Ϊfalse
 *       error_info   [out] ��ȡ������Ϣ
 * ����ֵ: 
 *       ִ�гɹ�����true, ���򷵻�false
 */
bool CDBForm::BindingParameter(bool is_out, std::string error)
{
    MessageBox(NULL, TEXT("���ݿ������¼���󶨲������������ڻ�ȡ����ֵ"),
		TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
	return true;
}




/*
 * ˵��: ִ�����ݿ�ṹ����ѯ���
 * ����:
 *       sql_statement [in]  �ṹ����ѯ���
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 *
 */
bool CDBForm::ExecuteSQL(const char *sql_statement, std::string &error_info )
{
	/*���������*/
    if (false == AllocHandleStmt())
	{
		return false;
	}
    /* ִ����� */
    m_return_code_ = SQLExecDirect(m_hstmt_, 
                                   (unsigned char *)sql_statement,
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) && 
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		error_info = "ִ�����ݿ�������ʧ��: ";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
		return false;
    }
    return true;
}

/*
 * ˵��: ���������Ϣ
 **/
bool CDBForm::ReportError(SQLHSTMT &hdbc, int handle_type, std::string &error_info)
{
	char message[500] = "\0";
	short message_length(0);
	SQLINTEGER native_error = 0;
    SQLSMALLINT record_number = 1;
     unsigned char *sql_state = new unsigned char[6];
    if (NULL == sql_state)
    {
		error_info = TEXT("�����������ԭ���ǣ�����sqlstate�ڴ�ʧ��");
		return false;
    }
/*	sql_state = 0;*/
	
	/*��ȡ����*/
    SQLGetDiagRec(handle_type, hdbc, record_number, sql_state, &native_error,
                  (unsigned char *)message, 500, &message_length);
	switch(native_error)
	{
	case 2627:
		{
			LTHROW(INPUT_EXIST_ERROR)
			error_info +=  TEXT("���������ظ��ı��");
	    	break;
		}
		/*TODO: Add other error information*/
	default:
		{
			error_info += message;
			break;
		}
	}
//     /*just for test*/
	char tmp[200]="\0";
	sprintf(tmp, "%s, %ld", sql_state, native_error);
	MessageBox(NULL, tmp, "sql_state, native_error", MB_OK);
	MessageBox(NULL, error_info.c_str(), "error", 0);

// 	/////
    delete [] sql_state;
    sql_state = NULL;
    return true;
}

/*
 * ˵��: ���������Ϣ(�׳��쳣��ʽ)
 **/
bool CDBForm::ReportError(SQLHSTMT &hdbc, int handle_type)
{
	char message[500] = "\0";
	short message_length(0);
	SQLINTEGER native_error = 0;
	SQLSMALLINT record_number = 1;
	unsigned char *sql_state = new unsigned char[6];
	if (NULL == sql_state)
	{
		return false;
	}
	/*	sql_state = 0;*/

	/*��ȡ����*/
	SQLGetDiagRec(handle_type, hdbc, record_number, sql_state, &native_error,
		(unsigned char *)message, 500, &message_length);
	switch(native_error)
	{
	case 2627:
		{
			LTHROW(INPUT_EXIST_ERROR)
			break;
		}
		/*TODO: Add other error information*/
	default:
		{
			LTHROW(EXEC_SQL_PROC_ERROR)
			break;
		}
	}
	delete [] sql_state;
	sql_state = NULL;
	return true;
}

/*
 * ˵��: ����sql���
 * ����:
 *       statement [in] ��ִ�е�sql���
 **/
void CDBForm::SetSQLStatement(const std::string statement)
{
	m_query_sql_ = statement;
}



bool CDBForm::Connect(const char *dsn, const char *id, 
					  const char *password, std::string &information)
{
	/* ���价����� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &m_henv_);
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(ALLOCATE_HANDLE_ERROR)

    /* ����ODBC�汾�Ļ������� */
    m_return_code_ = SQLSetEnvAttr(m_henv_, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(SET_ODBC_VERSION_ERROR)
    /* �������Ӿ�� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_DBC, m_henv_, &m_hdbc_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(ALLOCATE_CONNECT_HANDLE_ERROR)
    /* �������ݿ������ύ��ʽ��Ĭ��Ϊ�Զ��ύ��ʽ*/
	m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)m_auto_commit_, SQL_IS_POINTER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�������ݿ��ֶ��ύʧ�ܣ�";
        return false;
    }

	/*�����������ԣ���¼��ʱ��5s)*/
    m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_LOGIN_TIMEOUT, (void *)5, 0);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�������ݿⲢ����ʧ�ܣ�";
        return false;
    }
    /* ��������Դ */
    m_return_code_ = SQLConnect(m_hdbc_, (SQLCHAR *)dsn, 
                                SQL_NTS,(SQLCHAR *)id, SQL_NTS,
                                (SQLCHAR *)password, SQL_NTS);
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(CONNECT_ERROR)
    
	/*���������*/
    if (false == AllocHandleStmt())
	{
		return false;
	}
	m_is_connect_ = true;
    return m_is_connect_;
}



/*
 * ����: �Ͽ�������Դ�����ӣ��ͷ���Դ
 **/
void CDBForm::Disconnect()
{
    /*
     * HIT: There has something that we are not 
     *      clear. When you disconnect database,
     *      if has something wrong, you can check
     *      here.
     **/
	if (NULL != m_hstmt_)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
		m_hstmt_ = NULL;
	}
    if (NULL != m_hdbc_)
    {
        SQLDisconnect(m_hdbc_);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc_);
		m_hdbc_ = NULL;
		m_is_connect_ = false;
    }
    if (NULL != m_henv_)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, m_henv_);
		m_henv_ = NULL;
    }
}

/*
 *  ˵��:
 *      �ر��α꣬������ͬһ�������϶��ִ����䡣
 *      ִ����һ��������Ҫ�ر��α꣬������ܻ���֡���Ч���α�״̬��        
 *  ������
 *      ��
 *  ����ֵ:
 *      �ɹ�����true,ʧ�ܷ���false;
**/
bool CDBForm::CloseCursor()
{
	m_return_code_ = SQLCloseCursor(m_hstmt_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(CLOSE_CURSOR_ERROR)
		return true;
}



/*
 *  @˵��: ��ȡ�����������еĲ���
 *  @������datepart [in] ָ�����������е���һ����
 *          year,month,day,hour,minute,second
 *  @����ֵ: ���ɹ����ڵĲ��֣����򷵻�-1
**/
int CDBForm::GetDatePart(char *sql_selectdate)
{
	std::string error;
	/*���������*/
    if (false == AllocHandleStmt())
	{
		return -1;
	}
	if (false==this->ExecuteSQL(sql_selectdate, error))
	{
		MessageBox(NULL,error.c_str(), TEXT("����"), MB_OK|MB_ICONINFORMATION);
		return -1;
	}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_LONG, &m_datepart_, sizeof(m_datepart_), &m_sql_datetime_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		error = "�󶨲�������";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("�󶨴���"), MB_OK);
		return -1;
	}
	FetchData();
	return m_datepart_;
}

char *CDBForm::GetDatePartString(const char *datepart) {
	std::string error;
	/*���������*/
    if (false == AllocHandleStmt())
	{
		return NULL;
	}
	if (false==this->ExecuteSQL(datepart, error))
	{
		MessageBox(NULL,error.c_str(), TEXT("����"), MB_OK|MB_ICONINFORMATION);
		return NULL;
	}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, &m_server_datatime, 
		                        sizeof(m_server_datatime), &m_server_datetime_len_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		error = "�󶨲�������";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("�󶨴���"), MB_OK);
		return NULL;
	}
	FetchData();
	return m_server_datatime;
}

/*
 *  @˵��: ��ȡ�����������е����
 *  @����ֵ: ���
**/
int CDBForm::GetYear()
{
   return GetDatePart("select DATEPART(year,getdate())");
}

/*
 *  @˵��: ��ȡ�����������е��·�
 *  @����ֵ: �·�
**/
int CDBForm::GetMonth()
{
	return GetDatePart("select DATEPART(month,getdate())");
}

/*
 *  @˵��: ��ȡ�����������е�������
 *  @����ֵ: ������
**/
int CDBForm::GetDay()
{
	return GetDatePart("select DATEPART(day,getdate())");
}

/*
 *  @˵��: ��ȡ�����������е�Сʱ
 *  @����ֵ: Сʱ
**/
int CDBForm::GetHour()
{
	return GetDatePart("select DATEPART(hour,getdate())");
}

/*
 *  @˵��: ��ȡ�����������еķ���
 *  @����ֵ: ����
**/
int CDBForm::GetMinute()
{
	return GetDatePart("select DATEPART(minute,getdate())");
}
/*
 *  @˵��: ��ȡ�����������е���
 *  @����ֵ: ��
**/
int CDBForm::GetSecond()
{
	return GetDatePart("select DATEPART(second,getdate())");
}

/*
 * @ brief: ��ȡ������ʱ��-��
 * @ return: ��
 * */
std::string CDBForm::GetYearString() {
	std::string server_year(GetDatePartString("select datename(year, getdate())"));
	return server_year;
}

/*
 * @ brief: ��ȡ������ʱ��-��
 * @ return: ��
 * */
std::string CDBForm::GetMonthString() {
	std::string server_month(GetDatePartString("select datename(month, getdate())"));
	if (1 == server_month.length()) {
		server_month = "0" + server_month;
	}
	return server_month;
}

/*
 * @ brief: ��ȡ������ʱ��-��
 * @ return: ��
 * */
std::string CDBForm::GetDayString() {
	std::string server_day(GetDatePartString("select datename(day, getdate())"));
	if (1 == server_day.length()) {
		server_day = "0" + server_day;
	}
	return server_day;
}

/*
 * @ brief: ��ȡ������ʱ��-ʱ
 * @ return: ʱ
 * */
std::string CDBForm::GetHourString() {
	std::string server_hour(GetDatePartString("select datename(hour, getdate())"));
	if (1 == server_hour.length()) {
		server_hour = "0" + server_hour;
	}
	return server_hour;
}

/*
 * @ brief: ��ȡ������ʱ��-��
 * @ return: ��
 * */
std::string CDBForm::GetMinuteString() {
	std::string server_minute(GetDatePartString("select datename(minute, getdate())"));
	if (1 == server_minute.length()) {
		server_minute = "0" + server_minute;
	}
	return server_minute;
}

/*
 * @ brief: ��ȡ������ʱ��-��
 * @ return: ��
 * */
std::string CDBForm::GetSecondString() {
	std::string server_second(GetDatePartString("select datename(second, getdate())"));
	if (1 == server_second.length()) {
		server_second = "0" + server_second;
	}
	return server_second;
}

/*
 * @ brief: ɾ���ַ���ĩβ�ո�
 * @ param: src [in] Դ�ַ���
 * @ param: des [out] ���ص�Ŀ���ַ���
 */
void CDBForm::DeleteSpace(const char * src, char * des)
{
	int i = 0;
	int len = strlen(src);
	char* buffer = new char[len];
	strncpy(buffer, src, len);
	memset(des, 0, len);
	char *temp = (buffer + len - 1);
	while (*temp-- == ' ') {
		i++;
	}
	strncpy(des, buffer, len - i);
	delete [] buffer;
}


 /*
  * ˵����
  *       ���������ύ��ʽ��Ĭ��Ϊ�Զ��ύ
  * ������
  *       is_auto_commit   [in]  tureΪ�Զ��ύ��falseΪ�ֶ��ύ
  * ����ֵ��
  *       �ɹ�����true, ���򷵻�false
  */
bool CDBForm::SetAutoCommit(bool is_auto_commit)
{
	if (true == is_auto_commit)
	{
		m_auto_commit_ = SQL_AUTOCOMMIT_ON;
	}
	else
	{
		m_auto_commit_ = SQL_AUTOCOMMIT_OFF;
	}
	/* �������ݿ������ύ��ʽ��Ĭ��Ϊ�Զ��ύ��ʽ*/
	m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)m_auto_commit_, SQL_IS_POINTER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string error;
		ReportError(m_hdbc_, SQL_HANDLE_DBC, error);
        return false;
    }
	return true;
}


 /*
  * ˵����
  *       �����ύ�������ڳ����п���SQL����ִ�У�ʹ��ǰ��Ҫ����������ύ��ʽΪ�ֶ��ύ
  * ����ֵ��
  *       �ɹ�����true, ���򷵻�false
  */
bool CDBForm::Commit()
{
	
	m_return_code_ = SQLEndTran(SQL_HANDLE_DBC, m_hdbc_, SQL_COMMIT);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string error;
		ReportError(m_hdbc_, SQL_HANDLE_DBC, error);
        return false;
    }
	return true;
}

 /*
  * ˵����
  *       ����ع��������ڳ����лع�ִ�е�SQL��䣬ʹ��ǰ��Ҫ����������ύ��ʽΪ�ֶ��ύ
  * ����ֵ��
  *       �ɹ�����true, ���򷵻�false
  */
bool CDBForm::RollBack()
{
	m_return_code_ = SQLEndTran(SQL_HANDLE_DBC, m_hdbc_, SQL_ROLLBACK);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string error;
		ReportError(m_hdbc_, SQL_HANDLE_DBC, error);
        return false;
    }
	return true;
}


 /*
  * ˵����
  *      ִ����Ҫ���ز����Ĵ洢����
  * ������
  *      sql_proc [in] ִ�еĴ洢������䣬 ���磺��{? = call �洢������(?,?.........)}��
  *      error    [out] ��¼������Ϣ
  * ����ֵ��
  *       �ɹ�����true, ���򷵻�false
  */
 bool CDBForm::ExecSQLProc(const char * sql_proc, std::string &error)
 {
	// ִ�д洢����
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)sql_proc, SQL_NTS);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);   // TODO: �����ã���ɺ�
	    LTHROW(EXEC_SQL_PROC_ERROR)
	}
 	return true;
 }

 bool CDBForm::ExecSQLProc(const char * sql_proc)
 {
	 // ִ�д洢����
	 std::string error;
	 m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)sql_proc, SQL_NTS); 
	
	
	 if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
     {
		 ReportError(m_hstmt_,SQL_HANDLE_STMT,error);
		 LTHROW(EXEC_SQL_PROC_ERROR)
			 return false;
	 }
		
		 return true;
 }

 /*
  * ˵����
  *      �жϴ洢����ִ���Ƿ�ɹ�
         ���Ǵ洢���̵ķ���ֵ���������ݼ�¼��һ�𷵻أ�
  *      ����ȡ���ݼ�¼��������ݣ��ٵ��ô˺����жϴ洢���̵�ִ���Ƿ�ɹ�
  * ������
  *      error    [out] ��¼������Ϣ
  * ����ֵ��
  *       �ɹ�����true, ���򷵻�false
  */
bool CDBForm::IsSQLProcRetRight(std::string &error)
{
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (0 == m_pro_ret)
	{
		return true;
	}
	else if (2627 == m_pro_ret )
	{
		error="�ֶ��ظ��������Ϊ��ͬ��ֵ��";
		return false;
	}
	else
	{
		char ret[10];
		sprintf(ret, "%d",m_pro_ret);
		error="δ������󣺴洢���̷���ֵ->";
		error+=ret;
		return false;
	}
	return true;
}

 /*
  * ˵��������Ϊ�׳��쳣��
  *      �жϴ洢����ִ���Ƿ�ɹ�
         ���Ǵ洢���̵ķ���ֵ���������ݼ�¼��һ�𷵻أ�
  *      ����ȡ���ݼ�¼��������ݣ��ٵ��ô˺����жϴ洢���̵�ִ���Ƿ�ɹ�
  * ������
  *      error    [out] ��¼������Ϣ
  * ����ֵ��
  *       �ɹ�����true, ���򷵻�false
  */
bool CDBForm::IsSQLProcRetRight()
{
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (0 == m_pro_ret)
	{
		return true;
	}
	else if (2627 == m_pro_ret )
	{
		LTHROW(INPUT_EXIST_ERROR)
	}
	else
	{
		LTHROW(EXEC_SQL_PROC_ERROR)
	}
	return true;
}

/*
 * @ brief: �󶨷���ֵ
 * @ return: ���ɹ�����true�����򷵻�false
 *           ��ִ��ʧ��ʱ��������ͨ��ReportError������ȡ������Ϣ
 **/
bool CDBForm::BindReturn() {
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SHORT,\
		                              SQL_INTEGER, 0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RETURN_ERROR)
	return true;
}

bool CDBForm::FetchData() {
	m_return_code_ = SQLFetch(m_hstmt_);
	if (m_return_code_ == SQL_NO_DATA) {
		return true;
	}else if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(FETCH_ROWSET_ERROR)
	return false;
}

bool CDBForm::FreeStatemetHandle() {
	if (NULL != m_hstmt_) {
		SQLRETURN sql_ret = SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
		if (SQL_SUCCESS != sql_ret && SQL_SUCCESS_WITH_INFO != sql_ret)
			LTHROW(FREE_STATEMENT_HANDLE_ERROR)
		m_hstmt_ = NULL;
	}
	return true;
}

/*
 * @ brief: ���ݿⱸ��
 * @ param: file_path [in] �����ļ����ƣ���sql��������,
 *          �̶ֹ�����ʱ��Ϊ�����ļ�����������SQL��������װĿ¼��BACKUPĿ¼��
 * @ return: �ɹ�����true
 **/
bool CDBForm::BackUp(const char *file_path) {
	std::string file_name;
	file_name += GetYearString();
	file_name += GetMonthString();
	file_name += GetDayString();
	file_name += GetHourString();
	file_name += GetMinuteString();
	file_name += GetSecondString();
	char backup_statement[1024];
	memset(backup_statement, 0, sizeof(backup_statement));
	sprintf(backup_statement, "backup database repaset to disk = '%s'", file_name.c_str()/*file_path*/);
	std::string err_info;
	if (!ExecuteSQL(backup_statement, err_info))
		LTHROW(BACKUP_DATABASE_ERROR)
	return true;
}

/*
 * @ brief: ���ݿ�ָ�
 * @ param: file_path [in] �ļ�����
 * @ return: ���ɹ�����true
 **/
bool CDBForm::Restore(const char *file_path) {
	char restore_statement[1024];
	memset(restore_statement, 0, sizeof(restore_statement));
	sprintf(restore_statement, "restore database repaset from disk = '%s'", file_path);
	std::string err_info;
	if (!ExecuteSQL(restore_statement, err_info))
		LTHROW(RESTORE_DATABASE_ERROR)
	return true;
}



#define MAXBUFLEN 256


/*
 * ˵����
 *     ��ȡ����ϸ�Ĵ�����Ϣ
 * ������
 *     plm_handle_type [in] �������
 *     plm_handle      [in] ���
 *     logstring       [out] �����ڴ洢������Ϣ����ʱû��ʹ��
 *     ConnInd         [in] ��־���Ƿ��ȡ���������Ϣ
 * ����ֵ��
 *     ��
 */
void CDBForm::ProcessLogMessages(SQLSMALLINT plm_handle_type,
	SQLHANDLE plm_handle,
	char *logstring, int ConnInd)
{
	RETCODE      plm_retcode = SQL_SUCCESS;
	UCHAR      plm_szSqlState[MAXBUFLEN] = "",
		plm_szErrorMsg[MAXBUFLEN] = "";
	SDWORD      plm_pfNativeError = 0L;
	SWORD      plm_pcbErrorMsg = 0;
	SQLSMALLINT   plm_cRecNmbr = 1;
	SDWORD      plm_SS_MsgState = 0, plm_SS_Severity = 0;
	SQLINTEGER   plm_Rownumber = 0;
	USHORT      plm_SS_Line;
	SQLSMALLINT   plm_cbSS_Procname, plm_cbSS_Srvname;
	SQLCHAR      plm_SS_Procname[MAXNAME], plm_SS_Srvname[MAXNAME];


	while (plm_retcode != SQL_NO_DATA_FOUND) {
		plm_retcode = SQLGetDiagRec(plm_handle_type, plm_handle,
			plm_cRecNmbr, plm_szSqlState, &plm_pfNativeError,
			plm_szErrorMsg, MAXBUFLEN - 1, &plm_pcbErrorMsg);

		// Note that if the application has not yet made a
		// successful connection, the SQLGetDiagField
		// information has not yet been cached by ODBC
		// Driver Manager and these calls to SQLGetDiagField
		// will fail.
		if (plm_retcode != SQL_NO_DATA_FOUND) {
			if (ConnInd) {
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_ROW_NUMBER, &plm_Rownumber,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_LINE, &plm_SS_Line,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_MSGSTATE, &plm_SS_MsgState,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_SEVERITY, &plm_SS_Severity,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_PROCNAME, &plm_SS_Procname,
					sizeof(plm_SS_Procname),
					&plm_cbSS_Procname);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_SRVNAME, &plm_SS_Srvname,
					sizeof(plm_SS_Srvname),
					&plm_cbSS_Srvname);
			}
			//just for test
			char m1[1024];
			sprintf(m1,"szSqlState = %s\n,pfNativeError = %d\n,szErrorMsg = %s\n,pcbErrorMsg = %d\n",\
				plm_szSqlState,plm_pfNativeError,plm_szErrorMsg,plm_pcbErrorMsg);
			MessageBox(NULL,m1,TEXT("m1"),0);
			if (ConnInd) {
				char m2[1024];
				sprintf(m2,"ODBCRowNumber = %d\n,SSrvrLine = %d\n,SSrvrMsgState = %d\n,\
						   SSrvrSeverity = %d\n,SSrvrProcname = %s\n,SSrvrSrvname = %s\n",\
						   plm_Rownumber, plm_Rownumber,plm_SS_MsgState,\
						   plm_SS_Severity,plm_SS_Procname,plm_SS_Srvname);
				MessageBox(NULL,m2,TEXT("m1"),0);
			}
		}
		plm_cRecNmbr++; //Increment to next diagnostic record.
	} // End while.
}
