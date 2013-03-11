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
	: m_hdbc_(SQL_NULL_HDBC),
	  m_hstmt_(SQL_NULL_HSTMT),
	  m_return_code_(NULL)
{
	std::string error;
	assert(true == this->Connect("repast", "repast", "repast", error));
}

CDBForm::CDBForm(std::string dns, std::string name, std::string password)
	: m_hdbc_(SQL_NULL_HDBC),
      m_hstmt_(SQL_NULL_HSTMT),
	  m_return_code_(NULL)
{
	std::string error;
	assert(true == this->Connect(dns.c_str(), name.c_str(), password.c_str(), error));
}

CDBForm::~CDBForm()
{
}

/*
 * ˵�������������
 * ����ֵ������ɹ�����true,���򷵻�false
 **/
bool CDBForm::SQLAllocHandleStmt(std::string &error_info)
{
	std::string error;
	if (NULL != m_hstmt_)
	{
		SQLFreeStmt(m_hstmt_, SQL_UNBIND);/*�ͷŰ�*/
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
		m_hstmt_ = NULL;
	}
	/* ��������� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�������ݿ������ʧ�ܣ�";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }

	/* �����α����ԣ����а汾�����ֹ۲������ö�̬�α����� */
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CURSOR_TYPE,
		(SQLPOINTER)SQL_CURSOR_DYNAMIC, 
		SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�������ݿ�����α�ʧ�ܣ�";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
	}
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CONCURRENCY,
		(SQLPOINTER)SQL_CONCUR_ROWVER, 
		SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "�������ݿ�����α�ʧ�ܣ�";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	return true;
}

/*
 * ˵��: �ж��Ƿ��˼�¼���Ľ�β
 * ����ֵ: ���˽�β����true�����򷵻�false
 */
bool CDBForm::IsEOF()
{
    if (SQL_NO_DATA == m_return_code_)
    {
        return true;
    }
    return false;
}

/*
 * ˵��: �ƶ�����¼���ĵ�һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MoveFirst()
{
	std::string error;
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_FIRST, 0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "��ȡ��һ����¼����";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("����"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * ˵��: �ƶ�����¼������һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MoveNext()
{
	std::string error;
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_NEXT,0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "��ȡ��һ����¼����";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("����"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * ˵��: �ƶ�����¼������һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MovePrior()
{
	std::string error;
    m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_PRIOR, 0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "��ȡ��һ����¼����";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("����"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * ˵��: �ƶ�����¼�������һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MoveLast()
{
	std::string error;
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_LAST,0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "��ȡ���һ����¼����";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
    	MessageBox(NULL, error.c_str(), TEXT("����"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * ˵��: �ƶ�����¼�������һ������
 * ����ֵ: ִ�гɹ�����true�����򷵻�false
 */
bool CDBForm::GetRecordSet()
{
	std::string error_info;
	/*���������*/
    if (false == SQLAllocHandleStmt(error_info))
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
 * ˵��: ִ�����ݿ�ṹ����ѯ���
 * ����:
 *       sql_statement [in]  �ṹ����ѯ���
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 *
 */
bool CDBForm::ExecuteSQL(const char *sql_statement, std::string &error_info )
{
	/*���������*/
    if (false == SQLAllocHandleStmt(error_info))
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
	sql_state = 0;
	
	/*��ȡ����*/
    SQLGetDiagRec(handle_type, hdbc, record_number, sql_state, &native_error,
                  (unsigned char *)message, 500, &message_length);
	switch(native_error)
	{
	case 2627:
		{
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
// 	/////
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
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "���价�����ʧ��!";
        return false;
    }
    /* ����ODBC�汾�Ļ������� */
    m_return_code_ = SQLSetEnvAttr(m_henv_, SQL_ATTR_ODBC_VERSION,
        (void *)SQL_OV_ODBC3, 0);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "����ODBC�汾�Ļ�������ʧ��!";
        return false;
    }
    /* �������Ӿ�� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_DBC, m_henv_, &m_hdbc_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		information = "�������Ӿ��ʧ��!";
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
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "��������Դʧ��!";
		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
        return false;
    }
	/*���������*/
    if (false == SQLAllocHandleStmt(information))
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
 *  @˵��: ��ȡ�����������еĲ���
 *  @������datepart [in] ָ�����������е���һ����
 *          year,month,day,hour,minute,second
 *  @����ֵ: ���ɹ����ڵĲ��֣����򷵻�-1
**/
int CDBForm::GetDatePart(char *sql_selectdate)
{
	std::string error;
	/*���������*/
    if (false == SQLAllocHandleStmt(error))
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
	this->MoveFirst();
	return m_datepart_;
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
